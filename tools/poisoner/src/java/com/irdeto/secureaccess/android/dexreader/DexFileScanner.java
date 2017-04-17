package com.irdeto.secureaccess.android.dexreader;

import java.util.HashMap;
import java.util.Map;

import com.googlecode.dex2jar.DexException;
import com.googlecode.dex2jar.DexOpcodes;
import com.googlecode.dex2jar.Field;
import com.googlecode.dex2jar.Method;
import com.googlecode.dex2jar.reader.Constant;
import com.googlecode.dex2jar.reader.DexAnnotationReader;
import com.googlecode.dex2jar.reader.DexFileReader;
import com.googlecode.dex2jar.reader.DexCodeReader;
import com.googlecode.dex2jar.reader.io.*;
import com.googlecode.dex2jar.visitors.DexAnnotationAble;
import com.googlecode.dex2jar.visitors.DexClassVisitor;
import com.googlecode.dex2jar.visitors.DexCodeVisitor;
import com.googlecode.dex2jar.visitors.DexFieldVisitor;
import com.googlecode.dex2jar.visitors.DexFileVisitor;
import com.googlecode.dex2jar.visitors.DexMethodVisitor;
import com.googlecode.dex2jar.visitors.OdexFileVisitor;
 
public class DexFileScanner extends DexFileReader{
	
	DexWriter dexWriter;
	DexInfo dexInfo;
	DexConfigure dexConfig;
	
	public DexFileScanner(DataIn in) {
		super(in);
	}
	public DexFileScanner(byte[] data) {
        super(data);        
        dexWriter = new DexWriter(in, data);
    }
	public DexFileScanner(byte[] data, DexConfigure dexConfig) {
		super(data);     
		this.dexConfig = dexConfig;
        this.dexWriter = new DexWriter(in, data);
        dexWriter.setDexConfig(dexConfig);
    }
	public DexFileScanner(byte[] data, DexWriter dexWriter) {
        super(data);
        this.dexWriter = dexWriter;
    }
	DataIn getInStream(){
		return in;
	}
	protected void acceptClass(DexFileVisitor dv, DexClassVisitor dcv, String className, int config) {
        DataIn in = this.in;
        int source_file_idx = in.readUIntx();
        if ((config & SKIP_DEBUG) == 0) {           
            if (source_file_idx != -1) {
                dcv.visitSource(this.getString(source_file_idx));
            }
        }
        dexInfo = new DexInfo();        
        dexInfo.setClassName(className);
        
        int annotations_off = in.readUIntx();
        Map<Integer, Integer> fieldAnnotationPositions;
        Map<Integer, Integer> methodAnnotationPositions;
        Map<Integer, Integer> paramAnnotationPositions;
        if ((config & SKIP_ANNOTATION) == 0) {            
            fieldAnnotationPositions = new HashMap<Integer, Integer>();
            methodAnnotationPositions = new HashMap<Integer, Integer>();
            paramAnnotationPositions = new HashMap<Integer, Integer>();
            if (annotations_off != 0) {
                in.pushMove(annotations_off);
                try {
                    int class_annotations_off = in.readUIntx();
                    if (class_annotations_off != 0) {
                        in.pushMove(class_annotations_off);
                        try {
                            DexAnnotationReader.accept(this, in, dcv);
                        } catch (Exception e) {
                            throw new RuntimeException("error on reading Annotation of class " + className, e);
                        } finally {
                            in.pop();
                        }
                    }
                    int field_annotation_size = in.readUIntx();
                    int method_annotation_size = in.readUIntx();
                    int parameter_annotation_size = in.readUIntx();
                    for (int i = 0; i < field_annotation_size; i++) {
                        int field_idx = in.readUIntx();
                        int field_annotations_offset = in.readUIntx();
                        fieldAnnotationPositions.put(field_idx, field_annotations_offset);
                    }
                    for (int i = 0; i < method_annotation_size; i++) {
                        int method_idx = in.readUIntx();
                        int method_annotation_offset = in.readUIntx();
                        methodAnnotationPositions.put(method_idx, method_annotation_offset);
                    }
                    for (int i = 0; i < parameter_annotation_size; i++) {
                        int method_idx = in.readUIntx();
                        int parameter_annotation_offset = in.readUIntx();
                        paramAnnotationPositions.put(method_idx, parameter_annotation_offset);
                    }
                } finally {
                    in.pop();
                }
            }
        } else {
            fieldAnnotationPositions = null;
            methodAnnotationPositions = null;
            paramAnnotationPositions = null;
        }
        int class_data_off = in.readUIntx();

        int static_values_off = in.readUIntx();

        if (class_data_off != 0) {
            in.pushMove(class_data_off);
            try {
                int static_fields = (int) in.readULeb128();
                int instance_fields = (int) in.readULeb128();
                int direct_methods = (int) in.readULeb128();
                int virtual_methods = (int) in.readULeb128();
                {
                    int lastIndex = 0;
                    {
                        Object[] constant = null;
                        if ((config & SKIP_FIELD_CONSTANT) == 0) {
                            if (static_values_off != 0) {
                                in.pushMove(static_values_off);
                                try {
                                    int size = (int) in.readULeb128();
                                    constant = new Object[size];
                                    for (int i = 0; i < size; i++) {
                                        constant[i] = Constant.ReadConstant(this, in);
                                    }
                                } finally {
                                    in.pop();
                                }
                            }
                        }
                        for (int i = 0; i < static_fields; i++) {
                            Object value = null;
                            if (constant != null && i < constant.length) {
                                value = constant[i];
                            }
                            lastIndex = acceptField(lastIndex, dcv, fieldAnnotationPositions, value, config);
                        }
                    }
                    lastIndex = 0;
                    for (int i = 0; i < instance_fields; i++) {
                        lastIndex = acceptField(lastIndex, dcv, fieldAnnotationPositions, null, config);
                    }
                    lastIndex = 0;
                    for (int i = 0; i < direct_methods; i++) {
                    	DexConfigure.displayMessage("\n[Direct method]");
                        lastIndex = acceptMethod(lastIndex, dcv, methodAnnotationPositions, paramAnnotationPositions,
                                config);
                    }
                    lastIndex = 0;
                    for (int i = 0; i < virtual_methods; i++) {
                    	DexConfigure.displayMessage("\n[Virtual method]");
                        lastIndex = acceptMethod(lastIndex, dcv, methodAnnotationPositions, paramAnnotationPositions,
                                config);
                    }
                }
            } finally {
                in.pop();
            }
        }
        dcv.visitEnd();
	}
	public int acceptMethod(int lastIndex, DexClassVisitor cv, Map<Integer, Integer> methodAnnos,
            Map<Integer, Integer> parameterAnnos, int config) {
        DataIn in = this.in;
        int diff = (int) in.readULeb128();
        int method_access_flags = (int) in.readULeb128();
        int code_off = (int) in.readULeb128();
        int method_id = lastIndex + diff;
        Method method = getMethod(method_id);
        
        String position = String.format("0x%x", in.getCurrentPosition());
        DexConfigure.displayMessage("Method name: "+method.getName()+" and position:"+  position);       
        dexInfo.setMethodName(method.getName());       
        try {
            DexMethodVisitor dmv = cv.visitMethod(method_access_flags, method);
            if (dmv != null) {
                if ((config & SKIP_ANNOTATION) == 0) {
                    Integer annotation_offset = methodAnnos.get(method_id);
                    if (annotation_offset != null) {
                        in.pushMove(annotation_offset);
                        try {
                            DexAnnotationReader.accept(this, in, dmv);
                        } catch (Exception e) {
                            throw new DexException(e, "while accept annotation in method:%s.", method.toString());
                        } finally {
                            in.pop();
                        }
                    }
                    Integer parameter_annotation_offset = parameterAnnos.get(method_id);
                    if (parameter_annotation_offset != null) {
                        in.pushMove(parameter_annotation_offset);
                        try {
                            int sizeJ = in.readUIntx();
                            for (int j = 0; j < sizeJ; j++) {
                                int field_annotation_offset = in.readUIntx();
                                in.pushMove(field_annotation_offset);
                                try {
                                    DexAnnotationAble dpav = dmv.visitParameterAnnotation(j);
                                    if (dpav != null) {
                                        DexAnnotationReader.accept(this, in, dpav);
                                    }
                                } catch (Exception e) {
                                    throw new DexException(e,
                                            "while accept parameter annotation in method:[%s], parameter:[%d]",
                                            method.toString(), j);
                                } finally {
                                    in.pop();
                                }
                            }
                        } finally {
                            in.pop();
                        }
                    }
                }
                if (code_off != 0 && (0 == (SKIP_CODE & config))) {
                    in.pushMove(code_off);
                    try {
                        DexCodeVisitor dcv = dmv.visitCode();
                        if (dcv != null) {
                            try {                            	                               
                            	dexWriter.setDexInfo(dexInfo);
                            	new DexCodeReader(this, in, (0 != (DexOpcodes.ACC_STATIC & method_access_flags)),
                                               method, dexWriter, dexConfig).accept(dcv, config);
                            } catch (Exception e) {
                                throw new DexException(e, "while accept code in method:[%s]", method.toString());
                            }
                        }
                    } finally {
                        in.pop();
                    }
                }
                dmv.visitEnd();
            }
        } catch (Exception e) {
            throw new DexException(e, "while accept method:[%s]", method.toString());
        }

        return method_id;
    }
	public int acceptField(int lastIndex, DexClassVisitor dcv, Map<Integer, Integer> fieldAnnotationPositions,
            Object value, int config) {
        DataIn in = this.in;
        int diff = (int) in.readULeb128();
        int field_id = lastIndex + diff;
        Field field = getField(field_id);
        int field_access_flags = (int) in.readULeb128();
       
        DexFieldVisitor dfv = dcv.visitField(field_access_flags, field, value);
        if (dfv != null) {
            if ((config & SKIP_ANNOTATION) == 0) {
                Integer annotation_offset = fieldAnnotationPositions.get(field_id);
                if (annotation_offset != null) {
                    in.pushMove(annotation_offset);
                    try {
                        DexAnnotationReader.accept(this, in, dfv);
                    } catch (Exception e) {
                        throw new DexException(e, "while accept annotation in field:%s.", field.toString());
                    } finally {
                        in.pop();
                    }
                }
            }
            dfv.visitEnd();
        }       
        return field_id;
    }

	public void accept(DexFileVisitor dv, int config) {
	        if (odex && !apiLevelSetted) {
	            log.warning("read an odex file without setting the apiLevel, use " + DEFAULT_API_LEVEL + " as default.");
	        }	        
	        if (odex && dv instanceof OdexFileVisitor) {
	            DataIn in = this.odex_in;
	            OdexFileVisitor odv = (OdexFileVisitor) dv;
	            in.pushMove(odex_depsOffset);
	            try {
	                in.skip(4 * 3);// skip modificationTime,crc,dalvikBuild
	                int size = in.readIntx();
	                for (int i = 0; i < size; i++) {
	                    int length = in.readIntx();
	                    odv.visitDepedence(new String(in.readBytes(length), 0, length - 1, UTF8), in.readBytes(20));
	                }
	            } finally {
	                in.pop();
	            }
	        }
	        DexConfigure.displayMessage("class defs size: "+class_defs_size);
	        DataIn in = this.in;
	        for (int cid = 0; cid < class_defs_size; cid++) {
	            int idxOffset = this.class_defs_off + cid * 32;
	            in.pushMove(idxOffset);
	            String className = null;
	            try {
	            	DexConfigure.displayMessage("\nClass Def position "+in.getCurrentPosition());
	                className = this.getType(in.readUIntx());
	                DexConfigure.displayMessage("ClassName: "+className);
	                int access_flags = in.readUIntx();
	                int superclass_idx = in.readUIntx();	               
	                String superClassName = superclass_idx == -1 ? null : this.getType(superclass_idx);	  
	                DexConfigure.displayMessage("Super class idx "+ superclass_idx+", name: "+superClassName);
	                String[] interfaceNames = null;
	                {
	                    int interfaces_off = in.readUIntx();
	                    if (interfaces_off != 0) {
	                        in.pushMove(interfaces_off);
	                        try {
	                            int size = in.readUIntx();
	                            interfaceNames = new String[size];
	                            for (int i = 0; i < size; i++) {	                           
	                                interfaceNames[i] = getType(in.readUShortx());	                           
	                            }
	                        } finally {
	                            in.pop();
	                        }
	                    }
	                }
	                DexClassVisitor dcv = dv.visit(access_flags, className, superClassName, interfaceNames);
	                if (dcv != null)
	                {
	                    acceptClass(dv, dcv, className, config);
	                }
	            } finally {
	                in.pop();
	            }
	        }
	        dv.visitEnd();
	        try {
	        	dexWriter.genChecksum();
	        	dexWriter.saveToFiles();
	        } catch(Exception e){
	        	e.printStackTrace();
	        }
	    }		
}
