package com.irdeto.secureaccess.android;

import java.util.ArrayList;
import java.util.HashMap;
import java.io.FileInputStream;
import java.io.File;

import com.irdeto.secureaccess.common.DomParserService;

/**
 * The class is to setup the working environment necessary for signing the applications. 
 * @author test
 *
 */
public class Configuration {
	
	private ArrayList signingClassArray = null;
	private ArrayList signingPackageArray = null;
	private ArrayList signingExcludeClassPackageArray = null;
	private ArrayList noSigningJavaPackageArray = null;
	private String configFilePath = null;
	private HashMap map = null;
	private String dummy = null;
	
	/**
	 * Constructor
	 * @param configFile, pointing to the configuration file in XML format.
	 */
	public Configuration(String configFile ){
		this.configFilePath = configFile;
		init();
	}
	
	private void init(){
		try{
			loadConfiguration();			
		} catch (Exception e){e.printStackTrace();};	
	}
	
	public ArrayList getSigningClassList(){
		return signingClassArray;
	}
	
	public String getSigningPackages(){
		
		StringBuffer buf = new StringBuffer();		
		String pathSep = System.getProperty("path.separator", ":");
		
		if(signingPackageArray != null && signingPackageArray.get(0) != null){
			buf.append(signingPackageArray.get(0));
		}else{
			return buf.toString();
		}
		for(int pos = 1; (signingPackageArray != null) && pos < signingPackageArray.size(); pos++){
			buf.append(pathSep+signingPackageArray.get(pos));
		}
		return buf.toString();
	}
	
	public String getClassSigningRejectPackages(){
		
		StringBuffer buf = new StringBuffer();		
		String pathSep = System.getProperty("path.separator", ":");
		
		if(	signingExcludeClassPackageArray != null 	&& 
			signingExcludeClassPackageArray.size() > 0 	&&
			signingExcludeClassPackageArray.get(0) != null ){
			buf.append(signingExcludeClassPackageArray.get(0));
		}else{
			return buf.toString();
		}
		for(int pos = 1; (signingExcludeClassPackageArray != null) && pos < signingExcludeClassPackageArray.size(); pos++){
			buf.append(pathSep+signingExcludeClassPackageArray.get(pos));
		}
		return buf.toString();
	}
	protected ArrayList getNoSigningJavaPackageArray(){
		return noSigningJavaPackageArray;
	}
	protected void loadConfiguration() throws Exception{
		
		FileInputStream fis = new FileInputStream(new File (configFilePath));	    		    	
		DomParserService xml = new DomParserService(fis);
		map = xml.parsePackageSigningConfig();
		signingPackageArray = (ArrayList) map.get(DomParserService.SIGNING_PACKAGE);	
		signingExcludeClassPackageArray = (ArrayList) map.get(DomParserService.SIGNING_PACKAGE_REJECT_CLASS);
		noSigningJavaPackageArray = (ArrayList) map.get(DomParserService.NO_SIGNING_JAVA_PACKAGE);
	}	
	public HashMap getConfigMap(){
		return map;
	}
	
}
