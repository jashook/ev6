////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: test_lock.java
//
// Modifications:
//
// 4-April-13: Version 1.0: Created
//
// Timeperiod: ev6
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

import java.util.*;

public class test_lock implements Runnable
{

   private static ArrayList<Integer> _m_integer = new ArrayList<Integer>();

   private static boolean _m_wait = true;

   private Object _m_lock = new Object();

   public void run() 
   {

      if (_m_wait)
      {

         synchronized (_m_lock)
         {
   
            System.out.println("Locked!");

            try { Thread.sleep(10000); } catch(Exception e) { }

            for (Integer _Int : _m_integer) System.out.print(_Int.toString() + " ");

            System.out.println();

            System.out.println("Unlocked!");

         }

      }

      else
      {
   
         synchronized (_m_lock)
         {

            System.out.println("Locked!");

            Integer _Int1 = _m_integer.get(2);

            System.out.println(_Int1.toString());

            for (Integer _Int : _m_integer) System.out.print(_Int.toString() + " ");

            System.out.println();

            System.out.println("Unlocked!");

         }  

      }
   
   }

   public static void main(String[] args) throws Exception
   {

      for (int i = 0; i < 10; ++i) _m_integer.add(new Integer(i));

      Thread _Test = new Thread(new test_lock());
      Thread _Test2 = new Thread(new test_lock());

      _Test.start();
      
      Thread.sleep(1000);
        
      _m_wait = false;

      _Test2.start();

      _Test.join();
      _Test2.join();

   }

}
