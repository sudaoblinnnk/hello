package com.irdeto.secureaccess.android;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Date;
import java.io.File;
import java.io.InputStream;
import java.io.FileOutputStream;

import android.util.Log;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;

import com.irdeto.secureaccess.Application;
import com.irdeto.secureaccess.CryptoManager;
import com.irdeto.secureaccess.common.IOUtils;
import com.irdeto.secureaccess.common.DomParserService;

/**
 * This class is to implement signing application.
 * 
 * @author jrong
 *
 */
public class ApplicationImpl implements Application {

	public final String VERSION = "IRDETO JAC Version 2.0";	
	static final String MYTAG = "ApplicationImpl";
	final String SignatureFileName = "irdeto_java_access.dat";
	final String SignatureExcludeClassFileName = "irdeto_java_access_exclude_class.dat";
	final String SignatureBadFileName = "irdeto_java_access_ns.dat";
	final String noSigningJavaPackage = "com.irdeto.secureaccess";
	final String STORE_NAME="jac_store.dat";
	final String CONFIG_FILE_NAME="irdeto_java_access_config.xml";
	final String myTag = "ApplicationImpl";
	static boolean notFirstTime = false;	
	 	
	File signatureOutputFile = null;
	Configuration myConfig = null;
		
	String dexPath = null;
	String dexPathExludeClass = null;
	String signOutputDir = null;
	String nativeLibPath = null;
	String signatureOutputPath = null;
	String configFilePath = null;
	String signatureBadOutputPath = null;
	String excludeClassOutputPath = null;
	String JACPolicy=null;
	String stubClass=null;
	String userTargetAPK = null;
	String storePath = null;
	String appAssetDir = null;
	ArrayList noSigningPackage = null;
	ArrayList includeJavaPackage = null;
	Context context = null;
	
	/**
	 * Constructor.
	 * @param config, pointing to the configuration file in XML format.
	 */
	public ApplicationImpl(String config, Object appContext){
		this.configFilePath = config;
		this.context = (Context) appContext;
		try{
			init(configFilePath);
		} catch (Exception e){
			e.printStackTrace();
		}
	}	
	
	/**
	 * To initialize operational variables via configuration file in XML. 
	 * @param String, configFile.
	 * @throws Exception
	 */
	private void init(String configFile) throws Exception{	
		int len;    	     
    	InputStream is = null;			
    	byte buf[] = new byte[1024];   
    	
		AssetManager aManager = context.getAssets();
		File filefir = context.getFilesDir();		
		appAssetDir = filefir.getAbsolutePath();
		Log.d(myTag, "The internal directory: "+appAssetDir);
		String assetFilePath = appAssetDir +"/"+CONFIG_FILE_NAME;
		Log.d(myTag, "Checking packaged configuration file: "+CONFIG_FILE_NAME ); 
		try{
			is = aManager.open(CONFIG_FILE_NAME);
		} catch (Exception e2){
			Log.w(myTag, "Message: "+e2.getMessage());
		}    		     		
		if(is == null){			
			Log.d(myTag, "Packaged configuration file doesn't exist, use configuration file: "+configFile );    			
		}else{
			FileOutputStream outputStream = new FileOutputStream(new File(assetFilePath));
        	while ((len = is.read(buf)) != -1) {
        		outputStream.write(buf, 0, len);
        	}
        	is.close();
        	outputStream.close();
        	configFile = assetFilePath;
			Log.d(myTag, "Use packaged configuration file: "+configFile );    
		}
		myConfig = new Configuration(configFile);
		HashMap map = myConfig.getConfigMap();
		this.dexPath = myConfig.getSigningPackages();
		this.dexPathExludeClass = myConfig.getClassSigningRejectPackages();
		this.signOutputDir = (String) map.get(DomParserService.TAG_OUTPUTFILE_PATH);
		this.nativeLibPath = (String) map.get(DomParserService.TAG_NATIVE_LIB_PATH);		
		this.signatureOutputPath = signOutputDir+System.getProperty("file.separator", "/")+SignatureFileName;	
		this.signatureBadOutputPath = signOutputDir+System.getProperty("file.separator", "/")+SignatureBadFileName;
		this.excludeClassOutputPath = signOutputDir+System.getProperty("file.separator", "/")+SignatureExcludeClassFileName;
		this.JACPolicy = (String) map.get(DomParserService.TAG_JAC_POLICY);
		this.stubClass = (String) map.get(DomParserService.TAG_STUB_CLASS);
		this.storePath = (String) map.get(DomParserService.TAG_STORE_PATH);
		
		if(JACPolicy == null){
			JACPolicy = "2";
		}
		this.noSigningPackage = (ArrayList) map.get(DomParserService.NO_SIGNING_JAVA_PACKAGE);
		this.includeJavaPackage = (ArrayList)map.get(DomParserService.INCLUDE_JAVA_PACKAGE);
		if(noSigningPackage != null)
			noSigningPackage.add(noSigningJavaPackage);
		this.userTargetAPK = (String) map.get(DomParserService.TAG_USER_TARGET_APK);		
	}
	/**
	 * To generate class signature in HMacSha1.
	 * @param className
	 * @param isStub
	 */
	private void generateClassSignature(String className, boolean isStub){			
		IOUtils it = new IOUtils(); 
		String message = null;
		
		
		try	{								
			generateHeader();			
			CryptoManager cm = new CryptoManager(storePath, null);
			message = cm.getDigitalSignatureFromCAT(className, isStub);
			if(!message.equalsIgnoreCase("null")){
				it.writeToPrintStream(signatureOutputPath, notFirstTime, message);
			}else{
				it.writeToPrintStream(signatureBadOutputPath, notFirstTime, className);
			}
		} catch (Exception e){
			try{
				it.writeToPrintStream(signatureBadOutputPath, notFirstTime, className);
			}catch (Exception e2){};	
			Log.w(MYTAG,"generateClassSignature, classname: "+className+" can't be signed, message: "+e.getMessage());
		}			
		
	}		
	private void generateHeader(){
		IOUtils it = new IOUtils(); 
		String message = null;
		try	{					
			if(!notFirstTime){				
				message = VERSION + ", "+new Date().toString();				
				it.writeToPrintStream(signatureOutputPath, notFirstTime, message);				
				it.writeToPrintStream(signatureBadOutputPath, notFirstTime, message);
				notFirstTime = true;
				message = "POLICY: " + JACPolicy;
				it.writeToPrintStream(signatureOutputPath, notFirstTime, message);				
			}			
		} catch (Exception e){						
		}				
	}
	/**
	 * This method is not in use.
	 * @param className
	 */
	private void generateExcludeClassVoucher(String className){
		IOUtils it = new IOUtils(); 
		String message = null;
		try	{					
			if(!notFirstTime){
				message = VERSION + ", "+new Date().toString();
				it.writeToPrintStream(excludeClassOutputPath, notFirstTime, message);								
				notFirstTime = true;
			}
			message = "Name: "+className;
			it.writeToPrintStream(excludeClassOutputPath, notFirstTime, message);						
		} catch (Exception e){			
			Log.w(MYTAG,"generateExcludeClassVoucher, classname: "+className+" can't be signed, message: "+e.getMessage());
		}			
	}
	
	private void generateAPKSignature(String APKPath){
		String message = null;
		IOUtils it = new IOUtils(); 		
		try{
			generateHeader();			
			CryptoManager cm = new CryptoManager(storePath, null);
			message = cm.getAPKDigitalSignatureFromCAT(APKPath);
			it.writeToPrintStream(signatureOutputPath, notFirstTime, message);	
		} catch (Exception e){
			try{
				it.writeToPrintStream(signatureBadOutputPath, notFirstTime, APKPath);
			}catch (Exception e2){};	
			Log.w(MYTAG,"generateAPKSignature, APK name: "+APKPath+" can't be signed, message: "+e.getMessage());
		}
	}
	private void generateEOFString(){
		IOUtils it = new IOUtils();
		try{
			String message ="#EOF";
			it.writeToPrintStream(signatureOutputPath, notFirstTime, message);
			it.setPermission(signatureOutputPath);
			it.setPermission(signatureBadOutputPath);
		}catch (Exception e){
			
		}
	}
	/**
	 * A public method to invoke the signing process.
	 * 
	 * @throws Exception
	 */
	public void signClasses() throws Exception{		
		
		DFileManager dexManager = new DFileManager(dexPath, appAssetDir, nativeLibPath);		
		ArrayList dexClasses = dexManager.getListOfClasses();				
		for(int dexPos = 0; dexPos < dexClasses.size(); dexPos++){			
			String dexClass = (String)dexClasses.get(dexPos); 	
			if(needToFilterOutClass(dexClass)) continue;
			generateClassSignature(dexClass, false);			
		}			
		if(stubClass != null){		
			if(foundStubClassInClassList(dexClasses, stubClass)){
				generateClassSignature(stubClass,true);
			}else{
				Log.w(MYTAG,"signClasses, stub class: "+stubClass+" dosen't exist, ignore");
			}			
		}		
		if(userTargetAPK != null){
			generateAPKSignature(userTargetAPK);
		}	
		generateEOFString();
		ArrayList array = new ArrayList();
	
		notFirstTime = false;
		if(dexPathExludeClass == null || dexPathExludeClass.length() == 0 ) return;
		
		dexManager = new DFileManager(dexPathExludeClass, appAssetDir, nativeLibPath);
		dexClasses = dexManager.getListOfClasses();						
		for(int dexPos = 0; dexPos < dexClasses.size(); dexPos++){			
			String dexClass = (String)dexClasses.get(dexPos); 			
			generateExcludeClassVoucher(dexClass);			
		}					
	}		
	/**
	 * Check if stub class is in the list of array that is generated from DEX file.
	 * @param array
	 * @param stubClass
	 * @return
	 */
	private boolean foundStubClassInClassList(ArrayList array, String stubClass){
		boolean retVal = false;
		for(int pos = 0; pos < array.size(); pos++){
			String tmpClassName = (String) array.get(pos);
			if(tmpClassName.equals(stubClass)){
				retVal = true;
				break;
			}
		}
		return retVal;
	}
	/**
	 * Check if the class is marked as no-signing class. 
	 * @param className
	 * @return true if is a no-signing class
	 */
	private boolean needToFilterOutClass(String className){
		
		//The includeJavaPackage option trumps the rest of options.	
		if(includeJavaPackage != null && includeJavaPackage.size() > 0){
			for(int pos =0; pos < includeJavaPackage.size(); pos++ ){
				String checkingPackage = (String) includeJavaPackage.get(pos);
				if(checkingPackage != null && checkingPackage.length() > 0 && className.startsWith(checkingPackage)){
					return false;
				}
			}
			//If the class doesn't match the package, exclude this one. 
			return true;
		}
		if(noSigningPackage == null || noSigningPackage.size() == 0){
			return false;
		}
		for(int pos =0; pos < noSigningPackage.size(); pos++ ){
			String checkingPackage = (String) noSigningPackage.get(pos);
			if(checkingPackage != null && checkingPackage.length() > 0 && className.startsWith(checkingPackage)){
				return true;
			}
		}
		return false;
	}
}
