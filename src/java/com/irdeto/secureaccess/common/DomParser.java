package com.irdeto.secureaccess.common;

import java.io.File;
import java.io.InputStream;
import java.io.IOException;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import org.w3c.dom.Document;
import org.xml.sax.SAXException;

public class DomParser {
	
	public DomParser(){
		super();
	}
	/** Use standard J2SE DOM XML parser to parse the data into DOM tree
	 * @param filePath
	 * 
	 */
	public synchronized Document parse(String filePath){
		Document doc = null;
		DocumentBuilderFactory dbf = null;
		DocumentBuilder docb = null;
		try {
			dbf = DocumentBuilderFactory.newInstance();
			docb = dbf.newDocumentBuilder();
			doc = docb.parse(new File(filePath));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (ParserConfigurationException e) {
			e.printStackTrace();
		} catch (SAXException e) {
			e.printStackTrace();
		}
		return doc;
	}
	public synchronized Document parse(InputStream is){
		Document doc = null;
		DocumentBuilderFactory dbf = null;
		DocumentBuilder docb = null;
		try {
			dbf = DocumentBuilderFactory.newInstance();
			docb = dbf.newDocumentBuilder();
			doc = docb.parse(is);
		} catch (IOException e) {
			e.printStackTrace();
		} catch (ParserConfigurationException e) {
			e.printStackTrace();
		} catch (SAXException e) {
			e.printStackTrace();
		}
		return doc;
	}

}
