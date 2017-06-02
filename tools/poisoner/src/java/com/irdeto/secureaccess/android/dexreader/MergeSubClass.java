package com.irdeto.secureaccess.android.dexreader;

import static java.lang.System.out;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.file.FileVisitResult;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.SimpleFileVisitor;
import java.nio.file.attribute.BasicFileAttributes;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class MergeSubClass {

	public static final int BUFSIZE = 1024 * 8;
	private static final String DIV = "$";

	private static Set<String> mainClasses = new HashSet<String>();

	private static void addRightCurveBrace(String outFile) {
		BufferedWriter writer = null;
		try {
			writer = new BufferedWriter(new FileWriter(outFile, true));
			writer.write("}");

		} catch (IOException e) {
		} finally {
			try {
				if (writer != null)
					writer.close();
			} catch (IOException e) {
			}
		}
	}

	/*
	 * public static void mergeFiles(String outFile, String[] files) {
	 * 
	 * FileChannel outChannel = null; // out.println("Merge " +
	 * Arrays.toString(files) + " into " + outFile); try { outChannel = new
	 * FileOutputStream(outFile, true).getChannel(); for (String f : files) {
	 * FileChannel fc = new FileInputStream(f).getChannel(); //
	 * outChannel.position(outChannel.size()); // fc.transferTo(0, fc.size(),
	 * outChannel); ByteBuffer bb = ByteBuffer.allocate(BUFSIZE);
	 * 
	 * // /////// by check last - 2 byte == ' ' , judge this class is // static
	 * class. ////////////////////////////////////// fc.position(fc.size() - 2);
	 * if (fc.read(bb) != -1) { if (bb.get(0) == ' ') {
	 * System.out.println("======= " + Arrays.toString(files) +
	 * "static method");
	 * outChannel.write(ByteBuffer.wrap("static ".getBytes())); } }
	 * fc.position(0); //
	 * ///////////////////////////////////////////////////////////
	 * 
	 * while (fc.read(bb) != -1) { bb.flip(); outChannel.write(bb); bb.clear();
	 * }
	 * 
	 * fc.close(); } out.println("Merged!! "); } catch (IOException ioe) {
	 * ioe.printStackTrace(); } finally { try { if (outChannel != null) {
	 * outChannel.close(); } } catch (IOException ignore) { } } }
	 */
	public static void mergeFiles(String outFile, String[] files) {
		BufferedWriter writer = null;
		// FileChannel outChannel = null;
		// out.println("Merge " + Arrays.toString(files) + " into " + outFile);
		try {
			// outChannel = new FileOutputStream(outFile, true).getChannel();
			writer = new BufferedWriter(new FileWriter(outFile, true));
			for (String f : files) {
				FileChannel fc = new FileInputStream(f).getChannel();
				// outChannel.position(outChannel.size());
				// fc.transferTo(0, fc.size(), outChannel);
				ByteBuffer bb = ByteBuffer.allocate(BUFSIZE);

				// /////// by check last - 2 byte == ' ' , judge this class is
				// static class. //////////////////////////////////////
				fc.position(fc.size() - 2);
				if (fc.read(bb) != -1) {
					if (bb.get(0) == ' ') {
						System.out.println("======= " + Arrays.toString(files)
								+ "static method");
						// outChannel.write(ByteBuffer.wrap("static ".getBytes()));
						writer.write("static ");
					}
				}
				fc.position(0);
				fc.close();
				// ///////////////////////////////////////////////////////////
				BufferedReader reader = new BufferedReader(new FileReader(f));
				String content = null;
				while ((content = reader.readLine()) != null) {
					// bb.flip();
					// outChannel.write(bb);
					writer.write(content);
					writer.write("\n");
					// bb.clear();
				}
				reader.close();

			}
			out.println("Merged!! ");
		} catch (IOException ioe) {
			ioe.printStackTrace();
		} finally {
			try {
				// if (outChannel != null) {
				// outChannel.close();
				// }
				if (writer != null)
					writer.close();
			} catch (IOException ignore) {
			}
		}
	}

	private static String removeJavaSuffix(String fileName) {
		return fileName.substring(0, fileName.length() - 5);
	}

	private static String[] getClassMainAndSubNames(String fileName) {
		int i = fileName.indexOf(DIV);

		return new String[] { fileName.substring(0, i),
				fileName.substring(i + 1) };
	}

	public static void collectMainClasses(String root) {
		mainClasses.clear();
		try {
			Path startPath = Paths.get(root);
			Files.walkFileTree(startPath, new SimpleFileVisitor<Path>() {
				@Override
				public FileVisitResult preVisitDirectory(Path dir,
						BasicFileAttributes attrs) {
					return FileVisitResult.CONTINUE;
				}

				@Override
				public FileVisitResult visitFile(Path file,
						BasicFileAttributes attrs) {
					String fileName = removeJavaSuffix(file.getFileName()
							.toString());

					if (file.getFileName().toString().contains(DIV)) {
						String classNames[] = getClassMainAndSubNames(fileName);
						String outClass = file.getParent() + "/"
								+ classNames[0] + ".java";

						mainClasses.add(outClass);
					}
					return FileVisitResult.CONTINUE;
				}

				@Override
				public FileVisitResult visitFileFailed(Path file, IOException e) {
					return FileVisitResult.CONTINUE;
				}
			});
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static void walk(String root) {
		try {
			Path startPath = Paths.get(root);
			Files.walkFileTree(startPath, new SimpleFileVisitor<Path>() {
				@Override
				public FileVisitResult preVisitDirectory(Path dir,
						BasicFileAttributes attrs) {
					// System.out.println("Dir: " + dir.toString());
					return FileVisitResult.CONTINUE;
				}

				@Override
				public FileVisitResult visitFile(Path file,
						BasicFileAttributes attrs) {
					// System.out.println("File: " + file.toString());
					String fileName = removeJavaSuffix(file.getFileName()
							.toString());
					System.out.println("FileName : " + file.getParent());
					if (file.getFileName().toString().contains(DIV)) {
						String classNames[] = getClassMainAndSubNames(fileName);
						// System.out.println("mainclass : " + classNames[0] +
						// "\n subclass : " + classNames[1]);
						String outClass = file.getParent() + "/"
								+ classNames[0] + ".java";
						mergeFiles(outClass, new String[] { file.toString() });
					}
					return FileVisitResult.CONTINUE;
				}

				@Override
				public FileVisitResult visitFileFailed(Path file, IOException e) {
					return FileVisitResult.CONTINUE;
				}
			});
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static void addRightCurveBrace() {
		for (String mainClass : mainClasses) {
			addRightCurveBrace(mainClass);
		}
	}

	private static void removeRightCurveBrace(String mainClass) {
		FileChannel outChannel = null;
		try {
			outChannel = new FileOutputStream(mainClass, true).getChannel();
			outChannel.truncate(outChannel.size() - 3);
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if (outChannel != null) {
					outChannel.close();
				}
			} catch (IOException ignore) {
			}
		}
	}

	public static void removeAllCollectedClassesRightCurveBrace() {
		for (String mainClass : mainClasses) {
			removeRightCurveBrace(mainClass);
		}
	}
}
