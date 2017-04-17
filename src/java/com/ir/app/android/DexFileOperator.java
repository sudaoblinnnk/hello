package com.ir.app.android;

import java.io.File;
import java.io.IOException;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.zip.ZipFile;

import android.util.Log;
import dalvik.system.DexClassLoader;
import dalvik.system.DexFile;

final public class DexFileOperator implements Serializable {

	final String MYTAG = "DexFileOperator";	
	private DexFile[] mDexs;  
	private ClassLoader loader;
	private ArrayList outputDexNames = null;
	private String rawDexPath;    
    private String dexOutputPath;
	
	public DexFileOperator(String javaArchives, String dexOutputDir, ClassLoader loader) throws Exception{
		this.loader = loader;
		this.rawDexPath = javaArchives;
		this.dexOutputPath = dexOutputDir;
		initialize();
	}
	private void initialize() throws Exception{
		             
		String[] dexPathList = rawDexPath.split(":");
		int length = dexPathList.length;
		mDexs = new DexFile[length];
		outputDexNames = new ArrayList();
        for (int i = 0; i < length; i++) { 
        	try {
                String outputName = generateOutputName(dexPathList[i], dexOutputPath);
                mDexs[i] = DexFile.loadDex(dexPathList[i], outputName, 0);
                outputDexNames.add(outputName);
            } catch (IOException ioex) {                                        
                Log.w(MYTAG,"Failed loadDex '" + dexPathList[i]+" message: "+ioex.getMessage());
            }
        }
	}
	protected void touchClasses() throws Exception {	
		
		/*for (int pos = 0; pos < mDexs.length; pos++) {
			DexFile dexFile = mDexs[pos];
			Enumeration  entries = dexFile.entries();		
			String className = null;
			while(entries.hasMoreElements()) {				
				className = (String)entries.nextElement();	
				String slashName = className.replace('.', '/');
				try {
					dexFile.loadClass(slashName,loader);
				} catch (Exception e){
					Log.w("MYTAG", "Checking, problem classname: "+ className);
				}
			}
		//	Log.d(MYTAG, "touchlasses(), classname: "+ className);
		}*/		
		String filePath = StubInterface.getAssetDir();
		File file = new File (filePath);
		File listFile[] = file.listFiles();					
		for(int pos =0; pos < listFile.length; pos++){			
			String fileName = listFile[pos].getName();			
			if(fileName.lastIndexOf(".dex") != -1 || fileName.lastIndexOf(".apk") != -1	||
					(fileName.lastIndexOf("_.jar") != -1 && fileName.startsWith("app"))){				
				try{
					listFile[pos].delete();
				}catch (Exception e){					
				}
			}										
		}
	}
	
	private String generateOutputName(String sourcePathName, String outputDir) {

		StringBuilder newStr = new StringBuilder(512);	 
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
	    newStr.append("2.dex");	        
	    return newStr.toString();
	}
}
