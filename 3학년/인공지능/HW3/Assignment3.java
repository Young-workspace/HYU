package assignment3;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;



public class Assignment3 {
	private static int N;											// Number of queens

	public static void main(String[] args) {
		N = Integer.parseInt(args[0]) ;			// save fisrt argument in N , means number of queens
		
		double start = System.currentTimeMillis();				// Check time when start
		
		Chromosome c = new Chromosome(N);
		c.generateStart();
		
		NQueens result = c.getBoard();
		int[] p = result.getPosition();
		double end = System.currentTimeMillis();					// Check time when end
	
		double time = (end - start) / 1000.0;
		System.out.println("Number of generation: " +  c.getCurrent());
		
		
		// Write ouput to resultN.txt file
				try {
					String place = args[1] +"\\result" + N + ".txt";					// Set directory address and text file name
					
					// Open file 
					File file = new File(place);
					BufferedWriter bw = new BufferedWriter(new FileWriter(file));
					
					//Write into the file
					if(file.isFile() && file.canWrite()) {
						// Write for Hill Climbing
						bw.write(">Genetic Algorithm");
						bw.newLine();			// Go to new line , equal to enter
						
						// Print Solution to File
						for(int i = 0; i < N; i++) {
							bw.write(Integer.toString(p[i]));
							bw.write(" ");
						}
						bw.newLine();
						
						// Print Elapsed Time
						bw.write("Total Elapsed Time: ");
						bw.write(Double.toString(time));
					}
						
					bw.close();
						
				}catch(IOException e) {					// Exception handling
					System.out.println(e);
				}
		
	}
}
