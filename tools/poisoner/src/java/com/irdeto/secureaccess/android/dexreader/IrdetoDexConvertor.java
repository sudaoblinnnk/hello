package com.irdeto.secureaccess.android.dexreader;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

import com.googlecode.dex2jar.DexOpcodes;
import com.googlecode.dex2jar.Field;
import com.googlecode.dex2jar.Method;
import com.googlecode.dex2jar.util.DumpDexCodeAdapter;
import com.googlecode.dex2jar.visitors.DexClassVisitor;
import com.googlecode.dex2jar.visitors.DexCodeVisitor;
import com.googlecode.dex2jar.visitors.DexFieldVisitor;
import com.googlecode.dex2jar.visitors.DexMethodVisitor;
import com.googlecode.dex2jar.visitors.EmptyVisitor;

public class IrdetoDexConvertor extends EmptyVisitor {

	static DexConfigure dexConfig = null;
	static String dummyFile = "dummy.jar";

	public interface WriterManager {
		PrintWriter get(String name);
	}

	private int class_count = 0;

	private PrintWriter out;

	private WriterManager writerManager;

	public IrdetoDexConvertor(WriterManager writerManager) {
		super();
		this.writerManager = writerManager;
	}

	public static void doData(DexFileScanner dexFileReader, File destJar)
			throws IOException {

		final ZipOutputStream zos = new ZipOutputStream(
				new BufferedOutputStream(new FileOutputStream(destJar)));
		dexFileReader.accept(new IrdetoDexConvertor(new WriterManager() {

			public PrintWriter get(String name) {
				try {
					String s = name.replace('.', '/') + ".dump.txt";
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

	public static void main(String... args) throws Exception {
		if (args.length < 1) {
			System.out.println("Specify input file in DEX or APK");
			return;
		}
		System.out.println("\nReceiving file: " + args[0] + "\n");
		setConfig();
		File output = new File(dummyFile);
		System.out.println("dummy file location : " + output.getAbsolutePath());
		doFile(new File(args[0]), output);
		System.out.println("\nDone!");
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
		case 'D':
			return "double";
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

	public DexClassVisitor visit(int access_flags, String className,
			String superClass, String[] interfaceNames) {

		String javaClassName = toJavaClass(className);
		out = writerManager.get(javaClassName);
		out.printf("//class:%04d  access:0x%04x\n", class_count++, access_flags);
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
		out.println();
		return new EmptyVisitor() {

			int field_count = 0;

			int method_count = 0;

			@Override
			public void visitEnd() {
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
				out.printf("%s %s %s", getAccDes(accesFlags),
						toJavaClass(field.getType()), field.getName());
				if (value != null) {
					out.print('=');
					out.print(value);
				}
				out.println(';');

				return null;
			}

			private static final String NATIVE_METHOD_PREFIX = "Java_";
			private static final String NATIVE_PARAMETER_OBJECT = "JNIEnv * env, jobject  obj";
			private static final String NATIVE_PARAMETER_STATIC = "JNIEnv *env, jclass type";
			private static final String JNI_FUNCTION_DELCLEAR_FORMAT = "extern \"C\" JNIEXPORT %s JNICALL";

			@Override
			public DexMethodVisitor visitMethod(final int accesFlags,
					final Method method) {
				out.println();
				out.printf("//method:%04d  access:0x%04x\n", method_count++,
						accesFlags);
				out.printf("//%s\n", method);

				String staticMethodArgs;
				if ((accesFlags & DexOpcodes.ACC_STATIC) != 0) {
					staticMethodArgs = NATIVE_PARAMETER_STATIC;
				} else {
					staticMethodArgs = NATIVE_PARAMETER_OBJECT;
				}

				out.printf(
						"%s %s%s(",
						String.format(JNI_FUNCTION_DELCLEAR_FORMAT,
								toJavaClass(method.getReturnType())),
						NATIVE_METHOD_PREFIX
								+ currentJavaClass.replace('.', '_') + "_",
						method.getName());

				out.printf(String.format("%s", staticMethodArgs));

				String ps[] = method.getParameterTypes();
				if (ps != null && ps.length > 0) {
					out.print(toJavaClass(ps[0]));
					for (int i = 1; i < ps.length; i++) {
						out.print(',');
						out.print(toJavaClass(ps[i]));
					}
				}
				out.println(')');
				out.println("\n{");
				EmptyVisitor ev = new EmptyVisitor() {
					@Override
					public DexCodeVisitor visitCode() {
						return new DumpDexCodeAdapter(
								(accesFlags & DexOpcodes.ACC_STATIC) != 0,
								method, out);
					}
				};
				out.println("\n}");
				return ev;
			}

		};
	}

	private String currentJavaClass;

	private void updateCurrentJavaClassName(String javaClassName) {
		currentJavaClass = javaClassName;

	}
}
