package assignment1;

public class DFID {
	private int N;
	private int cols[];
	private int ans[];
	
	public DFID(int N) {
		this.N = N;
		cols = new int[N];	
	}
	
	public int[] get_ans() {    // return answer array to main function
		return ans;
	}
	public boolean isPossible(int a[]) {					// Goal Test function 
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < i; j++) {
				if(cols[i] == cols[j] || Math.abs(j - i) == Math.abs(cols[j] - cols[i]))  {			// test row and diagonals
					return false;
				}
			}
		}
		return true;			// If queen can placed, return true
	}
	
	public void dfid() {			// loop bfs
		for(int i = 0; i < N; i++) {
			if(loop(i) ) {
				break;
			}
		}		
	}
	
	public boolean loop(int level) {
		if(level == N) {						// If level arrive at the last row
			if(isPossible(cols)) {			// check queen can be placed according to the saved position in cols	
		    	ans = cols;	
				return true;
				}
			return false;
		}
		for(int i = 0;  i <N; i++) {				// save temporary queen position into cols array 
			cols[level] = i;
			if(loop(level+ 1)) {						// recursively loop to the end
				return true;
			}
		}
		ans = null;
		return false;
	}
	
}



	


