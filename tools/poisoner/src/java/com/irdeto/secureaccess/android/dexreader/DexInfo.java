package com.irdeto.secureaccess.android.dexreader;

public class DexInfo {
	
	final String DEX_POISON_WHOLE_METHOD="DEX_POISON_WHOLE_METHOD";
	static final String DISPLAY_VERBOSE="VERBOSE";
	String className = null;
	String methodName = null;
	int registerSize = 0;
	int inArgsSize = 0;
	int outSize = 0;
	int triesSize = 0;
	boolean isWholeMethodInst = true;	
	String opcode = null;
	
	public DexInfo(){		
	
	}
	
	public DexInfo(String cn, String mn){
		this();
		this.className = cn;
		this.methodName = mn;		
	}
	
	private void setIsWholeMethod(boolean flag){
		isWholeMethodInst = flag;
	}
	public void setOpcode(int op ){
		if(op == 0xFFFFFFFF ){
			opcode="";
			return;
		}
		opcode = String.format("0x%x", op);
	}
	public void setClassName(String cn){
		className = cn;
	}
	public void setMethodName(String mn){
		methodName = mn;
	}
	public void setRegisterSize(int size){
		registerSize = size;
	}
	public void setInArgsSize(int size){
		inArgsSize = size;
	}
	public void setOutSize(int size){
		outSize = size;
	}
	public void setTriesSize(int size){
		triesSize = size;
	}
	
	public String getClassName(){
		return convertDotClassname(className);
	}
	public String getMethodName(){
		return methodName;
	}
	public int getRegisterSize(){
		return registerSize;
	}
	public int getInArgsSize(){
		return inArgsSize;
	}
	public int getOutSize(){
		return outSize;
	}
	public int getTriesSize(){
		return triesSize;
	}
	public String getOpcode(){
		return opcode;
	}
	public String convertDotClassname(String inClassName){		
		//Remove leading 'L' and trailing ';'
		String className = inClassName.substring(1, inClassName.lastIndexOf(59));
		className = className.replace('/', '.');				
		return className;
	}
}
