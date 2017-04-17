package com.ir.app;

import java.util.ArrayList;
import java.io.Serializable;

import android.util.Log;

 final public class NativeAppManager implements Serializable {
	 static final String MYTAG = "NativeAppManager";
	 static {

		 try{
			 if(ApplicationManager.useOwnLib){
				 System.loadLibrary("megjb");
			 }
		 } catch (java.lang.UnsatisfiedLinkError e){
			Log.w(MYTAG,"STATIC block, Failed to load library, message "+e.getMessage());			
		 }				
		
	}			
	public native String getPermission(String indicator, Object myObj);	
	public native int getAppIVStatus(String indicator, Object myObj);	
	public native int getOperationParameters(ArrayList archives, ArrayList nativeLibPath, ArrayList knowClasses, Object reseved);
}
