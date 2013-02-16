package com.example.a11shook;

import android.app.ListActivity;
import android.os.Bundle;

public class DrinkList extends ListActivity {

   public void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);

      DrinkAdapter _DAdapter = new DrinkAdapter(this);

      setListAdapter(_DAdapter);
   }

}
