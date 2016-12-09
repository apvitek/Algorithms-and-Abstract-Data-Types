// Lex.java
// Andrea Vitek
// 1559060
// pa 1
// This program reads strings from a text file, sorts them using a separate List ADT
// and exports the sorted strings to a text file

import java.io.*;
import java.util.Scanner;

public class Lex {	
	public static void main(String[] args) {
		//String[] files = Lex.getIOFiles();
		String[] files = args;
		
		if (files.length != 2) {
			System.out.println("You did not enter two files names separated by a space.");
			System.exit(0); // Exit as requested
		}

		String[] inputListStrings;
		List inputListIndexes = new List();

		try {
			inputListStrings = Lex.loadFromTextFile(files[0]);
			Lex.insertionSortForList(inputListStrings, inputListIndexes);
			
			Lex.exportToTextFile(inputListStrings, inputListIndexes, files[1]);
			
			System.out.println("Completed");

		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	// Performs insertionSort to sort the indexes of a String array in alphabetical order by storing
	// the array's sorted indexed in a List ADT
	public static void insertionSortForList(String[] inputListStrings, List inputListIndexes) {
		inputListIndexes.append(0);
		
		for (int j = 1; j < inputListStrings.length; j++) {
			inputListIndexes.moveFront();
			
			while (inputListIndexes.index() >= 0) {
				int cursor = inputListIndexes.get();
				
				if (inputListStrings[j].compareTo(inputListStrings[cursor]) < 0) {
					inputListIndexes.insertBefore(j);
					break;
				}
				
				inputListIndexes.moveNext();
				
				if (inputListIndexes.index() == -1) {
					inputListIndexes.append(j);
				}
			}
		}
	}

	// Asks for the input and output file names to the user
	public static String[] getIOFiles() {
		Scanner scanner = new Scanner(System.in);
		String[] IOFiles;

		// Get the user input
		System.out.println("Enter the name of the input and output files, in that order and including the file extension, separated by a space.");

		String line = scanner.nextLine();

		IOFiles = line.split(" ");

		if (IOFiles.length != 2) {
			System.out.println("You did not enter two files names separated by a space.");
			System.exit(0); // Exit as requested
		}

		scanner.close();

		return IOFiles;
	}

	// Loads the lines of an input file into a String array.
	public static String[] loadFromTextFile(String inputFileURL) throws IOException {
		File f = new File(inputFileURL);
		String[] inputListStrings = null;

		if (!f.exists()) {
			throw new RuntimeException("File does not exist");
		}

		try {
			// Count number of lines in input file
			LineNumberReader  lnr = new LineNumberReader(new FileReader(new File(inputFileURL)));
			lnr.skip(Long.MAX_VALUE);
			int totalLines = lnr.getLineNumber() + 1;
			lnr.close();

			inputListStrings = new String[totalLines];
			int currentIndex = 0;

			try (BufferedReader br = new BufferedReader(new FileReader(inputFileURL))) {
				String currentLine;

				while ((currentLine = br.readLine()) != null) {
					inputListStrings[currentIndex] = currentLine;
					currentIndex++;
				}
			}

		} catch (IOException e) {
			System.out.println("Error! " + e.toString());
		}

		return inputListStrings;
	}
	
	// Exports the Strings of an array in the correct alphabetical order to a text file
	// following their sorted indexes in a List ADT
	public static void exportToTextFile(String[] inputListStrings, List inputListIndexes, String outputFileName) {
		try (PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter(outputFileName, true)))) {
			inputListIndexes.moveFront();

			while (inputListIndexes.index() >= 0) {
				out.print(inputListStrings[inputListIndexes.get()] + "\n");
				inputListIndexes.moveNext();
			}

		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	// Prints the Strings of an array in the correct alphabetical order to the console
	// following their sorted indexes in a List ADT
	public static void printStringsInOrder(String[] inputListStrings, List inputListIndexes) {
		inputListIndexes.moveFront();

		System.out.print("[ ");

		while (inputListIndexes.index() >= 0) {
			System.out.print(inputListStrings[inputListIndexes.get()] + " ");
			inputListIndexes.moveNext();
		}

		System.out.print("]");
	}
}