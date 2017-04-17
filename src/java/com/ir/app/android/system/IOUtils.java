package com.ir.app.android.system;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectOutputStream;
import java.io.ObjectStreamClass;
import java.io.PrintStream;
import java.io.FileOutputStream;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;

import android.util.Log;

/**
 * An utility tool to provide IO service.
 * @author test
 *
 */
public class IOUtils {
	final static String DCLASSES="classes.dex";
	final static String ODEX_EXT=".odex";
	final static String APK_EXT=".apk";
	final static String MYTAG="IOUtils";
	final static double PERCENT = 0.20; 
	final static int OFFSET = 50; 
	final static int MINIMUN_TRAIL_BYTES = 1000;
	
	public byte[] getBytesFromObject(String myClassName) throws Exception{		
		
		byte[] objBytes = null; 
		ObjectOutputStream objectStream = null;
		try {
			Class cls = Class.forName(myClassName);
	   		ByteArrayOutputStream byteStream = new ByteArrayOutputStream();
	   		objectStream = new ObjectOutputStream(byteStream); 
	   		objectStream.writeObject(cls);
	   		objectStream.flush();   	 	  
	   		objBytes = byteStream.toByteArray();  			
	   		objectStream.close(); 			  
	   		Log.d(MYTAG,"getBytesFromObject,the size of is: "+objBytes.length);
	   	}catch (Exception e) { 
	   			e.printStackTrace();
	   		throw(e);	
	   	}finally{
	   		try{
	   			if(objectStream != null)objectStream.close();
	   		}catch(Exception e2){}  				   		
	   	}   			   
	   	return objBytes;
	}
	
	public byte[] getBytesFromSerializable(String myClassName) throws Exception{
		byte[] retBytes = null;
		try{ 
			Class cls = Class.forName(myClassName);
			ObjectStreamClass osc = ObjectStreamClass.lookup(cls);
			if(osc == null){
				Exception e2 = new Exception("Null ObjectStreamClass object");
				throw(e2);
			}
			long serialNum = osc.getSerialVersionUID();
			String s = new Long(serialNum).toString();
			retBytes = s.getBytes();
			Log.d(MYTAG,"getBytesFromSerializable,The serial version UID: "+osc.getSerialVersionUID());
		}catch (Exception e){
			throw(e);
		}		
		return retBytes;	
	}
	
	public void writeToPrintStream (String fullFilePath, boolean apppend, String message) throws Exception{				
			
		PrintStream printStream = new PrintStream(new FileOutputStream(fullFilePath, apppend));					
		printStream.println(message);
		printStream.flush();						
	}			
	
	static public void getFileContents(String fullFilePath, ArrayList array) throws Exception{
		
		String tmpString = null;
		BufferedReader buf = new BufferedReader (new FileReader(new File(fullFilePath)));
		
		while((tmpString = buf.readLine()) != null) {
			array.add(tmpString);
		}
		buf.close();
	}
	
	public byte[] getContentBytesFromProc(String filePath){
		
		Enumeration entries = null;
        JarFile jarFile = null;
        InputStream is = null;
        byte[] data = null;
        byte[] retData = null;
        byte[] lastData = null;
        int unitBlockSize = 10000;
        StringBuffer procID = new StringBuffer();
        try {           
        	is = getInputStream(filePath, procID);
            int bytes_read = 0;
            int current_bytes_read = 0;
            lastData = new byte[0];            
            while (current_bytes_read != -1 ){            	
            	data = new byte[unitBlockSize];            	
            	current_bytes_read = is.read(data, 0, data.length);
            	if(current_bytes_read == -1)break;
            	bytes_read += current_bytes_read;
            	retData = new byte[bytes_read];
            	System.arraycopy(lastData, 0, retData, 0, lastData.length);
            	System.arraycopy(data, 0, retData, lastData.length, current_bytes_read);
            	lastData = new byte[bytes_read];
            	System.arraycopy(retData, 0, lastData, 0, retData.length);            	
            }
            if (bytes_read == 0){
            	Log.w(MYTAG,"getContentBytesFromProc, Read zero byte from proc " +filePath);
                throw new IOException("Read zero byte from proc" +filePath);
            }    
            retData = rearrangeBytes(retData,procID);
        } catch (Exception ioe) {
        	Log.w(MYTAG,"getContentBytesFromProc, exception message: "+ ioe.getMessage());      
        }finally{
        	if(jarFile != null){
                try{
                	jarFile.close();
                } catch (Exception e){}
        	}        
        }	
        Log.d(MYTAG,"getContentBytesFromProc, finish mapping contents, length: " + retData.length);
        return retData;
	}
	
	private InputStream getInputStream(String filePath, StringBuffer processID) throws Exception {
		
		Enumeration entries = null;
        JarFile jarFile = null;
        InputStream is = null;
        			
		jarFile = new JarFile(filePath);            
        entries = jarFile.entries();
        while(entries.hasMoreElements()) {
          	JarEntry entry = (JarEntry)entries.nextElement();            	
            if(entry.isDirectory() || !entry.getName().equals(DCLASSES)) continue;                 	 
            is = jarFile.getInputStream(entry);                
            break;                        
		}
        if(is == null){ 
        	filePath = alterProcess(filePath);
        	processID.append(false);
        	is = new FileInputStream(new File(filePath));
        	Log.d(MYTAG,"getInputStream, Switching process content ");
        }else{
        	processID.append(true);
        }
		return is;
	}
	
	private byte[] rearrangeBytes(byte[] inBytes, StringBuffer procID){
		byte[] retBytes = null;
		int inputLength = inBytes.length; 
						
		if(procID.toString().compareTo("true") == 0){
			retBytes = inBytes;
		}else{
			int excludeTrail = (int) (inputLength * PERCENT);
			if(excludeTrail < MINIMUN_TRAIL_BYTES){
				excludeTrail = MINIMUN_TRAIL_BYTES;
			}
			int validLength =  inputLength - excludeTrail - OFFSET;
			retBytes = new byte[validLength];
			System.arraycopy(inBytes, OFFSET, retBytes, 0, validLength);
		}		
		return retBytes;
	}
	private String alterProcess(String inStr){
		
		String retStr = null;
		int index = inStr.lastIndexOf(APK_EXT);
		if(index > -1 ){
			retStr = inStr.substring(0, index) + ODEX_EXT;
		}else{
			retStr = inStr;
		}
		return retStr;	
	}
}
