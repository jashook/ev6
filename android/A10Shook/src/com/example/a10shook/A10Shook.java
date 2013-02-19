package com.example.a10shook;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.View;

public class A10Shook extends Activity {

   @Override
   public void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);
      setContentView(R.layout.activity_a10_shook);
   }

   public void changeColor(View view) {
      View v = findViewById(R.id.ColorView);
      if (v == null)
         Log.i("FAIL", "TJOS");
      customView cb = (customView) findViewById(R.id.customView);
      Log.i("FAIL", "ITS AIVE");
      cb.change_color(v);
   }

   public void clear(View view) {
      customView cv = (customView) findViewById(R.id.customView);
      if (cv != null)
         cv.clear();
   }

   @Override
   public boolean onCreateOptionsMenu(Menu menu) {
      getMenuInflater().inflate(R.menu.activity_a10_shook, menu);
      return true;
   }
}
