package com.irdeto.secureaccess.android.dexreader;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.FileWriter;
import java.io.OutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.lang.StringBuffer;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Hashtable;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.zip.Adler32;

import com.googlecode.dex2jar.reader.io.DataIn;
//import com.sun.org.apache.xalan.internal.xsltc.runtime.Hashtable;


public class DexWriter {

	final String INDEX_FILE_PATH = "IndexFilePath";
	final String BYTECODE_FILE_PATH = "BytecodeFilePath";
	final String POISONED_FILE_PATH = "PoinsonedFilePath";
	final int OFFSET_CHECKSUM = 8;
	final int OFFSET_DATA_FOR_HASH = 12;
	final int SIZE_CHECKSUM = 4;
	DataIn in = null;
	byte outData[] = null;
	int dataLen = 0;
	int bytecodeOffset = 0;
	String dexFileName="poisoned.dex";
	String indexFileName = "index.txt";
	String bytecodeFileName = "bytecode.dat";;
	DexInfo dexInfo = null;
	DexConfigure dexConfig = null;
	
	ArrayList indexList = new ArrayList();
	ArrayList dataList = new ArrayList();
	
	public DexWriter(DataIn in, byte[] inData){		
		this.in = in;		
		this.dataLen = inData.length;		
		this.outData = new byte[dataLen];		
		init(inData);				
	}	
	void init(byte[] inData){
		System.arraycopy(inData, 0, outData, 0, dataLen);
		String macro = System.getProperty(INDEX_FILE_PATH);
		if(macro != null){
			this.indexFileName = macro;
		}
		macro = System.getProperty(BYTECODE_FILE_PATH);
		if(macro != null){
			this.bytecodeFileName = macro;
		}
		macro = System.getProperty(POISONED_FILE_PATH);
		if(macro != null){
			this.dexFileName = macro;
		}
//		testChecksum(inData);
	}
	public void write(byte[] data){
				
		System.arraycopy(data, 0, outData, in.getCurrentPosition(), data.length);	
		trackIndex(data, in.getCurrentPosition(), data.length);
	}
	public void write(byte[] data, int length, int outPos){
				
		trackIndex(outData, outPos, length);
		System.arraycopy(data, 0, outData, outPos, length);
						
	}	
	public void write(byte data, int length, int outPos){
		if(dexInfo == null){
			System.out.println("Null DexInfo!!");
			return;
		}			
		if(!dexConfig.isIllegibleMethod(dexInfo.getClassName(), dexInfo.getMethodName())){
			DexConfigure.displayMessage("No entry for: "+dexInfo.getClassName()+" and "+dexInfo.getMethodName());
			return;
		}else{
			DexConfigure.displayMessage("Found entry for: "+dexInfo.getClassName()+" and "+dexInfo.getMethodName());
		}
		trackIndex(outData, outPos, length);
		Arrays.fill(outData, outPos, outPos + length, data);						
	}	
	
	void trackIndex(byte[] data, int dexOffset, int copyLength){		
		
		String opcodeStr ="";
		Hashtable indexHashTable = new Hashtable();
		
		if(!dexConfig.isWholeMethodInst){
			opcodeStr = dexInfo.getOpcode();
		}
			
		indexHashTable.put("bytecodeoffset", bytecodeOffset);
		indexHashTable.put("bytecodelen", copyLength);
		indexHashTable.put("fileindex", 0);
		indexHashTable.put("dexoffset", dexOffset);
//		System.out.printf("%d,  %d, %d \n", bytecodeOffset, copyLength, dexOffset);
//		indexHashTable.put("dexlen", copyLength);
		indexHashTable.put("registersize", dexInfo.getRegisterSize());
		indexHashTable.put("inssize", dexInfo.getInArgsSize());
		indexHashTable.put("outsize", dexInfo.getOutSize());
		indexHashTable.put("triessize", dexInfo.getTriesSize());
		indexHashTable.put("instruction", opcodeStr);
		indexHashTable.put("classname", dexInfo.getClassName());
		indexHashTable.put("methodname", dexInfo.getMethodName());
		indexList.add(indexHashTable);
		
		byte storeData[] = new byte[copyLength];
		System.arraycopy(outData, dexOffset, storeData, 0, copyLength);
		ByteBuffer buffer = ByteBuffer.wrap(storeData);
		byte[] testData = buffer.array();
		dataList.add(buffer);
		bytecodeOffset += copyLength;		
	}
	
	public void genChecksum(){
		byte[] data = new byte[4];
		Adler32 adler32 = new Adler32();
		adler32.update(outData, OFFSET_DATA_FOR_HASH, outData.length-OFFSET_DATA_FOR_HASH);
		int hashValue = (int)adler32.getValue();		
		data = int2BytesLe(hashValue, SIZE_CHECKSUM);
		System.arraycopy(data, 0, outData, OFFSET_CHECKSUM, SIZE_CHECKSUM);
		validateBytes(hashValue);
	}
	void testChecksum(byte[] data){
		Adler32 adler32 = new Adler32();
		adler32.update(data, OFFSET_DATA_FOR_HASH, data.length-OFFSET_DATA_FOR_HASH);
		int hashValue = (int)adler32.getValue();		
	}
	public static byte[] int2Bytes(int input, int size){
		byte[] bytes = ByteBuffer.allocate(size).putInt(input).array();
		return bytes;
	}
	
	public static byte[] int2BytesLe(int input, int size){
		
		int revesred = Integer.reverseBytes(input);				
		byte[] bytes = ByteBuffer.allocate(size).putInt(revesred).array();	
		byte[] tmpBytes = ByteBuffer.allocate(size).putInt(input).array();		
		String testStr = String.format("0x%x 0x%x 0x%x 0x%x",bytes[0],bytes[1],bytes[2],bytes[3]);
		return bytes;
	}	
	public void validateBytes(int originalData){
		byte[] data = new byte[4]; 
		System.arraycopy(outData, OFFSET_CHECKSUM, data, 0, SIZE_CHECKSUM);
		int b1 = (int) 0x000000FF & data[0];
    	int b2 = (int) 0x000000FF & data[1];
    	int b3 = (int) 0x000000FF & data[2];
    	int b4 = (int) 0x000000FF & data[3];    	
    	long result = b1 | b2 << 8 | b3 << 16 | b4 << 24;
    	if( result != originalData){
    		System.out.println("Error in data conversion");
    	}            
	}
	public byte[] getData(){
		return outData;
	}
	public int getLength(){
		return dataLen;
	}

	//covert the java 32 bit data as little endian format because the arem cpu used the little endia
    int to32LittleEndian(int bigEndianData){
        int b4 = bigEndianData & 0x000000ff;
        b4 <<= 24;
        int b3 = bigEndianData & 0x0000ff00;
        b3 <<= 8;
        bigEndianData >>= 8;
        int b2 = bigEndianData & 0x0000ff00;
        bigEndianData >>= 16;
        int b1 = 0x000000ff & bigEndianData;
        int result = (int) (b4 | b3 | b2 | b1);
        return result;
    }
	
	public void saveToFiles() throws Exception {
		
		FileOutputStream fout= new FileOutputStream(new File(dexFileName));
		fout.write(outData);
		fout.flush();
		fout.close();
		
		fout= new FileOutputStream(new File(bytecodeFileName));
		for(int pos =0; pos < dataList.size(); pos++){
			ByteBuffer buffer  = (ByteBuffer)(dataList.get(pos));
			byte[] data = buffer.array();
			fout.write(data);
		}			
		fout.flush();
		fout.close();
		
		//write the index information to index.txt
		DataOutputStream  indexDOS= new DataOutputStream(new FileOutputStream(indexFileName));		
		Hashtable indexHashTable = null;
		int listSize = indexList.size();
		System.out.printf("the size = %d\n", listSize);
		indexDOS.writeInt(to32LittleEndian(listSize));
		
		for(int pos =0; pos < indexList.size(); pos++ ){
			indexHashTable = (Hashtable)indexList.get(pos);
			int byteCodeOffSet = (Integer)indexHashTable.get("bytecodeoffset");
			int byteCodeLen = (Integer)indexHashTable.get("bytecodelen");
			int fileIndex = (Integer)indexHashTable.get("fileindex");
			int dexOffSet = (Integer)indexHashTable.get("dexoffset"); 
			int registerSize = (Integer)indexHashTable.get("registersize");
			int insSize = (Integer)indexHashTable.get("inssize");
			int outSize = (Integer)indexHashTable.get("outsize");
			int triesSize = (Integer)indexHashTable.get("triessize");
            indexDOS.writeInt(to32LittleEndian(byteCodeOffSet));
            indexDOS.writeInt(to32LittleEndian(byteCodeLen));
			indexDOS.writeInt(to32LittleEndian(fileIndex));
            indexDOS.writeInt(to32LittleEndian(dexOffSet));
			indexDOS.writeInt(to32LittleEndian(registerSize));
			indexDOS.writeInt(to32LittleEndian(insSize));
			indexDOS.writeInt(to32LittleEndian(outSize));
			indexDOS.writeInt(to32LittleEndian(triesSize));
			//below is to wrthe the instruction, class name and method name's pointer
            indexDOS.writeInt(0);
            indexDOS.writeInt(0);
			indexDOS.writeInt(0);        }   		
	
		for(int pos =0; pos < indexList.size(); pos++ ){ 
			indexHashTable = (Hashtable)indexList.get(pos);			
			String classname = (String)indexHashTable.get("classname");
            String methodname = (String)indexHashTable.get("methodname");
            if(pos < (indexList.size() - 1))
            {
            indexDOS.write((classname + " " + methodname + " ").getBytes());           
            }
            else
            {
            	indexDOS.write((classname + " " + methodname).getBytes());
            }
        }  

		indexDOS.flush();
		indexDOS.close();		
	}
	
	public DexInfo getDexInfo(){
		return dexInfo;
	}
	
	public void setDexInfo(DexInfo di){
		dexInfo = di;
	}
	public void setDexConfig(DexConfigure dc){
		dexConfig = dc;
	}
}
