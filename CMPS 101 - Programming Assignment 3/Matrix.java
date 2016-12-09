// Matrix.java
// Andrea Vitek
// abporghi
// pa 3
// This file contains the implementation of a sparse Matrix.

// It is required that your program perform these operations efficiently.
// Let n be the number of rows in A, and let a and b denote the number of non-zero entries in A and B respectively.
// Then the worst case run times of the above functions should have the following asymptotic growth rates.
// A.changeEntry(): Θ(𝑎)
// A.copy(): Θ(𝑛+𝑎)
// A.scalarMult(x): Θ(𝑛+𝑎)
// A.transpose(): Θ(𝑛+𝑎)
// A.add(B): Θ(𝑛+𝑎+𝑏)
// A.sub(B): Θ(𝑛+𝑎+𝑏)
// A.mult(B): Θ(𝑛^2+𝑎⋅𝑏)

public class Matrix {
	// Private inner class to represent an Entry in the Matrix
	private class Entry {
		// Instance variables
		int column;
		double value;

		// Constructor
		Entry(int column, double value) {
			this.column = column;
			this.value = value;
		}

		// Returns a new instance of Matrix identical to this
		Entry copy() {
			return new Entry(column, value);
		}

		// Overridden methods

		// Returns whether a Matrix is equal to another
		public boolean equals(Object obj) {
			// If the two objects are not the same type, return false
			if (!(obj instanceof Entry)) {
				return false;
			}

			// If the object to compare is itself, return true
			if (obj == this) {
				return true;
			}

			Entry entry = (Entry)obj;

			// Compare both private fields
			if (this.column == entry.column && this.value == entry.value) {
				return true;
			}

			return false;
		}

		// Returns the String representation of Matrix
		public String toString() {
			return "(" + this.column + ", " + this.value + ")";
		}
	}

	// Instance variables
	private List[] rows;
	private int size;
	private int NNZ;

	// Constructor

	// Makes a new n x n zero Matrix. pre: n>=1
	// Pre: n >= 0
	Matrix(int n) {
		if (n < 1) {
			throw new RuntimeException("Matrix Error: Matrix() called with n < 1");
		}

		size = n;
		NNZ = 0;
		rows = new List[size];

		for (int i = 0; i < size; i++) {
			rows[i] = new List();
		}
	}

	// Access functions

	// Returns n, the number of rows and columns of this Matrix
	int getSize() {
		return size;
	}

	// Returns the number of non-zero entries in this Matrix
	int getNNZ() {
		return NNZ;
	}

	// Manipulation procedures

	// Sets this Matrix to the zero state
	void makeZero() {
		// Iterate through all the columns and clear the rows
		for (List column: rows) {
			if (!column.isEmpty()) {
				column.clear();
			}
		}

		NNZ = 0;
	}

	// Returns a new Matrix that has the same entries as this Matrix
	Matrix copy() {
		Matrix duplicate = new Matrix(this.size);
		Entry currentEntry;
		// Start from 1, not from 0, as the user would do
		int index = 1;

		// Iterate through the columns
		for (List row: this.rows) {
			if (!row.isEmpty()) {
				row.moveFront();

				// Iterate through the individual row and copy entries
				while (row.index() != -1) {
					currentEntry = (Entry)row.get();
					duplicate.changeEntry(index, currentEntry.column, currentEntry.value);
					row.moveNext();
				}
			}

			// Go to the next column
			index++;
		}

		return duplicate;
	}

	// Changes ith row, jth column of this Matrix to x
	// Pre: 1 <= i <= getSize(), 1 <= j<= getSize()
	void changeEntry(int i, int j, double x) {
		if (i < 1 || j < 1 || i > size || j > size) {
			throw new RuntimeException("Matrix Error: changeEntry() called on invalid Matrix entry");
		}

		Entry currentEntry;
		Entry newEntry = new Entry(j, x);
		boolean found = false;
		// Since arrays start from 0, but the user will specify rows starting from 0
		List currentRow = rows[i - 1];

		// If no existing entry, insert a new entry
		if (currentRow.isEmpty()) {
			if (x != 0) {
				currentRow.append(newEntry);
				NNZ++;
			}

			// If the column is in the first half, start from the beginning
		} else {
			if (j < size / 2) {
				currentRow.moveFront();

				while (!found) {
					if (!(currentRow.get() instanceof Entry)) {
						throw new RuntimeException("Matrix Error: invalid type of Matrix entry");
					}

					currentEntry = (Entry)currentRow.get();

					if (currentEntry.column == j) {
						if (x != 0) {
							currentRow.insertAfter(newEntry);
						} else {
							NNZ--;
						}

						currentRow.delete();
						found = true;

					} else if (currentEntry.column > j) {
						if (x != 0) {
							currentRow.insertBefore(newEntry);
							NNZ++;
						}

						found = true;

					} else if (currentRow.index() == currentRow.length() - 1) {
						if (x != 0) {
							currentRow.insertAfter(newEntry);
							NNZ++;
						}

						found = true;
					}

					currentRow.moveNext();
				}

				// If the column is in the second half, start from the end
			} else {
				currentRow.moveBack();

				while (!found) {
					if (!(currentRow.get() instanceof Entry)) {
						throw new RuntimeException("Matrix Error: invalid type of Matrix entry");
					}

					currentEntry = (Entry)currentRow.get();

					if (currentEntry.column == j) {
						if (x != 0) {
							currentRow.insertBefore(newEntry);
						} else {
							NNZ--;
						}

						currentRow.delete();
						found = true;

					} else if (currentEntry.column < j) {
						if (x != 0) {
							currentRow.insertAfter(newEntry);
							NNZ++;
						}

						found = true;

					} else if (currentRow.index() == 0) {
						if (x != 0) {
							currentRow.insertBefore(newEntry);
							NNZ++;
						}

						found = true;
					}

					currentRow.movePrev();
				}
			}
		}
	}

	// Returns a new Matrix that is the scalar product of this Matrix with x
	Matrix scalarMult(double x) {
		Matrix doubleMatrix = this.copy();
		Entry currentEntry;
		int index = 1;

		for (List row: rows) {
			if (!row.isEmpty()) {
				row.moveFront();

				while (row.index() != -1) {
					currentEntry = (Entry)row.get();
					doubleMatrix.changeEntry(index, currentEntry.column, currentEntry.value * x);
					row.moveNext();
				}
			}

			index++;
		}

		return doubleMatrix;
	}

	// Returns a new Matrix that is the sum of this Matrix with M
	// Pre: getSize() == M.getSize()
	Matrix add(Matrix M) {
		if (size != M.size) {
			throw new RuntimeException("Matrix Error: add() called on matrices of different size");
		}

		// If either matrix is all zeros, return the other matrix
		if (this.getNNZ() == 0) {
			return M;
		} else if (M.getNNZ() == 0) {
			return this;
		}

		// Duplicate matrix if adding to itself
		if (this == M) {
			M = this.copy();
		}

		Matrix addedMatrix = new Matrix(size);
		List currentRow1, currentRow2;
		Entry currentEntry1, currentEntry2;

		// Repeat for all columns in this matrix
		for (int i = 0; i < size; i++) {
			// Get the current rows
			currentRow1 = rows[i];
			currentRow2 = M.rows[i];

			// Check if either row is 0
			if (!currentRow1.isEmpty()) {
				currentRow1.moveFront();
			}

			if (!currentRow2.isEmpty()) {
				currentRow2.moveFront();
			}

			// Repeat until either row is exhausted
			while ((currentRow1.index() != -1) || (currentRow2.index() != -1)) {
				// Exhausted currentRow1, copy the rest of currentRow2
				if (currentRow1.index() == -1) {
					if (!(currentRow2.get() instanceof Entry)) {
						throw new RuntimeException("Matrix Error: invalid type of Matrix entry");
					}

					currentEntry2 = (Entry)currentRow2.get();
					addedMatrix.rows[i].append(currentEntry2.copy());
					addedMatrix.NNZ += 1;
					currentRow2.moveNext();

					// Exhausted currentRow2, copy the rest of currentRow1
				} else if (currentRow2.index() == -1) {
					if (!(currentRow1.get() instanceof Entry)) {
						throw new RuntimeException("Matrix Error: invalid type of Matrix entry");
					}

					currentEntry1 = (Entry)currentRow1.get();
					addedMatrix.rows[i].append(currentEntry1.copy());
					addedMatrix.NNZ += 1;
					currentRow1.moveNext();

					// Add the corresponding entries in currentRow1 and currentRow2
				} else {
					if (!(currentRow1.get() instanceof Entry) || !(currentRow2.get() instanceof Entry)) {
						throw new RuntimeException("Matrix Error: invalid type of Matrix entry");
					}

					currentEntry1 = (Entry)currentRow1.get();
					currentEntry2 = (Entry)currentRow2.get();

					// Both entries are in the same column
					if (currentEntry1.column == currentEntry2.column) {
						currentEntry1 = currentEntry1.copy();
						currentEntry1.value = currentEntry1.value + currentEntry2.value;

						// If currentEntry1 = currentEntry2 = 0, do not insert
						if (currentEntry1.value != 0) {
							addedMatrix.rows[i].append(currentEntry1);
							addedMatrix.NNZ += 1;
						}

						currentRow1.moveNext();
						currentRow2.moveNext();

						// currentEntry1 is in a higher column than currentEntry2
					} else if (currentEntry1.column > currentEntry2.column) {
						currentEntry2 = currentEntry2.copy();
						addedMatrix.rows[i].append(currentEntry2);
						addedMatrix.NNZ += 1;
						currentRow2.moveNext();

						// currentEntry1 is in a lower column than currentEntry2
					} else {
						currentEntry1 = currentEntry1.copy();
						addedMatrix.rows[i].append(currentEntry1);
						addedMatrix.NNZ += 1;
						currentRow1.moveNext();
					}
				}
			}
		}

		return addedMatrix;
	}

	// Returns a new Matrix that is the difference of this Matrix with M
	// Pre: getSize() == M.getSize()
	Matrix sub(Matrix M) {
		if (size != M.size) {
			throw new RuntimeException("Matrix Error: add() called on matrices of different size");
		}

		// If either matrix is all zeros, return the other matrix
		if (this.getNNZ() == 0) {
			return M;
		} else if (M.getNNZ() == 0) {
			return this;
		}

		// Duplicate matrix if subtracting from itself
		if (this == M) {
			M = this.copy();
		}

		Matrix subtractedMatrix = new Matrix(size);
		List currentRow1, currentRow2;
		Entry currentEntry1, currentEntry2;

		// Repeat for all columns in this matrix
		for (int i = 0; i < size; i++) {
			// Get the current rows
			currentRow1 = rows[i];
			currentRow2 = M.rows[i];

			// Check if either row is 0
			if (!currentRow1.isEmpty()) {
				currentRow1.moveFront();
			}

			if (!currentRow2.isEmpty()) {
				currentRow2.moveFront();
			}

			// Repeat until either row is exhausted
			while ((currentRow1.index() != -1) || (currentRow2.index() != -1)) {
				// Exhausted currentRow1, copy the rest of currentRow2
				if (currentRow1.index() == -1) {
					if (!(currentRow2.get() instanceof Entry)) {
						throw new RuntimeException("Matrix Error: invalid type of Matrix entry");
					}

					currentEntry2 = (Entry)currentRow2.get();
					subtractedMatrix.rows[i].append(currentEntry2.copy());
					subtractedMatrix.NNZ += 1;
					currentRow2.moveNext();

					// Exhausted currentRow2, copy the rest of currentRow1
				} else if (currentRow2.index() == -1) {
					if (!(currentRow1.get() instanceof Entry)) {
						throw new RuntimeException("Matrix Error: invalid type of Matrix entry");
					}

					currentEntry1 = (Entry)currentRow1.get();
					subtractedMatrix.rows[i].append(currentEntry1.copy());
					subtractedMatrix.NNZ += 1;
					currentRow1.moveNext();

					// Subtract the corresponding entries in currentRow1 and currentRow2
				} else {
					if (!(currentRow1.get() instanceof Entry) || !(currentRow2.get() instanceof Entry)) {
						throw new RuntimeException("Matrix Error: invalid type of Matrix entry");
					}

					currentEntry1 = (Entry)currentRow1.get();
					currentEntry2 = (Entry)currentRow2.get();

					// Both entries are in the same column
					if (currentEntry1.column == currentEntry2.column) {
						currentEntry1 = currentEntry1.copy();
						currentEntry1.value = currentEntry1.value - currentEntry2.value;

						// If currentEntry1 = currentEntry2 = 0, do not insert
						if (currentEntry1.value != 0) {
							subtractedMatrix.rows[i].append(currentEntry1);
							subtractedMatrix.NNZ += 1;
						}

						currentRow1.moveNext();
						currentRow2.moveNext();

						// currentEntry1 is in a higher column than currentEntry2
					} else if (currentEntry1.column > currentEntry2.column) {
						currentEntry2 = currentEntry2.copy();
						subtractedMatrix.rows[i].append(currentEntry2);
						subtractedMatrix.NNZ += 1;
						currentRow2.moveNext();

						// currentEntry1 is in a lower column than currentEntry2
					} else {
						currentEntry1 = currentEntry1.copy();
						subtractedMatrix.rows[i].append(currentEntry1);
						subtractedMatrix.NNZ += 1;
						currentRow1.moveNext();
					}
				}
			}
		}

		return subtractedMatrix;
	}

	// Returns a new Matrix that is the transpose of this Matrix
	Matrix transpose() {
		Matrix transposed = new Matrix(size);
		List currentRow;
		Entry currentEntry;
		int j;

		// Step through the rows
		for (int i = 0; i < size; i++) {
			currentRow = rows[i];

			if (!currentRow.isEmpty()) {
				currentRow.moveFront();

				// Step through the entries and insert into the current row
				while (currentRow.index() != -1) {
					if (!(currentRow.get() instanceof Entry)) {
						throw new RuntimeException("Matrix Error: invalid type of Matrix entry");
					}

					currentEntry = (Entry)currentRow.get();

					// Set the current column to be the new row
					j = currentEntry.column;
					currentEntry = new Entry(i + 1, currentEntry.value);
					transposed.rows[j - 1].append(currentEntry);
					currentRow.moveNext();
				}
			}
		}

		// Copy NNZ, since it does not get updated automatically
		transposed.NNZ = NNZ;

		return transposed;
	}

	// Returns a new Matrix that is the product of this Matrix with M
	// Pre: getSize() == M.getSize()
	Matrix mult(Matrix M) {
		if (size != M.size) {
			throw new RuntimeException("Matrix Error: mul() called on matrices of different size");
		}

		// If this and M reference the same Matrix then duplicate
		if (this == M) {
			M = this.copy();
		}

		Matrix multiplied = new Matrix(size);
		Matrix transposed = M.transpose();
		List currentRow, currentTranposedColumn;
		Entry currentEntry;
		double dotProduct;

		// Θ(𝑛^2) since there is a nested for loop
		for (int i = 0; i < size; i++) {
			currentRow = rows[i];

			for (int j = 0; j < size; j++) {
				currentTranposedColumn = transposed.rows[j];
				dotProduct = dot(currentRow,currentTranposedColumn);

				if (dotProduct != 0) {
					currentEntry = new Entry(j + 1, dotProduct);
					multiplied.rows[i].append(currentEntry);
					multiplied.NNZ += 1;
				}
			}
		}

		return multiplied;
	}

	// Private static function that returns the vector dot product of a Matrix row and column.
	private static double dot(List P, List Q) {
		double dot = 0;

		// If either P or Q are empty, then the dot product is 0
		if (!P.isEmpty() && !Q.isEmpty()) {
			Entry currentEntry1, currentEntry2;
			P.moveFront();
			Q.moveFront();

			while ((P.index() != -1) && (Q.index() != -1)) {
				if (!(P.get() instanceof Entry) || !(Q.get() instanceof Entry)) {
					throw new RuntimeException("Matrix Error: invalid type of Matrix entry");
				}

				currentEntry1 = (Entry)P.get();
				currentEntry2 = (Entry)Q.get();

				if (currentEntry1.column == currentEntry2.column) {
					dot += currentEntry1.value * currentEntry2.value;
					P.moveNext();
					Q.moveNext();

				} else if (currentEntry1.column > currentEntry2.column) {
					Q.moveNext();

				} else {
					P.moveNext();
				}
			}
		}

		return dot;
	}

	// Overridden functions

	// Returns whether the two objects are equal
	public boolean equals(Object x) {
		// If X is not a Matrix, return false
		if (!(x instanceof Matrix)) {
			return false;
		}

		// If x refers to the same object as this, return true
		if (x == this) {
			return true;
		}

		Matrix otherMatrix = (Matrix)x;

		// If the two matrices are not the same size or don't have the same number of NNZ, return false
		if (size != otherMatrix.getSize() || NNZ != otherMatrix.getNNZ()) {
			return false;
		}

		boolean isEqual = true;
		List currentRowThis, currentRowOther;

		int i = 0;
		currentRowThis = this.rows[i];

		// Iterate over the non-zero rows
		while (isEqual && currentRowThis != null && i < size) {
			currentRowThis = this.rows[i];
			currentRowOther = otherMatrix.rows[i];
			isEqual = currentRowThis.equals(currentRowOther);
			i++;
		}

		return isEqual;
	}

	// Returns the String representation of this Matrix
	public String toString() {
		String result = "";
		int index = 1;

		for (List row: rows) {
			if (!row.isEmpty()) {
				result += index + ": ";
				result += row + "\n";
			}

			index++;
		}
		return result;
	}
}