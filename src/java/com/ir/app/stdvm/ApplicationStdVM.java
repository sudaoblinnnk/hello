package com.ir.app.stdvm;

import com.ir.app.*;

public class ApplicationStdVM implements Application {

	public ApplicationStdVM(Object appContext, Object reserved) throws Exception {
		init(appContext, reserved);
	}
	private  boolean init(Object input, Object reserved) throws Exception{
		return true;
	}
	public boolean execute(Object input, Object result) throws Exception{
		return true;
	}
	public void finish(Object obj){
		
	}
	
	public IVApplication getIVApplication(){
		IVApplication ivApp = null;
		return ivApp;
	}
	public ClassLoader getJACClassLoader(){
		return null;
	}
}
