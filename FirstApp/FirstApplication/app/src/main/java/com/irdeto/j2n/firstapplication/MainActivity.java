package com.irdeto.j2n.firstapplication;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.os.Bundle;

public class MainActivity extends Activity {

    static {
        System.loadLibrary("native-lib");
    }

    @SuppressLint("MissingSuperCall")
    @Override
    protected native void onCreate(Bundle savedInstanceState);

    //public native String stringFromJNI();
    //public native static String staticStringFromJNI();
}
