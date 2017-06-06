package com.irdeto.j2n.firstapplication;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

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

    private static class StaticPrivateClass{
        int add() {
            return 1 + 1;
        }
    }
    public static class StaticPublicClass{
    }
    public class PrivateClass{
    }
    public class PublicClass{
    }

}
