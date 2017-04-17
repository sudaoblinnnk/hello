package com.ir.app.android;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.Serializable;

import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.util.Log;

/**
 * An entry class to JAC runtime application. The setAplicationContext() needs to be called once per process.
 * before native library is loaded.
 * 
 * @author jrong
 *
 */
final public class StubInterface implements Serializable {
	
	private static Context context = null;	
	private static final String VOUCHER_NAME = "irdeto_java_access.dat";
	private static final String JAC_STORE_NAME = "jac_store_data.dat";
	private static final String JAC_ACV_NAME = "jac_store.dat";
//To avoid exception thrown in JNI
	private static String apkName = "null";	
	private static String voucherFullPath = "null";
	private static String storeFullPath = "null";
	private static String apkPath = "null";
	private static String appAssetDir = "null";
	private static Object locker = new Object();
	private static String MYTAG = "StubInterface";
	/**
	 * A constructor need to be called once. 
	 * @param ctx
	 * @throws Exception
	 */
	public StubInterface(Context ctx) throws Exception{		
		synchronized (locker){			
			initContext(ctx);
		}	
	}	
	/**
	 * An optional constructor if user wants to instantiate many times.
	 * @throws Exception
	 */
	public StubInterface() throws Exception{
		synchronized (locker){	
			if(apkName.compareToIgnoreCase("null") == 0 ) {
				Exception exception = new Exception("Application Context is not set, use construtor with the Context, ");
				throw(exception);
			}
		}
	}
	public static Context getApplicationContext(){
		return context;
	}
	/**
	 * An optional method to be called once.
	 * @param Context, an application context.
	 * @throws Exception
	 */
	public static void setAplicationContext(Context ctx) throws Exception{
		synchronized (locker){			
			initContext(ctx);
		}	
	}
	private static void initContext(Context ctx) throws Exception{
		
		synchronized (locker){			
			if(apkName.compareToIgnoreCase("null") != 0 ) {
				Exception exception = new Exception("Application Context is already set, ignore");
				throw(exception);
			}
			context = ctx;
			apkName = ctx.getPackageName();			
			if(apkName == null) {
				Exception exception = new Exception("Invalid APK name resulting from Application Context!");
				throw(exception);
			}			
			//setupInternalVoucher(ctx);
			setupAPKPath(ctx);
			setupSecureStore(ctx);
		}	
	}
	/**
	 * A static method to be called from JNI library.
	 * @return String, an APK name.
	 */
	public static String getAPKName(){						
		return apkName;
	}	
	
	public static String getVoucherFullPath(){
		return voucherFullPath;
	}
	private static void setupAPKPath(Context ctx) throws Exception{
		PackageManager pm = context.getPackageManager();
		ApplicationInfo aInfo = pm.getApplicationInfo(ctx.getPackageName(), PackageManager.GET_UNINSTALLED_PACKAGES);
		apkPath = aInfo.sourceDir;		
	}
	public static String getAPKPath(){
		return apkPath;
	}
	public static String getAssetDir (){
		return appAssetDir;
	}
	private static void setupInternalVoucher(Context ctx) throws Exception{
		
		AssetManager aManager = ctx.getAssets();		
		InputStream is = aManager.open(VOUCHER_NAME);
		File filefir = ctx.getFilesDir();		
		appAssetDir = filefir.getAbsolutePath();
		voucherFullPath = appAssetDir+"/"+VOUCHER_NAME;
		migrateDescriptor(is, voucherFullPath);		
	}
	private static void setupSecureStore(Context ctx) throws Exception{		
		AssetManager aManager = ctx.getAssets();				
		File filefir = ctx.getFilesDir();		
		appAssetDir = filefir.getAbsolutePath();

		InputStream is = aManager.open(JAC_ACV_NAME);		
		if(is != null){
			String javaAcvPath = appAssetDir + "/" + JAC_ACV_NAME;
			migrateDescriptor(is, javaAcvPath);
		}
				
		try
		{		
			is = aManager.open(JAC_STORE_NAME);
			if(is != null){			
				String javaDataPath = appAssetDir +"/"+JAC_STORE_NAME;
				migrateDescriptor(is, javaDataPath);
			}
		}
		catch(Exception e)
		{
			//the project without jac_store_data.dat executes this statement 
			;
		}
	}
	private static void migrateDescriptor(InputStream inputStream, String outputFileName) throws Exception{		
    	FileOutputStream outputStream = null;
    	int len = 0;
        
    	if(inputStream == null){
        	return;
        }        	
    			
        try {
			File outputFile = new File(outputFileName);			
			if(!outputFile.exists()){
				byte buf[] = new byte[1024];
	        	outputStream = new FileOutputStream(outputFile);
	        	while ((len = inputStream.read(buf)) != -1) {
	        		outputStream.write(buf, 0, len);
	        	}
			}
        } catch (Exception e){	        	
        	throw(new Exception(e));
        } finally{
        	if(outputStream != null)outputStream.close();
        	if(inputStream != null)inputStream.close();
        }
    }
}
