// MatrixClient.java
// Andrea Vitek
// abporghi
// pa 3
// This file contains a test program for Matrix

public class MatrixClient {
   public static void main(String[] args) {
      int n = 100000;
      Matrix A = new Matrix(n);
      Matrix B = new Matrix(n);

      A.changeEntry(1,1,1); B.changeEntry(1,1,1);
      A.changeEntry(1,2,2); B.changeEntry(1,2,0);
      A.changeEntry(1,3,3); B.changeEntry(1,3,1);
      A.changeEntry(2,1,4); B.changeEntry(2,1,0);
      A.changeEntry(2,2,5); B.changeEntry(2,2,1);
      A.changeEntry(2,3,6); B.changeEntry(2,3,0);
      A.changeEntry(3,1,7); B.changeEntry(3,1,1);
      A.changeEntry(3,2,8); B.changeEntry(3,2,1);
      A.changeEntry(3,3,9); B.changeEntry(3,3,1);

      // Print the two matrices
      System.out.println(A);
      System.out.println(B);

      // Print NNZ in both matrices
      System.out.println("A has " + A.getNNZ() + " non-zero entries:");
      System.out.println(A + "\n");

      System.out.println("B has " + B.getNNZ() + " non-zero entries:");
      System.out.println(B + "\n");

      // Print (1.5) * A
      System.out.println("(3) * A =");
      System.out.println(A.scalarMult(3) + "\n");

      // Print A + B
      System.out.println("A + B =");
      System.out.println(A.add(B) + "\n");

      // Print A + A
      System.out.println("A + A =");
      System.out.println(A.add(A) + "\n");

      // Print B - A
      System.out.println("B - A =");
      System.out.println(B.sub(A) + "\n");

      // Print A - A
      System.out.println("A - A =");
      System.out.println(A.sub(A) + "\n");

      // Print Transpose(A)
      System.out.println("Transpose(A) =");
      System.out.println(A.transpose() + "\n");

      // Print A * B
      System.out.println("A * B = (takes a couple of seconds when printing to console)");
      System.out.println(A.mult(B) + "\n");

      // Print B * B
      System. out.println("B * B = (takes a couple of seconds when printing to console)");
      System.out.println(B.mult(B) + "\n");

      // Print B == B
      System. out.println("B == B?");
      System.out.println(B.equals(B) + "\n");

      // Print A == B
      System. out.println("A == B?");
      System.out.println(A.equals(B) + "\n");

      // Copy A into B
      B = A.copy();

      // Print A == B
      System. out.println("A == B?");
      System.out.println(A.equals(B) + "\n");

      // Make A 0 and print its NNZ
      A.makeZero();
      System.out.println("A has " + A.getNNZ() + " non-zero entries:");
      System.out.println(A + "\n");
   }
}

//Output of this program:
//        1:  (1, 1.0) (2, 2.0) (3, 3.0)
//        2:  (1, 4.0) (2, 5.0) (3, 6.0)
//        3:  (1, 7.0) (2, 8.0) (3, 9.0)
//
//        1:  (1, 1.0) (3, 1.0)
//        2:  (2, 1.0)
//        3:  (1, 1.0) (2, 1.0) (3, 1.0)
//
//        A has 9 non-zero entries:
//        1:  (1, 1.0) (2, 2.0) (3, 3.0)
//        2:  (1, 4.0) (2, 5.0) (3, 6.0)
//        3:  (1, 7.0) (2, 8.0) (3, 9.0)
//
//
//        B has 6 non-zero entries:
//        1:  (1, 1.0) (3, 1.0)
//        2:  (2, 1.0)
//        3:  (1, 1.0) (2, 1.0) (3, 1.0)
//
//
//        (3) * A =
//        1:  (1, 3.0) (2, 6.0) (3, 9.0)
//        2:  (1, 12.0) (2, 15.0) (3, 18.0)
//        3:  (1, 21.0) (2, 24.0) (3, 27.0)
//
//
//        A + B =
//        1:  (1, 2.0) (2, 2.0) (3, 4.0)
//        2:  (1, 4.0) (2, 6.0) (3, 6.0)
//        3:  (1, 8.0) (2, 9.0) (3, 10.0)
//
//
//        A + A =
//        1:  (1, 2.0) (2, 4.0) (3, 6.0)
//        2:  (1, 8.0) (2, 10.0) (3, 12.0)
//        3:  (1, 14.0) (2, 16.0) (3, 18.0)
//
//
//        B - A =
//        1:  (2, 2.0) (3, -2.0)
//        2:  (1, 4.0) (2, -4.0) (3, 6.0)
//        3:  (1, -6.0) (2, -7.0) (3, -8.0)
//
//
//        A - A =
//
//
//        Transpose(A) =
//        1:  (1, 1.0) (2, 4.0) (3, 7.0)
//        2:  (1, 2.0) (2, 5.0) (3, 8.0)
//        3:  (1, 3.0) (2, 6.0) (3, 9.0)
//
//
//        A * B = (takes a couple of seconds when printing to console)
//        1:  (1, 4.0) (2, 5.0) (3, 4.0)
//        2:  (1, 10.0) (2, 11.0) (3, 10.0)
//        3:  (1, 16.0) (2, 17.0) (3, 16.0)
//
//
//        B * B = (takes a couple of seconds when printing to console)
//        1:  (1, 2.0) (2, 1.0) (3, 2.0)
//        2:  (2, 1.0)
//        3:  (1, 2.0) (2, 2.0) (3, 2.0)
//
//
//        B == B?
//        true
//
//        A == B?
//        false
//
//        A == B?
//        true
//
//        A has 0 non-zero entries:
//
//

