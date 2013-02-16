package com.example.a11shook;

import java.util.ArrayList;
import java.util.Random;

import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.drawable.Drawable;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;

public class DrinkAdapter extends ArrayAdapter<String> {

   private ArrayList<Drink> _m_list = new ArrayList<Drink>();

   public DrinkAdapter(Context context) {
      super(context, R.layout.activity_main, R.id.logostringview, context
            .getResources().getStringArray(R.array.logo_names));

      TypedArray values = context.getResources()
            .obtainTypedArray(R.array.logos);
      int _Colors[] = context.getResources().getIntArray(R.array.colors);

      Drawable _DArr[] = new Drawable[values.length()];

      int count = 0;

      for (int i = 0, size = values.length(); i < size; ++i)
         _DArr[i] = values.getDrawable(i);

      Random rand = new Random(System.currentTimeMillis());

      for (int i = 0, length = _DArr.length; i < length; ++i) {
         int randomInt = rand.nextInt();

         if (randomInt < 0) {
            randomInt = Math.abs(randomInt);
         }

         StringBuilder sb = new StringBuilder();
         sb.append(randomInt % _Colors.length);

         Log.i("rand", sb.toString());

         _m_list.add(new Drink(_DArr[i], _Colors[randomInt % _Colors.length]));
      }
   }

   @Override
   public View getView(int position, View convertView, ViewGroup parent) {
      View listItem = super.getView(position, convertView, parent);
      ImageView _Image = (ImageView) listItem.findViewById(R.id.logoview);
      View _View = (View) listItem.findViewById(R.id.colorview);

      _Image.setImageDrawable(_m_list.get(position).get_image());
      _View.setBackgroundColor(_m_list.get(position).get_color());

      return listItem;
   }

}
