package com.irdeto.secureaccess.android;

import java.io.Serializable;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;
import java.util.zip.ZipFile;

import android.util.Log;
import dalvik.system.*;

/**
 * This class is used to retrieve class information from Dalvik Dex file within the packages. 
 * @author test
 *
 */
public class DFileManager implements Serializable {

	private String MYTAG = "IrdetoDexfileManager";
	private  String mRawDexPath;
    private  String mRawLibPath;
    private  String mDexOutputPath;
    private boolean mInitialized;
   
    /*
     * Parallel arrays for jar/apk files.
     * (could stuff these into an object and have a single array;
     * improves clarity but adds overhead)
     */
    private File[] mFiles;              	
    private ZipFile[] mZips;            	
    private DexFile[] mDexs;            	
    private ArrayList classArray = null;	
    private static ClassLoader loader = null;
    /*
     * Native library path. reserved, not in use.
     */
    private String[] mLibPaths;
    
    public DFileManager(String dexPath, String dexOutputDir, String libPath) throws Exception{
    	if (dexPath == null || dexOutputDir == null)
            throw new NullPointerException();
        mRawDexPath = dexPath;
        mDexOutputPath = dexOutputDir;
        mRawLibPath = libPath;        
		initialize();
    }
    static public ClassLoader getDexClassLoader(){
    	return loader;
    }
    private void initialize2() throws Exception{
    	String[] dexPathList;
    	String pathList = System.getProperty("java.library.path", ".");
        String pathSep = System.getProperty("path.separator", ":");
        String fileSep = System.getProperty("file.separator", "/");
        
    	if (mInitialized) {
            return;
        }        
        mInitialized = true;
        dexPathList = mRawDexPath.split(":");
        int length = dexPathList.length;
        
        mFiles = new File[length];
        mZips = new ZipFile[length]; 
        mDexs = new DexFile[length];
        
        for (int i = 0; i < length; i++) {            
            File pathFile = new File(dexPathList[i]);
            
            if (pathFile.isFile()) {                
                try {                 
                	DexFile dexFile = new DexFile(dexPathList[i]);
                	generateListOfClassesByDexfile(dexFile);
                } catch (Exception ioex) {                                        
                    Log.w(MYTAG,"Failed loadDex '" + pathFile+" message: "+ioex.getMessage());
                }
            } else {                              
                Log.w(MYTAG,"Invalid file: " + pathFile.getPath());
                throw new Exception("File: "+pathFile.getPath()+" is invalid");
            }
        }    
    }
    
    private ArrayList generateListOfClassesByDexfile(DexFile dexFile) throws Exception {	
				
		Enumeration  entries = dexFile.entries();		
		String className = null;
		while(entries.hasMoreElements()) {				
			className = (String)entries.nextElement();					
			if(classArray == null){
				classArray = new ArrayList();
			}
			classArray.add(className);
			Log.d(MYTAG, "getListOfClasses(), classname: "+ className);																				
		}	
		return classArray;
	}
    public ArrayList getClassLists(){
    	return classArray;
    }
    private void initialize() throws Exception{
    	
    	String[] dexPathList;
    	String pathList = System.getProperty("java.library.path", ".");
        String pathSep = System.getProperty("path.separator", ":");
        String fileSep = System.getProperty("file.separator", "/");
        
    	if (mInitialized) {
            return;
        }        
        mInitialized = true;
        dexPathList = mRawDexPath.split(":");
        int length = dexPathList.length;
        
        loader =  new DexClassLoader(mRawDexPath,mDexOutputPath,mRawLibPath,ClassLoader.getSystemClassLoader());
        
        mFiles = new File[length];
        mZips = new ZipFile[length]; 
        mDexs = new DexFile[length];

        for (int i = 0; i < length; i++) {            
            File pathFile = new File(dexPathList[i]);
            mFiles[i] = pathFile;

            if (pathFile.isFile()) {
                try {
                    mZips[i] = new ZipFile(pathFile);
                } catch (IOException ioex) {             
                	Log.w(MYTAG,"failed opening '" + pathFile+ "': " + ioex.getMessage());                   
                }            
                try {
                    String outputName = generateOutputName(dexPathList[i], mDexOutputPath);
                    mDexs[i] = DexFile.loadDex(dexPathList[i], outputName, 0);
                } catch (IOException ioex) {                                        
                    Log.w(MYTAG,"Failed loadDex '" + pathFile+" message: "+ioex.getMessage());
                }
            } else {                              
                Log.w(MYTAG,"Invalid file: " + pathFile.getPath());
                throw new Exception("File: "+pathFile.getPath()+" is invalid");
            }
        }             
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
        for (int i = 0; i < length; i++) {
            if (!mLibPaths[i].endsWith(fileSep))
                mLibPaths[i] += fileSep;                      
        }
    }
    
	public DexFile [] getDexFile(String filePath){		
		return mDexs;
	}
	
	public ArrayList getListOfClasses() throws Exception {	
		
		for (int pos = 0; pos < mDexs.length; pos++) {
			DexFile dexFile = mDexs[pos];
			Enumeration  entries = dexFile.entries();		
			String className = null;
			while(entries.hasMoreElements()) {				
				className = (String)entries.nextElement();					
				if(classArray == null){
					classArray = new ArrayList();
				}
				classArray.add(className);
				Log.d(MYTAG, "getListOfClasses(), classname: "+ className);																		
			}
		}	
		return classArray;
	}
	
	private static String generateOutputName(String sourcePathName, String outputDir) {

		StringBuilder newStr = new StringBuilder(80);	 
	    newStr.append(outputDir);
	    if (!outputDir.endsWith("/"))
	        newStr.append("/");	 
	    String sourceFileName;
	    int lastSlash = sourcePathName.lastIndexOf("/");
	    if (lastSlash < 0)
	        sourceFileName = sourcePathName;
	    else
	        sourceFileName = sourcePathName.substring(lastSlash+1);
	        
	    int lastDot = sourceFileName.lastIndexOf(".");
	    if (lastDot < 0)
	        newStr.append(sourceFileName);
	    else
	        newStr.append(sourceFileName, 0, lastDot);
	    newStr.append(".dex");	        
	    return newStr.toString();
	}
}
