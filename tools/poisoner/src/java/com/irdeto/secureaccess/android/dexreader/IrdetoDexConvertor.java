package com.irdeto.secureaccess.android.dexreader;

import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.List;
import java.util.StringTokenizer;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

import com.googlecode.dex2jar.DexOpcodes;
import com.googlecode.dex2jar.Field;
import com.googlecode.dex2jar.Method;
import com.googlecode.dex2jar.util.AbstractDumpDexCodeAdapter;
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

	private static final String INCLUDE = "#include <jni.h>";

	private static final String OUTTER_CLASS_PTR = "this$0";

	private static final String SUBCLASS_DIV = "$";

	static int processing = PROCESS_NATIVE;

	static String nativeFile = "native.jar";
	static String javaFile = "java.jar";
	private static boolean isSubClass = false;
	private static boolean isStaticSubClass = true;

	public interface WriterManager {
		PrintWriter get(String name);
	}

	private int class_count = 0;

	private PrintWriter out;

	private WriterManager writerManager;

	private List<String[]> nativeFunctions = new LinkedList<String[]>();

	public IrdetoDexConvertor(WriterManager writerManager) {
		super();
		this.writerManager = writerManager;
	}

	public static void doData(DexFileScanner dexFileReader, File destJar)
			throws IOException {
		final String fileType = ((PROCESS_NATIVE == processing) ? ".cpp"
				: ".java");

		final ZipOutputStream zos = new ZipOutputStream(
				new BufferedOutputStream(new FileOutputStream(destJar)));
		dexFileReader.accept(new IrdetoDexConvertor(new WriterManager() {

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
		}));
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
			sb.append("interace ");
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
		String root = "java/com/irdeto/j2n/firstapplication";
		MergeSubClass.collectMainClasses(root);
		MergeSubClass.removeRightCurveBrace();
		MergeSubClass.walk(root);
		MergeSubClass.addRightCurveBrace();
	}

	public static void main(String... args) throws Exception {
		if (args.length < 1) {
			System.out.println("Specify input file in DEX or APK");
			return;
		}
		System.out.println("\nReceiving file: " + args[0] + "\n");
		setConfig();

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

		mergeSubClass();
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

	public DexClassVisitor visit(int access_flags, String className,
			String superClass, String[] interfaceNames) {

		isSubClass = false;
		isStaticSubClass = true;

		String javaClassName = toJavaClass(className);
		out = writerManager.get(javaClassName);

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

			updateCurrentJavaClassName(javaClassName);

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
				sb.append(" static {System.loadLibrary(\"native-lib\");} ");
			} else {
				isSubClass = true;
			}
			out.println(sb.toString());
		} else if (PROCESS_NATIVE == processing) {
			nativeFunctions.clear();

			out.println(INCLUDE);
			out.printf("//class:%04d  access:0x%04x\n", class_count++,
					access_flags);
			out.print("//");
			out.print(getAccDes(access_flags));
			if ((access_flags & DexOpcodes.ACC_INTERFACE) == 0) {
				out.print("class ");
			}
			out.print(javaClassName);

			updateCurrentJavaClassName(javaClassName);

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
					if (isStaticSubClass) {
						out.println("} ");
					} else {
						out.println("}");
					}
				} else if (PROCESS_NATIVE == processing) {
					registerNativeFunc();
					jniOnLoadFunc();
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
						out.printf("%s %s %s", getAccDes(accesFlags),
								toJavaClass(field.getType()), field.getName());
						if (value != null) {
							out.print('=');
							out.print(value);
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

			@Override
			public DexMethodVisitor visitMethod(final int accesFlags,
					final Method method) {
				if (method.getName().contains("<init>")
						|| method.getName().contains("<clinit>")
						|| (accesFlags & DexOpcodes.ACC_NATIVE) != 0) {
					return super.visitMethod(accesFlags, method);
				}
				if (PROCESS_NATIVE == processing) {
					out.println();
					out.printf("//method:%04d  access:0x%04x\n",
							method_count++, accesFlags);
					out.printf("//%s\n", method);

					String methodArgs;
					if ((accesFlags & DexOpcodes.ACC_STATIC) != 0) {
						methodArgs = NATIVE_PARAMETER_STATIC;
					} else {
						methodArgs = NATIVE_PARAMETER_OBJECT;
					}

					String funcReturn = String.format(
							JNI_FUNCTION_DELCLEAR_FORMAT, DumpDexCodeAdapter
									.toJniType(method.getReturnType()));

					String funcName = String.format(
							"%s%s",
							NATIVE_METHOD_PREFIX
									+ currentJavaClass.replace('.', '_') + "_",
							method.getName());

					String nativeFuncRegistrationInfo[] = new String[] {
							method.getName(), method.getDesc(), funcName };

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
				} else if (PROCESS_JAVA == processing) {
					out.println();
					out.printf(getAccDes(accesFlags));
					out.printf(" native ");

					out.printf(" %s ", AbstractDumpDexCodeAdapter
							.toJavaClass(method.getReturnType()));
					out.printf(" %s",
							method.getName() + method.getJavaParameter());
					out.print(";\n");
					EmptyVisitor ev = new EmptyVisitor();
					return ev;
				}
				return super.visitMethod(accesFlags, method);
			}

		};
	}

	private String currentJavaClass;

	private void updateCurrentJavaClassName(String javaClassName) {
		currentJavaClass = javaClassName;
	}

	private static final String NATIVE_FUNCTION_REGIST_FUNCTION = "static int registerNativeSymbols%d(JNIEnv * env) { int returnVal = JNI_TRUE; JNINativeMethod symbolListApi[] = { %s }; "
			+ "clazz = env->FindClass(\"%s\");"
			+ "if (clazz == NULL) { returnVal = JNI_FALSE; }"
			+ "if (env->RegisterNatives(clazz, symbolListApi, sizeof(symbolListApi) / sizeof(symbolListApi[0])) < 0) {"
			+ "returnVal = JNI_FALSE; }" + "return returnVal;}";

	private static int registerNativeFuncCount;

	private void registerNativeFunc() {
		if (nativeFunctions.isEmpty()) {
			return;
		}
		String nativeFuncListItem = "{\"%s\", \"%s\",  (void *)\"%s\" }";
		StringBuilder nativeFuncList = new StringBuilder();

		for (String[] item : nativeFunctions) {
			nativeFuncList.append(String.format(nativeFuncListItem, item[0],
					item[1], item[2]));
			nativeFuncList.append(",");
		}
		if (nativeFuncList.length() > 0) {
			nativeFuncList.deleteCharAt(nativeFuncList.length() - 1);
		}

		String registCode = String.format(NATIVE_FUNCTION_REGIST_FUNCTION,
				registerNativeFuncCount++, nativeFuncList, currentJavaClass);
		out.printf(registCode);
	}

	private static final String JNI_ONLOAD_FUNC = "JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) { JNIEnv *env; jint registerResult = JNI_FALSE; if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) { return -1; } registerResult = %s return JNI_VERSION_1_4; }";

	private void jniOnLoadFunc() {
		out.println();
		StringBuilder regFuns = new StringBuilder();
		String registCode = "";
		for (int i = 0; i < registerNativeFuncCount; i++) {
			regFuns.append(String.format("registerNativeSymbols%d(env);\n", i));

		}
		registCode = String.format(JNI_ONLOAD_FUNC, regFuns);
		out.print(registCode);
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
