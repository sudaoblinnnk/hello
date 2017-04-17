package com.irdeto.secureaccess.common;
import android.util.Log;

public class Tools {
	private static long initialTime = 0;
	private static  String MYTAG="Tools";
	
	static public long getTimeData(long startTime, boolean isGetDeltaTime, String message){
		long deltaTime = 0;
		if(isGetDeltaTime){
			deltaTime = System.currentTimeMillis()- initialTime;
			Log.d(MYTAG, message+" Time consumption: "+deltaTime);
			initialTime = 0;
		}else{
			initialTime = System.currentTimeMillis();
		}
		return deltaTime;
		
	}
}
