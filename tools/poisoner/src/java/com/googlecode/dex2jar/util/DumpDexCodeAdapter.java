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

	private static String lastNativeCodeLabel;

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

	@Override
	protected void nativeSPUT(String fromOrToReg, String fieldOwner,
			String fieldName, Field field) {
		String className = fieldOwner;

		StringBuilder sb = new StringBuilder();

		String type = getType(field.getType());
		String typeSignature = getTypeSignature(field.getType());

		String localClass = String.format("localClass%d", localClassCounter++);
		sb.append(getFindClass(localClass, className));
		sb.append("\n");

		String fieldId = String.format("fieldId%d", localFieldCounter++);
		sb.append(getField(localClass, fieldId, fieldName, typeSignature, true));
		sb.append("\n");

		sb.append(String.format(("env->SetStaticObjectField(%s, %s, %s);"),
				localClass, fieldId, fromOrToReg));

		sb.append("\n");
		out.println(sb);
	}

	@Override
	protected void nativeSGET(String fromOrToReg, String fieldOwner,
			String fieldName, Field field) {
		String className = fieldOwner;

		StringBuilder sb = new StringBuilder();

		String type = getType(field.getType());
		String typeSignature = getTypeSignature(field.getType());

		String localClass = String.format("localClass%d", localClassCounter++);
		sb.append(getFindClass(localClass, className));
		sb.append("\n");

		String fieldId = String.format("fieldId%d", localFieldCounter++);
		sb.append(getField(localClass, fieldId, fieldName, typeSignature, true));
		sb.append("\n");

		sb.append(String.format(("%s "), type));

		sb.append(getStaticObjectField(localClass, fromOrToReg, fieldId));
		sb.append("\n");
		out.println(sb);
	}

	private static String getField(String localClass, String fieldId,
			String fieldName, String typeSignature, boolean isStatic) {
		return String.format(("jfieldID %s = env->%s(%s, \"%s\", \"%s\");"),
				fieldId, isStatic ? "GetStaticFieldID" : "GetFieldID",
				localClass, fieldName, typeSignature);
	}

	private static String getStaticObjectField(String localClass,
			String fieldObject, String fieldName) {
		return String.format(("%s = env->%s(%s, %s);"), fieldObject,
				"GetStaticObjectField", localClass, fieldName);
	}

	private static String setStaticObjectField(String localClass,
			String fieldName, String value) {
		return String.format(("env->%s(%s, %s, %s);"), "SetStaticObjectField",
				localClass, fieldName, value);
	}

	private static String getObjectField(String obj, String fieldObject,
			String fieldName, String fieldType) {
		String GetXXXField = String.format("Get%sField", fieldType);
		return String.format(("%s = env->%s(%s, %s);"), fieldObject,
				GetXXXField, obj, fieldName);
	}

	private static String setObjectField(String obj, String fieldName,
			String value) {
		return String.format(("env->%s(%s, %s, %s);"), "SetObjectField", obj,
				fieldName, value);
	}

	private static String getFindClass(String localClass, String className) {
		return String.format(("jclass %s = env->FindClass(\"%s\");"),
				localClass, className);
	}

	private static String getClassNameFromclassNameSignature(
			String classNameSignature) {
		int start = classNameSignature.indexOf('L');
		int end = classNameSignature.indexOf(';');
		return classNameSignature.substring(start + 1, end);
	}

	public static final String TYPE_BOOLEAN = "Z";
	public static final String TYPE_BYTE = "B";
	public static final String TYPE_CHAR = "C";
	public static final String TYPE_DOUBLE = "D";
	public static final String TYPE_FLOAT = "F";
	public static final String TYPE_INT = "I";
	public static final String TYPE_LONG = "J";
	public static final String TYPE_OBJECT = "L";
	public static final String TYPE_SHORT = "S";
	public static final String TYPE_VOID = "V";
	public static final String TYPE_ARRAY = "[";

	private static final Map<String, String> TYPE_MAP = new HashMap<String, String>();
	private static final Map<String, String> METHOD_TYPE_MAP = new HashMap<String, String>();
	private static final Map<String, String> CALL_TYPE = new HashMap<String, String>();

	static {
		TYPE_MAP.put(TYPE_BOOLEAN, "jboolean");
		TYPE_MAP.put(TYPE_BYTE, "jbyte");
		TYPE_MAP.put(TYPE_CHAR, "jchar");
		TYPE_MAP.put(TYPE_DOUBLE, "jdouble");
		TYPE_MAP.put(TYPE_FLOAT, "jfloat");
		TYPE_MAP.put(TYPE_INT, "jint");
		TYPE_MAP.put(TYPE_LONG, "jlong");
		TYPE_MAP.put(TYPE_OBJECT, "jobject");
		TYPE_MAP.put(TYPE_SHORT, "jshort");
		TYPE_MAP.put(TYPE_VOID, "void");
		TYPE_MAP.put(TYPE_ARRAY, "jarray");
	}

	static {
		METHOD_TYPE_MAP.put(TYPE_BOOLEAN, "Boolean");
		METHOD_TYPE_MAP.put(TYPE_BYTE, "Byte");
		METHOD_TYPE_MAP.put(TYPE_CHAR, "Char");
		METHOD_TYPE_MAP.put(TYPE_DOUBLE, "Double");
		METHOD_TYPE_MAP.put(TYPE_FLOAT, "Float");
		METHOD_TYPE_MAP.put(TYPE_INT, "Int");
		METHOD_TYPE_MAP.put(TYPE_LONG, "Long");
		METHOD_TYPE_MAP.put(TYPE_OBJECT, "Object");
		METHOD_TYPE_MAP.put(TYPE_SHORT, "Short");
		METHOD_TYPE_MAP.put(TYPE_VOID, "Void");
		METHOD_TYPE_MAP.put(TYPE_ARRAY, "jarray");
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
		if (s.startsWith(TYPE_OBJECT))
			return "jobject";
		if (s.startsWith(TYPE_ARRAY))
			return "jarray";
		return s;
	}

	private static String getInvokeMethodType(String s) {
		if (METHOD_TYPE_MAP.keySet().contains(s))
			return METHOD_TYPE_MAP.get(s);
		if (s.startsWith(TYPE_OBJECT))
			return "Object";
		if (s.startsWith(TYPE_ARRAY))
			return "jarray";
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
		return String.format("jmethodID %s = env->%s(%s, \"%s\", \"%s\");",
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
			return toJavaClass(desc.substring(1)) + "[]";
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
			return String.format("env->%s(" + nonVirtualCaller + "%s);",
					callFunction, caller, methodId);
		else
			return String.format("env->%s(" + nonVirtualCaller + "%s, %s);",
					callFunction, caller, methodId, param);
	}

	@Override
	protected void info(int opcode, String format, Object... args) {
		String s = String.format(format, args);
		if (opcode < 0) {
			out.printf("%-20s|%5s|%s\n", "", "", s);
			out.printf("info opcode < 0 =============================================================\n");
		} else {
			String opStr = DexOpcodeDump.dump(opcode);
			out.printf("//%-20s|%5s|%s\n", opStr, "", s);
		}
		lastNativeCodeLabel = null;
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

		int i = 0;
		if (!isStatic) {
			int reg = args[i++];
			String type = Dump.toJavaClass(method.getOwner());
			String regName = "v" + reg;
			out.printf(" " + regName);
			addArgumentRegisters(regName, new Register(type, regName, regName));

			System.out.printf("//%20s:v%d   //%s\n", "this", reg, type);
		}
		for (String type : method.getParameterTypes()) {
			int reg = args[i++];
			type = toJniType(type);

			out.print(", ");
			out.print(type);
			String regName = "v" + reg;
			out.print(" " + regName);
			addArgumentRegisters(regName, new Register(type, regName, regName));
		}

		i = 0;
		for (String type : method.getParameterTypes()) {

			int reg = args[i++];
			type = toJniType(type);

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

		StringBuilder sb = new StringBuilder();
		lastNativeCodeLabel = labelToString(label);
		sb.append(lastNativeCodeLabel);
		sb.append(":\n");
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

	public static String getLastNativeCodeLabel() {
		return lastNativeCodeLabel;
	}

	public static void setLastNativeCodeLabel(String value) {
		lastNativeCodeLabel = value;
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

	protected void nativeCONST(int opcode, String reg, String value) {
		StringBuilder sb = new StringBuilder();
		String type = "int";

		String resultRegisterName = setRegister(reg, new Register(type, reg)).value;

		sb.append(type);
		sb.append(" ");
		sb.append(resultRegisterName);
		sb.append(" = ");
		sb.append(value);
		sb.append(";");
		out.println(sb);
	}

	protected void nativeCONST_STRING(int opcode, String reg, String value) {
		StringBuilder sb = new StringBuilder();
		sb.append(reg);
		sb.append(" = ");
		sb.append("env->NewStringUTF(");
		sb.append(value);
		sb.append(");");
		sb.append("\n");

		out.print(sb);
	}

	protected void nativeCONST_CLASS(int opcode, String reg, String signature,
			String cls) {

		String className = getClassNameFromclassNameSignature(signature);
		StringBuilder sb = new StringBuilder();

		String localClass = String.format("localClass%d", localClassCounter++);
		sb.append(getFindClass(localClass, className));
		sb.append("\n");

		out.print(sb);

		// type name=value : java/lang/Class v0=localClass
		setRegister(reg, new Register(className, reg, localClass));
	}

	protected void nativeVoidInvoke(int opcode, String reg, String methodName,
			String param, String method) {

		List<String> clazzFieldList = getClazzFieldName(method);
		String classNameSignature = clazzFieldList.get(0);
		String className = getClassNameFromclassNameSignature(classNameSignature);

		String methodSignature = clazzFieldList.get(1);
		String[] ms = getFunctionNameAndSignature(methodSignature);
		// String methodName = ms[0];
		String signature = ms[1];
		StringBuilder sb = new StringBuilder();

		String localClass = String.format("localClass%d", localClassCounter++);

		sb.append(getFindClass(localClass, className));
		sb.append("\n");

		String methodId = String.format("methodId%d", localMethodCounter++);

		sb.append(getMethodStr(methodId, localClass, methodName, signature,
				false));
		sb.append("\n");

		String caller = getCallerByReg(reg);

		boolean isVirtual = isVirtual(reg, className, opcode);

		boolean isStatic = false;
		if (opcode == OP_INVOKE_STATIC) {
			isStatic = true;
			caller = localClass;
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
			String methodName, String param, String method) {

		List<String> clazzFieldList = getClazzFieldName(method);
		String classNameSignature = clazzFieldList.get(0);
		String className = getClassNameFromclassNameSignature(classNameSignature);

		String methodSignature = clazzFieldList.get(1);
		String[] ms = getFunctionNameAndSignature(methodSignature);
		// String methodName = ms[0];
		String signature = ms[1];
		StringBuilder sb = new StringBuilder();

		String localClass = String.format("localClass%d", localClassCounter++);

		sb.append(getFindClass(localClass, className));
		sb.append("\n");

		String methodId = String.format("methodId%d", localMethodCounter++);

		sb.append(getMethodStr(methodId, localClass, methodName, signature,
				false));
		sb.append("\n");

		String returnType = toJniType(getReturnSignatureByMethodSignature(method));
		String castJObjectJString = (returnType.equals("jstring")) ? " (jstring) "
				: "";
		sb.append(String.format("%s %s = %s", returnType, temp,
				castJObjectJString));

		String caller;
		boolean isVirtual = isVirtual(reg, className, opcode);
		boolean isStatic = false;
		if (opcode == OP_INVOKE_STATIC) {
			isStatic = true;
			caller = localClass;
		} else {
			isStatic = false;
			caller = getCallerByReg(reg);
		}

		sb.append(getCallFunction(
				getInvokeMethodByMethodSignature(signature, isStatic, isVirtual),
				caller, methodId, param, isVirtual ? null : localClass));
		sb.append("\n");

		updateTEMP(new RegisterTemp(getReturnTypeByMethodSignature(method),
				temp, temp));

		out.print(sb);
	}

	protected void nativeReturnStmt(int opcode, String reg) {
		String caller = getCallerByReg(reg);
		out.println("return " + caller + ";");
	}

	private String getCallerByReg(String reg) {
		String caller = reg;
		if (registerValueMap.containsKey(reg)) {
			System.out.println(registerValueMap.get(reg).toString());
			caller = registerValueMap.get(reg).value;
		}
		return caller;
	}

	@Override
	protected void nativeIGET(int regFromOrTo, int ownerReg, String fieldName,
			Field field) {
		String fromRegister = "v" + regFromOrTo;
		String obj = "v" + ownerReg;

		String className = toJavaClass(field.getOwner());

		StringBuilder sb = new StringBuilder();

		String type = getType(field.getType());
		String typeSignature = getTypeSignature(field.getType());

		String fieldType = getReturnTypeByMethodSignature(typeSignature);

		String localClass = String.format("localClass%d", localClassCounter++);
		sb.append(getFindClass(localClass, className));
		sb.append("\n");

		String fieldId = String.format("fieldId%d", localFieldCounter++);
		sb.append(getField(localClass, fieldId, fieldName, typeSignature, false));
		sb.append("\n");

		sb.append(String.format(("%s "), type));

		sb.append(getObjectField(obj, fromRegister, fieldId, fieldType));
		sb.append("\n");
		out.println(sb);
	}

	@Override
	protected void nativeIPUT(int ownerReg, String fieldName, int regFromOrTo,
			Field field) {

		String toRegister = "v" + regFromOrTo;
		String obj = "v" + ownerReg;

		String className = toJavaClass(field.getOwner());

		StringBuilder sb = new StringBuilder();

		String type = getType(field.getType());
		String typeSignature = getTypeSignature(field.getType());

		String localClass = String.format("localClass%d", localClassCounter++);
		sb.append(getFindClass(localClass, className));
		sb.append("\n");

		String fieldId = String.format("fieldId%d", localFieldCounter++);
		sb.append(getField(localClass, fieldId, fieldName, typeSignature, false));
		sb.append("\n");

		sb.append(String.format(("%s "), type));

		sb.append(setObjectField(obj, fieldId, toRegister));
		sb.append("\n");
		out.println(sb);
	}

	@Override
	protected void nativeNEW_INSTANCE(int toReg, String type) {
		String toRegister = "v" + toReg;
		String className = toJavaClass(type);

		StringBuilder sb = new StringBuilder();

		sb.append(String.format("jobject %s = AllocObject(%s)", toRegister,
				className));
		sb.append("\n");
		out.println(sb);
	}

	@Override
	protected void nativeReturnVoidStmt(String reg) {
		out.println(reg + ";");
	}

	@Override
	protected void nativeIf(int opcode, String code, int reg,
			String labelToString) {
		String s = String.format(code, reg, labelToString);
		out.println(s);
	}

	@Override
	protected void nativeIf(int opcode, String code, int reg1, int reg2,
			String labelToString) {
		String s = String.format(code, reg1, reg2, labelToString);
		out.println(s);
	}

	@Override
	protected void nativeGoto(int opcode, String code, String labelToString) {
		String s = String.format(code, labelToString);
		out.println(s);
	}

	@Override
	protected void nativeBinopLitXStmt(int opcode, String code, int saveToReg,
			int opReg, int value) {

		String firstOperator = "v" + opReg;

		String firstOperatorRegisterName = getRegister(firstOperator).value;

		String registerName = "v" + saveToReg;
		String registerType = getRegister(registerName).type;
		String registerValue = getRegister(registerName).value;
		String resultRegisterName = setRegister(registerName, new Register(registerType,
				registerName, registerValue)).value;

		out.println(String.format(code, resultRegisterName,
				firstOperatorRegisterName, value + ""));
	}

	protected void nativeBinop(int opcode, String code, int saveToReg,
			int opReg, int opReg2) {
		String firstOperator = "v" + opReg;
		String SecondOperator = "v" + opReg2;

		String firstOperatorRegisterName = getRegister(firstOperator).value;
		String SecondOperatorRegisterName = getRegister(SecondOperator).value;

		String registerName = "v" + saveToReg;
		
		String type = getRegister(registerName).type;
		String registerValue = getRegister(registerName).value;
		String resultRegisterName = setRegister(registerName, new Register(type,
				registerName, registerValue)).value;

		out.println(String.format(code, resultRegisterName,
				firstOperatorRegisterName, SecondOperatorRegisterName));
	}
}
