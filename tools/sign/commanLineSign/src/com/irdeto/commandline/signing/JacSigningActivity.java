package com.irdeto.commandline.signing;

import android.app.Activity;
import android.os.Bundle;
import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.util.Log;
import java.io.File;
import com.irdeto.secureaccess.SigningApplicationManager;
import com.irdeto.secureaccess.android.ApplicationImpl;
import android.os.Environment;


public class JacSigningActivity extends Activity
{
	public final String signConfigFile = Environment.getExternalStorageDirectory() + "/irdeto_java_access_config.xml";
	String myTag = "JacSigningActivity";
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        testSigning();
    }
    void testSigning(){    	
    	try {    		  		
    		SigningApplicationManager signingTool = new SigningApplicationManager(
			SigningApplicationManager.DALVIKVM, signConfigFile,	this);
    		signingTool.sign();
    		Log.d(myTag, "Signing completed");
    	} catch (Exception e){    		
    	}
    }	       
}
