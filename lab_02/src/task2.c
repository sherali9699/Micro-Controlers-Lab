#include <stdio.h>
#include <stm32f10x.h>


int main(void) {
	
	// my ID: 71, Hexa Code: 0111 0001, Decimal Value: 113
	int key = 113;
	
	char user_data[] = {'H', 'a', 'b', 'i', 'b', ' ','U', 'n', 'i', 'v', 'e', 'r', 's', 'i', 't', 'y', '\0'};

	int encrypted[16];
	int decrypted[16];
	
	int i;
	printf("Printing the Encrypted Hexa Decimal Values\n");
	for (i = 0; i < 16; i = i + 1){
		encrypted[i] = user_data[i] ^ key;
		printf("(%x, %c)", encrypted[i], encrypted[i]);
	}
	printf("\nPrinting the Decrypted Characters Now: \n");
	for (i = 0; i < 16; i = i + 1){
		decrypted[i] = encrypted[i] ^ key;
		printf("%x, ", decrypted[i]);
	}
	printf("\nThe Final Decrypted String Is:\n");
	for (i = 0; i < 16; i = i + 1){
		printf("%c", decrypted[i]);
	}
}