package com.ir.app.common;

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
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;
import java.util.zip.ZipFile;

import com.ir.app.common.HexUtils;

import android.util.Log;

/**
 * An utility tool to provide IO service.
 * @author test
 *
 */
public class IOUtils implements Serializable{
	
	final static String DCLASSES="classes.dex";
	final static String ODEX_EXT=".odex";
	final static String APK_EXT=".apk";
	final static String MYTAG="IOUtils";
	final static double PERCENT = 0.20; 
	final static int OFFSET = 50; 
	final static int MINIMUN_TRAIL_BYTES = 1000;

    public int bytes_read = 0;
    public int iteration = 0;
    public static InputStream is_handle;
    public static JarFile jarFileHandle;
    public static StringBuffer procBytesID = new StringBuffer();

	
	public byte[] getBytesFromObject(String myClassName) throws Exception{		
		
		byte[] objBytes = null; 
		ObjectOutputStream objectStream = null;
		try {
			//Class cls = Class.forName(myClassName, false, Thread.currentThread().getContextClassLoader());
			Class cls = Class.forName(myClassName);
	   		ByteArrayOutputStream byteStream = new ByteArrayOutputStream();
	   		objectStream = new ObjectOutputStream(byteStream); 
	   		objectStream.writeObject(cls);
	   		objectStream.flush();   	 	  
	   		objBytes = byteStream.toByteArray();  			
	   		objectStream.close(); 			  
	   	//	Log.d(MYTAG,"getBytesFromObject,the size of is: "+objBytes.length);
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
		//	Log.d(MYTAG,"getBytesFromSerializable,The serial version UID: "+osc.getSerialVersionUID());
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


    public byte[] getContentBytesFromProc(String filePath)
    {
        byte[] data = null;
        byte[] retData = null;
        int unitBlockSize = 100000;
        int current_bytes_read = 0;
        try
        {
            if(iteration == 0)
            {
       //         Log.w(MYTAG," getInputStream ");
                is_handle = getInputStream(filePath, procBytesID);
            }

            /*Define the array of length 40000*/
            data = new byte[unitBlockSize];
            iteration++;
            current_bytes_read = is_handle.read(data, 0, data.length);

            /* Break if exhausted*/
            if(current_bytes_read == -1) {
                bytes_read = 0;
                iteration = 0;
                data =  null;
     //           Log.w(MYTAG," reset the iteration var - " + iteration);

                if(jarFileHandle != null){
                    jarFileHandle.close();
                }

                if(is_handle != null)
                    is_handle.close();

                return data;
            }

            retData = new byte[current_bytes_read];
            System.arraycopy(data, 0, retData, 0, current_bytes_read);
            bytes_read += current_bytes_read;			

            if (bytes_read == 0){
                Log.w(MYTAG,"getContentBytesFromProc, Read zero byte from proc " +filePath);
                throw new IOException("Read zero byte from proc" +filePath);
            }

	        //retData = rearrangeBytes(retData,procBytesID);
        } catch (Exception ioe) {
            Log.w(MYTAG,"getContentBytesFromProc, exception message: "+ ioe.getMessage());
        }

        //Log.d(MYTAG,"getContentBytesFromProc, finish mapping contents, length: " + retData.length);
        return retData;
    }
	
	private InputStream getInputStream(String filePath, StringBuffer processID) throws Exception {
		
		Enumeration entries = null;
        JarFile jarFile = null;
        InputStream is = null;	
		
        jarFile = new JarFile(filePath);   		
      	JarEntry entry = (JarEntry)jarFile.getEntry(DCLASSES);
        is = jarFile.getInputStream(entry);              		
        
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
