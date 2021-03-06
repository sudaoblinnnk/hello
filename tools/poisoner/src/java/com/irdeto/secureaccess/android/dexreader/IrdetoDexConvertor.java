package com.irdeto.secureaccess.android.dexreader;

import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.StringTokenizer;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

import com.googlecode.dex2jar.DexOpcodes;
import com.googlecode.dex2jar.Field;
import com.googlecode.dex2jar.Method;
import com.googlecode.dex2jar.util.Dump;
import com.googlecode.dex2jar.util.DumpDexCodeAdapter;
import com.googlecode.dex2jar.visitors.DexClassVisitor;
import com.googlecode.dex2jar.visitors.DexCodeVisitor;
import com.googlecode.dex2jar.visitors.DexFieldVisitor;
import com.googlecode.dex2jar.visitors.DexMethodVisitor;
import com.googlecode.dex2jar.visitors.EmptyVisitor;

public class IrdetoDexConvertor extends EmptyVisitor {

	static DexConfigure dexConfig = null;

	static final int PROCESS_NATIVE = 1;
	static final int PROCESS_JAVA = 2;

	private static final String INCLUDES = "#include <jni.h>\n#include <stdio.h>";

	private static final String OUTTER_CLASS_PTR = "this$0";

	private static final String SUBCLASS_DIV = "$";

	public static String[] AUTO_GENERATED_CLASS = { "BuildConfig", "R$", "R." };

	private static final String APP_PACKAGE = "com.irdeto.j2n.firstapplication";
	private static List<String> packageFilter = new ArrayList<String>();

	protected static final String APP_MAIN_ENTRANCE = APP_PACKAGE
			+ ".MainActivity";
	private static final String ROOT = "java/com/irdeto/j2n/firstapplication";
	static int processing = PROCESS_NATIVE;

	private static final String LINE = "_";

	static String nativeFile = "native.jar";
	static String javaFile = "java.jar";
	private static boolean isSubClass = false;
	private static boolean isStaticSubClass = true;

	public static final String LOCAL_CTOR = "<init>";
	public static final String LOCAL_NATIVE_INIT = "__initNative";
	public static final String JAVA_LANG_OBJECT = "java/lang/Object";
	public static final String INVOKE_FROM_NATIVE = "invokeFromNative__";
	protected static final String INVALID_METHOD_NAME = "@@@";

	protected static final String INVALID_METHOD_TYPE = "@@@";

	public interface WriterManager {
		PrintWriter get(String name);

		void flush();
	}

	public static abstract class AbstractWriterManager implements WriterManager {
		@Override
		public void flush() {

		}
		
		@Override
		public PrintWriter get(String name) {
			return null;
		}
	}

	private int class_count = 0;

	private PrintWriter out;

	private WriterManager writerManager;

	private List<String[]> nativeFunctions = new LinkedList<String[]>();

	private List<String> packageRegisterNativeSymbols = new ArrayList<String>();

	public IrdetoDexConvertor(WriterManager writerManager) {
		super();
		this.writerManager = writerManager;
	}

	private static class JavaCodeWriterManager extends AbstractWriterManager {
		private ZipOutputStream zos;
		private String fileType;

		public JavaCodeWriterManager(ZipOutputStream zs, String type) {
			fileType = type;
			zos = zs;
		}

		@Override
		public PrintWriter get(String name) {
			try {
				String s = name.replace('.', '/') + fileType;
				ZipEntry zipEntry = new ZipEntry(s);
				zos.putNextEntry(zipEntry);
				return new PrintWriter(zos) {
					@Override
					public void close() {
						try {
							zos.closeEntry();
						} catch (IOException e) {
							throw new RuntimeException(e);
						}
					}
				};
			} catch (Exception e) {
				throw new RuntimeException(e);
			}
		}
	}

	private static List<String> CodeList = new LinkedList<String>();

	private static class NativeCodeWriterManager extends AbstractWriterManager {
		private ZipOutputStream zos;
		private String fileType;

		public NativeCodeWriterManager(ZipOutputStream zs, String type) {
			fileType = type;
			zos = zs;
		}
		
		@Override
		public PrintWriter get(String name) {
			try {
				String s = name.replace('.', '/') + fileType;
				ZipEntry zipEntry = new ZipEntry(s);
				zos.putNextEntry(zipEntry);
				return new PrintWriter(zos) {
					@Override
					public void println(String x) {
						// super.println(x);
						CodeList.add(x);
					}

					@Override
					public void print(String x) {
						// super.print(x);
						CodeList.add(x);
					}

					@Override
					public void close() {
						try {
							zos.closeEntry();
						} catch (IOException e) {
							throw new RuntimeException(e);
						}
					}
				};
			} catch (Exception e) {
				throw new RuntimeException(e);
			}
		}
	}

	public static void doData(DexFileScanner dexFileReader, File destJar)
			throws IOException {
		final String fileType = ((PROCESS_NATIVE == processing) ? ".c"
				: ".java");
		final ZipOutputStream zos = new ZipOutputStream(
				new BufferedOutputStream(new FileOutputStream(destJar)));

		WriterManager wm = null;
		if (PROCESS_NATIVE == processing) {
			wm = new NativeCodeWriterManager(zos, fileType);
		} else {
			wm = new JavaCodeWriterManager(zos, fileType);
		}

		dexFileReader.accept(new IrdetoDexConvertor(wm));
		zos.finish();
		zos.close();
	}

	public static void doData(byte[] data, File destFile) throws IOException {
		doData(new DexFileScanner(data, dexConfig), destFile);
	}

	public static void doFile(File srcDex, File destFile) throws IOException {
		doData(DexFileScanner.readDex(srcDex), destFile);
	}

	public static String getAccDes(int acc) {
		StringBuilder sb = new StringBuilder();
		if ((acc & DexOpcodes.ACC_PUBLIC) != 0) {
			sb.append("public ");
		}
		if ((acc & DexOpcodes.ACC_PROTECTED) != 0) {
			sb.append("protected ");
		}
		if ((acc & DexOpcodes.ACC_PRIVATE) != 0) {
			sb.append("private ");
		}
		if ((acc & DexOpcodes.ACC_STATIC) != 0) {
			sb.append("static ");
		}
		if ((acc & DexOpcodes.ACC_ABSTRACT) != 0
				&& (acc & DexOpcodes.ACC_INTERFACE) == 0) {
			sb.append("abstract ");
		}
		if ((acc & DexOpcodes.ACC_ANNOTATION) != 0) {
			sb.append("annotation ");
		}
		if ((acc & DexOpcodes.ACC_BRIDGE) != 0) {
			sb.append("bridge ");
		}
		if ((acc & DexOpcodes.ACC_ENUM) != 0) {
			sb.append("enum ");
		}
		if ((acc & DexOpcodes.ACC_FINAL) != 0) {
			sb.append("final ");
		}
		if ((acc & DexOpcodes.ACC_INTERFACE) != 0) {
			sb.append("interface ");
		}
		if ((acc & DexOpcodes.ACC_NATIVE) != 0) {
			sb.append("native ");
		}
		if ((acc & DexOpcodes.ACC_STRICT) != 0) {
			sb.append("strict ");
		}
		if ((acc & DexOpcodes.ACC_SYNCHRONIZED) != 0) {
			sb.append("synchronized ");
		}
		if ((acc & DexOpcodes.ACC_TRANSIENT) != 0) {
			sb.append("transient ");
		}
		if ((acc & DexOpcodes.ACC_VARARGS) != 0) {
			sb.append("varargs ");
		}
		if ((acc & DexOpcodes.ACC_VOLATILE) != 0) {
			sb.append("volatile ");
		}
		return sb.toString();
	}

	static void setConfig() throws Exception {
		try {
			dexConfig = new DexConfigure();
		} catch (Exception e) {
			throw new Exception(e);
		}
	}

	static DexConfigure getConfig() {
		return dexConfig;
	}

	private static void mergeSubClass() {
		MergeSubClass.collectMainClasses(ROOT);
		MergeSubClass.removeAllCollectedClassesRightCurveBrace();
		MergeSubClass.walk(ROOT);
		MergeSubClass.addRightCurveBrace();
	}

	public static void main(String... args) throws Exception {
		if (args.length < 1) {
			System.out.println("Specify input file in DEX or APK");
			return;
		}
		System.out.println("\nReceiving file: " + args[0] + "\n");
		setConfig();

		packageFilter.add(APP_PACKAGE);

		processing = PROCESS_NATIVE;
		File output = new File(nativeFile);
		System.out
				.println("native file location : " + output.getAbsolutePath());
		doFile(new File(args[0]), output);

		String removeNativeJavaDir = "rm -rf java native";
		Command.exeCmd(removeNativeJavaDir);

		String extract = "unzip " + output.getAbsolutePath() + " -d native";
		Command.exeCmd(extract);
		System.out.println("\nDone!");

		processing = PROCESS_JAVA;
		output = new File(javaFile);
		System.out.println("java file location : " + output.getAbsolutePath());
		doFile(new File(args[0]), output);
		System.out.println("\nDone!");

		extract = "unzip " + output.getAbsolutePath() + " -d java";
		Command.exeCmd(extract);

		// mergeSubClass();
	}

	public static String toJavaClass(String desc) {
		switch (desc.charAt(0)) {
		case 'L':
			return desc.substring(1, desc.length() - 1).replace('/', '.');
		case 'B':
			return "byte";
		case 'S':
			return "short";
		case 'C':
			return "char";
		case 'I':
			return "int";
		case 'J':
			return "long";
		case 'F':
			return "float";
		case 'V':
			return "double";
		case 'D':
			return "void";
		case 'Z':
			return "boolean";
		case '[':
			return toJavaClass(desc.substring(1)) + "[]";
		}
		return desc;
	}

	StringBuilder deps = new StringBuilder();

	public void visitDepedence(String name, byte[] checksum) {
		deps.append("dep: " + name + ", checksum: ");
		for (byte element : checksum) {
			deps.append(String.format("%02x", element));
		}
		deps.append("\n");
	}

	public void visitEnd() {
		if (deps.length() > 0) {
			PrintWriter out = writerManager.get("depedence");
			out.print(deps.toString());
			out.flush();
			out.close();
		}
	}

	private String[] getPackageNameByClassName(String s) {
		StringTokenizer stringTokenizer = new StringTokenizer(s, ".");
		String className = "";
		while (stringTokenizer.hasMoreElements()) {
			className = stringTokenizer.nextElement().toString();
		}
		return new String[] {
				s.substring(0, s.length() - className.length() - 1), className };
	}

	public DexClassVisitor visit(int access_flags, final String className,
			String superClass, String[] interfaceNames) {

		isSubClass = false;
		isStaticSubClass = true;

		final String javaClassName = toJavaClass(className);
		out = writerManager.get(javaClassName);

		updateCurrentJavaClassName(javaClassName, access_flags);

		if (PROCESS_JAVA == processing) {

			String[] header = getPackageNameByClassName(javaClassName);
			String pkgName = header[0];
			String clsName = header[1];

			if (clsName.contains(SUBCLASS_DIV)) {
				isSubClass = true;
			}

			if (!isSubClass) {
				out.printf("package %s;\n", pkgName);
			}
			out.printf("//class:%04d  access:0x%04x\n", class_count++,
					access_flags);
			out.print(getAccDes(access_flags));
			if ((access_flags & DexOpcodes.ACC_INTERFACE) == 0) {
				out.print("class ");
			}
			if (isSubClass) {
				int i = clsName.indexOf(SUBCLASS_DIV) + 1;
				out.print(clsName.substring(i));
			} else {
				out.print(clsName);
			}

			if (superClass != null) {
				if (!"Ljava/lang/Object;".equals(superClass)) {
					out.print(" extends ");
					out.print(toJavaClass(superClass));
				}
			}
			if (interfaceNames != null && interfaceNames.length > 0) {
				out.print(" implements ");
				out.print(toJavaClass(interfaceNames[0]));
				for (int i = 1; i < interfaceNames.length; i++) {
					out.print(',');
					out.print(toJavaClass(interfaceNames[i]));
				}
			}

			StringBuilder sb = new StringBuilder();
			out.println("\n{\n");
			if (!clsName.contains("$")) { // skip inner class
				// sb.append(" static {System.loadLibrary(\"native-lib\");} ");
			} else {
				isSubClass = true;
			}
			out.println(sb.toString());
		} else if (PROCESS_NATIVE == processing) {
			nativeFunctions.clear();

			out.println(INCLUDES);
			out.printf("//class:%04d  access:0x%04x\n", class_count++,
					access_flags);
			out.print("//");
			out.print(getAccDes(access_flags));
			if ((access_flags & DexOpcodes.ACC_INTERFACE) == 0) {
				out.print("class ");
			}
			out.print(javaClassName);

			if (superClass != null) {
				if (!"Ljava/lang/Object;".equals(superClass)) {
					out.print(" extends ");
					out.print(toJavaClass(superClass));
				}
			}
			if (interfaceNames != null && interfaceNames.length > 0) {
				out.print(" implements ");
				out.print(toJavaClass(interfaceNames[0]));
				for (int i = 1; i < interfaceNames.length; i++) {
					out.print(',');
					out.print(toJavaClass(interfaceNames[i]));
				}
			}
		}
		out.println();

		return new EmptyVisitor() {

			int field_count = 0;

			int method_count = 0;

			@Override
			public void visitEnd() {
				if (PROCESS_JAVA == processing) {
					if (isSubClass && isStaticSubClass) {
						out.println("} ");
					} else {
						out.println("}");
					}
				} else if (PROCESS_NATIVE == processing) {
					registerNativeFunc();
					if (currentJavaClass.equals(APP_MAIN_ENTRANCE)) {
						jniOnLoadFunc();
					}
				}
				out.flush();
				out.close();
				out = null;
				super.visitEnd();
			}

			@Override
			public DexFieldVisitor visitField(int accesFlags, Field field,
					Object value) {

				out.printf("//field:%04d  access:0x%04x\n", field_count++,
						accesFlags);
				out.printf("//%s\n", field);

				if (PROCESS_NATIVE == processing) {

				} else if (PROCESS_JAVA == processing) {
					if (field.getName().equals(OUTTER_CLASS_PTR)) {
						if (isSubClass) {
							isStaticSubClass = false;
						}
					} else {
						String javaClass = Dump.toJavaClass(field.getType());
						out.printf("%s %s %s", getAccDes(accesFlags),
								javaClass, field.getName());
						if (value != null) {
							out.print('=');
							if (javaClass.equals("java.lang.String")) {
								out.print(String.format("\"%s\"", value));
							} else {
								out.print(value);
							}
						}
						out.println(';');
					}
				}

				return super.visitField(accesFlags, field, value);
			}

			private static final String NATIVE_METHOD_PREFIX = "Java_";
			private static final String NATIVE_PARAMETER_OBJECT = "JNIEnv * env, jobject ";
			private static final String NATIVE_PARAMETER_STATIC = "JNIEnv *env, jclass type";
			private static final String JNI_FUNCTION_DELCLEAR_FORMAT = "%s ";// "extern \"C\" JNIEXPORT %s JNICALL";

			private String handleInitMethod(final Method method) {
				String methodName = currentJavaClass;
				if (PROCESS_NATIVE == processing) {

					return methodName;
				} else if (PROCESS_JAVA == processing) {
					if (method.getName().equals(LOCAL_CTOR)) {
						methodName = LOCAL_NATIVE_INIT;
					}
					return methodName;
				}
				return methodName;
			}

			@Override
			public DexMethodVisitor visitMethod(final int accesFlags,
					final Method method) {
				isCurrentMethodConstructor = false;
				if (method.getName().contains("<clinit>")
						|| (accesFlags & DexOpcodes.ACC_NATIVE) != 0) {
					return super.visitMethod(accesFlags, method);
				}
				if (PROCESS_NATIVE == processing) {
					out.println();
					out.printf("//method:%04d  access:0x%04x\n",
							method_count++, accesFlags);
					out.printf("//%s\n", method);

					if ((currentJavaClassAccessFlags & DexOpcodes.ACC_INTERFACE) == DexOpcodes.ACC_INTERFACE) {
						return new EmptyVisitor();
					} else {
						if ((accesFlags & DexOpcodes.ACC_ABSTRACT) == DexOpcodes.ACC_ABSTRACT
								|| (accesFlags & DexOpcodes.ACC_NATIVE) == DexOpcodes.ACC_NATIVE) {
							return new EmptyVisitor();
						}
						String methodArgs;
						if ((accesFlags & DexOpcodes.ACC_STATIC) != 0) {
							methodArgs = NATIVE_PARAMETER_STATIC;
						} else {
							methodArgs = NATIVE_PARAMETER_OBJECT;
						}

						String funcReturn = INVALID_METHOD_TYPE;
						String methodName = INVALID_METHOD_NAME;

						if (method.getName().equals(LOCAL_CTOR)) {
							funcReturn = "void ";
							methodName = LOCAL_NATIVE_INIT;
							isCurrentMethodConstructor = true;
						} else {
							funcReturn = String.format(
									JNI_FUNCTION_DELCLEAR_FORMAT,
									DumpDexCodeAdapter.toJniType(method
											.getReturnType()));
							methodName = method.getName();
						}

						String funcName = String
								.format("%s%s",
										NATIVE_METHOD_PREFIX
												+ currentJavaClass.replace('.',
														'_') + LINE,
										methodName
												+ LINE
												+ Math.abs(method.getDesc()
														.hashCode()));

						String nativeFuncRegistrationInfo[] = new String[] {
								methodName, method.getDesc(), funcName };

						nativeFunctions.add(nativeFuncRegistrationInfo);

						out.printf("%s %s(", funcReturn, funcName);
						out.printf(String.format("%s", methodArgs));

						EmptyVisitor ev = new EmptyVisitor() {
							@Override
							public DexCodeVisitor visitCode() {
								return new DumpDexCodeAdapter(
										(accesFlags & DexOpcodes.ACC_STATIC) != 0,
										method, out);
							}

							@Override
							public void visitEnd() {
								out.println("}\n");
							}
						};
						return ev;
					}
				} else if (PROCESS_JAVA == processing) {

					out.println();
					if ((accesFlags & DexOpcodes.ACC_VARARGS) == DexOpcodes.ACC_VARARGS) {
						out.printf(getAccDes(accesFlags
								& ~DexOpcodes.ACC_VARARGS));
						if ((currentJavaClassAccessFlags & DexOpcodes.ACC_INTERFACE) != DexOpcodes.ACC_INTERFACE
								&& (accesFlags & DexOpcodes.ACC_ABSTRACT) != DexOpcodes.ACC_ABSTRACT
								&& (accesFlags & DexOpcodes.ACC_NATIVE) != DexOpcodes.ACC_NATIVE
								&& !method.getName().equals(LOCAL_CTOR)) {
							out.printf(" native ");
						}
						if (!method.getName().equals(LOCAL_CTOR)) {
							out.printf(" %s ",
									Dump.toJavaClass(method.getReturnType()));
						}

						String methodName = method.getName();
						if (method.getName().equals(LOCAL_CTOR)) {
							methodName = getPackageNameByClassName(javaClassName)[1];
						}
						out.printf(
								" %s",
								methodName
										+ method.getJavaParameterLastIsVarParameter());
						out.print(";");
						out.println();

					} else {
						out.printf(getAccDes(accesFlags));

						if ((currentJavaClassAccessFlags & DexOpcodes.ACC_INTERFACE) != DexOpcodes.ACC_INTERFACE
								&& (accesFlags & DexOpcodes.ACC_ABSTRACT) != DexOpcodes.ACC_ABSTRACT
								&& (accesFlags & DexOpcodes.ACC_NATIVE) != DexOpcodes.ACC_NATIVE
								&& !method.getName().equals(LOCAL_CTOR)) {
							out.printf(" native ");
						}

						String methodName;

						// generate code as below
						// ////////////////////////////////////////////////////////////////
						// public PlayerActivity()
						// {
						// __initNative();
						// };
						if (method.getName().equals(LOCAL_CTOR)) {
							methodName = getPackageNameByClassName(javaClassName)[1];
							out.printf(" %s",
									methodName + method.getJavaParameter());
							out.println();
							out.print("{" + "\n" + LOCAL_NATIVE_INIT
									+ method.getJavaParameterList() + ";"
									+ "\n" + "}");
							out.print(";");
						}

						// generate code as below
						// ////////////////////////////////////////////////////////////////
						// void native __initNative(); //this is constructor
						// or
						// private native void initializePlayer(); // this is
						// normal function

						String returnType = "";
						if (!method.getName().equals(LOCAL_CTOR)) {
							returnType = Dump.toJavaClass(method
									.getReturnType());
							methodName = method.getName();
						} else {
							returnType = " native void ";
							methodName = LOCAL_NATIVE_INIT;
						}
						generateJavaMethod(returnType, methodName, method);
						generateInvokeJavaMethod(returnType, methodName, method);
					}

					EmptyVisitor ev = new EmptyVisitor();
					return ev;
				}
				return super.visitMethod(accesFlags, method);
			}

			private void generateJavaMethod(String returnType,
					String methodName, Method method) {
				out.printf(" %s ", returnType);
				out.printf(" %s", methodName + method.getJavaParameter());
				out.print(";");
				out.println();
			}

			private void generateInvokeJavaMethod(String returnType,
					String methodName, Method method) {
				if (methodName.equals(LOCAL_NATIVE_INIT)) {
					return;
				}

				StringBuilder body = new StringBuilder();
				String obj = "obj";
				StringBuilder caller = new StringBuilder(currentJavaClass + " "
						+ obj);
				if (method.hasParameter()) {
					caller.append(", ");
				}

				body.append("\nprivate ");
				body.append(returnType);
				body.append(" ");
				body.append(INVOKE_FROM_NATIVE);
				body.append(methodName);
				body.append("(");
				body.append(caller);
				body.append(method.getJavaParameter().substring(1));
				body.append(" {");
				body.append("\n");
				body.append("  ");
				if (!returnType.equals("void")) {
					body.append("return ");
				}
				body.append(obj);
				body.append(".");
				body.append(methodName);
				body.append(method.getJavaParameterList());
				body.append(";\n");
				body.append(" }");
				body.append("\n");
				out.println(body);
			}
		};
	}

	private String currentJavaClass;
	public static boolean isCurrentMethodConstructor;
	private int currentJavaClassAccessFlags;

	private void updateCurrentJavaClassName(String javaClassName,
			int access_flags) {
		currentJavaClass = javaClassName;
		currentJavaClassAccessFlags = access_flags;
	}

	private static final String NATIVE_FUNCTION_REGIST_FUNCTION = "int registerNativeSymbols%s(JNIEnv * env) { "
			+ "\n"
			+ "int returnVal = JNI_TRUE; JNINativeMethod symbolListApi[] = { "
			+ "\n"
			+ "%s "
			+ "\n"
			+ "}; "
			+ "\n"
			+ "jclass clazz = (*env)->FindClass(env, \"%s\");"
			+ "\n"
			+ "if (clazz == NULL) { "
			+ "\n"
			+ " returnVal = JNI_FALSE; "
			+ "\n"
			+ "}"
			+ "\n"
			+ "if ((*env)->RegisterNatives(env, clazz, symbolListApi, sizeof(symbolListApi) / sizeof(symbolListApi[0])) < 0) {"
			+ "\n"
			+ "returnVal = JNI_FALSE; "
			+ "\n"
			+ "}"
			+ "\n"
			+ "return returnVal;" + "\n" + "}";

	private static int registerNativeFuncCount;

	private void registerNativeFunc() {
		if (nativeFunctions.isEmpty()) {
			return;
		}
		String nativeFuncListItem = "{\"%s\", \"%s\",  (void *)%s }";
		StringBuilder nativeFuncList = new StringBuilder();

		for (String[] item : nativeFunctions) {
			nativeFuncList.append(String.format(nativeFuncListItem, item[0],
					item[1], item[2]));
			nativeFuncList.append(",");
			nativeFuncList.append("\n");
		}
		if (nativeFuncList.length() > 0) {
			nativeFuncList.deleteCharAt(nativeFuncList.length() - 1);
		}

		String registerNativeSymbols = registerNativeSymbolsSuffix()
				+ registerNativeFuncCount++;

		packageRegisterNativeSymbols.add(registerNativeSymbols);

		String registCode = String.format(NATIVE_FUNCTION_REGIST_FUNCTION,
				registerNativeSymbols, nativeFuncList,
				currentJavaClass.replace('.', '/'));
		out.println(registCode);
	}

	private String registerNativeSymbolsSuffix() {
		return getPackageNameByClassName(currentJavaClass)[0].hashCode() + LINE;
	}

	private static final String JNI_ONLOAD_FUNC = "JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) { JNIEnv *env; jint registerResult = JNI_FALSE; if ((*vm)->GetEnv(vm, (void **) &env, JNI_VERSION_1_4) != JNI_OK) { return -1; } registerResult = %s return JNI_VERSION_1_4; }";

	private void jniOnLoadFunc() {
		out.println();
		StringBuilder regFuns = new StringBuilder();
		String registCode = "";
		for (int i = 0; i < packageRegisterNativeSymbols.size(); i++) {
			String registerNativeSymbols = packageRegisterNativeSymbols.get(i);
			for (int j = 0; j < packageFilter.size(); j++) {
				String suffix = packageFilter.get(j).hashCode() + "_";
				if (registerNativeSymbols.contains(suffix)) {
					regFuns.append(String.format(
							"registerNativeSymbols%s(env);\n",
							registerNativeSymbols));
				}
			}
		}
		registCode = String.format(JNI_ONLOAD_FUNC, regFuns);
		out.println(registCode);
	}

	private static class Command {
		public static void exeCmd(String commandStr) {
			BufferedReader br = null;
			try {
				Process p = Runtime.getRuntime().exec(commandStr);
				br = new BufferedReader(new InputStreamReader(
						p.getInputStream()));
				String line = null;
				StringBuilder sb = new StringBuilder();
				while ((line = br.readLine()) != null) {
					sb.append(line + "\n");
				}
				System.out.println(sb.toString());
			} catch (Exception e) {
				e.printStackTrace();
			} finally {
				if (br != null) {
					try {
						br.close();
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}
		}
	}

}
