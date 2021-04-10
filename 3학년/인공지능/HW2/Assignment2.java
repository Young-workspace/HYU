package assignment2;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class Assignment2 {
	private static int N;
	//private static int s_Restart = 0;		// count steps after restarted
	//private static int steps=0;					// count steps
	private static int heuristic = 0;		
	private static int random = 0;
	
	//Create initial board
	public static NQueen[] Board() {
		NQueen[] initial = new NQueen[N];
		Random r = new Random();				// get random number
		for(int i = 0; i < N; i ++ ) {
			initial[i] = new NQueen(r.nextInt(N), i);			// Save random number to board
		}
		return initial;
	}
	
	// Check to print Current State
	private static void printState(NQueen[] state) {
		// Temporary Board
		int [][] tmpBoard = new int[N][N];
		for(int i= 0; i < N; i++) {
			// Get Position and set it as 1
			tmpBoard[state[i].getRow()][state[i].getCol()] = 1;
		}
		System.out.println();
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				System.out.print(tmpBoard[i][j] + " ");
			}
			System.out.println();
		}
	}
	
	// Find State
	public static int find(NQueen[] state) {
		//int heuristic = 0;
		heuristic = 0;
		for(int i = 0; i < state.length; i++) {
			for(int j = i+1; j<state.length;j++) {
				if(state[i].Check(state[j])) {
					heuristic++;
				}
			}
		}
		return heuristic;
	}
	
	// Next step
	public static NQueen[] nextBoard(NQueen[] now) {
		NQueen[] next = new NQueen[N];
		NQueen[] tmp = new NQueen[N];
		int p = find(now);
		int best = p;
		int h;
		
		for(int i = 0; i <N; i++) {
			// copy present to best
			next[i] = new NQueen(now[i].getRow(), now[i].getCol());
			tmp[i] = next[i];
		}
		
		// Look column
		for(int i = 0; i < N; i++) {
			if( i > 0) {
				tmp[i-1] = new NQueen(now[i-1].getRow(), now[i-1].getCol());
			}
			tmp[i] = new NQueen(0, tmp[i].getCol());
			// Look row
			for(int j = 0; j < N; j++) {
				h = find(tmp);
				// Check tmp better than saved
				if(h < best) {
					best = h;
					// Copy tmp to best
					for(int k = 0; k < N; k++) {
						next[k] = new NQueen(tmp[k].getRow(), tmp[k].getCol());
					}
				}
				// Move Queen
				if(tmp[i].getRow() != N-1) {
					tmp[i].move();
				}
			}
		}
		//Check p & best equal
		if(best == p) {
			random++;
			//s_Restart= 0;
			next = Board();
			h = find(next);
		}
		else {
			h = best;
		}
		//steps++;
		//s_Restart++;
		return next;
		
	}
	
	public static void main(String[] args) {
		N = Integer.parseInt(args[0]) ;			// save fisrt argument in N , means number of queens
		double start = System.currentTimeMillis();
		int p;
		// initialization
		NQueen[] now = Board();
		p = find(now);
		while(p !=0) {
			//Get Next
			now = nextBoard(now);
			p = heuristic;
		}
		double end = System.currentTimeMillis();
		
		double time = (end - start) / 1000.0;					// Elapsed time
		
		//Test Print
		//printState(now);
		//System.out.println("Total number of climb: " + steps);
		System.out.println("Random Restart count: "  + random);
		//System.out.println("Climbed after restart: " + s_Restart);
		
		int [][] tmpBoard = new int[N][N];
		for(int i= 0; i < N; i++) {
			// Get Position and set it as 1
			tmpBoard[now[i].getRow()][now[i].getCol()] = 1;
		}
			
		// Write ouput to resultN.txt file
		try {
			String place = args[1] +"\\result" + N + ".txt";					// Set directory address and text file name
			
			// Open file 
			File file = new File(place);
			BufferedWriter bw = new BufferedWriter(new FileWriter(file));
			
			//Write into the file
			if(file.isFile() && file.canWrite()) {
				// Write for Hill Climbing
				bw.write(">Hill Climbing");
				bw.newLine();			// Go to new line , equal to enter
				
				for(int i = 0; i < N; i++) {
					for(int j = 0; j < N; j++) {
						if(tmpBoard[j][i] == 1) {				// Write col to txt file if Queen is located
							//bufferedWriter.write(i);
							bw.write(Integer.toString(j));
							System.out.println(j);
						}
					}
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
