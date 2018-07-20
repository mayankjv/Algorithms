/* This program encrypts a given number using the binary inverter operator.
*/
#include<stdio.h>
#include<stdlib.h>

char* encrypt(char* num); //function declaration of the encryption function
char* decrypt(char* num); //function declaration of the encryption function

int main(int argc,const char* argv[]){
	char* str= (char*)malloc(1000*sizeof(char));
	gets(str);
	if(argc==1){
		printf("The Encrypted number is: %s\n", encrypt(str));  //printing the encrptyed number
		printf("The Decrypted number is: %s\n", decrypt(encrypt(str)));  //printing the decrypted number
		return 0;
	}
	else{
		if(argv[1][0]=='0'){
			printf("The Encrypted number is: %s\n", encrypt(str));  //printing the encrptyed number
		}
		else{
			printf("The Decrypted number is: %s\n", decrypt(str));  //printing the decrypted number
		}
	}
}
// a fuction that accepts a number and returns after encrypting it
char* encrypt(char* str){
//	return ~num; // Inverting all the bits of the number to change its bit pattern

	char key='A';
	char* encrypted=str;
	for(int i=0;str[i]!='\0';i++){
		encrypted[i]=str[i]^key;
	}
	return encrypted;

}
// a function that accepts encrypted number and returns after decrypting it
char* decrypt(char* str){
	return encrypt(str); // inverting all the bits of encrypted number to get the original number back
}
