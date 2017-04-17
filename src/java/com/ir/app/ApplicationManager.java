package com.ir.app;

import java.util.*;
import java.io.Serializable;
import java.lang.reflect.*;


/**
 * 
 * A public class for user to gain access to JAC system. It automatically dispatches the JAC application depending 
 * upon type of JVM.
 * 
 * @author jrong
 *
 */
final public class ApplicationManager implements Serializable {

	final static public String DALVIKVM = "DALVIKVM";
	final static public String STDVM = "STDVM";	
	final static public String SYMBIANVM = "SYMBIANVM";
	static protected boolean useOwnLib = false;
	static private Application app = null;
	static private Hashtable jvmTable = new Hashtable();
	static private Class params[] = new Class[2];	
	static private String OS_VERSION_FROYO= "2.2";
	
	static {
		jvmTable.put(DALVIKVM, "com.ir.app.android.ApplicationDalvikVM");
		jvmTable.put(STDVM, "com.ir.app.stdvm.ApplicationStdVM");
		try {
			params[0] = Object.class; 
			params[1] = Object.class;
		} catch (Exception e){};	
	}
	/**
	 * A constructor includes initializing the JAC application. The class has to be instantiated once for JAC to
	 * perform initialization of environment.   
	 * 
	 * @param appType
	 * @param appContext
	 * @param reserved
	 * @param isMyLib, load libirdetojavasecurity.so if it is true. Default is false.
	 * @throws Exception
	 */
	public ApplicationManager(String appType, Object appContext, Object reserved, boolean isMyLib) throws Exception{
		useOwnLib = isMyLib;
		init(appType, appContext, reserved);
	}
	/**
	 * A constructor includes initializing the JAC application. The class has to be instantiated once for JAC to
	 * perform initialization of environment.   
	 * 
	 * @param appType
	 * @param appContext
	 * @param reserved
	 * @throws Exception
	 */
	public ApplicationManager(String appType, Object appContext, Object reserved) throws Exception{
		init(appType, appContext, reserved);
	}
	private void init(String appType, Object appContext, Object config) throws Exception{		
		Object args[] = new Object[2];		
		if(android.os.Build.VERSION.RELEASE.compareToIgnoreCase(OS_VERSION_FROYO) < 0){
			Thread.currentThread().setContextClassLoader(this.getClass().getClassLoader());
		}			
		String className = (String) jvmTable.get(appType);		
		Class myClass = Class.forName(className);					
		Constructor myConstructor = myClass.getConstructor(params);		
		args[0] = appContext;
		args[1] = null;
		app = (Application) myConstructor.newInstance(args);
	}
	/**
	 * An optional API for user to check classes in the calling chain. An alternative way is to check within the
	 * C/C++ function, such as aCC(). 
	 * 	
	 * @return String, status code, check Application class for detail.
	 */
	public String getPermission(){
		IVApplication ivApp = this.getApplication().getIVApplication();
		return ivApp.getPermission();
	}	
	/**
	 * Reture a secure classloader containing all the classes stored inside the secure store.. 
	 * 
	 * @return ClassLoader 
	 */
	public ClassLoader getClassLoader(){			
		return app.getJACClassLoader();	
	}		
	
	protected Application getApplication(){
		return app;
	}		
	
}
