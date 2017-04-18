package com.allivault.cloudsafe.playground;

import com.yljt.platform.common.ThreadTask;
import android.content.Context;
import android.content.ContextWrapper;
import android.os.Bundle;
import android.util.Log;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;
import android.widget.Toast;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;


public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";
    public static final String DBYXSCQ_SO = "dbyxscq.so";

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
        String uname = "test574";
        //AllivaultApi.createRSAKeyPair(uname);

        String allFiles = "\n";
        try {
            String libSourcePath = "lib/" + DBYXSCQ_SO;
            InputStream in = getAssets().open(libSourcePath);
            String filename = DBYXSCQ_SO;
            FileOutputStream out;
            byte[] buffer = new byte[1024];
            out = openFileOutput(filename, Context.MODE_PRIVATE);
            int len = in.read(buffer);
            while (len != -1) {
                out.write(buffer, 0, len);
                len = in.read(buffer);
            }
            out.close();

            // Debugging
            String md5 = Utils.md5(openFileInput(filename));
            allFiles += "fileName :" + filename + " \nmd5sum :" + md5;
            allFiles += " \noriginal    :" + Utils.md5(getAssets().open(libSourcePath));
            allFiles += "\n";
        } catch (IOException e) {
            e.printStackTrace();
        }

        File dir = getFilesDir();
        for (String fileName : dir.list()) {
            allFiles += fileName;
            allFiles += "\n";
        }
        textView.setText("hello example, files in home dir:" + allFiles);

        // task 5: call AllivaultApi.createUserAccountOnServer()
        String fullname = uname;
        String email = uname + "@gmail.com";
        String passwd = "12345678";
//        AllivaultApi.createUserAccountOnServer(
//                uname, passwd, fullname, email, "path-to-publickey", 1234, 1456,
//                5678);

        // task 6: call AllivaultApi.processNewUser()
        //AllivaultApi.processNewUser(uname);

        // task 7: call AllivaultApi.batchActionsForNewMachine()
        //AllivaultApi.batchActionsForNewMachine();
        new SyncFileTask().execute();
    }
    class SyncFileTask extends ThreadTask<String> {

        @Override
        public void onStart() {
            super.onStart();
        }

        @Override
        public String onDoInBackground() {
            try {
            } catch (Exception e) {
                e.printStackTrace();
            }
            boolean ret = AllivaultApi.registerAppStatusUpdated();
            if (ret)
            {
                AllivaultApi.batchActionsForNewMachine();
            }
            return  "";
        }

        @Override
        public void onResult(String s) {
            super.onResult(s);
        }
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
