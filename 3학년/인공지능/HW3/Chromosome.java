package assignment3;

import java.util.Arrays;
import java.util.Comparator;


public class Chromosome {
	private int N;
	private int p_size = 100;									// Size of population ( Randomly selected)
	private int generation = 400;							// Number of generation
	private int current = 1;										// Position of current generation
	private int mutation = 80;
	
	private int factor = 5;										// Higher = higher fitness selection
	private NQueens best;
	private boolean isFinished = false;

	private NQueens[] population;							// Save random queen position
	
	public Chromosome(int N) {							  // Save N to N in Chromosome
		this.N= N;
	}
	
	private  void initialize() {									// Initialize board 
		best = getBoard();
	}
	

	// Return most fit Board
	public NQueens getBoard() {							// Initilize best board -> first board
		NQueens board = population[0];
		
		int maxScore = 100000;
		for(int i = 0; i < p_size; i++) {
			int score = population[i].getFitness();
			
			if(score < maxScore) {
				maxScore = score;
				board = population[i];
			}
		}
		return board;
	}
	
	// Make current board as parent and generate child by calling reproduce function
	public void update() {
		if(current < generation && best.getFitness() > 0) {
			NQueens[] parentP = population.clone();				// Parent Population
			for(int i = 0; i < p_size; i+=2) {
				// Copy parent population
				NQueens[] parent = select(parentP);
				NQueens[] children = reproduce(parent);
				
				population[i] = children[0];
				
				// If population size = odd, add final child
				if(i!=p_size -1) {
					population[i+1] = children[1];
				}
			}
			current++;
			best = getBoard();
			
		}
		else{
			isFinished = true;
		}
	}
	
	
	// Update Variables
	public void updateVar(int mut, int f, int num) {
		mutation = mut;
		factor = f;
		generation = num;
	}
	
	// Function to produce child, using cross over
	public NQueens[] reproduce(NQueens[] parent) {
		NQueens[] children = new NQueens[2];
		
		// Get cross over point value randomly
		int cross = (int)(Math.random() * (N-1))+1;						// Cross Over point
		int[] firstP, secondP, firstC, secondC;
		firstP = split(parent[0].getPosition(), 0, cross);
		secondP = split(parent[1].getPosition(), cross, N);
		firstC = combine(firstP, secondP);
		
		firstP = split(parent[0].getPosition(), cross, N);
		secondP = split(parent[1].getPosition(), 0, cross);
		secondC = combine(secondP, firstP);
		
		firstC = mutate(firstC);
		secondC = mutate(secondC);
		
		children[0] = new NQueens(firstC);
		children[1] = new NQueens(secondC);
		
		return children;
	}
	
	// Function for mutation
	public int[] mutate(int[] positions) {
		int rand = (int) Math.round(Math.random() * 100);
		
		if(rand <= mutation) {
			int randIndex = (int) Math.round(Math.random()*(N-1));
			positions[randIndex] = (int) Math.round(Math.random() * (N-1));
		}
		
		if(rand <= mutation /2) {										// Double mutation Chance
			int randIndex = (int) Math.round(Math.random() * (N-1));
			positions[randIndex] = (int) Math.round(Math.random()* (N-1));
		}
		return positions;
	}
	
	// combine numbers from parent1 and parent 2
	public int[] combine(int[] array1, int[] array2) {
		int[] tmp = new int[array1.length +array2.length];
		System.arraycopy(array1, 0, tmp, 0, array1.length);
		System.arraycopy(array2, 0, tmp, array1.length, array2.length);
		return tmp;
	}

	// Split parent1 or parent2 at cross point
	public int[] split(int[] array, int start, int end) {
		int length = end - start;
		
		int [] tmp = new int[length];
		
		for(int i = 0; i < tmp.length; i++) {
			tmp[i] = array[start + i];
		}
		return tmp;
	}
	
	// Select parent, parent1 =  most fit, parent2 second most fit
	public NQueens[] select(NQueens[] parentP) {
		NQueens[] parent = new NQueens[2];
		
		Arrays.sort(parentP, new Comparator<NQueens>() {
			public int compare(NQueens q1, NQueens q2) {
				int f1 = q1.getFitness();
				int f2 = q2.getFitness();
				
				if(f1<f2)
					return -1;
				else if(f1>f2)
					return 1;
				else
					return 0;
			}
		});
		
		// Give new fit board
		for(int i = 0; i<parent.length; i++) {
			double rand = Math.random();
			
			// p_size * rand^factor
			int randIndex = (int) (p_size * Math.pow(rand, factor));
			parent[i] = parentP[randIndex];
		}
		return parent;
	}
	
	// Check if all queens are set and no queen attacking
	public boolean isFinished() {
		return isFinished;
	}
	
	// return current generation
	public int getCurrent() {
		return current;
	}
	
	// Beginning program
	public void generateStart() {
		population = new NQueens[p_size];
		for(int i = 0; i < p_size; i++) {
			population[i] = new NQueens(generatePosition());
		}
		initialize();
		
		// update until program found answer
		while(!isFinished) {
			update();
		}
		
	}

	// Randomly generate position
	public int[] generatePosition() {
		int[] position = new int[N];
		for(int i = 0; i <N; i++) {
			position[i] = (int)Math.floor(Math.random()*N);
		}
		return position;
	}
	
		
}
