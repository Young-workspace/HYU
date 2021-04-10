package assignment1;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;


public class Assignment1{
	public static void main(String[] args) {
		int N = Integer.parseInt(args[0]) ;			// save fisrt argument in N , means number of queens
		
		
		// call DFS class
		long be_DFS = System.currentTimeMillis();
		DFS_1 dfs = new DFS_1(N);
		dfs.dfs();
		int[] col = new int[N];
		col = dfs.get_ans();
		long af_DFS = System.currentTimeMillis();
		long DFS_time = (af_DFS - be_DFS)/1000;
		
		// call BFS class
		long be_BFS = System.currentTimeMillis();
		BFS_1 bfs = new BFS_1(N);
		bfs.bfs();
		int[] b = new int [N];
		b = bfs.get_ans();
		long af_BFS = System.currentTimeMillis();
		long BFS_time = (af_BFS - be_BFS)/1000;
		
		//call DFID class
		long be_DFID = System.currentTimeMillis();
		DFID dfid = new DFID(N);
		dfid.dfid();
		int[] d = new int [N];
		d = dfid.get_ans();
		long af_DFID = System.currentTimeMillis();
		long DFID_time = (af_DFID - be_DFID)/1000;
		
		try {
			String place = args[1] +"\\result" + N + ".txt";					// Set directory address and text file name
			
			// Open file 
			File file = new File(place);
			BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(file));
			
			//Write into the file
			if(file.isFile() && file.canWrite()) {
				// Write for DFS
				bufferedWriter.write(">DFS");
				bufferedWriter.newLine();
				
				// If Answer Not Exist print No solution without Location:
				if(col != null) {
					bufferedWriter.write("Location: ");
					for(int i = N-1; i >=0; i--) {
						bufferedWriter.write(col[i] + " ");
					}
				}
				else {
					bufferedWriter.write("No Solution");
				}
				bufferedWriter.newLine();
				bufferedWriter.write("Time: ");
				bufferedWriter.write(DFS_time + "\0");
				// Print Time
				
				bufferedWriter.newLine();
				
				// Write for BFS
				bufferedWriter.newLine();
				
				bufferedWriter.write(">BFS");
				bufferedWriter.newLine();
	
				//print answer
				if(b!= null) {
					bufferedWriter.write("Location: ");
					for(int i = 0; i < N; i++) {
						bufferedWriter.write(b[i] + " ");
					}
				}
				else {
					bufferedWriter.write("No Solution");
				}
				
				
				
				bufferedWriter.newLine();
				bufferedWriter.write("Time: ");
				System.out.println(BFS_time);
				bufferedWriter.write(BFS_time  + "\0");
				//Print time
				bufferedWriter.newLine();
				bufferedWriter.newLine();
				
				// Write for DFID
				bufferedWriter.write(">DFID");
				bufferedWriter.newLine();
				
				//Print answer
				if(d!= null) {
					bufferedWriter.write("Location: ");
					for(int i = N-1; i >=0; i--) {
						bufferedWriter.write(d[i] + " ");
					}
				}
				else {
					bufferedWriter.write("No Solution");
				}
				bufferedWriter.newLine();
				bufferedWriter.write("Time: ");			//Print time
				bufferedWriter.write(DFID_time + "\0");
				
				
				bufferedWriter.newLine();
				
				bufferedWriter.close();
			}
			
		}catch(IOException e) {
			System.out.println(e);
		}
		
		
    }
}
