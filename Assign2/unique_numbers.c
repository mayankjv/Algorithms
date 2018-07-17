/*This program takes an array as input and prints out the unique elements in that array, for example if there are repeating elements in the array, the elements will be printed just once*/
#include<stdio.h>

int generate_hash(int number);
int generate_hash(int number){
	return number%101;
}
struct node{
	int number;
	struct node* next;
}
int main(){
	int arr[1000];
	int lookup[101];
	int size;
	printf("Enter the size of the aray:");
	scanf("%d",&size);
	printf("Enter the elements of the array:");
	for(int i=0;i<size;i++){
		scanf("%d",&arr[i]);
	}
	for(int i=0;i<409;i++)
		lookup[i]=-1;
	for(int i=0;i<size;i++){
		if(lookup[generate_hash(arr[i])]==-1){
			printf("%d ",arr[i]);
			lookup[generate_hash(arr[i])]= ;
		}
	}
	return 0;
}
