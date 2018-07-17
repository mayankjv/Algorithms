/* This program encrypts a given number using the binary inverter operator.
*/
#include<stdio.h>

long encrypt2(long num);
long encrypt(long num); //function declaration of the encryption function
long decrypt(long num); //function declaration of the encryption function
long decrypt2(long num);
int main(){
	long num; // a variable to take input from the user
	scanf("%ld",&num); // getting the integer input
	printf("The Encrypted number using algorithm 1 is: %ld\n", encrypt(num));  //printing the encrptyed number
	printf("The Encrypted number using algorithm 2 is: %ld\n", encrypt2(num));  //printing the encrptyed number
	printf("The Decrypted number using algorithm 1 is: %ld\n", decrypt(encrypt(num)));  //printing the decrypted number
	printf("The Decrypted number using algorithm 2 is: %ld\n", decrypt2(encrypt2(num)));  //printing the decrypted number
	return 0;
}
// a fuction that accepts a number and returns after encrypting it
long encrypt(long num){
	return ~num; // Inverting all the bits of the number to change its bit pattern
}
long encrypt2(long num){
	long temp=1;
	temp=temp<<8;
	return temp^num;
}
long decrypt2(long num){
	long temp=1;
	temp=temp<<8;
	return temp^num;
}
// a function that accepts encrypted number and returns after decrypting it
long decrypt(long num){
	return ~num; // inverting all the bits of encrypted number to get the original number back
}
