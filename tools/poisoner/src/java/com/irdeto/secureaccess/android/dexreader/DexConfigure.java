package com.irdeto.secureaccess.android.dexreader;

import java.io.InputStream;
import java.io.FileInputStream;
import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.w3c.dom.Node;

public class DexConfigure {
	
	final String OPERATION_SCOPE_TOKEN = "scope";
	final String INCLDE_OPCODE_TOKEN ="includeOpcode";
	final String EXCLUDE_OPCODE_TOKEN="excludeOpcode";
	final String INCLUDE_CLASS_TOKEN="includeClass";
	final String EXCLUDE_CLASS_TOKEN="excludeClass";
	final String DEX_POISON_WHOLE_METHOD_TOKEN="replaceWholeMethodOpcode";
	final String DISPLAY_VERBOSE_TOKEN="verbose";
	final String CLASS_TOKEN="class";
	final String CLASS_NAME_TOKEN="name";
	final String MOTHOD_TOKEN="method";
	final String CONFIG_FILE_PATH="ConfigureFilePath";	
	final public String KEY_INCLUDE_CLASS_MAP_LIST = "includeClassMapList";
	final public String KEY_EXCLUDE_CLASS_MAP_LIST = "excludeClassMapList";
	
	static public String OPERATION_SCOPE_ALL="all";
	static public String OPERATION_SCOPE_PARTIAL = "partial";
	
	private DomParser parser;
	private InputStream is;
	
	private HashMap resultMap = null ;
	private ArrayList includeClassMapList = null;	
	private ArrayList excludeClassMapList = null;	
	private ArrayList includeOpcodeList = null;
	private ArrayList excludeOpcodeList = null;
	
	private boolean isIncludeAll = true;
	boolean isWholeMethodInst = true;
	boolean isExcludesiveMode = false;
	static boolean verbose=false;
		
	public DexConfigure() throws Exception{				
		try{
			init();
		} catch(Exception e){
			throw(e);
		}
	}
	void init() throws Exception {		
		String token = System.getProperty(CONFIG_FILE_PATH);
		if(token!= null){
			is = new FileInputStream(new File(token));
		}else{
			throw new Exception("No configuration file found");
		}				
		parser = new DomParser();
		resultMap = new HashMap();
		resultMap.put(OPERATION_SCOPE_TOKEN, OPERATION_SCOPE_ALL);
		parseXML();
	}
	
	public HashMap getConfigMap(){
		return resultMap;
	}
		
	private void parseXML(){
		
		Document doc = parser.parse(is);		
		NodeList methodsItemList = null;
		NodeList methodItemList = null;
		NodeList classesItemList = null;
		NodeList classItemList = null;
		NodeList tagItemList = null;		
		Element methodNameItem = null;
		Element classesItem = null;
		Element classItem = null;		
		Node node;
		String className = null;
		String methodName = null;
		ArrayList methodList = null;	
		
		tagItemList =  doc.getElementsByTagName(OPERATION_SCOPE_TOKEN);
		if((node = tagItemList.item(0)) != null && node.getFirstChild() != null){
			setAllOperationScopeInd(node.getFirstChild().getNodeValue());
		}		
		tagItemList =  doc.getElementsByTagName(DEX_POISON_WHOLE_METHOD_TOKEN);
		if((node = tagItemList.item(0)) != null && node.getFirstChild() != null){
			setIsWholeMethodInstruction(node.getFirstChild().getNodeValue());
		}						
		tagItemList =  doc.getElementsByTagName(DISPLAY_VERBOSE_TOKEN);
		if((node = tagItemList.item(0)) != null && node.getFirstChild() != null){
			setDisplayOption(node.getFirstChild().getNodeValue());
		}		
		addIncludeClass(doc);
		addExcludeClass(doc);
	}
	private void addIncludeClass(Document doc){
		NodeList methodsItemList = null;
		NodeList methodItemList = null;
		NodeList classesItemList = null;
		NodeList classItemList = null;
		NodeList tagItemList = null;		
		Element methodNameItem = null;
		Element classesItem = null;
		Element classItem = null;		
		Node node;
		String className = null;
		String methodName = null;
		ArrayList methodList = null;	
		
		displayMessage("Parsing includeClass block");	
		tagItemList =  doc.getElementsByTagName(INCLUDE_CLASS_TOKEN);		
		if((node = tagItemList.item(0)) != null && node.getFirstChild() != null){			
			for (int pos =0; pos < tagItemList.getLength(); pos++ ){
				classesItem = (Element) tagItemList.item(pos);				
				classesItemList = classesItem.getElementsByTagName(CLASS_TOKEN);
				HashMap classMap = null;
				className = null;
				for(int pos2 =0; pos2 < classesItemList.getLength(); pos2++) {					
					classItem =  (Element) classesItemList.item(pos2);
					classItemList = classItem.getElementsByTagName(CLASS_NAME_TOKEN);
					methodsItemList = classItem.getElementsByTagName(MOTHOD_TOKEN);
					if((node = classItemList.item(0)) != null && node.getFirstChild() != null){
						className = node.getFirstChild().getNodeValue();
						displayMessage("DexConfigure, Classname: "+className);						
					}	
					methodList = null;
					for(int metPos= 0; metPos < methodsItemList.getLength() && className != null; metPos++){
						methodNameItem = (Element) methodsItemList.item(metPos);									
						methodName = methodNameItem.getFirstChild().getNodeValue();						
						displayMessage("DexConfigure, Method: "+methodName);
						if(methodList == null) {
							methodList = new ArrayList();
						}			
						methodList.add(methodName);
					}
					if(className != null){
						classMap = new HashMap();
						classMap.put(className, methodList);
						if(includeClassMapList == null){
							includeClassMapList = new ArrayList();
						}
						includeClassMapList.add(classMap);
					}	
				}//pos2					
			}//pos	
			resultMap.put(KEY_INCLUDE_CLASS_MAP_LIST, includeClassMapList);
		}	
	}
	private void addExcludeClass(Document doc){
		NodeList methodsItemList = null;
		NodeList methodItemList = null;
		NodeList classesItemList = null;
		NodeList classItemList = null;
		NodeList tagItemList = null;		
		Element methodNameItem = null;
		Element classesItem = null;
		Element classItem = null;		
		Node node;
		String className = null;
		String methodName = null;
		ArrayList methodList = null;	
		
		displayMessage("Parsing excludeClass block");	
		tagItemList =  doc.getElementsByTagName(EXCLUDE_CLASS_TOKEN);		
		if((node = tagItemList.item(0)) != null && node.getFirstChild() != null){			
			for (int pos =0; pos < tagItemList.getLength(); pos++ ){
				classesItem = (Element) tagItemList.item(pos);				
				classesItemList = classesItem.getElementsByTagName(CLASS_TOKEN);
				HashMap classMap = null;
				className = null;
				for(int pos2 =0; pos2 < classesItemList.getLength(); pos2++) {					
					classItem =  (Element) classesItemList.item(pos2);
					classItemList = classItem.getElementsByTagName(CLASS_NAME_TOKEN);
					methodsItemList = classItem.getElementsByTagName(MOTHOD_TOKEN);
					if((node = classItemList.item(0)) != null && node.getFirstChild() != null){
						className = node.getFirstChild().getNodeValue();
						displayMessage("DexConfigure, Classname: "+className);						
					}	
					methodList = null;
					for(int metPos= 0; metPos < methodsItemList.getLength() && className != null; metPos++){
						methodNameItem = (Element) methodsItemList.item(metPos);									
						methodName = methodNameItem.getFirstChild().getNodeValue();						
						displayMessage("DexConfigure, Method: "+methodName);
						if(methodList == null) {
							methodList = new ArrayList();
						}			
						methodList.add(methodName);
					}
					if(className != null){
						classMap = new HashMap();
						classMap.put(className, methodList);
						if(excludeClassMapList == null){
							excludeClassMapList = new ArrayList();
						}
						excludeClassMapList.add(classMap);
						isExcludesiveMode = true;
					}	
				}//pos2					
			}//pos	
			resultMap.put(KEY_EXCLUDE_CLASS_MAP_LIST, excludeClassMapList);
		}	
	}
	public boolean getAllOperationScopeInd(){
		return isIncludeAll;
	}
	void setAllOperationScopeInd(String indStr){
		if(indStr.equalsIgnoreCase(OPERATION_SCOPE_ALL)){
			isIncludeAll = true;
		}else{
			isIncludeAll = false;
		}		
	}	
	public boolean isIllegibleMethod(String className, String methodName){
			
		if(isIncludeAll){ //No class limit
			return true;							
		}else if (isExcludesiveMode){								
			for(int pos=0; excludeClassMapList != null && pos < excludeClassMapList.size(); pos++){
				HashMap mapClass = (HashMap)excludeClassMapList.get(pos);	
				Iterator iterator = mapClass.keySet().iterator();
				while(iterator.hasNext()){
					String keyClassName = (String) iterator.next();		
					if(keyClassName.equals(className)){ // found the class						
						ArrayList myMethodList = (ArrayList) mapClass.get(keyClassName);
						if(myMethodList == null || myMethodList.size() == 0){ //exclude all methods
							return false;
						}
						for(int metPos = 0; metPos < myMethodList.size(); metPos++){
							String myMetName = (String)myMethodList.get(metPos);
							if(myMetName.equals(methodName)){ // exclude the method found
								return false;
							}
						}						
					}			
				}			
			}	
			return true;		
		}else{	
			if (includeClassMapList == null || includeClassMapList.size() == 0){ //No restriction from config
				return true;
			}	
			for(int pos=0; pos < includeClassMapList.size(); pos++){
				HashMap mapClass = (HashMap)includeClassMapList.get(pos);	
				Iterator iterator = mapClass.keySet().iterator();
				while(iterator.hasNext()){
					String keyClassName = (String) iterator.next();					
					if(keyClassName.equals(className)){ // found the class						
						ArrayList myMethodList = (ArrayList) mapClass.get(keyClassName);
						if(myMethodList == null || myMethodList.size() == 0){ //No method limit
							return true;
						}
						for(int metPos = 0; metPos < myMethodList.size(); metPos++){
							String myMetName = (String)myMethodList.get(metPos);
							if(myMetName.equals(methodName)){ // include the method found
								return true;
							}
						}
						return false;
					}					
				}								
			}
			return false;
		}		
	}
	public boolean isIllegibleOpcode(int opcode){
		
		return true;
	}
	public boolean isWholeMethodInstruction(){
		return isWholeMethodInst;
	}
	static public void displayMessage(String message){
		if(verbose){
			System.out.println(message);
		}
	}
	private void setIsWholeMethodInstruction(String flag){
		if(flag == null || flag.length() == 0) return; // Default to enable whole method
		isWholeMethodInst = Boolean.valueOf(flag);	
	}
	private void setDisplayOption(String flag){		
		if(flag == null || flag.length() == 0) return; 
		verbose = Boolean.valueOf(flag);		
	}
	
}
