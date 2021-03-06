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

import java.util.HashMap;
import java.util.Map;

import com.googlecode.dex2jar.DexLabel;
import com.googlecode.dex2jar.Field;
import com.googlecode.dex2jar.Method;
import com.googlecode.dex2jar.visitors.EmptyVisitor;

/**
 * @author <a href="mailto:pxb1988@gmail.com">Panxiaobo</a>
 * @version $Rev$
 */
public abstract class AbstractDumpDexCodeAdapter extends EmptyVisitor {

	protected static final String[] causes = new String[] { "no-error",
			"generic-error", "no-such-class", "no-such-field",
			"no-such-method", "illegal-class-access", "illegal-field-access",
			"illegal-method-access", "class-change-error",
			"instantiation-error" };

	protected abstract void info(int opcode, String format, Object... args);

	protected abstract String labelToString(DexLabel label);

	@Override
	public void visitArrayStmt(int opcode, int value, int array, int index,
			int xt) {
		String code = "";
		String code1 = "";
		switch (opcode) {
		case OP_APUT:
			code = "v%d[v%d]=v%d;";
			code1 = "%s[%s]=%s;";
			info(opcode, code, array, index, value);
			nativeAPUT(code1, array, index, value);
			break;
		case OP_AGET:
			code = "v%d=v%d[v%d];";
			code1 = "%s=%s[%s];";
			info(opcode, code, value, array, index);
			nativeAGET(code1, value, array, index);
			break;
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * com.googlecode.dex2jar.visitors.DexCodeAdapter#visitBinopLitXStmt(int,
	 * int, int, int)
	 */
	@Override
	public void visitBinopLitXStmt(int opcode, int saveToReg, int opReg,
			int value) {
		String code = "";
		String code1 = "";
		switch (opcode) {
		case OP_AND_INT_LIT_X:
			code = "v%d = v%d & %d;";
			code1 = "%s = %s & %s;";
			info(opcode, code, saveToReg, opReg, value);
			break;
		case OP_ADD_INT_LIT_X:
			code = "v%d = v%d + %d;";
			code1 = "%s = %s + %s;";
			info(opcode, code, saveToReg, opReg, value);
			break;
		case OP_REM_INT_LIT_X:
			code = "v%d = v%d %% %d;";
			code1 = "%s = %s %% %s;";
			info(opcode, code, saveToReg, opReg, value);
			break;
		case OP_DIV_INT_LIT_X:
			code = "v%d = v%d / %d;";
			code1 = "%s = %s / %s;";
			info(opcode, code, saveToReg, opReg, value);
			break;
		case OP_MUL_INT_LIT_X:
			code = "v%d = v%d * %d;";
			code1 = "%s = %s * %s;";
			info(opcode, code, saveToReg, opReg, value);
			break;
		case OP_SHR_INT_LIT_X:
			code = "v%d = v%d >> %d;";
			code1 = "%s = %s >> %s;";
			info(opcode, code, saveToReg, opReg, value);
			break;
		case OP_SHL_INT_LIT_X:
			code = "v%d = v%d << %d;";
			code1 = "%s = %s << %s;";
			info(opcode, code, saveToReg, opReg, value);
			break;
		case OP_USHR_INT_LIT_X:
			code = "v%d = v%d >>> %d;";
			code1 = "%s = %s >>> %s;";
			info(opcode, code, saveToReg, opReg, value);
			break;
		case OP_OR_INT_LIT_X:
			code = "v%d = v%d | %d;";
			code1 = "%s = %s | %s;";
			info(opcode, code, saveToReg, opReg, value);
			break;
		case OP_XOR_INT_LIT_X:
			code = "v%d = v%d ^ %d;";
			code1 = "%s = %s ^ %s;";
			info(opcode, code, saveToReg, opReg, value);
			break;
		}
		nativeBinopLitXStmt(opcode, code1, saveToReg, opReg, value);
	}

	@Override
	public void visitBinopStmt(int opcode, int saveToReg, int opReg,
			int opReg2, int xt) {
		String code = "";
		String code1 = "";
		switch (opcode) {
		case OP_AND:
			code = "v%d = v%d & v%d;";
			code1 = "%s = %s & %s;";
			info(opcode, code, saveToReg, opReg, opReg2);
			break;
		case OP_OR:
			code = "v%d = v%d | v%d;";
			code1 = "%s = %s | %s;";
			info(opcode, code, saveToReg, opReg, opReg2);
			break;
		case OP_XOR:
			code = "v%d = v%d ^ v%d;";
			code1 = "%s = %s ^ %s;";
			info(opcode, code, saveToReg, opReg, opReg2);
			break;
		case OP_SUB:
			code = "v%d = v%d - v%d;";
			code1 = "%s = %s - %s;";
			info(opcode, code, saveToReg, opReg, opReg2);
			break;
		case OP_MUL:
			code = "v%d = v%d * v%d;";
			code1 = "%s = %s * %s;";
			info(opcode, code, saveToReg, opReg, opReg2);
			break;
		case OP_DIV:
			code = "v%d = v%d / v%d;";
			code1 = "%s = %s / %s;";
			info(opcode, code, saveToReg, opReg, opReg2);
			break;
		case OP_ADD:
			code = "v%d = v%d + v%d;";
			code1 = "%s = %s + %s;";
			info(opcode, code, saveToReg, opReg, opReg2);
			break;
		case OP_REM:
			code = "v%d = v%d %% v%d;";
			code1 = "%s = %s %% %s;";
			info(opcode, code, saveToReg, opReg, opReg2);
			break;
		}
		nativeBinop(opcode, code1, saveToReg, opReg, opReg2);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.googlecode.dex2jar.visitors.DexCodeAdapter#visitTypeInsn(int,
	 * java.lang.String, int, int)
	 */
	@Override
	public void visitClassStmt(int opcode, int toReg, int fromReg, String type) {
		switch (opcode) {
		case OP_INSTANCE_OF:
			info(opcode, "v%d=v%d instanceof %s", toReg, fromReg,
					Dump.toJavaClass(type));
			nativeIntanceof(opcode, toReg, fromReg, type);
			break;
		case OP_NEW_ARRAY:
			String javaClass = Dump.toJavaClass(type);
			info(opcode, "v%d=new %s[v%d]", toReg, javaClass, fromReg);
			nativeNewArray(toReg, type, fromReg);
			break;
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.googlecode.dex2jar.visitors.DexCodeAdapter#visitTypeInsn(int,
	 * java.lang.String, int)
	 */
	@Override
	public void visitClassStmt(int opcode, int toReg, String type) {
		switch (opcode) {
		case OP_NEW_INSTANCE:
			info(opcode, "v%d=NEW %s", toReg, type);
			nativeNEW_INSTANCE(toReg, type);
			break;
		case OP_CHECK_CAST:
			info(opcode, "v%d=(%s) v%d", toReg, Dump.toJavaClass(type), toReg);
			break;
		}
	}

	@Override
	public void visitCmpStmt(int opcode, int distReg, int bB, int cC, int xt) {
		switch (opcode) {
		case OP_CMPL:
			info(opcode, "v%d = v%d cmpl v%d ", distReg, bB, cC);
			break;
		case OP_CMPG:
			info(opcode, "v%d = v%d cmpg v%d", distReg, bB, cC);
			break;
		case OP_CMP:
			info(opcode, "v%d = v%d cmp v%d", distReg, bB, cC);
			break;
		}
		nativeCmpStmt(opcode, distReg, bB, cC);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.googlecode.dex2jar.visitors.DexCodeAdapter#visitLdcInsn(int,
	 * java.lang.Object, int)
	 */
	@Override
	public void visitConstStmt(int opcode, int reg, Object value, int xt) {
		switch (opcode) {
		case OP_CONST:
			if (xt == TYPE_SINGLE) {
				info(opcode, "v%d=0x%08x  // int:%d   float:%f", reg, value,
						value, Float.intBitsToFloat((Integer) value));

				nativeCONST(opcode, String.format("v%d", reg),
						String.format("0x%08x", value), value);
			} else {
				info(opcode, "v%d=0x%016x  // long:%d   double:%f", reg, value,
						value, Double.longBitsToDouble((Long) value));

				nativeCONST(opcode, String.format("v%d", reg),
						String.format("0x%016x", value), value);
			}

			break;
		case OP_CONST_STRING:
			info(opcode, "v%d=\"%s\"", reg, value);
			nativeCONST_STRING(opcode, String.format("v%d", reg),
					String.format("\"%s\"", value));
			break;
		case OP_CONST_CLASS:
			info(opcode, "v%d=%s.class", reg, value);
			nativeCONST_CLASS(opcode, String.format("v%d", reg),
					String.format("%s", value), "class");
			break;
		default:
			info(opcode, "v%d=%s  //", reg, value);
			nativeCONST(opcode, String.format("v%d", reg),
					String.format("%s", value), value);
			break;
		}
	}

	@Override
	public void visitFieldStmt(int opcode, int fromOrToReg, Field field, int xt) {
		switch (opcode) {
		case OP_SPUT:
			info(opcode, "%s.%s=v%d  //%s", Dump.toJavaClass(field.getOwner()),
					field.getName(), fromOrToReg, field);
			nativeSPUT("v" + fromOrToReg, Dump.toJavaClass(field.getOwner()),
					field.getName(), field);
			break;
		case OP_SGET:
			info(opcode, "v%d=%s.%s  //%s", fromOrToReg,
					Dump.toJavaClass(field.getOwner()), field.getName(), field);
			nativeSGET("v" + fromOrToReg, Dump.toJavaClass(field.getOwner()),
					field.getName(), field);
			break;
		}
	}

	@Override
	public void visitFieldStmt(int opcode, int regFromOrTo, int owner_reg,
			Field field, int xt) {
		switch (opcode) {
		case OP_IGET:
			info(opcode, "v%d=v%d.%s  //%s", regFromOrTo, owner_reg,
					field.getName(), field);
			nativeIGET(regFromOrTo, owner_reg, field.getName(), field);
			break;
		case OP_IPUT:
			info(opcode, "v%d.%s=v%d  //%s", owner_reg, field.getName(),
					regFromOrTo, field);
			nativeIPUT(owner_reg, field.getName(), regFromOrTo, field);
			break;
		}
	}

	@Override
	public void visitFieldStmt(int opcode, int fromOrToReg, int objReg,
			int fieldoff, int xt) {
		switch (opcode) {
		case OP_IGET_QUICK:
			info(opcode, "Q+ v%d=v%d.fieldoff+%04x", fromOrToReg, objReg,
					fieldoff);
			break;
		case OP_IPUT_QUICK:
			info(opcode, "Q+ v%d.fieldoff+%04x=v%d", objReg, fieldoff,
					fromOrToReg);
			break;
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * com.googlecode.dex2jar.visitors.DexCodeAdapter#visitFillArrayInsn(int,
	 * int, int, int, java.lang.Object[])
	 */
	@Override
	public void visitFillArrayStmt(int opcode, int reg, int elemWidth,
			int initLength, Object[] values) {

		StringBuilder sb = new StringBuilder();
		for (Object value : values) {
			sb.append(',').append(value);
		}
		if (sb.length() > 0) {
			sb.deleteCharAt(0);
		}

		info(opcode, "v%d[0..%d]=[%s]", reg, initLength - 1, sb.toString());
		nativeFillArrayStmt(reg, initLength, values);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * com.googlecode.dex2jar.visitors.DexCodeAdapter#visitFilledNewArrayIns
	 * (int, java.lang.String, int[])
	 */
	@Override
	public void visitFilledNewArrayStmt(int opcode, int[] regs, String type) {
		info(opcode, "TEMP=new %s[%d]", Dump.toJavaClass(type.substring(1)),
				regs.length);
		for (int i = 0; i < regs.length; i++) {
			info(opcode, "TEMP[%d]=v%d", i, regs[i]);
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.googlecode.dex2jar.visitors.DexCodeAdapter#visitJumpInsn(int,
	 * int)
	 */
	@Override
	public void visitJumpStmt(int opcode, DexLabel label) {
		String code = "";
		switch (opcode) {
		case OP_GOTO:
			code = "goto %s;";
			info(opcode, code, labelToString(label));
			break;
		}
		nativeGoto(opcode, code, labelToString(label));
	}

	@Override
	public void visitJumpStmt(int opcode, int reg, DexLabel label) {
		String code = "";
		String code1 = "";
		switch (opcode) {
		case OP_IF_EQZ:
			code = "if (v%d == 0) { goto %s; }";
			code1 = "if (%s == 0) { goto %s; }";
			info(opcode, code, reg, labelToString(label));
			break;
		case OP_IF_NEZ:
			code = "if (v%d != 0) { goto %s; }";
			code1 = "if (%s != 0) { goto %s; }";
			info(opcode, code, reg, labelToString(label));
			break;
		case OP_IF_LTZ:
			code = "if (v%d <  0) { goto %s; }";
			code1 = "if (%s < 0) { goto %s; }";
			info(opcode, code, reg, labelToString(label));
			break;
		case OP_IF_GEZ:
			code = "if (v%d >= 0) { goto %s; }";
			code1 = "if (%s >= 0) { goto %s; }";
			info(opcode, code, reg, labelToString(label));
			break;
		case OP_IF_GTZ:
			code = "if (v%d >  0) { goto %s; }";
			code1 = "if (%s > 0) { goto %s; }";
			info(opcode, code, reg, labelToString(label));
			break;
		case OP_IF_LEZ:
			code = "if (v%d <= 0) { goto %s; }";
			code1 = "if (%s <= 0) { goto %s; }";
			info(opcode, code, reg, labelToString(label));
			break;
		}

		nativeIf(opcode, code1, reg, labelToString(label));
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.googlecode.dex2jar.visitors.DexCodeAdapter#visitJumpInsn(int,
	 * int, int, int)
	 */
	@Override
	public void visitJumpStmt(int opcode, int reg1, int reg2, DexLabel label) {
		String code = "";
		String code1 = "";
		switch (opcode) {
		case OP_IF_EQ:
			code = "if (v%d == v%d) {  goto %s; }";
			code1 = "if (%s == %s) {  goto %s; }";
			info(opcode, code, reg1, reg2, labelToString(label));
			break;
		case OP_IF_NE:
			code = "if (v%d != v%d) {  goto %s; }";
			code1 = "if (%s != %s) {  goto %s; }";
			info(opcode, code, reg1, reg2, labelToString(label));
			break;
		case OP_IF_LT:
			code = "if (v%d <  v%d) {  goto %s; }";
			code1 = "if (%s < %s) {  goto %s; }";
			info(opcode, code, reg1, reg2, labelToString(label));
			break;
		case OP_IF_GE:
			code = "if (v%d >= v%d) {  goto %s; }";
			code1 = "if (%s >= %s) {  goto %s; }";
			info(opcode, code, reg1, reg2, labelToString(label));
			break;
		case OP_IF_GT:
			code = "if (v%d >  v%d) {  goto %s; }";
			code1 = "if (%s > %s) {  goto %s; }";
			info(opcode, code, reg1, reg2, labelToString(label));
			break;
		case OP_IF_LE:
			code = "if (v%d <= v%d) {  goto %s; }";
			code1 = "if (%s <= %s) {  goto %s; }";
			info(opcode, code, reg1, reg2, labelToString(label));
			break;
		}
		nativeIf(opcode, code1, reg1, reg2, labelToString(label));
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * com.googlecode.dex2jar.visitors.DexCodeAdapter#visitLookupSwitchInsn(int,
	 * int, int, int[], int[])
	 */
	@Override
	public void visitLookupSwitchStmt(int opcode, int reg, DexLabel label,
			int[] cases, DexLabel[] label2) {
		info(opcode, "switch(v%d)", reg);
		for (int i = 0; i < cases.length; i++) {
			info(-1, "case %d: goto %s", cases[i], labelToString(label2[i]));
		}
		info(-1, "default: goto %s", labelToString(label));
	}

	@Override
	public void visitMethodStmt(int opcode, int[] args, int a) {
		StringBuilder sb = new StringBuilder();
		for (int arg : args) {
			sb.append('v').append(arg).append(',');
		}
		if (sb.length() > 0) {
			sb.setLength(sb.length() - 1);
		}
		switch (opcode) {
		case OP_INVOKE_SUPER_QUICK:
		case OP_INVOKE_VIRTUAL_QUICK:
			info(opcode, "Q+ TEMP=taboff+%04x(%s)", a, sb.toString());
			break;
		case OP_EXECUTE_INLINE:
			info(opcode, "Q+ TEMP=inline+%04x(%s)", a, sb.toString());
			break;
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.googlecode.dex2jar.visitors.DexCodeAdapter#visitMethodInsn(int,
	 * com.googlecode.dex2jar.Method, int[])
	 */
	@Override
	public void visitMethodStmt(int opcode, int[] regs, Method method) {

		switch (opcode) {
		case OP_INVOKE_STATIC: {
			int i = 0;
			StringBuilder sb = new StringBuilder();
			for (int j = 0; j < method.getParameterTypes().length; j++) {
				String regName = "v" + regs[i++];
				sb.append(getRegister(regName).value).append(',');
			}
			if (sb.length() > 0) {
				sb.deleteCharAt(sb.length() - 1);
			}
			if (method.getReturnType().equals("V")) {
				info(opcode, "%s.%s(%s)  //%s",
						Dump.toJavaClass(method.getOwner()), method.getName(),
						sb.toString(), method.toString());

				nativeVoidInvoke(opcode, null, method.getName(), sb.toString(),
						method);
			} else {
				info(opcode, "TEMP=%s.%s(%s)  //%s",
						Dump.toJavaClass(method.getOwner()), method.getName(),
						sb.toString(), method.toString());

				nativeReturnInvoke(opcode,
						String.format("TEMP%d", tempCounter++), null,
						method.getName(), sb.toString(), method);
			}
		}
			break;
		case OP_INVOKE_VIRTUAL:
		case OP_INVOKE_DIRECT:
		case OP_INVOKE_INTERFACE:
		case OP_INVOKE_SUPER: {
			int i = 1;
			StringBuilder sb = new StringBuilder();
			for (int j = 0; j < method.getParameterTypes().length; j++) {
				String regName = "v" + regs[i++];
				sb.append(getRegister(regName).value).append(',');
			}
			if (sb.length() > 0) {
				sb.deleteCharAt(sb.length() - 1);
			}
			if (method.getReturnType().equals("V")) {
				info(opcode, "v%d.%s(%s)  //%s", regs[0], method.getName(),
						sb.toString(), method);
				nativeVoidInvoke(opcode,
						getRegister(String.format("v%d", regs[0])).name,
						method.getName(), sb.toString(), method);
			} else {
				info(opcode, "TEMP=v%d.%s(%s)  //%s", regs[0],
						method.getName(), sb.toString(), method);
				nativeReturnInvoke(opcode,
						String.format("TEMP%d", tempCounter++),
						getRegister(String.format("v%d", regs[0])).name,
						method.getName(), sb.toString(), method);
			}
		}
			break;
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.googlecode.dex2jar.visitors.DexCodeAdapter#visitMonitorStmt(int,
	 * int)
	 */
	@Override
	public void visitMonitorStmt(int opcode, int reg) {
		switch (opcode) {
		case OP_MONITOR_ENTER:
			info(opcode, "lock v%d", reg);
			break;
		case OP_MONITOR_EXIT:
			info(opcode, "unlock v%d", reg);
			break;
		}
	}

	@Override
	public void visitMoveStmt(int opcode, int reg, int xt) {
		switch (opcode) {
		case OP_MOVE_RESULT:
			String register = String.format("v%d", reg);
			if (lastTemp != null) {
				info(opcode, register + "=" + lastTemp.value);
				nativeMoveResult(reg, lastTemp);
			} else {
				info(opcode, register + "=" + "kurt");
			}

			break;
		case OP_MOVE_EXCEPTION:
			info(opcode, "v%d=@Exception", reg);
			nativeMoveResult(reg);
			break;
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.googlecode.dex2jar.visitors.DexCodeAdapter#visitMoveStmt(int,
	 * int, int)
	 */
	@Override
	public void visitMoveStmt(int opcode, int toReg, int fromReg, int xt) {
		switch (opcode) {
		case OP_MOVE:
			info(opcode, "v%d = v%d", toReg, fromReg);
			nativeMoveStmt(opcode, toReg, fromReg);
			break;
		}
	}

	@Override
	public void visitReturnStmt(int opcode) {
		switch (opcode) {
		case OP_RETURN_VOID:
			info(opcode, "return");
			nativeReturnVoidStmt("return");
			break;
		}
	}

	@Override
	public void visitReturnStmt(int opcode, int reg, int xt) {
		switch (opcode) {
		case OP_RETURN:
			info(opcode, "return v%d", reg);
			nativeReturnStmt(opcode, reg);
			break;
		case OP_THROW:
			info(opcode, "throw v%d", reg);
			break;
		}
	}

	@Override
	public void visitReturnStmt(int opcode, int cause, Object ref) {
		String c = cause >= causes.length ? "unknown" : causes[cause];
		info(opcode, "Q+ throw new VerificationError(%s)", c);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * com.googlecode.dex2jar.visitors.DexCodeAdapter#visitTableSwitchInsn(int,
	 * int, int, int, int, int[])
	 */
	@Override
	public void visitTableSwitchStmt(int opcode, int reg, DexLabel label,
			int first_case, int last_case, DexLabel[] labels) {
		String code = "switch(%s)";
		code += "\n{";

		info(opcode, "switch(v%d)", reg);
		for (int i = 0; i < labels.length; i++) {
			String caseStmt = String.format("case %d: goto %s;",
					first_case + i, labelToString(labels[i]));
			code += "\n";
			code += caseStmt;
			info(opcode, caseStmt);
		}
		String defaultStmt = String.format("default: goto %s;",
				labelToString(label));
		info(opcode, defaultStmt);
		code += "\n";
		code += defaultStmt;
		code += "\n}";
		nativeSwitchStmt(opcode, code, "v" + reg, label, first_case, last_case,
				labels);
	}

	@Override
	public void visitUnopStmt(int opcode, int saveToReg, int opReg, int xt) {
		String code = "";
		String code1 = "";
		switch (opcode) {
		case OP_NEG:
			code = "v%d = ~v%d";
			code1 = "%s = ~%s;";
			info(opcode, code, saveToReg, opReg);
			break;
		case OP_NOT:
			code = "v%d = !v%d";
			code1 = "%s = !%s;";
			info(opcode, code, saveToReg, opReg);
			break;
		case OP_ARRAY_LENGTH:
			code = "v%d = v%d.length";
			code1 = "%s = %s.length;";
			info(opcode, code, saveToReg, opReg);
			break;
		}
		nativeUnopStmt(opcode, code1, saveToReg, opReg);
	}

	@Override
	public void visitUnopStmt(int opcode, int saveToReg, int opReg, int xta,
			int xtb) {
		String code = "";
		String code1 = "";

		switch (opcode) {
		case OP_X_TO_Y:
			switch (xtb) {
			case TYPE_BOOLEAN:
				code = "v%d = (boolean)v%d";
				code1 = "%s = (boolean) %s;";
				info(opcode, code, saveToReg, opReg);
				break;
			case TYPE_BYTE:
				code = "v%d = (byte)v%d";
				code1 = "%s = (byte) %s;";
				info(opcode, code, saveToReg, opReg);
				break;
			case TYPE_CHAR:
				code = "v%d = (char)v%d";
				code1 = "%s = (char) %s";
				info(opcode, code, saveToReg, opReg);
				break;
			case TYPE_DOUBLE:
				code = "v%d = (double)v%d";
				code1 = "%s = (double) %s;";
				info(opcode, code, saveToReg, opReg);
				break;
			case TYPE_FLOAT:
				code = "v%d = (float)v%d";
				code1 = "%s = (float) %s;";
				info(opcode, code, saveToReg, opReg);
				break;
			case TYPE_INT:
				code = "v%d = (int)v%d";
				code1 = "%s = (int) %s;";
				info(opcode, code, saveToReg, opReg);
				break;
			case TYPE_LONG:
				code = "v%d = (long)v%d";
				code1 = "%s = (long) %s;";
				info(opcode, code, saveToReg, opReg);
				break;
			case TYPE_SHORT:
				code = "v%d = (short)v%d";
				code1 = "%s = (short) %s;";
				info(opcode, code, saveToReg, opReg);
				break;
			}
			break;
		}
		nativeCast(xtb, code1, saveToReg, opReg);
	}

	protected abstract void nativeCONST(int opcode, String reg, String value,
			Object valueObject);

	protected abstract void nativeCONST_STRING(int opcode, String reg,
			String value);

	protected abstract void nativeCONST_CLASS(int opcode, String reg,
			String value, String cls);

	protected abstract void nativeVoidInvoke(int opcode, String reg,
			String methodName, String param, Method method);

	protected abstract void nativeReturnInvoke(int opcode, String temp,
			String reg, String methodName, String param, Method method);

	protected abstract void nativeReturnStmt(int opcode, int reg);

	protected abstract void nativeReturnVoidStmt(String reg);

	protected abstract void nativeBinop(int op, String code, int saveToReg,
			int opReg, int opReg2);

	protected abstract void nativeSGET(String fromOrToReg, String fieldOwner,
			String fieldName, Field field);

	protected abstract void nativeSPUT(String fromOrToReg, String fieldOwner,
			String fieldName, Field field);

	protected abstract void nativeIGET(int regFromOrTo, int owner_reg,
			String fieldName, Field field);

	protected abstract void nativeIPUT(int owner_reg, String fieldName,
			int regFromOrTo, Field field);

	protected abstract void nativeNEW_INSTANCE(int toReg, String type);

	protected abstract void nativeIf(int opcode, String code, int reg,
			String labelToString);

	protected abstract void nativeIf(int opcode, String code, int reg1,
			int reg2, String labelToString);

	protected abstract void nativeGoto(int opcode, String code,
			String labelToString);

	protected abstract void nativeBinopLitXStmt(int opcode, String code,
			int saveToReg, int opReg, int value);

	protected abstract void nativeNewArray(int toReg, String javaClass,
			int fromReg);

	protected abstract void nativeFillArrayStmt(int reg, int initLength,
			Object[] values);

	protected abstract void nativeAGET(String code, int value, int array,
			int index);

	protected abstract void nativeAPUT(String code, int array, int index,
			int value);

	protected abstract void nativeUnopStmt(int opcode, String code1,
			int saveToReg, int opReg);

	protected abstract void nativeMoveStmt(int opcode, int toReg, int fromReg);

	protected abstract void nativeIntanceof(int opcode, int toReg, int fromReg,
			String type);

	protected abstract void nativeCast(int opcode, String code1, int saveToReg,
			int opReg);

	protected abstract void nativeCmpStmt(int opcode, int distReg, int bB,
			int cC);

	protected abstract void nativeMoveResult(int reg, Register temp);

	protected abstract void nativeMoveResult(int reg);

	protected abstract void nativeSwitchStmt(int opcode, String code,
			String string, DexLabel label, int first_case, int last_case,
			DexLabel[] labels);

	// ////////////////////////////////////////////////////////////////////

	public static class Register {
		String type;
		String name;
		String value;

		public Register(String t, String n) {
			if (argumentRegister.keySet().contains(n)) {
				// throw new RuntimeException("argment could not be set.");
				init(t, n, n);// TODO kurt
				return;
			}

			if (!registerValueMap.keySet().contains(n)) {
				String v = n + "_0";
				init(t, n, v);
			} else {
				String v = (String) registerValueMap.get(n).value;
				int i = v.lastIndexOf("_");
				if (i < 0) {// TODO kurt
					init(t, n, n);
					return;
				}
				String major = v.substring(0, i);
				String minor = v.substring(i + 1);
				String minor_plus_one = String
						.valueOf(Integer.parseInt(minor) + 1);
				String newValue = major + "_" + minor_plus_one;
				init(t, n, newValue);
			}
		}

		public Register(String t, String n, String v) {
			init(t, n, v);
		}

		private void init(String t, String n, String v) {
			type = t;
			name = n;
			value = v;
		}

		public void setValue(String v) {
			value = v;
		}

		public String toString() {
			return "type = " + type + ", name = " + name + ", value = " + value;
		}
	}

	public static class RegisterTemp extends Register {

		public RegisterTemp(String t, String n, String v) {
			super(t, n, v);
		}

	}

	protected static Map<String, Register> registerValueMap = new HashMap<String, Register>();
	protected static Map<String, Register> argumentRegister = new HashMap<String, Register>();

	protected int tempCounter = 0;
	protected RegisterTemp lastTemp;

	protected void updateTEMP(RegisterTemp rt) {
		lastTemp = rt;
	}

	protected boolean setRegister(String type, String register,
			String externalValue) {
		if (!registerValueMap.keySet().contains(register)) {
			registerValueMap.put(register, new Register(type, register));
			return true;
		}
		boolean isNew = false;
		if (!getRegister(register).type.equals(type)) {
			registerValueMap.put(register, new Register(type, register));
			isNew = true;
		}
		if (externalValue != null) {
			registerValueMap.put(register, new Register(type, register,
					externalValue));
		}
		return isNew;
	}

	protected Register getRegister(String register) {
		if (argumentRegister.keySet().contains(register)) {
			return argumentRegister.get(register);
		}
		Register r = registerValueMap.get(register);
		if (r == null) {
			r = new Register("kurt1", register, "kurt2_" + register);
		}
		return r;
	}

	protected void clearRegisterValueMap() {
		argumentRegister.clear();
		registerValueMap.clear();
	}

	protected void addArgumentRegisters(String r, Register reg) {
		argumentRegister.put(r, reg);
	}

	// ////////////////////////////////////////////////////////////////////
	private static String currentLabel;

	public static void updateCurrentLabel(String label) {
		currentLabel = label;
	}

	public static class ReturnBlock {
		public String label;
		public Register register;

		public ReturnBlock(String l, Register r) {
			label = l;
			register = r;
		}
	}

	private static ReturnBlock returnBlock;

	protected static void saveReturnBlock(Register register) {
		if (currentLabel == null) {
			throw new NullPointerException("currentLabel is null");
		}
		if (returnBlock != null) {
			throw new RuntimeException("returnBlock already set.");
		}
		returnBlock = new ReturnBlock(currentLabel, register);
	}

	protected static String checkUnconditionGoto(String label) {
		String ret = null;
		if (returnBlock != null) {
			if (label.equals(returnBlock.label)) {
				Register returnBlockRegister = returnBlock.register;
				Register currentGotoRegister = registerValueMap
						.get(returnBlock.register.name);

				if (currentGotoRegister != null) {
					ret = returnBlockRegister.value + " = "
							+ currentGotoRegister.value + ";";
				} else {
					if (argumentRegister.containsKey(returnBlock.register.name)) {
						// return argument. this code is ok.
						// example:
						// com/google/android/exoplayer2/text/webvtt/WebvttCue\$Builder.c
						// derivePositionAnchorFromAlignment function will come
						// here.
					} else {
						//
						ret = "error register .";
					}
				}
			}
		}
		return ret;
	}

	protected static void clearReturnBlockWhenNewMethodStart() {
		currentLabel = null;
		returnBlock = null;
	}

}
