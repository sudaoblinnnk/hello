package com.irdeto.j2n.firstapplication;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;
import android.util.Log;

public class MainActivity extends Activity {
    boolean isPrint = false;
    static boolean sIsPrint = false;
    private byte[][] dimen22 = new byte[2][2];

    private static final String TAG = "kurt";

    //private static final String days[] = {"mon", "sun"};
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        isPrint = true;
        sIsPrint = true;
        if (isPrint) {
            Log.d(TAG, "non static print");
        }
        if (sIsPrint) {
            Log.d(TAG, "static print");
        }
        //testTryCatch("hello");
        byte v = 0;
        //testDim22();
        //testVarags(3, "one", "two", "three");
        for (int i = 0;i < 2;i++) {
            for (int j = 0; j < 2; j++) {
                dimen22[i][j] = v++;
                Log.d(TAG, " " + i + " " +j + " ");
            }
        }

        ClassA.SubClassA subA = new ClassA().new SubClassA();
        subA.print();
    }

    //private native void testTryCatch(String hello);
    //private native void testDim22();
    //private native void testVarags(int n, String ... names);

    private static class StaticPrivateClass{
        int add() {
            return 1 + 1;
        }
    }
    public static class StaticPublicClass{

    }

    private class PrivateClass{

    }
    public class PublicClass{
    }

    private void test0() {
        int i = 0;
        int sum = 0;
        for (;i<100;i++) {
            sum += i;
        }
    }

    private void test1() {
        int i = 0;
        int sum = 0;
        for (;i<3;i++) {
            sum += i;
        }
        int j = 3;
        while(j > 0) {
            sum -= --j;
        }
    }

    private int test2_move_stmt() {
        Class clazz = MainActivity.class;
        String s = clazz.getSimpleName();
        return s.hashCode();
    }

    private int test3_int_array() {
        int num[] = {1, 2, 3};
        int all = 0;
        for (int i = 0; i < num.length; i++) {
            all += num[i];
        }
        return all;
    }

    private String test3_str_array() {
        String num[] = {"1", "2", "3"};
        String all = "";
        for (int i = 0; i < num.length; i++) {
            all += num[i];
        }
        return all;
    }

    private String test3_str_array2() {
        String num[] = {"1", "2", "3"};
        String all = "";
        for (String n : num) {
            all += n;
        }
        return all;
    }

    private int test4_NEG(int b) {
        return ~b;
    }

    private boolean test4_NOT(boolean a) {
        boolean b = true;
        return !(a && b);
    }

    private int test4_switch(int a) {
        int b = 0;
        switch (a) {
            case 1:
                b = 1;
                break;
            case 2:
                b = 2;
                break;
            default:
                b = 3;
                break;
        }
        return b;
    }
}
