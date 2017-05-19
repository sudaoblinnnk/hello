package com.irdeto.j2n.firstapplication;

import android.app.Activity;
import android.os.Bundle;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        add();

        KeyLogic.getValue();
    }

    private int add() {
        return 1+2;
    }

    private static class KeyLogic {
        int value;
        private KeyLogic(int value) {
            this.value = value;
        }

        private static KeyLogic instance = new KeyLogic(1);

        public static KeyLogic getInstance() {
            return instance;
        }

        public static int getValue() {
            return KeyLogic.class.getSimpleName().hashCode();
        }

    }

    private static class StaticPrivateClass{
    }
    public static class StaticPublicClass{
    }
    public class PrivateClass{
    }
    public class PublicClass{
    }

}
