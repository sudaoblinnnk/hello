/*
 * Copyright (c) 2009-2012 Panxiaobo
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.googlecode.dex2jar.util;

import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.StringTokenizer;
import java.util.regex.Pattern;

import com.googlecode.dex2jar.DexLabel;
import com.googlecode.dex2jar.Method;

/**
 * @author <a href="mailto:pxb1988@gmail.com">Panxiaobo</a>
 * @version $Rev$
 */
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

	// SGET | |v0=j2n.irdeto.com.demo.MainActivity.debug
	// //Lj2n/irdeto/com/demo/MainActivity;.debug Z
	// v0=j2n.irdeto.com.demo.MainActivity.debug
	// //Lj2n/irdeto/com/demo/MainActivity;.debug Z
	private void parseSGET_OP(String s) {
		String[] codeBlocks = getCodeBlocks(s);

		// for (String c : codeBlocks) {
		// System.out.println("===========" + c + "======");
		// }

		String varible = getVarible(codeBlocks[0]);

		List<String> clazzFieldList = getClazzFieldName(codeBlocks[2]);

		String classNameSignature = clazzFieldList.get(0);
		String className = getClassNameFromclassNameSignature(classNameSignature);
		String fieldName = clazzFieldList.get(1);

		StringBuilder sb = new StringBuilder();

		String type = getType(codeBlocks[3]);
		String typeSignature = getTypeSignature(codeBlocks[3]);

		String localClass = String.format("localClass%d", localClassCounter++);
		sb.append(getFindClass(localClass, className));
		sb.append("\n");

		String fieldId = String.format("fieldId%d", localFieldCounter++);
		sb.append(getField(localClass, fieldId, fieldName, typeSignature, true));
		sb.append("\n");

		sb.append(String.format(("%s "), type));

		sb.append(getStaticObjectField(localClass, varible, fieldId));
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

	private static String getObjectField(String obj, String fieldObject,
			String fieldName) {
		return String.format(("%s = env->%s(%s, %s);"), fieldObject,
				"GetObjectField", obj, fieldName);
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

	// SPUT | |j2n.irdeto.com.demo.MainActivity.debug=v0
	// //Lj2n/irdeto/com/demo/MainActivity;.debug Z
	private void parseSPUT_OP(String s) {
		String[] codeBlocks = getCodeBlocks(s);

		for (String c : codeBlocks) {
			System.out.println("===========" + c + "======");
		}

		String varible = getVarible(codeBlocks[0]);
		String varibleValue = getVaribleValue(codeBlocks[0]);

		List<String> clazzFieldList = getClazzFieldName(codeBlocks[2]);

		String classNameSignature = clazzFieldList.get(0);
		String className = getClassNameFromclassNameSignature(classNameSignature);
		String fieldName = clazzFieldList.get(1);

		StringBuilder sb = new StringBuilder();

		String type = getType(codeBlocks[3]);
		String typeSignature = getTypeSignature(codeBlocks[3]);

		String localClass = String.format("localClass%d", localClassCounter++);
		sb.append(getFindClass(localClass, className));
		sb.append("\n");

		String fieldId = String.format("fieldId%d", localFieldCounter++);
		sb.append(getField(localClass, fieldId, fieldName, typeSignature, true));
		sb.append("\n");

		sb.append(String.format(("env->SetStaticObjectField(%s, %s, %s);"),
				localClass, fieldId, varibleValue));

		sb.append("\n");
		out.println(sb);

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

	private String getVarible(String s) {
		String patternEqual = "=";
		Pattern patternE = Pattern.compile(patternEqual);
		String[] elements = patternE.split(s);
		return elements[0];
	}

	private String getVaribleValue(String s) {
		String patternEqual = "=";
		Pattern patternE = Pattern.compile(patternEqual);
		String[] elements = patternE.split(s);
		return elements[1];
	}

	private String[] getCodeBlocks(String s) {
		String patternSpace = " ";
		Pattern patternS = Pattern.compile(patternSpace);
		return patternS.split(s);
	}

	private void parseCONST_OP(String s) {
		String patternSpace = " ";
		Pattern patternS = Pattern.compile(patternSpace);
		String[] split = patternS.split(s);

		System.out.println("split.length = " + split.length);

		for (String element : split) {
			System.out.println("element = " + element);
		}
		if (split.length > 0) {
			String patternEqual = "=";
			Pattern patternE = Pattern.compile(patternEqual);
			String[] elements = patternE.split(split[0]);

			StringBuilder sb = new StringBuilder();
			sb.append("int ");
			sb.append(elements[0]);
			sb.append(" = ");
			sb.append(elements[1]);
			sb.append(";\n");

			out.print(sb);
		}
	}

	// if v0 == 0 goto L2
	private void parseIF_EQZ_OP(String s) {
		out.println(s);
	}

	// RETURN_VOID | |return
	private void parseRETURN_VOID_OP(String s) {
		out.println("return;");
	}

	private void parseCONST_STRING_OP(String s) {
		String patternSpace = " ";
		Pattern patternS = Pattern.compile(patternSpace);
		String[] split = patternS.split(s);

		System.out.println("split.length = " + split.length);

		for (String element : split) {
			System.out.println("element = " + element);
		}
		if (split.length > 0) {
			String patternEqual = "=";
			Pattern patternE = Pattern.compile(patternEqual);
			String[] elements = patternE.split(split[0]);

			StringBuilder sb = new StringBuilder();
			sb.append(elements[0]);
			sb.append(" = ");
			sb.append("env->NewStringUTF(");
			sb.append(elements[1]);
			sb.append(");");
			sb.append("\n");

			out.print(sb);
		}
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
			return desc.substring(1, desc.length() - 1).replace('/', '.');
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
			String methodId) {
		return String
				.format("env->%s(%s, %s);", callFunction, caller, methodId);
	}

	private void parseINVOKE_OP(String s, boolean isStatic) {
		String[] codeBlocks = getCodeBlocks(s);

		System.out.println("===========" + s + "======");
		for (String c : codeBlocks) {
			System.out.println("===========" + c + "======");
		}

		List<String> clazzFieldList = getClazzFieldName(codeBlocks[2]);
		String classNameSignature = clazzFieldList.get(0);
		String className = getClassNameFromclassNameSignature(classNameSignature);

		String methodSignature = clazzFieldList.get(1);
		String[] ms = getFunctionNameAndSignature(methodSignature);
		String methodName = ms[0];
		String signature = ms[1];
		StringBuilder sb = new StringBuilder();

		String localClass = String.format("localClass%d", localClassCounter++);

		sb.append(getFindClass(localClass, className));
		sb.append("\n");

		String methodId = String.format("methodId%d", localMethodCounter++);

		sb.append(getMethodStr(methodId, localClass, methodName, signature,
				true));
		sb.append("\n");

		sb.append(getCallFunction(
				getInvokeMethodByMethodSignature(signature, isStatic, false),
				"obj", methodId));
		sb.append("\n");

		out.print(sb);
	}

	@Override
	protected void info(int opcode, String format, Object... args) {
		String s = String.format(format, args);
		if (opcode < 0) {
			out.printf("%-20s|%5s|%s\n", "", "", s);
			out.printf("info opcode < 0 =============================================================\n");
		} else {
			String opStr = DexOpcodeDump.dump(opcode);
			if (!opStr.equals(RETURN_VOID_OP))
				out.printf("%-20s|%5s|%s\n", opStr, "", s);

			if (opStr.equals(CONST_OP)) {
				parseCONST_OP(s);
			} else if (opStr.equals(CONST_CLASS_OP)) {

			} else if (opStr.equals(CONST_STRING_OP)) {
				parseCONST_STRING_OP(s);
			} else if (opStr.equals(SGET_OP)) {
				parseSGET_OP(s);
			} else if (opStr.equals(SPUT_OP)) {
				parseSPUT_OP(s);
			} else if (opStr.equals(IF_EQZ_OP)) {
				parseIF_EQZ_OP(s);
			} else if (opStr.equals(RETURN_OP)) {

			} else if (opStr.equals(RETURN_VOID_OP)) {
				parseRETURN_VOID_OP(s);
			} else if (opStr.equals(INVOKE_SUPER_OP)
					|| opStr.equals(INVOKE_DIRECT_OP)
					|| opStr.equals(INVOKE_VIRTUAL_OP)) {
				// parseINVOKE_OP(s, false);
			} else if (opStr.equals(INVOKE_STATIC_OP)) {
				parseINVOKE_OP(s, true);
			}
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
		int i = 0;
		if (!this.isStatic) {
			int reg = args[i++];
			String type = Dump.toJavaClass(method.getOwner());
			out.printf("v" + reg);

			System.out.printf("//%20s:v%d   //%s\n", "this", reg, type);
		}
		for (String type : method.getParameterTypes()) {
			int reg = args[i++];
			type = toJniType(type);

			out.print(',');
			out.print(type);
			out.print(" v" + reg);
		}

		i = 0;
		for (String type : method.getParameterTypes()) {

			int reg = args[i++];
			type = Dump.toJavaClass(type);

			System.out.printf("//%20s:v%d   //%s\n", "", reg, type);

		}

		out.print(")\n {\n");
		clearRegisterValueMap();// TODO clear register map when function begin
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
			// out.printf("%-20s|%5s: line %d\n", "LABEL", "L"
			// + labelToString(label), line);
			StringBuilder sb = new StringBuilder();
			sb.append("L" + labelToString(label));
			sb.append(":\n");
			out.print(sb);
		} else {
			// LABEL | LL1:
			// out.printf("%-20s|%5s:\n", "LABEL", "L" + labelToString(label));
		}
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

	protected void nativeCONST(int opcode, String reg, String value) {

	}

	protected void nativeCONST_STRING(int opcode, String reg, String value) {

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
		recordRegister(reg, new Register(className, reg, localClass));
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

		boolean isVirtual = isVirtual(reg, className);

		sb.append(getCallFunction(
				getInvokeMethodByMethodSignature(signature, false, isVirtual),
				caller, methodId));

		sb.append("\n");

		out.print(sb);
	}

	private final boolean isVirtual(String reg, String methodClassName) {
		// if (getRegister(reg) != null) {
		// return getRegister(reg).type.equals(methodClassName);
		// }
		// return false;
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

		// sb.append(String.format("%s %s = ",
		// CALL_TYPE.get(getReturnTypeByMethodSignature(method)), temp));
		sb.append(String.format("%s %s = ",
				toJniType(getReturnSignatureByMethodSignature(method)), temp));

		String caller = getCallerByReg(reg);

		boolean isVirtual = isVirtual(reg, className);

		sb.append(getCallFunction(
				getInvokeMethodByMethodSignature(signature, false, isVirtual),
				caller, methodId));
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

	protected void nativeBinop(int opcode, int saveToReg, int opReg, int opReg2) {
		String opStr = null;
		switch (opcode) {
		case OP_AND:
			opStr = "&";
			break;
		case OP_OR:
			opStr = "|";
			break;
		case OP_XOR:
			opStr = "^";
			break;
		case OP_SUB:
			opStr = "-";
			break;
		case OP_MUL:
			opStr = "*";
			break;
		case OP_DIV:
			opStr = "/";
			break;
		case OP_ADD:
			opStr = "+";
			break;
		case OP_REM:
			opStr = "%%";
			break;
		default:
			throw new IllegalArgumentException();
		}

		out.print(String.format("v%d = v%d %s v%d", saveToReg, opReg, opStr,
				opReg2));
		out.println("\n");
		String register = "v" + saveToReg;
		String type = getRegister(register).type;
		recordRegister(register, new Register(type, register, register));
	}
}
