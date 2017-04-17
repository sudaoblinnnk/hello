package com.irdeto.secureaccess.common;

import java.io.File;
import java.util.HashMap;
import java.util.ArrayList;
import java.io.InputStream;
import java.io.IOException;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

/**
 * To provide parsing service for Java Access Control.
 * @author test
 *
 */
public class DomParserService {
	
	public static final String TAG_APPLICATION_TYPE = "applicationtype";
	public static final String TAG_LOG_LEVEL = "loglevel";
	public static final String TAG_OPERATION = "operation";
	public static final String TAG_OUTPUTFILE_PATH = "outputFilePath";
	public static final String TAG_NATIVE_LIB_PATH = "nativeLibPath";
	public static final String TAG_PACKAGE_PARAMETERS = "packageParameters";
	public static final String TAG_PARAMETER = "parameter";
	public static final String TAG_PACKAGE_NO_SIGING = "noSigningJavaPackage";
	public static final String TAG_PACKAGE = "package";
	public static final String TAG_PACKAGE_EXCLUDE_CLASS = "packageExcludeClass";
	public static final String TAG_PACKAGE_INCLUDE = "includeJavaPackage";
	public static final String TAG_NAME= "name";
	public static final String TAG_JAC_POLICY="JACPolicy";
	public static final String TAG_VALUE = "value";
	public static final String TAG_STUB_CLASS = "stubClass";
	public static final String XML_VALUE_PACKAGE = "package";
	public static final String XML_VALUE_PACKAGE_EXCLUDE_CLASS = "packageExcludeClass";
	public static final String XML_VALUE_PACKAGE_NO_SIGING = "noSigningJavaPackage";
	public static final String XML_VALUE_SIGNING="signing";	
	public static final String SIGNING_PACKAGE = "signingPackage";
	public static final String SIGNING_PACKAGE_REJECT_CLASS = "signingExcludeClassPackage";
	public static final String NO_SIGNING_JAVA_PACKAGE = XML_VALUE_PACKAGE_NO_SIGING;
	public static final String INCLUDE_JAVA_PACKAGE = TAG_PACKAGE_INCLUDE;
	public static final String TAG_USER_TARGET_APK = "userTargetAPK";
	public static final String TAG_STORE_PATH = "storePath";
	
	DomParser parser = null;
	InputStream is = null;

	/**
	 * Constructor to take input stream of XML file
	 * @param is
	 */
	public DomParserService (InputStream is){
		parser = new DomParser();
		this.is= is;		
	}	
	
	public HashMap parsePackageSigningConfig(){
		
		NodeList parmItemList = null;
		NodeList parmsItemList = null;
		NodeList tagItemList = null;		
		Element paramItem = null;
		Element paramsItem = null;
		String paramName = null;
		String paramValue = null;
		Node node = null;
		HashMap map = new HashMap();
		Document doc = parser.parse(is);
		
		
		tagItemList = doc.getElementsByTagName(TAG_OPERATION);
		if((node = tagItemList.item(0)) != null && node.getFirstChild() != null)
			map.put(TAG_OPERATION, node.getFirstChild().getNodeValue());
		
		tagItemList = doc.getElementsByTagName(TAG_OUTPUTFILE_PATH);
		if((node = tagItemList.item(0)) != null && node.getFirstChild() != null)
			map.put(TAG_OUTPUTFILE_PATH, node.getFirstChild().getNodeValue());
		
		tagItemList = doc.getElementsByTagName(TAG_NATIVE_LIB_PATH);
		if((node = tagItemList.item(0)) != null && node.getFirstChild() != null)
			map.put(TAG_NATIVE_LIB_PATH, node.getFirstChild().getNodeValue());
		
		tagItemList = doc.getElementsByTagName(TAG_JAC_POLICY);
		if((node = tagItemList.item(0)) != null && node.getFirstChild() != null)
			map.put(TAG_JAC_POLICY, node.getFirstChild().getNodeValue());
		
		tagItemList = doc.getElementsByTagName(TAG_STUB_CLASS);
		if((node = tagItemList.item(0)) != null && node.getFirstChild() != null)
			map.put(TAG_STUB_CLASS, node.getFirstChild().getNodeValue());
		
		tagItemList = doc.getElementsByTagName(TAG_USER_TARGET_APK);
		if((node = tagItemList.item(0)) != null && node.getFirstChild() != null)
			map.put(TAG_USER_TARGET_APK, node.getFirstChild().getNodeValue());
		
		tagItemList = doc.getElementsByTagName(TAG_STORE_PATH);
		if((node = tagItemList.item(0)) != null && node.getFirstChild() != null)
			map.put(TAG_STORE_PATH, node.getFirstChild().getNodeValue());
		
		ArrayList packageArray = new ArrayList();
		ArrayList packageExcludeClassArray = new ArrayList();
		ArrayList noSigningPackageArray = new ArrayList();
		ArrayList includeJavaPackageArray = new ArrayList();
		map.put(SIGNING_PACKAGE, packageArray);
		map.put(SIGNING_PACKAGE_REJECT_CLASS, packageExcludeClassArray);
		map.put(NO_SIGNING_JAVA_PACKAGE, noSigningPackageArray);
		map.put(INCLUDE_JAVA_PACKAGE, includeJavaPackageArray);
		tagItemList = doc.getElementsByTagName(TAG_PACKAGE_PARAMETERS);		
		for (int pos =0; pos < tagItemList.getLength(); pos++ ){
			
			paramsItem =  (Element) tagItemList.item(pos);			
			parmsItemList = paramsItem.getElementsByTagName(TAG_PACKAGE);			
			for(int pos2 =0; pos2 < parmsItemList.getLength(); pos2++) {							
				if((node =parmsItemList.item(pos2)) != null && node.getFirstChild() != null){
					paramValue = node.getFirstChild().getNodeValue();
					packageArray.add(paramValue);
				}
			}						
			parmsItemList = paramsItem.getElementsByTagName(TAG_PACKAGE_NO_SIGING);
			for(int pos2 =0; pos2 < parmsItemList.getLength(); pos2++) {				
				if((node = parmsItemList.item(pos2)) != null && node.getFirstChild() != null){
					paramValue = node.getFirstChild().getNodeValue();
					noSigningPackageArray.add(paramValue);
				}	
			}
			parmsItemList = paramsItem.getElementsByTagName(TAG_PACKAGE_EXCLUDE_CLASS);
			for(int pos2 =0; pos2 < parmsItemList.getLength(); pos2++) {
				if((node = parmsItemList.item(pos2)) != null && node.getFirstChild() != null){
					paramValue = node.getFirstChild().getNodeValue();
					packageExcludeClassArray.add(paramValue);
				}	
			}
			parmsItemList = paramsItem.getElementsByTagName(TAG_PACKAGE_INCLUDE);
			for(int pos2 =0; pos2 < parmsItemList.getLength(); pos2++) {
				if((node = parmsItemList.item(pos2)) != null && node.getFirstChild() != null){
					paramValue = node.getFirstChild().getNodeValue();
					includeJavaPackageArray.add(paramValue);
				}	
			}			
		}	
		
		return map;
	}
}
