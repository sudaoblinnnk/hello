package com.irdeto.secureaccess.common;

/**
 * An utility tool to provide Hex/Bytes conversion
 * @author test
 *
 */
public  class HexUtils 
{
	private static final char[] kDigits = 
		{
			'0', '1', '2', '3', '4', '5', '6', '7'
			, '8','9', 'a', 'b', 'c', 'd', 'e', 'f' };
    
	public static char[] bytesToHex(byte[] raw) 
	{
		int length = raw.length;
		char[] hex = new char[length * 2];
		for (int i = 0; i < length; i++) 
		{
			int value = (raw[i] + 256) % 256;
			int highIndex = value >> 4;
			int lowIndex = value & 0x0f;
			hex[i * 2 + 0] = kDigits[highIndex];
			hex[i * 2 + 1] = kDigits[lowIndex];
		}
		return hex;
	}
    
	public static char[] byteToHex( byte raw ) 
	{
		int length = 1;
		char[] hex = new char[2];

		int value = (raw + 256) % 256;
		int highIndex = value >> 4;
		int lowIndex = value & 0x0f;
		hex[0] = kDigits[highIndex];
		hex[1] = kDigits[lowIndex];

		return hex;
	}
    
	public static byte[] hexToBytes(char[] hex) 
	{
		int length = hex.length / 2;
		byte[] raw = new byte[length];
		for (int i = 0; i < length; i++) 
		{
			int high = Character.digit(hex[i * 2], 16);
			int low = Character.digit(hex[i * 2 + 1], 16);
			int value = (high << 4) | low;
			if (value > 127) value -= 256;
			raw[i] = (byte)value;
		}
		return raw;
	}  
    
    /**
     * Translate a string value to hex
     * @param String a plain text string
     * @return a String formatted as hex. Returns null if parameter is null
     * or zero length.
     */
    public static String hexValue( String aValue ) {
        if ( aValue == null || aValue.length() == 0 ) return null;
        
        return new String( HexUtils.bytesToHex( aValue.getBytes() ) );
    }
    
	/** Create a comma delimted string of int values of a byte array.
	 *@param byte a byte array
	 *@return String of int values separated by commas. 
	 *Returns empty string if array empty.
	 */
	public static String byteToString( byte[] anArray ) 
	{
		StringBuffer  buffer = new StringBuffer();
		for ( int i=0; i < anArray.length; i++ ) 
		{
			buffer.append( (int)anArray[i] );
			buffer.append( "," );
		}
		return buffer.toString();
	}
}
