package com.irdeto.j2n.firstapplication;

import android.util.Log;

/**
 * Created by kurt on 17-6-7.
 */

public class ClassA {
    String TAG = "ClassA";
    void print() {
        Log.d(TAG, "this is ClassA");
    }

    public class SubClassA {
        public SubClassA() {
            Log.d(TAG, "this is SubClassA constructor");
        }
        void print() {
            Log.d(TAG, "this is SubClassA");
        }
        native void printNative();
    }
}
