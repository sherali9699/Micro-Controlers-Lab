#include <stdio.h>
#include <stm32f10x.h>

int main(void) {
	
	
	int start;
	int end = 1000;
	
	int counter = 0;
	
	int u, t, h; // unit, tens, hundreds
	
	for (start = 100; start < end; start = start + 1){
		u = start % 10;        
    t = (start / 10) % 10; 
    h = (start / 100) % 10;
		
		int sum;
		sum = (h * h * h) + (t * t * t) + (u * u * u);

		if (sum == start) {
			counter = counter + 1;
			printf("%d: %d\n", counter, sum);
		}
		
		if (counter > 4){break;}
		
	}	
	
}