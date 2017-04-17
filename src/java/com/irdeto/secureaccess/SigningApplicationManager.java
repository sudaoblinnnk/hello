package com.irdeto.secureaccess;

import java.lang.reflect.Constructor;
import java.util.Hashtable;

import com.irdeto.secureaccess.Application;

/**
 * A main entry class to access the JAC signing process.
 * 
 * @author jrong
 *
 */
public class SigningApplicationManager {
	final static public String DALVIKVM = "DALVIKVM";
	final static public String STDVM = "STDVM";	
	final static public String SYMBIANVM = "SYMBIANVM";	
	static private Application app = null;
	static private Hashtable jvmTable = new Hashtable();
	static private Class params[] = new Class[2];
	String appType = null;
	String configFile = null;
	Object appCtx = null;
	
	static {
		jvmTable.put(DALVIKVM, "com.irdeto.secureaccess.android.ApplicationImpl");
		jvmTable.put(STDVM, "com.irdeto.security.stdvm.ApplicationImpl");
		try {
			params[0] = String.class; 
			params[1] = Object.class;
		} catch (Exception e){};	
	}
	public SigningApplicationManager(String appType, String configFile, Object appContext) throws Exception{
		this.appType = appType;
		this.configFile = configFile;
		this.appCtx = appContext;
		init();		
	}
	private void init() throws Exception{
		
		Object args[] = new Object[2];
		String className = (String) jvmTable.get(appType);		
		Class myClass = Class.forName(className);
					
		Constructor myConstructor = myClass.getConstructor(params);		
		args[0] = configFile;
		args[1] = appCtx;
		app = (Application) myConstructor.newInstance(args);			
	}
	public void sign() throws Exception{
		app.signClasses();
	}
}
