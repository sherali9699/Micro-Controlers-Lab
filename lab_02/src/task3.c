#include <stdio.h>
#include <stm32f10x.h>
 
int main(void) {
 
	int A[3][3] = {
			  {2, 1, 4},
				{4, 0, -1},
				{5, -1, 2}
    };
	
	int B[3][3] = {
				{1, 0, 4},
				{3, 7, 1},
				{5, -1, 2}
	};
	
	int res[3][3] = {{0, 0, 0},
	{0, 0, 0}, {0, 0, 0}};
	
	int i, j, k;
	
	for (i = 0; i < 3; i = i + 1){
		for (j = 0; j < 3; j = j + 1){
			for (k = 0; k < 3; k = k + 1){
				res[i][j] = res[i][j] + A[i][k] * B[k][j];
			}
		}
	}
	
	for (i = 0; i < 3; i = i + 1) {
     for(j = 0; j < 3; j = j + 1) {
           printf("%d, ", res[i][j]); 
     }
		 printf("\n");
   }
	
}