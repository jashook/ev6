package com.example.a10shook;

import java.util.ArrayList;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;

public class customView extends View {
   private ArrayList<point> _m_list = new ArrayList<point>();
   private int[] _m_colors;
   private View _m_v;
   private int _m_last;
   Paint _m_paint;
   private static int at = 0;

   public void clear() {
      _m_list.clear();
      invalidate();
   }

   public void change_color(View view) {

      if (at >= _m_colors.length - 1)
         at = 0;

      View colorPrev = view;

      if (colorPrev != null)
         colorPrev.setBackgroundColor(_m_colors[++at]);

      invalidate();

      StringBuilder sb = new StringBuilder();
      sb.append(at);
      Log.i("COLOR", sb.toString());

   }

   public customView(Context context) {
      super(context);
      _m_v = this.findViewById(R.id.customView);
      _m_last = 0;
      _m_paint = new Paint();
      _m_colors = getResources().getIntArray(R.array.colors);
   }

   public customView(Context context, AttributeSet attrs) {
      this(context, attrs, 0);
   }

   public customView(Context context, AttributeSet attrs, int defStyle) {
      super(context, attrs, defStyle);

      _m_v = this.findViewById(R.id.customView);
      _m_last = 0;
      _m_paint = new Paint();
      _m_colors = getResources().getIntArray(R.array.colors);
   }

   @Override
   public void onDraw(Canvas canvas) {
      super.onDraw(canvas);

      _m_paint.setColor(_m_colors[at]);

      for (int i = 0, size = _m_list.size(); i < size; ++i) {
         float x = _m_list.get(i).get_x();
         float y = _m_list.get(i).get_y();

         canvas.drawCircle(x, y, 40, _m_paint);
      }

   }

   @Override
   public boolean onTouchEvent(MotionEvent ev) {

      final int action = ev.getAction();

      if (action == MotionEvent.ACTION_DOWN) {
         final float x = ev.getX();
         final float y = ev.getY();

         point p = new point(x, y);
         _m_list.add(p);
         Log.i("TOUCH", ":)");
      }

      else if (action == MotionEvent.ACTION_MOVE) {
         final float x = ev.getX();
         final float y = ev.getY();

         point p = new point(x, y);
         _m_list.add(p);

      }

      invalidate();

      return true;
   }

}
