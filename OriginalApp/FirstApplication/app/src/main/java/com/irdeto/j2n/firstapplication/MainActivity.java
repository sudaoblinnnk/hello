package com.irdeto.j2n.firstapplication;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;
import android.util.Log;

public class MainActivity extends Activity {
    boolean isPrint = false;

    private static final String TAG = "kurt";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        isPrint = true;
        if (isPrint) {
            Log.d(TAG, "kkkkkkkkkkkkkkkkkkkkkkkk");
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

}
