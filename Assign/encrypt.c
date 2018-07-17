/* This program encrypts a given number using the binary inverter operator.
*/
#include<stdio.h>

int encrypt(int num); //function declaration of the encryption function
int decrypt(int num); //function declaration of the encryption function
int main(){
	int num; // a variable to take input from the user
	scanf("%d",&num); // getting the integer input
	printf("The Encrypted number is: %d\n", encrypt(num));  //printing the encrptyed number
	printf("The Decrypted number is: %d\n", decrypt(encrypt(num)));  //printing the decrypted number
	return 0;
}
// a fuction that accepts a number and returns after encrypting it
int encrypt(int num){
	return ~num; // Inverting all the bits of the number to change its bit pattern
}
// a function that accepts encrypted number and returns after decrypting it
int decrypt(int num){
	return ~num; // inverting all the bits of encrypted number to get the original number back
}
