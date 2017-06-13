package com.irdeto.j2n.firstapplication;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;
import android.util.Log;

public class MainActivity extends Activity {
    boolean isPrint = false;
    static boolean sIsPrint = false;

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
    }

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
