public class test {

   public static void change_array(int [] _Array) {

      int [] _NewArray = { 9, 8, 7, 6, 5 };

		_Array = _NewArray;

      for (int i = 0; i < _Array.length; ++i) {

         System.out.print(_Array[i] + " ");

      }

      System.out.println();

   }

	public static void main(String [] Args) {

		int [] _Array = { 1, 2, 3, 4, 5 };

		for (int i = 0; i < _Array.length; ++i) {

			System.out.print(_Array[i] + " ");

		}

      System.out.println();

      System.out.println("Array changed!");

      change_array(_Array);

      for (int i = 0; i < _Array.length; ++i) {

         System.out.print(_Array[i] + " ");
      }

		System.out.println();

	}

}
