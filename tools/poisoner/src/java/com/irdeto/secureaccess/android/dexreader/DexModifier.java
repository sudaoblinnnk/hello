package com.irdeto.secureaccess.android.dexreader;

import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import java.util.logging.Logger;


import com.googlecode.dex2jar.DexException;
import com.googlecode.dex2jar.reader.DexFileReader;
import com.googlecode.dex2jar.reader.io.BeArrayDataIn;
import com.googlecode.dex2jar.reader.io.DataIn;
import com.googlecode.dex2jar.reader.io.LeArrayDataIn;
import com.googlecode.dex2jar.reader.io.OffsetedDataIn;

public class DexModifier  {

	private static final byte[] DEX_FILE_MAGIC = new byte[] { 0x64, 0x65, 0x78 };
    private static final byte[] ODEX_FILE_MAGIC = new byte[] { 0x64, 0x65, 0x79 };
    private static final byte[] VERSION_035 = new byte[] { 0x30, 0x33, 0x35 };
    private static final byte[] VERSION_036 = new byte[] { 0x30, 0x33, 0x36 };
    protected static final int DEFAULT_API_LEVEL = 13;
    final int ENDIAN_CONSTANT = 0x12345678;
    final int REVERSE_ENDIAN_CONSTANT = 0x78563412;
    byte OP_NOP_REAL_BYTE = 0x00;
    
    protected int class_defs_off;
    protected int class_defs_size;
    protected int field_ids_off;
    protected int field_ids_size;
    
    protected int method_ids_off;
    protected int method_ids_size;
    protected int proto_ids_off;
    protected int proto_ids_size;
    protected int string_ids_off;
    protected int string_ids_size;
    protected int type_ids_off;
    protected int type_ids_size;
    protected boolean odex;
    protected DataIn odex_in;
    protected int odex_depsOffset;
    protected int apiLevel = DEFAULT_API_LEVEL;
    static boolean  isLittleEndian = true;    
    DexWriter dexWriter = null;
    DataIn in;
    byte[] inData = null;
	static String outputFileName= null;
	
	int pos1 = 5886; //opcode: 112
	int pos2 = 5892; //opcode: 14
	
	
	public void initInStream() {
		
        in.move(0);
        byte[] magic = in.readBytes(3);

        if (Arrays.equals(magic, DEX_FILE_MAGIC)) {
            odex = false;
        } else if (Arrays.equals(magic, ODEX_FILE_MAGIC)) {
            odex = true;
            odex_in = in;
        } else {
            throw new DexException("not support magic.");
        }
        in.skip(1);// 0x0A
        byte[] version = in.readBytes(3);
        if (!Arrays.equals(version, VERSION_035) && !Arrays.equals(version, VERSION_036)) {
            throw new DexException("not support version.");
        }
        in.skip(1);// 0x00

        System.out.println("After initial header section, the position: "+in.getCurrentPosition());
        // skip uint checksum
        // and 20 bytes signature
        // and uint file_size
        // and uint header_size 0x70
        in.skip(4 + 20 + 4 + 4);       
        
        int endian_tag = in.readUIntx();
        if (endian_tag != ENDIAN_CONSTANT) {
            throw new DexException("not support endian_tag");
        }
        System.out.println("The endian_tag: "+endian_tag);
        
        this.in = in;
        // skip uint link_size
        // and uint link_off
        // and uint map_off
        in.skip(4 + 4 + 4);

        string_ids_size = in.readUIntx();
        string_ids_off = in.readUIntx();
        type_ids_size = in.readUIntx();
        type_ids_off = in.readUIntx();
        proto_ids_size = in.readUIntx();
        proto_ids_off = in.readUIntx();
        field_ids_size = in.readUIntx();
        field_ids_off = in.readUIntx();
        method_ids_size = in.readUIntx();
        method_ids_off = in.readUIntx();
        class_defs_size = in.readUIntx();
        class_defs_off = in.readUIntx();
        // skip uint data_size data_off
        System.out.println("After header, the position: "+in.getCurrentPosition());
    }
	
	
	private DataIn opDataIn(byte[] data) {
        try {
            if (isLittleEndian) {
                return new LeArrayDataIn(data);
            } else {
                return new BeArrayDataIn(data);
            }
        } catch (RuntimeException e) {
            throw e;
        } catch (Exception e) {
            throw new DexException(e);
        }
	}    
	private void writeData(byte[] data) throws Exception{
		
		int length;		
		byte[] myData = dexWriter.getData();
		byte[] myData2 ={1,2,3,4};
		dexWriter.write(myData2);	
		myData = dexWriter.getData();
		dexWriter.write(myData2);		
		myData = dexWriter.getData();
		length = dexWriter.getLength();
		int test = in.readUIntx();
		myData2 = new byte[]{5,6};		
		dexWriter.write(myData2);
		myData = dexWriter.getData();
		length = dexWriter.getLength();
		in.skip(2);
		myData2 = new byte[]{7,8};		
		dexWriter.write(myData2);
		myData = dexWriter.getData();
		length = dexWriter.getLength();
		
		dexWriter.saveToFiles();
		
	}	
	public void doFile(File srcDex, File destFile) throws Exception {
		inData = DexFileScanner.readDex(srcDex);
		in = opDataIn(inData);		
		initInStream();			
		dexWriter = new DexWriter(in, inData);
	}	
	public static void main(String... args) throws Exception {
		 if (args.length < 2) {	          
            System.out.println("Input: dex OR apk,  Output: destFile");
            return;
		 }
		 outputFileName = args[1];
		 DexModifier dm = new DexModifier();
		 dm.doFile(new File(args[0]), new File(args[1]));
		 dm.writeData(null);
    }
}
