package com.irdeto.secureaccess;


import java.security.MessageDigest;
import java.io.Serializable;
import java.security.SignatureException;
import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;
import java.util.ArrayList;
import java.util.zip.*;
import java.util.*;
import java.io.*;

import android.util.Log;

import com.irdeto.secureaccess.common.HexUtils;
import com.irdeto.secureaccess.common.IOUtils;
import com.irdeto.secureaccess.common.Tools;

/**
 * To provide cryptographic service.
 * @author test
 *
 */
final public class CryptoManager {
	
	static String MYTAG = "CryptoManager";	
	static final String HMAC_SIGNATURE = "signature";
	static long cumulatedTime =0;
	String storePath = null; 
	String keyHandle = null;
	
	static {
		try{
			System.loadLibrary("javasign");
		} catch (java.lang.UnsatisfiedLinkError e){
			Log.w(MYTAG,"STATIC block, Failed to load library, message "+e.getMessage());			
		}		
	}
	public native String getHmacShaSignature(byte[] inputBytes, String storePath, String keyHandle, String SHAType);
	
	public CryptoManager(){		
	}
	public CryptoManager(String storePath, String keyHandle){
		this.storePath = storePath;
		this.keyHandle = keyHandle;
	}
	public String SHA1(byte[] inputBytes) throws Exception  {
		MessageDigest md;
		md = MessageDigest.getInstance("SHA-1");
		byte[] sha1hash = new byte[40];
		md.update(inputBytes, 0, inputBytes.length);
		sha1hash = md.digest();
		return String.valueOf(HexUtils.bytesToHex(sha1hash));
    }
    	
	public String getAPKDigitalSignatureFromCAT(String APKPath)throws Exception{
		String entityName = null;
		String message = "null";
		IOUtils it = new IOUtils(); 
				
		Tools.getTimeData(0, false,"");
		byte[] myData = it.getContentBytesFromZipFile(APKPath);
		Tools.getTimeData(0, true,"decommpress time");
		Tools.getTimeData(0, false,"");
					
		String hash = getHmacShaSignature(myData, storePath, keyHandle, null);
		Tools.getTimeData(0,true,"hash time");
		Tools.getTimeData(0, false,"");
		entityName = APKPath.substring(APKPath.lastIndexOf('/')+1, APKPath.length());		
		message = buildSigningOutputMessageForAPK(entityName, hash);
		Tools.getTimeData(0, true,"The rest of APK time");
		return message;
	}
	
	public String getDigitalSignatureFromCAT(String className, boolean isStub) throws Exception {
		
		byte[] myBytes2 = null;
		byte[] myDestBytes = null;
		String message = "null";
		IOUtils it = new IOUtils(); 
		Tools.getTimeData(0, false,"");
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
			String hash = getHmacShaSignature(myDestBytes, storePath, keyHandle, null);			
			if(isStub){
				message = buildSigningOutputMessageForStub(className, hash);
			}else{
				message = buildSigningOutputMessage(className, hash);
			}											
			Log.d(MYTAG,"getDigitalSignatureFromCAT, classname: "+className+", hash value: "+hash+", total bytes : "+ myDestBytes.length);
		} catch (Exception e){			
						throw(e);
		} finally{
			cumulatedTime += Tools.getTimeData(0, true,"Regular digital time consumption");
			Log.d(MYTAG, "Cumulated time: "+cumulatedTime);
			return message;
		}		
	}	
	static private  String buildSigningOutputMessageForAPK(String entityName, String hash){
		StringBuffer buf = new StringBuffer();
		buf.append("APKName: "+entityName+"\n");
		buf.append(HMAC_SIGNATURE+": "+hash);
		return buf.toString();
	}
	static private  String buildSigningOutputMessage(String entityName, String hash){
		
		StringBuffer buf = new StringBuffer();
		buf.append("Name: "+entityName+"\n");
		buf.append(HMAC_SIGNATURE+": "+hash);
		return buf.toString();
	}
	static private  String buildSigningOutputMessageForStub(String entityName, String hash){
		
		StringBuffer buf = new StringBuffer();
		buf.append("StubName: "+entityName+"\n");
		buf.append(HMAC_SIGNATURE+": "+hash);
		return buf.toString();
	}
}
