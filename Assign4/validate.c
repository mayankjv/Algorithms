#include<stdio.h>
#include<stdlib.h>

int validate_int(char* arr);
int change_to_int(char* arr);

char* input();

int validate_int(char* arr){
	for(int i=0;arr[i]!='\0';i++)
		if(arr[i]-'0'<0 || arr[i]-'0'>9)
			return 0;
	return 1;
}
int change_to_int(char* arr){
	return atoi(arr);

}
char* input(){
	char* arr= (char*)malloc(100*sizeof(char));
	gets(arr);
}
int main(){
	char* arr= input();
        if(validate_int(arr)==0)
                printf("Invalid!");
        else{
		int i=change_to_int(arr);
		printf("%d",i);	
	}
	return 0;

}
