package com.ir.app.stdvm;

import java.net.URLClassLoader;
import java.net.URL;

public class StdClassLoader extends URLClassLoader {
	
	public StdClassLoader(URL[] repository){
		super(repository);
	}
	
}
