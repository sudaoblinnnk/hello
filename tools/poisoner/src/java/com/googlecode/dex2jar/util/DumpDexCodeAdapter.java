package com.googlecode.dex2jar.util;

import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.StringTokenizer;

import com.googlecode.dex2jar.DexLabel;
import com.googlecode.dex2jar.Field;
import com.googlecode.dex2jar.Method;
import com.irdeto.secureaccess.android.dexreader.IrdetoDexConvertor;

public class DumpDexCodeAdapter extends AbstractDumpDexCodeAdapter {
	private static class TryCatch {
		public DexLabel end;

		public DexLabel handler;
		public DexLabel start;
		public String type;

		public TryCatch(DexLabel start, DexLabel end, DexLabel handler,
				String type) {
			super();
			this.start = start;
			this.end = end;
			this.handler = handler;
			this.type = type;
		}
	}

	private List<DexLabel> labels = new ArrayList<DexLabel>();

	private Method method;

	private PrintWriter out;

	private List<TryCatch> trys = new ArrayList<TryCatch>();

	private Map<DexLabel, Integer> lines = new HashMap<DexLabel, Integer>();

	private boolean isStatic;

	private int localFieldCounter = 0;
	private int localMethodCounter = 0;
	private int localClassCounter = 0;

	/**
	 * @param dcv
	 */
	public DumpDexCodeAdapter(boolean isStatic, Method m, PrintWriter out) {
		this.method = m;
		this.out = out;
		this.isStatic = isStatic;
	}

	public static final String CONST_OP = "CONST";
	public static final String CONST_STRING_OP = "CONST_STRING";
	public static final String CONST_CLASS_OP = "CONST_CLASS";

	public static final String SGET_OP = "SGET";
	public static final String SPUT_OP = "SPUT";
	public static final String RETURN_OP = "RETURN";
	public static final String RETURN_VOID_OP = "RETURN_VOID";
	public static final String IF_EQZ_OP = "IF_EQZ";
	public static final String INVOKE_SUPER_OP = "INVOKE_SUPER";
	public static final String INVOKE_VIRTUAL_OP = "INVOKE_VIRTUAL";
	public static final String INVOKE_DIRECT_OP = "INVOKE_DIRECT";
	public static final String INVOKE_STATIC_OP = "INVOKE_STATIC";

	public static final String INVALID_REGISTER_NAME = "@invalid_register";

	@Override
	protected void nativeSPUT(String fromOrToReg, String fieldOwner,
			String fieldName, Field field) {
		String className = getClassNameFromclassNameSignature(field.getOwner());

		StringBuilder sb = new StringBuilder();

		String type = getType(field.getType());
		String typeSignature = getTypeSignature(field.getType());

		String localClass = String.format("localClass%d", localClassCounter++);
		sb.append(getFindClass(localClass, className));
		sb.append("\n");

		String fieldId = String.format("fieldId%d", localFieldCounter++);
		sb.append(getFieldID(localClass, fieldId, fieldName, typeSignature,
				true));
		sb.append("\n");

		sb.append(setStaticXXXField(typeSignature, localClass, fieldId,
				getRegister(fromOrToReg).value));
		sb.append("\n");
		out.println(sb);
	}

	@Override
	protected void nativeSGET(String fromOrToReg, String fieldOwner,
			String fieldName, Field field) {
		String className = getClassNameFromclassNameSignature(field.getOwner());
		StringBuilder sb = new StringBuilder();

		String type = toJniType(field.getType());
		String typeSignature = getTypeSignature(field.getType());

		String localClass = String.format("localClass%d", localClassCounter++);
		sb.append(getFindClass(localClass, className));
		sb.append("\n");

		String fieldId = String.format("fieldId%d", localFieldCounter++);
		sb.append(getFieldID(localClass, fieldId, fieldName, typeSignature,
				true));
		sb.append("\n");

		boolean isNew = setRegister(typeSignature, fromOrToReg, null);
		if (isNew) {
			sb.append(String.format(("%s "), type));
		}

		sb.append(getStaticXXXField(typeSignature, localClass,
				getRegister(fromOrToReg).value, fieldId));
		out.println(sb);
	}

	private static String getFieldID(String localClass, String fieldId,
			String fieldName, String typeSignature, boolean isStatic) {
		return String.format(
				("jfieldID %s = (*env)->%s(env, %s, \"%s\", \"%s\");"),
				fieldId, isStatic ? "GetStaticFieldID" : "GetFieldID",
				localClass, fieldName, typeSignature);
	}

	private static String getStaticXXXField(String typeSignature,
			String localClass, String fieldObject, String fieldName) {
		String getStaticXXXField = String.format("GetStatic%sField",
				getInvokeMethodType(typeSignature));

		return String.format(("%s = (*env)->%s(env, %s, %s);"), fieldObject,
				getStaticXXXField, localClass, fieldName);
	}

	private static String setStaticXXXField(String typeSignature,
			String localClass, String fieldName, String value) {
		String setStaticXXXField = String.format("SetStatic%sField",
				getInvokeMethodType(typeSignature));
		return String.format(("(*env)->%s(env, %s, %s, %s);"),
				setStaticXXXField, localClass, fieldName, value);
	}

	private static String getXXXField(String obj, String fieldObject,
			String fieldName, String fieldType) {
		String GetXXXField = String.format("Get%sField", fieldType);
		return String.format(("%s = (*env)->%s(env, %s, %s);"), fieldObject,
				GetXXXField, obj, fieldName);
	}

	private static String setXXXField(String typeSignature, String obj,
			String fieldName, String value) {
		String setXXXField = String.format("Set%sField",
				getInvokeMethodType(typeSignature));
		return String.format(("(*env)->%s(env, %s, %s, %s);"), setXXXField,
				obj, fieldName, value);
	}

	private static String getFindClass(String localClass, String className) {
		return String.format(("jclass %s = (*env)->FindClass(env, \"%s\");"),
				localClass, className);
	}

	private static String getFindClass(String className) {
		return String.format(("(*env)->FindClass(env, \"%s\")"), className);
	}

	private static String getClassNameFromclassNameSignature(
			String classNameSignature) {

		int start = classNameSignature.indexOf('L');
		if (start == -1) {
			return classNameSignature;
		}
		int end = classNameSignature.indexOf(';');
		return classNameSignature.substring(start + 1, end);
	}

	public static final String JNI_TYPE_BOOLEAN = "Z";
	public static final String JNI_TYPE_BYTE = "B";
	public static final String JNI_TYPE_CHAR = "C";
	public static final String JNI_TYPE_DOUBLE = "D";
	public static final String JNI_TYPE_FLOAT = "F";
	public static final String JNI_TYPE_INT = "I";
	public static final String JNI_TYPE_LONG = "J";
	public static final String JNI_TYPE_OBJECT = "L";
	public static final String JNI_TYPE_SHORT = "S";
	public static final String JNI_TYPE_VOID = "V";
	public static final String JNI_TYPE_ARRAY = "[";

	private static final Map<String, String> TYPE_MAP = new HashMap<String, String>();
	private static final Map<String, String> METHOD_TYPE_MAP = new HashMap<String, String>();
	private static final Map<String, String> CALL_TYPE = new HashMap<String, String>();

	static {
		TYPE_MAP.put(JNI_TYPE_BOOLEAN, "jboolean");
		TYPE_MAP.put(JNI_TYPE_BYTE, "jbyte");
		TYPE_MAP.put(JNI_TYPE_CHAR, "jchar");
		TYPE_MAP.put(JNI_TYPE_DOUBLE, "jdouble");
		TYPE_MAP.put(JNI_TYPE_FLOAT, "jfloat");
		TYPE_MAP.put(JNI_TYPE_INT, "jint");
		TYPE_MAP.put(JNI_TYPE_LONG, "jlong");
		TYPE_MAP.put(JNI_TYPE_OBJECT, "jobject");
		TYPE_MAP.put(JNI_TYPE_SHORT, "jshort");
		TYPE_MAP.put(JNI_TYPE_VOID, "void");
		TYPE_MAP.put(JNI_TYPE_ARRAY, "jarray");
	}

	static {
		METHOD_TYPE_MAP.put(JNI_TYPE_BOOLEAN, "Boolean");
		METHOD_TYPE_MAP.put(JNI_TYPE_BYTE, "Byte");
		METHOD_TYPE_MAP.put(JNI_TYPE_CHAR, "Char");
		METHOD_TYPE_MAP.put(JNI_TYPE_DOUBLE, "Double");
		METHOD_TYPE_MAP.put(JNI_TYPE_FLOAT, "Float");
		METHOD_TYPE_MAP.put(JNI_TYPE_INT, "Int");
		METHOD_TYPE_MAP.put(JNI_TYPE_LONG, "Long");
		METHOD_TYPE_MAP.put(JNI_TYPE_OBJECT, "Object");
		METHOD_TYPE_MAP.put(JNI_TYPE_SHORT, "Short");
		METHOD_TYPE_MAP.put(JNI_TYPE_VOID, "Void");
		METHOD_TYPE_MAP.put(JNI_TYPE_ARRAY, "jarray");
	}

	static {
		CALL_TYPE.put("Object", "jobject");
		CALL_TYPE.put("Boolean", "jboolean");
		CALL_TYPE.put("Byte", "jbyte");
		CALL_TYPE.put("Char", "jchar");
		CALL_TYPE.put("Short", "jshort");
		CALL_TYPE.put("Int", "jint");
		CALL_TYPE.put("Long", "jlong");
		CALL_TYPE.put("Float", "jfloat");
		CALL_TYPE.put("Double", "jdouble");
	}

	private static String getTypeSignature(String s) {
		return s;
	}

	private static String getType(String s) {
		if (TYPE_MAP.keySet().contains(s))
			return TYPE_MAP.get(s);
		if (s.startsWith(JNI_TYPE_OBJECT))
			return "jobject";
		if (s.startsWith(JNI_TYPE_ARRAY))
			return "jarray";
		return s;
	}

	private static String getInvokeMethodType(String s) {
		if (METHOD_TYPE_MAP.keySet().contains(s))
			return METHOD_TYPE_MAP.get(s);
		if (s.startsWith(JNI_TYPE_OBJECT))
			return "Object";
		if (s.startsWith(JNI_TYPE_ARRAY))
			return "Array";
		throw new IllegalArgumentException();
	}

	private List<String> getClazzFieldName(String s) {
		System.out.println(s);
		if (s.length() < 4)
			throw new IllegalArgumentException();
		int divL = s.indexOf('L');
		String c = s.substring(divL);
		System.out.println("clazzMethodType : " + c);
		StringTokenizer st = new StringTokenizer(c, ".");

		List<String> list = new ArrayList<String>();
		while (st.hasMoreTokens()) {
			list.add(st.nextToken());
		}
		return list;
	}

	// INVOKE_DIRECT | |v1.printLog()
	// //Lj2n/irdeto/com/demo/MainActivity;.printLog()V
	// INVOKE_VIRTUAL | |v1.setContentView(v0)
	// //Lj2n/irdeto/com/demo/MainActivity;.setContentView(I)V
	private String[] getFunctionNameAndSignature(String s) {
		int i = s.indexOf('(');
		return new String[] { s.substring(0, i), s.substring(i) };
	}

	private static String getMethodStr(String methodId, String className,
			String methodName, String signature, boolean isStatic) {
		return String.format(
				"jmethodID %s = (*env)->%s(env, %s, \"%s\", \"%s\");",
				methodId, isStatic ? "GetStaticMethodID" : "GetMethodID",
				className, methodName, signature);
	}

	public static String toJniType(String desc) {
		System.out.println("toJniType :" + desc);
		switch (desc.charAt(0)) {
		case 'L':
			if (desc.equals("Ljava/lang/String;")) {
				return "jstring";
			}
			return "jobject";
		case 'B':
			return "jbyte";
		case 'S':
			return "jshort";
		case 'C':
			return "jchar";
		case 'Z':
			return "jboolean";
		case 'I':
			return "jint";
		case 'J':
			return "jlong";
		case 'F':
			return "jfloat";
		case 'D':
			return "jdouble";
		case 'V':
			return "void";
		case '[':
			switch (desc.substring(1).charAt(0)) {
			case 'B':
				return "jbyteArray";
			case 'S':
				return "jshortArray";
			case 'C':
				return "jcharArray";
			case 'Z':
				return "jbooleanArray";
			case 'I':
				return "jintArray";
			case 'J':
				return "jlongArray";
			case 'F':
				return "jfloatArray";
			case 'D':
				return "jdoubleArray";
			case 'L':
				return "jobjectArray";
			case '[':
				return toJniType(desc.substring(1));
			}
			throw new RuntimeException("illegal Array jni type.");
		}
		return desc;
	}

	private static String getReturnTypeByMethodSignature(String methedSignature) {
		int i = methedSignature.indexOf(')');
		String returnStr = methedSignature.substring(i + 1);
		return getInvokeMethodType(returnStr);
	}

	private static String getReturnSignatureByMethodSignature(
			String methedSignature) {
		int i = methedSignature.indexOf(')');
		String returnStr = methedSignature.substring(i + 1);
		return returnStr;
	}

	private static String getInvokeMethodByMethodSignature(
			String methedSignature, boolean isStatic, boolean isVirtual) {
		String methodReturnType = getReturnTypeByMethodSignature(methedSignature);
		StringBuilder sb = new StringBuilder();
		sb.append(isVirtual ? "Call" : "CallNonvirtual");
		sb.append(isStatic ? "Static" : "").append(methodReturnType)
				.append("Method");
		return sb.toString();
	}

	private static String getCallFunction(String callFunction, String caller,
			String methodId, String param, String superClass) {

		String nonVirtualCaller = ((superClass == null) ? "%s, " : "%s, "
				+ superClass + ", ");

		if (param == null || param.equals(""))
			return String.format(
					"(*env)->%s(env, " + nonVirtualCaller + "%s);",
					callFunction, caller, methodId);
		else
			return String.format("(*env)->%s(env, " + nonVirtualCaller
					+ "%s, %s);", callFunction, caller, methodId, param);
	}

	@Override
	protected void info(int opcode, String format, Object... args) {
		String s = String.format(format, args);
		if (opcode < 0) {
			out.printf("//%-20s|%5s|%s\n", "", "", s);
			out.printf("//info opcode < 0 =============================================================\n");
		} else {
			String opStr = DexOpcodeDump.dump(opcode);
			out.printf("//%-20s|%5s|%s\n", opStr, "", s);
		}
	}

	@Override
	protected String labelToString(DexLabel label) {
		int i = labels.indexOf(label);
		if (i > -1) {
			return "L" + i;
		}
		labels.add(label);
		return "L" + labels.indexOf(label);
	}

	@Override
	public void visitArguments(int total, int[] args) {
		clearRegisterValueMap();// TODO clear register map when function begin
		clearReturnBlockWhenNewMethodStart();

		int i = 0;
		if (!isStatic) {
			int reg = args[i++];
			String type = Dump.toJavaClass(method.getOwner());
			String regName = "v" + reg;
			out.printf(" " + regName);
			addArgumentRegisters(regName, new Register(method.getOwner(),
					regName, regName));

			System.out.printf("//%20s:v%d   //%s\n", "this", reg, type);
		}
		for (String typeSignature : method.getParameterTypes()) {
			int reg = args[i++];
			String type = toJniType(typeSignature);

			out.print(", ");
			out.print(type);
			String regName = "v" + reg;
			out.print(" " + regName);
			addArgumentRegisters(regName, new Register(typeSignature, regName,
					regName));
		}

		i = 0;
		for (String type : method.getParameterTypes()) {

			int reg = args[i++];
			// type = toJniType(type);

			System.out.printf("//%20s:v%d   //%s\n", "", reg, type);
		}

		out.print(")\n{\n");
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.googlecode.dex2jar.visitors.DexCodeAdapter#visitLabel(int)
	 */
	@Override
	public void visitLabel(DexLabel label) {
		boolean find = false;
		for (TryCatch tc : trys) {
			if (label.equals(tc.end)) {
				info(-1, " } // TC_%d", trys.indexOf(tc));
				find = true;
				break;
			}

		}
		Integer line = lines.get(label);
		if (line != null) {
			out.printf("//%-20s|%5s: line %d\n", "LABEL", "L"
					+ labelToString(label), line);
		} else {
			out.printf("//%-20s|%5s:\n", "LABEL", "L" + labelToString(label));
		}

		String outputLabel = labelToString(label);

		updateCurrentLabel(outputLabel);

		StringBuilder sb = new StringBuilder();
		sb.append(outputLabel);
		sb.append(": ;\n");
		out.print(sb);

		if (!find) {
			for (TryCatch tc : trys) {
				if (label.equals(tc.start)) {
					info(-1, "try { // TC_%d ", trys.indexOf(tc));
					break;
				}
				if (label.equals(tc.handler)) {
					String t = tc.type;
					info(-1, "catch(%s) // TC_%d", t == null ? "all" : t,
							trys.indexOf(tc));
					break;
				}
			}
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.googlecode.dex2jar.visitors.DexCodeAdapter#visitTryCatch(int,
	 * int, int, java.lang.String)
	 */
	@Override
	public void visitTryCatch(DexLabel start, DexLabel end, DexLabel handler,
			String type) {
		TryCatch tc = new TryCatch(start, end, handler, type);
		trys.add(tc);
		int id = trys.indexOf(tc);
		if (type == null) {
			out.printf("TR_%d L%s ~ L%s > L%s all\n", id, labelToString(start),
					labelToString(end), labelToString(handler));
		} else {
			out.printf("TR_%d L%s ~ L%s > L%s %s\n", id, labelToString(start),
					labelToString(end), labelToString(handler), type);
		}
		super.visitTryCatch(start, end, handler, type);
	}

	@Override
	public void visitLineNumber(int line, DexLabel label) {
		lines.put(label, line);
	}

	// LOCAL_VARIABLE LL0 ~ LL1 v1 -> this // Lj2n/irdeto/com/demo/MainActivity;
	@Override
	public void visitLocalVariable(String name, String type, String signature,
			DexLabel start, DexLabel end, int reg) {
		out.printf("//LOCAL_VARIABLE L%s ~ L%s v%d -> %s // %s \n",
				labelToString(start), labelToString(end), reg, name, type);

		// out.println("visitLocalVariable reg:" + reg);
		// out.println("visitLocalVariable name:" + name);
		// out.println("visitLocalVariable sig:" + signature);
		// out.println("visitLocalVariable type:" + type);

		// StringBuilder sb = new StringBuilder();
		//
		// String localClass = String.format("localClass%d",
		// localClassCounter++);
		// String className = getClassNameFromclassNameSignature(type);
		// sb.append(getFindClass(localClass, className));
		// sb.append("\n");
		//
		// String fieldId = String.format("field%d", reg);
		// sb.append(getField(localClass, fieldId, name, type, false));
		// sb.append("\n");
		//
		// sb.append(String.format(("%s "), getType(type)));
		// sb.append(getObjectField(String.format("v%d", reg), "object",
		// fieldId));
		// sb.append("\n");
		//
		// out.print(sb);
	}

	protected void nativeCONST(int opcode, String reg, String value,
			Object valueObject) {
		StringBuilder sb = new StringBuilder();

		boolean isObjectRegisterAndSetNull = false;
		String orginalType = getRegister(reg).type;

		if (isObjectType(orginalType.charAt(0))) {
			long v = Long.parseLong(valueObject + "");
			if (v == 0x0) {
				isObjectRegisterAndSetNull = true;
			}
		}

		String resultRegisterName = INVALID_REGISTER_NAME;
		String typeSignature = "I";

		if (!isObjectRegisterAndSetNull) {
			boolean isNew = setRegister(typeSignature, reg, null);
			if (isNew) {
				sb.append(String.format(("%s "), toJniType(typeSignature)));
			}
			resultRegisterName = getRegister(reg).value;
		} else {
			resultRegisterName = getRegister(reg).value;
		}

		sb.append(resultRegisterName);
		sb.append(" = ");
		sb.append(value);
		sb.append(";");
		out.println(sb);
	}

	protected void nativeCONST_STRING(int opcode, String reg, String value) {
		String typeSignature = "Ljava/lang/String;";
		boolean isNew = setRegister(typeSignature, reg, null);
		String resultRegisterName = getRegister(reg).value;
		StringBuilder sb = new StringBuilder();
		if (isNew) {
			sb.append("jstring ");
		}
		sb.append(resultRegisterName);
		sb.append(" = ");
		sb.append("(*env)->NewStringUTF(env, ");
		sb.append(value);
		sb.append(");");
		sb.append("\n");

		out.print(sb);
	}

	protected void nativeCONST_CLASS(int opcode, String reg, String signature,
			String cls) {
		String className = getClassNameFromclassNameSignature(signature);
		StringBuilder sb = new StringBuilder();

		// type name=value : java/lang/Class v0=localClass
		boolean isNew = setRegister(signature, reg, null);
		if (isNew) {
			sb.append(String.format(("%s "), "jclass"));
		}
		sb.append(getRegister(reg).value);
		sb.append(" = ");
		sb.append(getFindClass(className));
		sb.append(";");
		out.println(sb);
	}

	protected void nativeVoidInvoke(int opcode, String reg, String methodName,
			String param, Method method) {
		String classNameSignature = method.getOwner();
		String className = getClassNameFromclassNameSignature(classNameSignature);

		String methodSignature = method.signature();
		String[] ms = getFunctionNameAndSignature(methodSignature);
		// String methodName = ms[0];
		String signature = ms[1];

		// do not need to java.lang.Object init method.
		if (methodName.equals(IrdetoDexConvertor.LOCAL_CTOR)
				&& method.toString().startsWith(
						"L" + IrdetoDexConvertor.JAVA_LANG_OBJECT)) {
			return;
		}
		StringBuilder sb = new StringBuilder();

		String localClass = String.format("localClass%d", localClassCounter++);

		sb.append(getFindClass(localClass, className));
		sb.append("\n");

		String methodId = String.format("methodId%d", localMethodCounter++);

		boolean isStatic = false;
		if (opcode == OP_INVOKE_STATIC) {
			isStatic = true;
		} else {
			isStatic = false;
		}

		sb.append(getMethodStr(methodId, localClass, methodName, signature,
				isStatic));
		sb.append("\n");

		String caller = "";

		boolean isVirtual = isVirtual(reg, className, opcode);

		if (opcode == OP_INVOKE_STATIC) {
			caller = localClass;
		} else {
			caller = getRegister(reg).value;
		}
		sb.append(getCallFunction(
				getInvokeMethodByMethodSignature(signature, isStatic, isVirtual),
				caller, methodId, param, isVirtual ? null : localClass));

		sb.append("\n");

		out.print(sb);
	}

	private final boolean isVirtual(String reg, String methodClassName,
			int opcode) {
		// if (getRegister(reg) != null) {
		// return getRegister(reg).type.equals(methodClassName);
		// }
		// return false;
		if (opcode == OP_INVOKE_SUPER)
			return false;
		return true;
	}

	protected void nativeReturnInvoke(int opcode, String temp, String reg,
			String methodName, String param, Method method) {

		String classNameSignature = method.getOwner();

		String className = getClassNameFromclassNameSignature(classNameSignature);
		System.out.println("8888888888 : " + method + " class :" + className);

		String methodSignature = method.signature();
		String[] ms = getFunctionNameAndSignature(methodSignature);
		// String methodName = ms[0];
		String signature = ms[1];
		StringBuilder sb = new StringBuilder();

		String localClass = String.format("localClass%d", localClassCounter++);

		sb.append(getFindClass(localClass, className));
		sb.append("\n");

		String methodId = String.format("methodId%d", localMethodCounter++);

		boolean isStatic = false;
		if (opcode == OP_INVOKE_STATIC) {
			isStatic = true;
		} else {
			isStatic = false;
		}

		sb.append(getMethodStr(methodId, localClass, methodName, signature,
				isStatic));
		sb.append("\n");

		String returnType = toJniType(method.getReturnType());
		String castJObjectJString = (returnType.equals("jstring")) ? " (jstring) "
				: "";
		sb.append(String.format("%s %s = %s", returnType, temp,
				castJObjectJString));

		String caller;
		boolean isVirtual = isVirtual(reg, className, opcode);

		if (opcode == OP_INVOKE_STATIC) {
			caller = localClass;
		} else {
			caller = getRegister(reg).value;
		}

		sb.append(getCallFunction(
				getInvokeMethodByMethodSignature(signature, isStatic, isVirtual),
				caller, methodId, param, isVirtual ? null : localClass));
		sb.append("\n");

		updateTEMP(new RegisterTemp(method.getReturnType(), temp, temp));

		out.print(sb);
	}

	protected void nativeReturnStmt(int opcode, int reg) {
		String firstOperator = "v" + reg;
		Register r = getRegister(firstOperator);
		String firstOperatorRegisterName = r.value;
		saveReturnBlock(r);
		out.println("return " + firstOperatorRegisterName + ";");
	}

	@Override
	protected void nativeIGET(int regFromOrTo, int ownerReg, String fieldName,
			Field field) {
		String r = "v" + regFromOrTo;

		String obj = getRegister("v" + ownerReg).value;

		String className = getClassNameFromclassNameSignature(field.getOwner());

		StringBuilder sb = new StringBuilder();

		String typeSignature = getTypeSignature(field.getType());

		String fieldType = getReturnTypeByMethodSignature(typeSignature);

		String localClass = String.format("localClass%d", localClassCounter++);
		sb.append(getFindClass(localClass, className));
		sb.append("\n");

		String fieldId = String.format("fieldId%d", localFieldCounter++);
		sb.append(getFieldID(localClass, fieldId, fieldName, typeSignature,
				false));
		sb.append("\n");

		boolean isNew = setRegister(typeSignature, r, null);
		if (isNew) {
			sb.append(String.format(("%s "), toJniType(typeSignature)));
		}
		String fromRegister = getRegister(r).value;

		sb.append(getXXXField(obj, fromRegister, fieldId, fieldType));
		sb.append("\n");
		out.println(sb);
	}

	@Override
	protected void nativeIPUT(int ownerReg, String fieldName, int regFromOrTo,
			Field field) {

		String toRegister = getRegister("v" + regFromOrTo).value;
		String obj = getRegister("v" + ownerReg).value;

		String className = getClassNameFromclassNameSignature(field.getOwner());

		StringBuilder sb = new StringBuilder();

		String type = getType(field.getType());
		String typeSignature = getTypeSignature(field.getType());

		String localClass = String.format("localClass%d", localClassCounter++);
		sb.append(getFindClass(localClass, className));
		sb.append("\n");

		String fieldId = String.format("fieldId%d", localFieldCounter++);
		sb.append(getFieldID(localClass, fieldId, fieldName, typeSignature,
				false));
		sb.append("\n");

		sb.append(setXXXField(typeSignature, obj, fieldId, toRegister));
		sb.append("\n");
		out.println(sb);
	}

	@Override
	protected void nativeNEW_INSTANCE(int toReg, String signature) {
		String registerName = "v" + toReg;

		boolean isNew = setRegister(signature, registerName, null);

		String registerValue = getRegister(registerName).value;

		String className = getClassNameFromclassNameSignature(signature);
		StringBuilder sb = new StringBuilder();

		String jclazz = String.format(("(*env)->FindClass(env, \"%s\")"),
				className);
		if (isNew) {
			sb.append(String.format("%s ", toJniType(signature)));
		}
		sb.append(String.format("%s = (*env)->AllocObject(env, %s);",
				registerValue, jclazz));
		sb.append("\n");
		out.println(sb);
	}

	@Override
	protected void nativeReturnVoidStmt(String command) {
		out.println(command + ";");
	}

	@Override
	protected void nativeIf(int opcode, String code, int reg,
			String labelToString) {
		String firstOperator = "v" + reg;
		String firstOperatorRegisterName = getRegister(firstOperator).value;
		out.println(String.format(code, firstOperatorRegisterName,
				labelToString));
	}

	@Override
	protected void nativeIf(int opcode, String code, int reg1, int reg2,
			String labelToString) {
		String firstOperator = "v" + reg1;
		String secondOperator = "v" + reg2;

		String firstOperatorRegisterName = getRegister(firstOperator).value;
		String secondOperatorRegisterName = getRegister(secondOperator).value;
		out.println(String.format(code, firstOperatorRegisterName,
				secondOperatorRegisterName, labelToString));
	}

	@Override
	protected void nativeGoto(int opcode, String code, String labelToString) {
		String changeCurrentRegisterToReturnRegister = checkUnconditionGoto(labelToString);
		if (changeCurrentRegisterToReturnRegister != null) {
			out.println(changeCurrentRegisterToReturnRegister);
			out.println();
		}
		String s = String.format(code, labelToString);
		out.println(s);
	}

	@Override
	protected void nativeBinopLitXStmt(int opcode, String code, int saveToReg,
			int opReg, int value) {

		String firstOperator = "v" + opReg;

		String firstOperatorRegisterName = getRegister(firstOperator).value;

		String registerName = "v" + saveToReg;
		StringBuilder sb = new StringBuilder();
		String type = getRegister(firstOperator).type;
		boolean isNew = setRegister(type, registerName, null);
		if (isNew) {
			sb.append(String.format(("%s "), toJniType(type)));
		}

		String resultRegisterName = getRegister(registerName).value;

		sb.append(String.format(code, resultRegisterName,
				firstOperatorRegisterName, value + ""));
		out.println(sb);
	}

	protected void nativeBinop(int opcode, String code, int saveToReg,
			int opReg, int opReg2) {
		String firstOperator = "v" + opReg;
		String SecondOperator = "v" + opReg2;

		String firstOperatorRegisterName = getRegister(firstOperator).value;
		String SecondOperatorRegisterName = getRegister(SecondOperator).value;

		String registerName = "v" + saveToReg;

		StringBuilder sb = new StringBuilder();
		String type = getRegister(firstOperator).type;
		boolean isNew = setRegister(type, registerName, null);
		if (isNew) {
			sb.append(String.format(("%s "), toJniType(type)));
		}

		sb.append(String.format(code, getRegister(registerName).value,
				firstOperatorRegisterName, SecondOperatorRegisterName));
		out.println(sb);
	}

	private static boolean isObjectType(char signature) {
		return signature == 'L';
	}

	@Override
	protected void nativeNewArray(int toReg, String type, int fromReg) {
		String javaClass = toJniType(type);
		char arrayType = type.substring(1).charAt(0);

		String registerName = "v" + toReg;

		String resultType = javaClass;
		String XXX = getInvokeMethodType(arrayType + "");
		String newXXXArray = String.format("New%sArray", XXX);
		String size = getRegister("v" + fromReg).value;

		String param = "";
		if (isObjectType(arrayType)) {// object array
			String clazz = String.format("(*env)->FindClass(env, \"%s\")",
					getClassNameFromclassNameSignature(type));
			String object = "0";
			param = String.format("%s, %s, %s", size, clazz, object);
		} else {
			param = size;
		}
		StringBuilder sb = new StringBuilder();
		boolean isNew = setRegister(type, registerName, null);
		if (isNew) {
			sb.append(String.format(("%s "), toJniType(type)));
		}
		String code = "%s = (*env)->%s(env, %s);";
		sb.append(String.format(code, getRegister(registerName).value,
				newXXXArray, param));
		out.println(sb);
	}

	@Override
	protected void nativeFillArrayStmt(int reg, int initLength, Object[] values) {
		StringBuilder sb = new StringBuilder();
		for (Object value : values) {
			sb.append(',').append(value);
		}
		if (sb.length() > 0) {
			sb.deleteCharAt(0);
		}

		String registerValue = getRegister("v" + reg).value;
		String type = null;
		String jniType = null;
		if (values != null) {
			Object v = values[0];
			if (v instanceof Boolean) {
				type = "Boolean";
				jniType = "jboolean";
			} else if (v instanceof Byte) {
				type = "Byte";
				jniType = "jbyte";
			} else if (v instanceof Character) {
				type = "Char";
				jniType = "jchar";
			} else if (v instanceof Short) {
				type = "Short";
				jniType = "jshort";
			} else if (v instanceof Long) {
				type = "Long";
				jniType = "jlong";
			} else if (v instanceof Float) {
				type = "Float";
				jniType = "jfloat";
			} else if (v instanceof Double) {
				type = "Double";
				jniType = "jdouble";
			} else if (v instanceof Integer) {
				type = "Int";
				jniType = "jint";
			} else {
				type = "Object";
				jniType = "Object ";

				String buffer = "___values_" + registerValue;
				out.println(jniType + " " + buffer + "[] = {" + sb + "};");
				out.println(String.format("for (int i = 0; i < %d; i++) {",
						initLength));
				out.println(String.format(
						" (*env)->Set%sArrayElement(env, %s , i, %s);", type,
						registerValue, String.format("%s[i]", buffer)));
				out.println("}");
				return;
			}
			String buffer = "___values_" + registerValue;
			out.println(jniType + " " + buffer + "[] = {" + sb + "};");
			out.println(String.format(
					"(*env)->Set%sArrayRegion(env, %s , 0, %d, %s);", type,
					registerValue, initLength, buffer));
		}
	}

	@Override
	protected void nativeAGET(String code, int value, int array, int index) {
		StringBuilder sb = new StringBuilder();

		String arrayName = "v" + array;
		String indexName = "v" + index;

		String valueName = "v" + value;

		String arrayTypeSignature = getRegister(arrayName).type;
		String typeSignature = arrayTypeSignature.substring(0);

		// ////////// value
		boolean isNew = setRegister(typeSignature, valueName, null);
		// if (isNew) {
		sb.append(String.format(("%s  rrrrrrrrr "), (typeSignature)));
		// this.getInvokeMethodType(typeSignature)));
		// }

		String valueRegisterName = getRegister(valueName).value;

		sb.append(String.format(code, valueRegisterName,
				getRegister(arrayName).value, getRegister(indexName).value));

		String cmd = String.format(
				"(*env)->Get%sArrayRegion(env, %s, %s, 1, &%s);",
				(typeSignature), getRegister(arrayName).value,
				getRegister(indexName).value, getRegister(valueName).value);
		sb.append(cmd);
		out.println(sb);
	}

	@Override
	protected void nativeAPUT(String code, int array, int index, int value) {
		// TODO Auto-generated method stub

	}

	@Override
	protected void nativeUnopStmt(int opcode, String code, int saveToReg,
			int opReg) {
		String r1 = "v" + saveToReg;
		String r2 = "v" + opReg;
		String code1 = "";
		StringBuilder sb = new StringBuilder();
		if (OP_ARRAY_LENGTH == opcode) {

			String type = "I";
			boolean isNew = setRegister(type, r1, null);
			if (isNew) {
				sb.append(String.format(("%s "), toJniType(type)));
			}
			code1 = String.format("%s = (*env)->GetArrayLength(env, %s);",
					getRegister(r1).value, getRegister(r2).value);
		} else {
			String type = getRegister(r2).type;
			boolean isNew = setRegister(type, r1, null);
			if (isNew) {
				sb.append(String.format(("%s "), toJniType(type)));
			}
			code1 = String.format(String.format(code, getRegister(r1).value,
					getRegister(r2).value));

		}
		sb.append(code1);
		out.println(sb);
	}

	@Override
	protected void nativeMoveStmt(int opcode, int toReg, int fromReg) {
		String toRegisterName = "v" + toReg;
		String fromRegisterName = "v" + fromReg;

		StringBuilder sb = new StringBuilder();
		String type = getRegister(fromRegisterName).type;
		boolean isNew = setRegister(type, toRegisterName, null);
		if (isNew) {
			sb.append(String.format(("%s "), toJniType(type)));
		}
		String code = "%s = %s;";
		sb.append(String.format(code, getRegister(toRegisterName).value,
				getRegister(fromRegisterName).value));
		out.println(sb);
	}

	@Override
	protected void nativeIntanceof(int opcode, int toReg, int fromReg,
			String targetTypeSignature) {
		String toRegisterName = "v" + toReg;
		String fromRegisterName = "v" + fromReg;

		StringBuilder sb = new StringBuilder();
		String booleanType = "Z";

		boolean isNew = setRegister(booleanType, toRegisterName, null);
		if (isNew) {
			sb.append(String.format(("%s "), toJniType(booleanType)));
		}
		String targetJClass = getFindClass(getClassNameFromclassNameSignature(targetTypeSignature));

		String code = "%s = (*env)->IsInstanceOf(env, %s, %s);";
		sb.append(String.format(code, getRegister(toRegisterName).value,
				getRegister(fromRegisterName).value, targetJClass));
		out.println(sb);
	}

	private static String castFromOpcode2JniSignature(int opcode) {
		String jniType = null;
		switch (opcode) {
		case TYPE_BOOLEAN:
			jniType = JNI_TYPE_BOOLEAN;
			break;
		case TYPE_BYTE:
			jniType = JNI_TYPE_BYTE;
		case TYPE_CHAR:
			jniType = JNI_TYPE_CHAR;
			break;
		case TYPE_DOUBLE:
			jniType = JNI_TYPE_DOUBLE;
			break;
		case TYPE_FLOAT:
			jniType = JNI_TYPE_FLOAT;
			break;
		case TYPE_INT:
			jniType = JNI_TYPE_INT;
			break;
		case TYPE_LONG:
			jniType = JNI_TYPE_LONG;
			break;
		case TYPE_SHORT:
			jniType = JNI_TYPE_SHORT;
			break;
		}
		return jniType;
	}

	@Override
	protected void nativeCast(int opcode, String code, int saveToReg, int opReg) {
		String jniType = castFromOpcode2JniSignature(opcode);

		String toRegisterName = "v" + saveToReg;
		String fromRegisterName = "v" + opReg;

		StringBuilder sb = new StringBuilder();

		boolean isNew = setRegister(jniType, toRegisterName, null);
		if (isNew) {
			sb.append(String.format(("%s "), toJniType(jniType)));
		}

		sb.append(String.format(code, getRegister(toRegisterName).value,
				getRegister(fromRegisterName).value));
		out.println(sb);
	}

	@Override
	protected void nativeCmpStmt(int opcode, int distReg, int bB, int cC) {
		// reference: http://www.2cto.com/kf/201608/532598.html
		String code = "";
		switch (opcode) {
		case OP_CMPL:
			code = "%s = ((%s == %s) ? 0 : (%s < %s ? -1 : 1));";
			break;
		case OP_CMPG:
		case OP_CMP:
			code = "%s = ((%s == %s) ? 0 : (%s > %s ? -1 : 1));";
			break;
		}

		String toRegisterName = "v" + distReg;

		String r1 = "v" + bB;
		String r2 = "v" + cC;

		StringBuilder sb = new StringBuilder();
		String distRegType = "I";
		boolean isNew = setRegister(distRegType, toRegisterName, null);
		if (isNew) {
			sb.append(String.format(("%s "), toJniType(distRegType)));
		}

		sb.append(String.format(code, getRegister(toRegisterName).value,
				getRegister(r1).value, getRegister(r2).value,
				getRegister(r1).value, getRegister(r2).value));
		out.println(sb);

	}

	@Override
	protected void nativeMoveResult(int reg, Register temp) {
		String code = "%s = %s;";
		String toRegisterName = "v" + reg;

		StringBuilder sb = new StringBuilder();

		boolean isNew = setRegister(temp.type, toRegisterName, null);
		if (isNew) {
			sb.append(String.format(("%s "), toJniType(temp.type)));
		}

		sb.append(String.format(code, getRegister(toRegisterName).value,
				temp.value));
		out.println(sb);
	}

	@Override
	protected void nativeMoveResult(int reg) {
		String code = "%s = %s;";
		String toRegisterName = "v" + reg;
		String type = "Ljava/lang/Exception;";
		StringBuilder sb = new StringBuilder();

		boolean isNew = setRegister(type, toRegisterName, null);
		if (isNew) {
			sb.append(String.format(("%s "), toJniType(type)));
		}

		sb.append(String
				.format(code, getRegister(toRegisterName).value, "NULL"));
		out.println(sb);
	}

	@Override
	protected void nativeSwitchStmt(int opcode, String code, String reg,
			DexLabel label, int first_case, int last_case, DexLabel[] labels) {

		out.println(String.format(code, getRegister(reg).value));
	}
}
