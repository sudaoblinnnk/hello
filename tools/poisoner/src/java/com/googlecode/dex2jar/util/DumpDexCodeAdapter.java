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

	// v0=0x00000000 // int:0 float:0.000000
	// j2n.irdeto.com.demo.MainActivity.debug=v0
	// //Lj2n/irdeto/com/demo/MainActivity;.debug Z
	// RETURN_VOID | |return

	// private V printLog()
	// this:v2 //j2n.irdeto.com.demo.MainActivity
	// LOCAL_VARIABLE LL0 ~ LL1 v2 -> this // Lj2n/irdeto/com/demo/MainActivity;
	// LABEL | LL0: line 20
	// SGET | |v0=j2n.irdeto.com.demo.MainActivity.debug
	// //Lj2n/irdeto/com/demo/MainActivity;.debug Z
	// IF_EQZ | |if v0 == 0 goto L2
	// LABEL | LL3: line 21
	// CONST_STRING | |v0="MainActivity"
	// v0="MainActivity"v0 = env->NewStringUTF("MainActivity")CONST_STRING |
	// |v1="printLog"
	// v1="printLog"v1 = env->NewStringUTF("printLog")INVOKE_STATIC |
	// |TEMP=android.util.Log.d(v0,v1)
	// //Landroid/util/Log;.d(Ljava/lang/String;Ljava/lang/String;)I
	// LABEL | LL2: line 23
	// RETURN_VOID | |return
	// LABEL | LL1:

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

		sb.append(getFindClass(className));
		sb.append("\n");

		sb.append(getField("field1", fieldName, typeSignature, true));
		sb.append("\n");

		sb.append(String.format(("%s "), type));

		sb.append(getFieldObject(varible, "localClazz1", "field1", true));
		sb.append("\n");
		out.println(sb);

	}

	private static String getField(String fieldId, String fieldName,
			String typeSignature, boolean isStatic) {
		return String.format(
				("jfield %s = env->%s(localClazz1, \"%s\", \"%s\");"), fieldId,
				isStatic ? "GetFieldID" : "GetStaticFieldID", fieldName,
				typeSignature);
	}

	private static String getFieldObject(String fieldObject, String className,
			String fieldName, boolean isStatic) {
		return String.format(("%s = env->%s(%s, %s);"), fieldObject,
				isStatic ? "GetObjectField" : "GetStaticObjectField",
				className, fieldName);
	}

	private static String getFindClass(String className) {
		return String.format(("jclass localClazz1 = env->FindClass(\"%s\");"),
				className);
	}

	private static String getClassNameFromclassNameSignature(
			String classNameSignature) {
		return classNameSignature.substring("\\L".length() - 1,
				classNameSignature.length() - 1);
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

		sb.append(getFindClass(className));
		sb.append("\n");

		sb.append(getField("field1", fieldName, typeSignature, true));
		sb.append("\n");

		sb.append(String.format(("env->SetStaticObjectField(%s, %s, %s);"),
				"localClazz1", "field1", varibleValue));

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
	}

	private static String getTypeSignature(String s) {
		return s;
	}

	private static String getType(String s) {
		if (TYPE_MAP.keySet().contains(s))
			return TYPE_MAP.get(s);
		if (s.startsWith(TYPE_OBJECT))
			return "jobject";
		return s;
	}

	private static String getInvokeMethodType(String s) {
		if (METHOD_TYPE_MAP.keySet().contains(s))
			return METHOD_TYPE_MAP.get(s);
		if (s.startsWith(TYPE_OBJECT))
			return "Object";
		throw new IllegalArgumentException();
	}

	private List<String> getClazzFieldName(String s) {
		System.out.println(s);
		if (s.length() < 4)
			throw new IllegalArgumentException();
		String c = s.substring(2);// skip //
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

	private void parseRETURN_OP(String s) {
		out.println(s + ";");
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

	// v0=Lcom/irdeto/aca/key/KeyLogic;.class
	private void parseCONST_CLASS_OP(String s) {
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
		return String.format("jmethodID %s = env->%s(\"%s\", \"%s\", \"%s\");",
				methodId, isStatic ? "GetStaticMethodID" : "GetMethodID",
				className, methodName, signature);
	}

	private static String getInvokeMethodByMethodSignature(
			String methedSignature, boolean isStatic) {
		int i = methedSignature.indexOf(')');
		String returnStr = methedSignature.substring(i + 1);
		String methodReturnType = getInvokeMethodType(returnStr);
		StringBuilder sb = new StringBuilder();
		sb.append("Call").append(isStatic ? "Static" : "")
				.append(methodReturnType).append("Method");
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

		sb.append(getFindClass(className));
		sb.append("\n");

		sb.append(getMethodStr("method1", className, methodName, signature,
				true));
		sb.append("\n");

		sb.append(getCallFunction(
				getInvokeMethodByMethodSignature(signature, isStatic), "obj",
				"method1"));
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
				parseCONST_CLASS_OP(s);
			} else if (opStr.equals(CONST_STRING_OP)) {
				parseCONST_STRING_OP(s);
			} else if (opStr.equals(SGET_OP)) {
				parseSGET_OP(s);
			} else if (opStr.equals(SPUT_OP)) {
				parseSPUT_OP(s);
			} else if (opStr.equals(IF_EQZ_OP)) {
				parseIF_EQZ_OP(s);
			} else if (opStr.equals(RETURN_OP)) {
				parseRETURN_OP(s);
			} else if (opStr.equals(RETURN_VOID_OP)) {
				parseRETURN_VOID_OP(s);
			} else if (opStr.equals(INVOKE_SUPER_OP)
					|| opStr.equals(INVOKE_DIRECT_OP)
					|| opStr.equals(INVOKE_VIRTUAL_OP)) {
				parseINVOKE_OP(s, false);
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
			out.printf("%20s:v%d   //%s\n", "this", reg, type);
		}
		for (String type : method.getParameterTypes()) {
			int reg = args[i++];
			type = Dump.toJavaClass(type);
			out.printf("%20s:v%d   //%s\n", "", reg, type);
		}
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
		// out.printf("LOCAL_VARIABLE L%s ~ L%s v%d -> %s // %s \n",
		// labelToString(start), labelToString(end), reg, name, type);

		// out.println("visitLocalVariable reg:" + reg);
		// out.println("visitLocalVariable name:" + name);
		// out.println("visitLocalVariable sig:" + signature);
		// out.println("visitLocalVariable type:" + type);

		String className = getClassNameFromclassNameSignature(type);
		StringBuilder sb = new StringBuilder();
		sb.append(getFindClass(className));
		sb.append("\n");
		String fieldId = String.format("field%d", reg);
		sb.append(getField(fieldId, name, type, false));
		sb.append("\n");

		sb.append(String.format(("%s "), getType(type)));
		sb.append(getFieldObject(String.format("v%d", reg), className, fieldId,
				false));
		sb.append("\n");

		out.print(sb);
	}

}
