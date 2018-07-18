/* This program takes array as input, additionally it takes an element that is to be inserted in the array
and the index at which it is to be inserted and it inserts the element at that position and shifts all the
subsequent numbers in the array*/
#include<stdio.h>

void insert_element(int element, int index, int arr[], int size); 
//This function accepts the element to be inserted, the index at which the element is to be inserted, the array,
// and the size of the array and it inserts the element in the given array at the required position.
void insert_element(int element, int index, int arr[],int size){
	int temp=arr[index]; // A temporary variable to store the element that will be overwritten.
	int i;	//Iterator variable
	//writing the element at the index and shifting all the subsequent elements.
	for(i=index;i<size-1;i++){
		arr[i]=element;
		element=temp;
		temp=arr[i+1];
	}
	arr[i]=element;
	//since maximum array size is specified to be 10000
	if(size<10000){
			arr[i+1]=temp;
	}
}

int main(){
	int size,arr[10000],element,index; 
	lab:
	printf("Enter the Size of the array");
	scanf("%d",&size);
	// Since size constraint is specified and size can not be negative
	if(size<0 || size>10000 ){
		printf("Enter a valid size !!!/n");
		goto lab;
	}
	//Not asking for any elements when the entered size is zero
	if(size!=0)
		printf("Enter the elements of the array:");
	for(int i=0;i<size;i++)
		scanf("%d",&arr[i]);
	printf("Enter the element to be inserted:");
	scanf("%d",&element);
	printf("Enter the Index:");
	scanf("%d",&index);
	//Validating the index.
	if(index<0 || index>size){
		printf("Invalid Index\n");
		return 0;
	}
	//Calling the function to insert the element at the given position
	insert_element(element, index, arr, size);
	//printing the array after insertion
	for( int i =0;i<size+1;i++)
		printf("%d ",arr[i]);
	return 0;
}


