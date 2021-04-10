package assignment2;

public class NQueen {
	private int row;
	private int col;
	
	//Save variable
	public NQueen(int row, int col) {
		this.row = row;							// save row from main to row in NQueen
		this.col = col;								// save column from main to column in NQueen
	}
	
	
	public void move() {					// move to next row
		row++;
	}
	
	public int getRow() {					// Return row value
		return row;
	}
	
	public int getCol() {					// Return column value
		return col;
	}
	
	// Goal Test
	public boolean Check(NQueen q) {				
		//Check row and column
		if(row == q.getRow() || col == q.getCol()) {
			return true;
		}
		else if(Math.abs(col - q.getCol()) == Math.abs(row - q.getRow())) {			// check diagonal
			return true;
		}
		return false;
	}
}
