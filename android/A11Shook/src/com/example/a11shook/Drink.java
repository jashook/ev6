package com.example.a11shook;

import android.graphics.drawable.Drawable;

public class Drink {

   private Drawable _m_image;
   private int _m_color;

   public Drink(Drawable image, int color) {

      _m_color = color;
      _m_image = image;

   }

   public int get_color() {
      return _m_color;
   }

   public Drawable get_image() {
      return _m_image;
   }

   public void set_color(int color) {
      _m_color = color;
   }

}
