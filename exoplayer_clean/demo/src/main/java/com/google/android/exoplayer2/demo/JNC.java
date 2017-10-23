package com.google.android.exoplayer2.demo;

import android.util.Log;

public class JNC extends Wine{
    private static final String TAG = "JNC";

    public JNC(){
        setName("JNC");
    }

    /**
     * 重写父类方法，实现多态
     */
    public String drink(){
        return "喝的是 " + getName();
    }

    /**
     * 重写toString()
     */
    public String toString(){
        return "Wine : " + getName();
    }
}