// Sparse.java
// Andrea Vitek
// apborghi
// pa 3
// This program reads sparse Matrices from a input file, performs some operations and outputs the result to a file

import java.io.*;

public class Sparse {
	public static void main(String[] args) {
		if (args.length != 2) {
			System.out.println("You did not enter two files names separated by a space.");
			System.exit(0); // Exit as requested
		}

		try {
			Matrix[] res = loadFromTextFile(args[0]);
			writeOpsToTextFile(res[0], res[1], args[1]);

		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	// Loads the lines of an input file into a String array
	public static Matrix[] loadFromTextFile(String inputFileURL) throws IOException {
		File f = new File(inputFileURL);
		String[] inputListStrings = null;
		boolean readingEntries = false;
		boolean readingA = true;
		Matrix A = null, B = null;
		int nonZeroA = 0, nonZeroB = 0;

		if (!f.exists()) {
			throw new RuntimeException("File does not exist");
		}

		try {
			try (BufferedReader br = new BufferedReader(new FileReader(inputFileURL))) {
				String currentLine;

				while ((currentLine = br.readLine()) != null) {
					String[] splitLine = currentLine.split(" ");

					if (!readingEntries) {
						A = new Matrix(Integer.valueOf(splitLine[0]));
						B = new Matrix(Integer.valueOf(splitLine[0]));

						if (splitLine.length != 3) {
							throw new RuntimeException("Invalid first line in input file");
						}

						try {
							nonZeroA = Integer.valueOf(splitLine[1]);
							nonZeroB = Integer.valueOf(splitLine[2]);

						} catch (NumberFormatException e) {
							throw new RuntimeException("Invalid first line in input file");
						}

						readingEntries = true;

					} else if (!currentLine.isEmpty()) {
						try {
							int i = Integer.valueOf(splitLine[0]);
							int j = Integer.valueOf(splitLine[1]);
							double x = Double.valueOf(splitLine[2]);

							if (readingA && nonZeroA > 0) {
								A.changeEntry(i, j, x);
								nonZeroA--;

								if (nonZeroA == 0) {
									readingA = false;
								}
							} else {
								B.changeEntry(i, j, x);
								nonZeroB--;
							}

						} catch (NumberFormatException e) {
							throw new RuntimeException("Invalid input file format");
						}
					}
				}
			}

		} catch (IOException e) {
			System.out.println("Error! " + e.toString());
		}

		return new Matrix[]{A, B};
	}

	// Exports a few test operations on two Matrices to a text file
	public static void writeOpsToTextFile(Matrix A, Matrix B, String outputFileName) {
		try (PrintWriter out = new PrintWriter(outputFileName)) {
			// Print non-zero entries
			out.println("A has " + A.getNNZ() + " non-zero entries:");
			out.println(A + "\n");
			out.println("B has " + B.getNNZ() + " non-zero entries:");
			out.println(B + "\n");

			// Print (1.5) * A
			out.println("(1.5) * A =");
			out.println(A.scalarMult(1.5) + "\n");

			// Print A + B
			out.println("A + B =");
			out.println(A.add(B) + "\n");

			// Print A + A
			out.println("A + A =");
			out.println(A.add(A) + "\n");

			// Print B - A
			out.println("B - A =");
			out.println(B.sub(A) + "\n");

			// Print A - A
			out.println("A - A =");
			out.println(A.sub(A) + "\n");

			// Print Transpose(A)
			out.println("Transpose(A) =");
			out.println(A.transpose() + "\n");

			// Print A * B
			out.println("A * B =");
			out.println(A.mult(B) + "\n");

			// Print B * B
			out.println("B * B =");
			out.println(B.mult(B) + "\n");

		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}