/* this program prints fibonacci series upto the number of terms entered by a user. */
#include<stdio.h>

int main(){
	int num; //variable that will be entered the by the user.
	scanf("%d",&num); //taking input from the user
	if(num<=0){
		printf("Please Enter a Valid number");// in case user enters 0 or less, we have to give an appropriate error message
		return 0;	
	}
	for(int i=1;i<=num;i++){ // looping through to print all the values upto "num"th term
		printf("%d ",fibonacci(i));
	}
	return 0;
}
// A fuction to find "num"th term of the fibonacci series using recursion
//it accepts the parameter num and returns an integer equal to the value of the term
int fibonacci(int num){
	if(num<=2){
		return num-1;	
	}
	return (fibonacci(num-1)+fibonacci(num-2)); // sum of the previous two terms
}
