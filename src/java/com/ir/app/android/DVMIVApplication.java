package com.ir.app.android;

import android.content.Context;
import android.util.Log;

import com.ir.app.IVApplication;
import com.ir.app.NativeAppManager;
import com.ir.app.android.StubInterface;

/**
 * 
 * A skeleton class. The major IV checking activities happen within C/C++ code. 
 * 
 * @author jrong
 *
 */
final public class DVMIVApplication implements IVApplication {
	
	String MYTAG = "DVMIVApplication";
	
	NativeAppManager ntApp = null;
	Context context = null;
	
	public DVMIVApplication(Object context) throws Exception{
		this.context = (Context) context;
		init();
	}		
	private void init() throws Exception {
		try {
			StubInterface.setAplicationContext(context);
		} catch (Exception e){
			Log.d(MYTAG, "init(), Excetion message from StubInterface: "+e.getMessage());
		}
		ntApp = new NativeAppManager();
	}
	public String  getPermission(){		
		return ntApp.getPermission(null, null);
	}
	public NativeAppManager getNativeManager(){
		return ntApp;
	}
}
