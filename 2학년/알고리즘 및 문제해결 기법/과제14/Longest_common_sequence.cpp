#include<iostream> 
#include<cstring> 
#include<cstdlib> 
using namespace std; 
  
void lcs( char *X, char *Y, int m, int n ) 
{ 
   int L[m+1][n+1]; 
  
   for (int i=0; i<=m; i++) 
   { 
     for (int j=0; j<=n; j++) 
     { 
       if (i == 0 || j == 0) 
         L[i][j] = 0; 
       else if (X[i-1] == Y[j-1]) 
         L[i][j] = L[i-1][j-1] + 1; 
       else
         L[i][j] = max(L[i-1][j], L[i][j-1]); 
     } 
   } 
  

   int index = L[m][n]; 

   char lcs[index+1]; 
   lcs[index] = ' ';
  
   int i = m, j = n; 
   while (i > 0 && j > 0) 
   { 
 
      if (X[i-1] == Y[j-1]) 
      { 
          lcs[index-1] = X[i-1]; 
          i--; j--; index--;    
      } 
  
     
      else if (L[i-1][j] > L[i][j-1]) 
         i--; 
      else
         j--; 
   } 
  
   cout << lcs << "\n"; 
} 

int main() 
{ 
	char *A = new char[500];
	char *B = new char[500];
	cin >> A;
	cin >> B;
  	int m = strlen(A); 
  	int n = strlen(B); 
  	lcs(A, B, m, n); 
  	return 0; 
} 
