// ListClient.java
// Andrea Vitek
// abporghi
// pa 3
// This file contains a test program for the List ADT

public class ListClient {
	public static void main(String[] args) {
		List A = new List();
		List B = new List();

		// Generate random lists
		for (int i = 1; i <= 20; i++) {
			A.append(i * 2);
			B.prepend(i);
		}

		// Print lists
		System.out.println(A);
		System.out.println(B);

		for (A.moveFront(); A.index() >= 0; A.moveNext()) {
			System.out.print(A.get() + " ");
		}

		System.out.println();

		// Print B backwards
		for (B.moveBack(); B.index() >= 0; B.movePrev()) {
			System.out.print(B.get() + " ");
		}

		System.out.println();

		// Print whether the two lists are equal
		System.out.println(A.equals(B));

		B.clear();

		// Copy A into B
		for (A.moveFront(); A.index() >= 0; A.moveNext()) {
			B.append(A.get());
		}

		System.out.println(A.equals(B));

		A.moveFront();
		for(int i = 0; i < 3; i++) {
			A.moveNext();
		}

		A.insertBefore(-2);
		for(int i = 0; i < 3; i++) {
			A.moveNext();
		}

		A.insertBefore(-9);
		for(int i = 0; i < 7; i++) {
			A.movePrev();
		}

		A.delete();

		System.out.println(A);
		System.out.println(A.length());

		for (A.moveFront(); A.index() >= 0; A.moveNext()) {
			B.append(A.get());
		}

		A.clear();

		System.out.println(A.length());
	}
}

//Output of this program:
// 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30 32 34 36 38 40
// 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
// 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30 32 34 36 38 40
// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
// false
// true
// 2 6 -2 8 10 12 -9 14 16 18 20 22 24 26 28 30 32 34 36 38 40
// 21
// 0