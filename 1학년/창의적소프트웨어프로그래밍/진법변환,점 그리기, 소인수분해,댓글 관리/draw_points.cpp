#include<iostream>
#include<stdio.h>

using namespace std;

void loop(int x, int y, **point[x][y]){
	for ( int i = 0; i <= y; i++ )
			{
				for ( int j = 0; j <= x; j++ )
				{
					if ( i == y && j == x )
					{
						point[i][j] = 1;
					}
					else
					{
						point[i][j] = 2;
					}
					if ( point[i][j] == 1 )
					{
						cout << "*" << " ";
					}
					else if ( point[i][j] == 2 )
					{
						cout << "." << " ";
					}
					
				}
				
				cout << endl;
			}
}

int main()
{
	int x = 0, y = 0;
	char again = 'y';
	int save_x = 0, save_y = 0;
	
	while (again == 'y' )
	{
		
		cin >>x>>y;

		// 2D array
		int **point = new int *[x];
		for ( int i = 0; i<x+1; i++ )
		{
				point[i] = new int[y + 1];
		}
		
		//check postitive
		if ( x<0 || y<0 )
		{
			return -1;
		}
		else
		{
			loop (x, y, point[x][y]);
			// for ( int i = 0; i <= y; i++ )
			// {
			// 	for ( int j = 0; j <= x; j++ )
			// 	{
			// 		if ( i == y && j == x )
			// 		{
			// 			point[i][j] = 1;
			// 		}
			// 		else
			// 		{
			// 			point[i][j] = 2;
			// 		}
			// 		if ( point[i][j] == 1 )
			// 		{
			// 			cout << "*" << " ";
			// 		}
			// 		else if ( point[i][j] == 2 )
			// 		{
			// 			cout << "." << " ";
			// 		}
					
			// 	}
				
			// 	cout << endl;
			// }
			
			cout << "continue?" << endl;
			cin >> again;
			if(again = 'y'){
				save_x = x;
				save_y = y;
				loop(save_x, save_y, point);
			}
			

			if (again != 'y')
			{
				return -1;
				// free array
				for ( int i = 0; i < y; i++ )
				{
					delete[] point[i];
				}
				delete[] point;
			}
			
		}
	}
	
	
}