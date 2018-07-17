#include<stdio.h>

void insert_element(int element, int index, int arr[], int size);
void insert_element(int element, int index, int arr[],int size){
	int temp=arr[index];
	int i;
	for(i=index;i<size-1;i++){
		arr[i]=element;
		element=temp;
		temp=arr[i+1];
	}
	arr[i]=element;
	arr[i+1]=temp;
}

int main(){
	int size,arr[10000],element,index;
	printf("Enter the Size of the array");
	scanf("%d",&size);
	printf("Enter the elements of the array:");
	for(int i=0;i<size;i++)
		scanf("%d",&arr[i]);
	printf("Enter the element to be inserted:");
	scanf("%d",&element);
	printf("Enter the Index:");
	scanf("%d",&index);
	insert_element(element, index, arr, size);
	for( int i =0;i<size+1;i++)
		printf("%d ",arr[i]);
	return 0;
}
