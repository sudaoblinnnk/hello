package com.irdeto.aca.key;

public class KeyLogic {

    private static KeyLogic instance = new KeyLogic();
    public static native KeyLogic getInstance();

    public int value() {
        Class clazz = KeyLogic.class;
        String s = clazz.getSimpleName();
        return s.hashCode();
    }

    public static native int value1(int a);
    public native int value2(int b);
    public native String valueAdd(int a, String s);

}
