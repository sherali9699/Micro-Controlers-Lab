#include <stdio.h>
#include <stm32f10x.h>

int check_right_side(int x, int y);
int check_left_side(int x, int y);

int check_right_side(int x, int y) {
	// checks the right hand side of the equation
	return (x*x) + (2*x*y) + (y*y);
}

int check_left_side(int x, int y) {
	// checks the left hand side of the equation
	return (x+y)*(x+y);	
}


int main(void) {
	
	int left, right;
	int a, b;
	
	a = 2; b = 3;
	
	left = check_left_side(a, b);
	right = check_right_side(a, b);
	
	if (left == right) {
		printf("For a = %d, b = %d, the left side is %d and the right side is %d", a, b, left, right);
	}
	else {
		printf("Not same!");
	}	
}