package com.example.myfirstapp;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.EditText;

public class MainActivity extends Activity {
   public static final String EXTRA_MESSAGE = "com.example.myfirstapp.MESSAGE";

   @Override
   public void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);
      Log.i("JAS", "onCreate()");
      setContentView(R.layout.activity_main);
   }

   @Override
   public void onStart() {
      super.onStart();
      Log.i("JAS", "onStart()");
   }

   @Override
   public void onResume() {
      super.onResume();
      Log.i("JAS", "onResume()");
   }

   @Override
   public void onPause() {
      super.onPause();
      Log.i("JAS", "onPause()");
   }

   @Override
   public void onStop() {
      super.onStop();
      Log.i("JAS", "onStop()");
   }

   @Override
   public void onRestart() {
      super.onRestart();
      Log.i("JAS", "onRestart()");
   }

   @Override
   public void onDestroy() {
      super.onDestroy();
      Log.i("JAS", "onDestroy()");
   }

   public void sendMessage(View view) {
      Intent intent = new Intent(this, DisplayMessageActivity.class);

      EditText editText = (EditText) findViewById(R.id.edit_message);
      String message = editText.getText().toString();
      intent.putExtra(EXTRA_MESSAGE, message);
      startActivity(intent);
   }

   @Override
   public boolean onCreateOptionsMenu(Menu menu) {
      getMenuInflater().inflate(R.menu.activity_main, menu);
      return true;
   }
}
