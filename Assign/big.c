//This program adds two big numbers in C by storing them as a character array and storing the result in another character array
// The program focuses on the core operations involved in addition of two integers.
// Addition is done by maintaining a carry and proceeding backwards.
#include<stdio.h>

int main(){
	char num1[100],num2[100]; // char arrays to take input from user, the idea is to store numbers as char arrays because the number may be out of the range of long
	scanf("%s",num1); //taking input
	scanf("%s",num2); //taking input
	// If The user has entered a negative number, an appropriate message is displayed
	if(num1[0]=='-' || num2[0]=='-'){ 
		printf("Negative numbers not yet supported!");
		return 0;
	}
	int len1=str_length(num1); len1--;   //finding lenght of the input1 and decrementing because indexing is 0 based.
	int len2=str_length(num2); len2--;   //finding lenght of the input2 and decrementing because indexing is 0 based.
	//printf("%d %d",len1,len2);     debug statement
	int carry=0;	// integer to store the carry at a given point of time.
	int temp_sum=0;	// variable to store the temporary sum of the two digits
	int pos=0;		// variable to incrementally write in the third char array which stores the result
	char num3[200];	// This will be the result when read backwards.
	while(len1>=0 && len2>=0){ //iterating from the back until at least one of the number ends
		//validation of input
		if((int)(num1[len1]-'0')>9 || (int)(num2[len2]-'0')>9){
			printf("Invalid Input!!!");
			return 0;
		}
		temp_sum=(int)(num1[len1]-'0')+(int)(num2[len2]-'0')+carry; //calculating temporary sum
		//printf("\n%d\n",temp_sum);      debug statement
		num3[pos++]=(temp_sum%10)+'0';	//assigning value to the result
		carry=temp_sum/10;				//updating the carry
		len1--; len2--;					//updating the pointers of both the numbers
	}
	if(len1<=0){						//case when number2 will be bigger in size than number1
		while(len2!=-1){					//just adding carry to the remaining digits of number2
		if((int)(num2[len2]-'0')>9){
			printf("Invalid Input!!!");
			return 0;
		}
			temp_sum=(int)(num2[len2--]-'0')+carry;
			num3[pos++]=temp_sum%10+'0';
			carry=temp_sum/10;
		}
		if(carry==1){		//appending the last value of carry to the result if it is not zero
			num3[pos++]=carry+'0';
		}

	}
	else if(len2<=0){ 			//case when number1 will be bigger in size than number2
		while(len1!=-1){			// just adding carry to the remaining digits of number1
		if((int)(num1[len1]-'0')>9){
			printf("Invalid Input!!!");
			return 0;
		}
			temp_sum=(int)(num1[len1--]-'0')+carry;
			num3[pos++]=temp_sum%10+'0';
			carry=temp_sum/10;
		}
		if(carry==1){			//appending the last value of carry to the result if it is not zero
			num3[pos++]=carry+'0';
		}
	}
	else{						// the case when number1 and number2 will be of equal length
		if(carry==1){			//appending the last value of carry to the result if it is not zero
			num3[pos++]=carry+'0';
		}		
	}
	num3[pos]='\0';				//since number 3 is a string, terminating it with a null character.
	int len3= str_length(num3)-1;
	for(int i=len3;i>=0;i--){	//loop for printing the string backwards	
		printf("%c",num3[i]);
	}	
	return 0;
}
// This function accepts a characeter array and iterated through it to calculate its length.
int str_length(char str[]) {
   int len = 0;
   while (str[len] != '\0')
      len++;
   return len;
}
