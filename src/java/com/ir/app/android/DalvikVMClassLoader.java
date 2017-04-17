
package com.ir.app.android;

import java.io.File;
import java.io.IOException;
import java.io.Serializable;
import java.net.URL;
import java.util.ArrayList;
import java.util.zip.ZipFile;
import java.net.MalformedURLException;

import android.util.Log;

import dalvik.system.DexFile;


final public class DalvikVMClassLoader extends ClassLoader implements Serializable {

    private static final boolean VERBOSE_DEBUG = false;

    /* constructor args, held for init */
    private final String mRawDexPath;
    private final String mRawLibPath;
    private final String mDexOutputPath;

    private boolean mInitialized;

    /*
     * Parallel arrays for jar/apk files.
     *
     * (could stuff these into an object and have a single array;
     * improves clarity but adds overhead)
     */
    private File[] mFiles;              // source file Files, for rsrc URLs
    private ZipFile[] mZips;            // source zip files, with resources
    static private DexFile[] mDexs;            // opened, prepped DEX files

    /*
     * Native library path.
     */
    private String[] mLibPaths;

    private ClassLoader loaderToUse = null;

    public DalvikVMClassLoader(String myStorage, String bufferedDirectory, String libPath, ClassLoader sLoader, ArrayList knownClasses) throws Exception{
    	
        super(sLoader);
        if (myStorage == null || bufferedDirectory == null)
            throw new NullPointerException();
        mRawDexPath = myStorage;
        mDexOutputPath = bufferedDirectory;
        mRawLibPath = libPath;       
        loaderToUse = this;       
        try {
        	ensureInit();
        	initDexFile();
        } catch (Exception e){
        	
        }
    }

    private void initDexFile() throws Exception{		
		
		DexFileOperator dexFile = new DexFileOperator(mRawDexPath, mDexOutputPath, loaderToUse);
		dexFile.touchClasses();
	}		
    /**
     * Complete initialization on first use of the class loader.
     */
    private synchronized void ensureInit() {
        if (mInitialized) {
            return;
        }
        String[] dexPathList;

        mInitialized = true;

        dexPathList = mRawDexPath.split(":");
        int length = dexPathList.length;

        //System.out.println("DexClassLoader: " + dexPathList);
        mFiles = new File[length];
        mZips = new ZipFile[length];
        mDexs = new DexFile[length];

        /* open all Zip and DEX files up front */
        for (int i = 0; i < length; i++) {
            //System.out.println("My path is: " + dexPathList[i]);
            File pathFile = new File(dexPathList[i]);
            mFiles[i] = pathFile;

            if (pathFile.isFile()) {
                try {
                    mZips[i] = new ZipFile(pathFile);
                } catch (IOException ioex) {
                    // expecting IOException and ZipException
                    System.out.println("Failed opening '" + pathFile
                        + "': " + ioex);
                    //ioex.printStackTrace();
                }
                /* we need both DEX and Zip, because dex has no resources */
                try {
                    String outputName =
                        generateOutputName(dexPathList[i], mDexOutputPath);
                    mDexs[i] = DexFile.loadDex(dexPathList[i], outputName, 0);
                } catch (IOException ioex) {
                    // might be a resource-only zip
                    System.out.println("Failed loadDex '" + pathFile
                        + "': " + ioex);
                }
            } else {
                if (VERBOSE_DEBUG)
                    System.out.println("Not found: " + pathFile.getPath());
            }
        }

        /*
         * Prep for native library loading.
         */
        String pathList = System.getProperty("java.library.path", ".");
        String pathSep = System.getProperty("path.separator", ":");
        String fileSep = System.getProperty("file.separator", "/");

        if (mRawLibPath != null) {
            if (pathList.length() > 0) {
                pathList += pathSep + mRawLibPath;
            }
            else {
                pathList = mRawLibPath;
            }
        }

        mLibPaths = pathList.split(pathSep);
        length = mLibPaths.length;

        // Add a '/' to the end so we don't have to do the property lookup
        // and concatenation later.
        for (int i = 0; i < length; i++) {
            if (!mLibPaths[i].endsWith(fileSep))
                mLibPaths[i] += fileSep;
            if (VERBOSE_DEBUG)
                System.out.println("Native lib path " +i+ ":  " + mLibPaths[i]);
        }
    }

    /**
     * Convert a source path name and an output directory to an output
     * file name.
     */
    private static String generateOutputName(String sourcePathName,
        String outputDir) {

        StringBuilder newStr = new StringBuilder(80);

        /* start with the output directory */
        newStr.append(outputDir);
        if (!outputDir.endsWith("/"))
            newStr.append("/");

        /* get the filename component of the path */
        String sourceFileName;
        int lastSlash = sourcePathName.lastIndexOf("/");
        if (lastSlash < 0)
            sourceFileName = sourcePathName;
        else
            sourceFileName = sourcePathName.substring(lastSlash+1);

        /*
         * Replace ".jar", ".zip", whatever with ".dex".  We don't want to
         * use ".odex", because the build system uses that for files that
         * are paired with resource-only jar files.  If the VM can assume
         * that there's no classes.dex in the matching jar, it doesn't need
         * to open the jar to check for updated dependencies, providing a
         * slight performance boost at startup.  The use of ".dex" here
         * matches the use on files in /data/dalvik-cache.
         */
        int lastDot = sourceFileName.lastIndexOf(".");
        if (lastDot < 0)
            newStr.append(sourceFileName);
        else
            newStr.append(sourceFileName, 0, lastDot);
        newStr.append(".dex");

        if (VERBOSE_DEBUG)
            System.out.println("Output file will be " + newStr.toString());
        return newStr.toString();
    }

 
    @Override
    protected Class<?> findClass(String name) throws ClassNotFoundException {
        ensureInit();

        if (VERBOSE_DEBUG)
            System.out.println("DexClassLoader " + this
                + ": findClass '" + name + "'");

        byte[] data = null;
        int length = mFiles.length;
        try{
        	for (int i = 0; i < length; i++) {
        		if (VERBOSE_DEBUG)
        			System.out.println("  Now searching: " + mFiles[i].getPath());
        		if (mDexs[i] != null) {
        			String slashName = name.replace('.', '/');
        			Class clazz = mDexs[i].loadClass(slashName,loaderToUse);
        			if (clazz != null) {
        				if (VERBOSE_DEBUG)
        					System.out.println("    found");
        				return clazz;
        			}
        		}
        	}
        } catch (Exception e){        	
        	Log.w("DVM Loader", "Class: "+name+" can't be resolved");
        }       
        throw new ClassNotFoundException("DVM Loader, Class: "+name+" can't be resolved");        
    }

    @Override
    protected URL findResource(String name) {
        ensureInit();

        int length = mFiles.length;

        for (int i = 0; i < length; i++) {
            File pathFile = mFiles[i];
            ZipFile zip = mZips[i];

            if (zip.getEntry(name) != null) {
                if (VERBOSE_DEBUG)
                    System.out.println("  found " + name + " in " + pathFile);
                try {
                    // File.toURL() is compliant with RFC 1738 in always
                    // creating absolute path names. If we construct the
                    // URL by concatenating strings, we might end up with
                    // illegal URLs for relative names.
                    return new URL("jar:" + pathFile.toURL() + "!/" + name);
                } catch (MalformedURLException e) {
                    throw new RuntimeException(e);
                }
            }
        }

        if (VERBOSE_DEBUG)
            System.out.println("  resource " + name + " not found");

        return null;
    }


    @Override
    protected String findLibrary(String libname) {
        ensureInit();

        String fileName = System.mapLibraryName(libname);
        for (int i = 0; i < mLibPaths.length; i++) {
            String pathName = mLibPaths[i] + fileName;
            File test = new File(pathName);

            if (test.exists()) {
                if (VERBOSE_DEBUG)
                    System.out.println("  found " + libname);
                return pathName;
            }
        }

        if (VERBOSE_DEBUG)
            System.out.println("  library " + libname + " not found");
        return null;
    }

    @Override
    protected Package getPackage(String name) {
        if (name != null && !"".equals(name)) {
            synchronized(this) {
                Package pack = super.getPackage(name);

                if (pack == null) {
                    pack = definePackage(name, "Unknown", "0.0", "Unknown",
                            "Unknown", "0.0", "Unknown", null);
                }

                return pack;
            }
        }

        return null;
    }
    static public DexFile[] getDexFile(){
    	return mDexs;
    }
}

