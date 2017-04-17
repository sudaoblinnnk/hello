package com.ir.app;

import java.io.Serializable;


public interface  Application extends Serializable{
		
	final static String SHARED_LIB_PATH = "LIB_PATH";
	final static String JAVA_LIB = "JAVA_LIB";
	/**
	 * The status code below should be in synch. with c/c++ header file irdetoJavaSecurity.h
	 */

	public boolean execute(Object input, Object result) throws Exception;	
	public void finish(Object obj);
	public IVApplication getIVApplication();
	public ClassLoader getJACClassLoader();
}
