import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class Converter {
	public static void main(String[] args) throws FileNotFoundException {
		System.out.println("Model filename:");
		
		Scanner scanner = new Scanner(System.in);
		
		String path = scanner.nextLine();
		
		File file = new File(path);
		System.out.println("Opening " + file.getAbsolutePath());
		
		Scanner fileScanner = new Scanner(file);
		
		//Holds the lines of info that we actually care about
		ArrayList<String> vertices = new ArrayList<String>();
		ArrayList<String> indices = new ArrayList<String>();
		
		while (fileScanner.hasNextLine()) {
			String line = fileScanner.nextLine();
			if (line.startsWith("v ")) {
				vertices.add(line.substring(1).trim());
			} else if (line.startsWith("f")) {
				
				//This gets fun.  There can be 3 or 4 points to a quad
				//The format is a/b/c a/b/c a/b/c a/b/c
				//b and c are texture and normal indices, we don't care about them
				String[] data = line.substring(1).trim().split(" ");
				
				//Split out the last two elements of each
				for (int i = 0; i < data.length; i++) {
					data[i] = data[i].split("/")[0];
				}
				
				//Put the first 3 in indices
				indices.add(data[0] + " " + data[1] + " " + data[2]);
				
				//If there were 4, put values 1 2 and 3 in!
				if (data.length > 3) {
					indices.add(data[1] + " " + data[2] + " " + data[3]);
				}
			}
		}
		
		//Write to the file
		PrintWriter out = new PrintWriter(file.getPath() + ".model");
		out.println(vertices.size());
		
		for (String str : vertices) {
			out.println(str);
		}
		
		for (String str : indices) {
			out.println(str);
		}
		out.close();
	}
}
