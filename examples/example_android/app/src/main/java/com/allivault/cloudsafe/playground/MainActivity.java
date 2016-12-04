package com.allivault.cloudsafe.playground;

import android.os.Bundle;
import android.util.Log;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;

import java.io.File;


public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // task 1: call AllivaultApi.appInitialize()
        File rootDir = getFilesDir();
        AllivaultApi.appInitialize(rootDir.getAbsolutePath());

        // task 2: call AllivaultApi.getLibGit2Version()
        TextView textView = (TextView)findViewById(R.id.textView);
        textView.setText("hello example, git2 version -" + AllivaultApi.getLibGit2Version());

        // task 3: call AllivaultApi.aesEncrypt() and aesDecrypt()
        byte[] input = "a string".getBytes();
        byte[] outpout;
        byte[] plain;

        outpout = AllivaultApi.aesEncrypt(input, input.length);
        plain = AllivaultApi.aesDecrypt(outpout, outpout.length);
        Log.v(TAG, "original :" + new String(input));
        Log.v(TAG, "decrypted :" + new String(plain));

        // task 4: call AllivaultApi.createRSAKeyPair()
        AllivaultApi.createRSAKeyPair("test566");

        // task 5: call AllivaultApi.createUserAccountOnServer()
        AllivaultApi.createUserAccountOnServer(
                "a-user", "a-pass", "full-name", "user@gmail.com", "path-to-publickey", 1234, 1456,
                5678);

        // task 6: call AllivaultApi.processNewUser()
        AllivaultApi.processNewUser("a-user");
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
