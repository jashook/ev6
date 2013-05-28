package com.example.a11shook;

import android.app.ListActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ListView;

public class MainActivity extends ListActivity {

   public void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);

      DrinkAdapter _DAdapter = new DrinkAdapter(this);

      setListAdapter(_DAdapter);
   }

   @Override
   public void onListItemClick(ListView l, View v, int position, long id) {
      super.onListItemClick(l, v, position, id);
   }

}
