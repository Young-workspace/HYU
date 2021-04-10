package assignment3;

public class NQueens {

	private int[] position;
	private int boardSize;
	
	private int fitness;								// Number of queen attacking each other
	
	public NQueens(int[] position) {
		this.position = position;
		boardSize = position.length;
		fitness = measure();
	}
	
	public int[] getPosition() {
		return position;
	}
	
	public int getFitness() {
		return fitness;
	}
	
	public int measure() {
		int total = 0;
		int [] copy = position.clone();
		
		while(copy.length > 0) {
			int attack = Count(copy, copy[0]);
			// If attack < 1, no interaction between queens
			if(attack > 1) {
				total += calculate(attack);
			}
			copy = remove(copy, copy[0], copy.length - attack);
		}
		copy = position.clone();
		int[][] diagonals = new int[2][boardSize];
		
		// Generate diagonals
		for(int i = 0; i < 2; i++) {
			for (int j = 0; j < boardSize; j++) {
				if(i == 0)
					diagonals[i][j] = copy[j] + j;
				else
					diagonals[i][j] = copy[j] - j;
			}
		}
		
		for(int i = 0; i < 2; i++) {
			while(diagonals[i].length > 0) {
				int attack = Count(diagonals[i], diagonals[i][0]);
				// If no interaction among queens
				if(attack > 1) {
					total += calculate(attack);
				}
				diagonals[i] = remove(diagonals[i], diagonals[i][0], diagonals[i].length - attack);
			}
		}
		return total;
	}
	
	// Count list
	private int Count(int[] list, int num) {
		int total = 0;
		for(int i = 0; i < list.length; i++) {
			if(list[i] == num)
				total++;
		}
		return total;
	}
	
	// Remove Element
	private int[] remove(int[] list, int num, int newLength) {
		int[] newList = new int[newLength];
		int j = 0;
		for(int i = 0; i < list.length; i++) {
			if(list[i] != num) {
				newList[j] = list[i];
				j++;
			}
		}
		return newList;
	}
	
	// Sum the range of number
	private int calculate(int num) {
		int total = 0;
		for(int i = 0; i < num; i++) {
			total += i;
		}
		return total;
	}
	
	
	
}
