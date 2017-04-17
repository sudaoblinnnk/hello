package com.ir.app.android;

import com.ir.app.Application;
import com.ir.app.ApplicationManager;
import com.ir.app.IVApplication;
import com.ir.app.NativeAppManager;
import com.ir.app.android.StubInterface;

import android.content.Context;
import android.util.Log;

import java.util.Hashtable;
import java.util.ArrayList;

/**
 * 
 * An Android specific application class. The class is invoked by ApplicationManager if DVM is chosen.
 * 
 * @author jrong
 *
 */
final public class ApplicationDalvikVM implements Application {
	
	static private String archives = null;
	static private String nativeLibPath = null;	
	static private String bufferedDir = null;
	static private Object loaderLocker = new Object();
	static private DalvikVMClassLoader classLoader = null;
	
	final static String MYTAG = "ApplicationDalvikVM";
	
	private Context myAppContext = null;
	private DVMIVApplication appIV = null;	
			
	/**
	 * This constructor has to be called once per process. 
	 * 
	 * @param appContext
	 * @param params
	 * @throws Exception
	 */
	public ApplicationDalvikVM(Object appContext, Object params) throws Exception {
		myAppContext = (Context) appContext;		
		init();
	}	 
	private void init() throws Exception{		
		appIV = new DVMIVApplication(myAppContext);									
		bufferedDir = StubInterface.getAssetDir();
	}
	
	static protected void setupLoaderEnv(String javaArchives, String nativePath) throws Exception{		
		synchronized(loaderLocker){
			archives = javaArchives;
			nativeLibPath = nativePath;
			if(bufferedDir == null ){
				bufferedDir = StubInterface.getAssetDir();
			}		
			if(archives != null && archives.length() > 0){
				classLoader = new DalvikVMClassLoader(archives,bufferedDir,nativeLibPath,ApplicationDalvikVM.class.getClassLoader(), null);
			}else{
				Log.d(MYTAG, "Empty archives for class loader, ignore...");
			}
		}			
	}

	private String getJavaArchivePath(ArrayList archives){
		StringBuffer buf = new StringBuffer();		
		String separator = "";
		for(int pos= 0; pos < archives.size(); pos++){
			buf.append(separator+(String)archives.get(pos));
			separator = ":";
		}
		return buf.toString();
	}
	private String getNativeLibPath(ArrayList nativeLibPath){
		StringBuffer buf = new StringBuffer();
		if(nativeLibPath == null) return buf.toString();
		String separator = "";
		for(int pos= 0; pos < nativeLibPath.size(); pos++){
			buf.append(separator+(String)nativeLibPath.get(pos));
			separator = ":";
		}
		return buf.toString();
	}
		
	public boolean execute(Object input, Object result) throws Exception{
		return true;
	}
	public void finish(Object obj){
		
	}
	public IVApplication getIVApplication(){
		return appIV;
	}
	public ClassLoader getJACClassLoader(){
		return classLoader;
	}
	static public  DalvikVMClassLoader getDVMLoader(){
		return classLoader;
	}
}	
