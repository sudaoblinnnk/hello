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
package com.googlecode.dex2jar;

import java.util.Arrays;

import com.googlecode.dex2jar.util.Dump;

/**
 * represent a method_id_item in dex file format
 * 
 * @author <a href="mailto:pxb1988@gmail.com">Panxiaobo</a>
 * @version $Rev$
 */
public class Method {
	/**
	 * descriptor of the method, this will build after {@link #getDesc()}.
	 */
	private String desc;
	/**
	 * name of the method.
	 */
	private String name;
	/**
	 * owner class of the method, in TypeDescriptor format.
	 */
	private String owner;
	/**
	 * parameter types of the method, in TypeDescriptor format.
	 */
	private String[] parameterTypes;

	/**
	 * return type of the method, in TypeDescriptor format.
	 */
	private String returnType;

	public Method(String owner, String name, String[] parameterTypes,
			String returnType) {
		this.owner = owner;
		this.name = name;
		this.parameterTypes = parameterTypes;
		this.returnType = returnType;
	}

	public String getDesc() {
		if (desc == null) {
			StringBuilder ps = new StringBuilder("(");
			if (parameterTypes != null) {
				for (String t : parameterTypes) {
					ps.append(t);
				}
			}
			ps.append(")").append(returnType);
			desc = ps.toString();
		}
		return desc;
	}

	// parameter list(int n, int[] a)
	public String getJavaParameterLastIsVarParameter() {
		int paramter = 0;
		StringBuilder ps = new StringBuilder("(");
		if (parameterTypes != null) {
			int i = 0;
			for (i = 0; i < parameterTypes.length - 1; i++) {
				String t = parameterTypes[i];
				ps.append(Dump.toJavaClass(t));
				ps.append(" p");
				ps.append(paramter++);
				ps.append(',');
			}
			String t = parameterTypes[i];
			ps.append(Dump.toJavaClass(t));
			// delete []
			ps.deleteCharAt(ps.length() - 1);
			ps.deleteCharAt(ps.length() - 1);
			ps.append("...");

			ps.append(" p");
			ps.append(paramter++);
		}
		ps.append(")");
		return ps.toString();
	}

	public String getJavaParameterLastIsVarParameterList() {
		int paramter = 0;
		StringBuilder ps = new StringBuilder("(");
		if (parameterTypes != null) {
			int i = 0;
			for (i = 0; i < parameterTypes.length - 1; i++) {
				String t = parameterTypes[i];
				ps.append(" p");
				ps.append(paramter++);
				ps.append(',');
			}
			String t = parameterTypes[i];
			// delete []
			ps.deleteCharAt(ps.length() - 1);
			ps.deleteCharAt(ps.length() - 1);
			ps.append("...");

			ps.append(" p");
			ps.append(paramter++);
		}
		ps.append(")");
		return ps.toString();
	}

	public boolean hasParameter() {
		return (parameterTypes != null) && parameterTypes.length > 0;
	}

	public String getJavaParameter() {
		int paramter = 0;
		StringBuilder ps = new StringBuilder("(");
		if (parameterTypes != null) {
			for (String t : parameterTypes) {
				ps.append(Dump.toJavaClass(t));
				ps.append(" p");
				ps.append(paramter++);
				ps.append(',');
			}
			if (paramter > 0) {
				ps.deleteCharAt(ps.length() - 1);
			}
		}
		ps.append(")");
		return ps.toString();
	}

	public String getJavaParameterList() {
		int paramter = 0;
		StringBuilder ps = new StringBuilder("(");
		if (parameterTypes != null) {
			for (String t : parameterTypes) {
				ps.append(" p");
				ps.append(paramter++);
				ps.append(',');
			}
			if (paramter > 0) {
				ps.deleteCharAt(ps.length() - 1);
			}
		}
		ps.append(")");
		return ps.toString();
	}

	/**
	 * @return the name
	 */
	public String getName() {
		return name;
	}

	/**
	 * @return the owner
	 */
	public String getOwner() {
		return owner;
	}

	/**
	 * @return the parameterTypes
	 */
	public String[] getParameterTypes() {
		return parameterTypes;
	}

	public String getReturnType() {
		return returnType;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((name == null) ? 0 : name.hashCode());
		result = prime * result + ((owner == null) ? 0 : owner.hashCode());
		result = prime * result + Arrays.hashCode(parameterTypes);
		result = prime * result
				+ ((returnType == null) ? 0 : returnType.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj) {
			return true;
		}
		if (obj == null) {
			return false;
		}
		if (getClass() != obj.getClass()) {
			return false;
		}
		Method other = (Method) obj;
		if (name == null) {
			if (other.name != null) {
				return false;
			}
		} else if (!name.equals(other.name)) {
			return false;
		}
		if (owner == null) {
			if (other.owner != null) {
				return false;
			}
		} else if (!owner.equals(other.owner)) {
			return false;
		}
		if (!Arrays.equals(parameterTypes, other.parameterTypes)) {
			return false;
		}
		if (returnType == null) {
			if (other.returnType != null) {
				return false;
			}
		} else if (!returnType.equals(other.returnType)) {
			return false;
		}
		return true;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return this.getOwner() + "." + this.getName() + this.getDesc();
	}

	public String signature() {
		return this.getName() + this.getDesc();
	}
}
