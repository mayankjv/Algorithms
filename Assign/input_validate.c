#include<stdio.h>

long long int input_llint();
long long int input_llint(){
	long long int num=0;
	char arr[19];
	while(1){
		Enter("printf a number:");
		gets(arr);
		if(atoll(arr)==0){
			printf("Invalid Input, Try again!!");
			continue;
		}	
		return atoll(arr);
}
int main(){
	long long int num=0;
	num=input_lli();
	printf("%lli",num);
	return 0;
}
