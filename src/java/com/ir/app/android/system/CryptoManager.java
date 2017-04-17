package com.ir.app.android.system;


import java.security.MessageDigest;
import java.io.Serializable;
import java.security.SignatureException;
import java.util.ArrayList;

import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;

import android.util.Log;



/**
 * To provide cryptographic service.
 * @author test
 *
 */
public class CryptoManager implements Serializable {
	
	static String MYTAG = "CryptoManager";

	static public byte[] getClassBytes(String className) throws Exception {
		byte[] myBytes2 = null;
		byte[] myDestBytes = null;		
		IOUtils it = new IOUtils(); 
		try	{
			byte[] myBytes1 = it.getBytesFromObject(className);
			try{ // trap this 
				myBytes2 = it.getBytesFromSerializable(className);
			}catch (Exception ee){};
						
			if(myBytes2 != null){
				myDestBytes = new byte[myBytes1.length + myBytes2.length];
			}else{
				myDestBytes = new byte[myBytes1.length];
			}
			System.arraycopy(myBytes1, 0, myDestBytes, 0, myBytes1.length);
			if(myBytes2 != null){
				System.arraycopy(myBytes2, 0, myDestBytes, myBytes1.length, myBytes2.length);
			}
			Log.d(MYTAG,"getClassBytes, byte size: "+myDestBytes.length);
		} catch (Exception e){			
//			Log.w(MYTAG,"getClassBytes, classname: "+className+" can't be identified, message: "+e.getMessage());
			throw(e);
		} finally{
			
			return myDestBytes;
		}	
	}
	
	static public byte[] getAPKBytes(String APKPath)throws Exception{
		String entityName = null;
		String message = "null";
		IOUtils it = new IOUtils(); 
				
		byte[] myData = it.getContentBytesFromProc(APKPath);		
		Log.d(MYTAG,"getAPKBytes, byte size: "+myData.length);
		return myData;
	}

}
