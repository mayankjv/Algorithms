//This program takes the size of an array and the array as input from the user and
//displays only the elements that occur just once in the array.
// the approach used is to sort the elements and if any two consecutive elements are equal, do not print them.
#include<stdio.h>
#include<stdlib.h>

void quicksort(int arr[], int start, int end);
void swap(int arr[], int index1, int index2);

int main(){
	int size;
	printf("Enter the size of the array:");
	scanf("%d",&size);
	int *arr= (int*)malloc(size*sizeof(int));  //dynamic memory allocation to the array
	printf("Enter the elements of the array:");
	//Taking input
	for(int i=0;i<size;i++)
		scanf("%d",&arr[i]);
	quicksort(arr,0,size-1); //Function call to quicksort
	for(int i=0;i<size;){
		if(arr[i]==arr[i+1]){  //checking if the currect element is equal to the next element
			int temp=arr[i];
			while(arr[i]==temp && i<size)	//skipping all the elements that are equal to the current element
				i++;
		}
		else{ //If the two adjacent elements are not equal then print the current element.
			printf("%d ",arr[i]);
			i++;
		}
	}
}
//recursive function for quicksort, which takes an array as input and the boundary indices which are to be sorted
void quicksort(int arr[], int start, int end){
	int pivot= start; // taking the first element as the pivot everytime quicksort is called
	int first=start; //this will be the running variable that will store the left bound during traversal
	int last=end;   //this will be the running variable that will store the right bound during traversal
	while(first<last){
		while(arr[first]<=arr[pivot] && first<last) //skip all the elements starting at the beginning that are smaller than or equal to the pivot element
			first++;
		while(arr[last]>arr[pivot] )  //skip all the elements starting at the end that are greater than pivot element
			last--;
		if(first<last){
			swap(arr, first ,last); //swap the elements that first and the last index because the at this point of time the element at last is smaller than pivot and the one at first is larger than pivot element
		}
		swap(arr,pivot,last); // swap in order to send pivot to its position
		quicksort(arr,start,last-1); //call quicksort for the left side of pivot elemet
		quicksort(arr,last+1,end); //call quicksort for the right side of the pivot element.
		
	}
}
//a function that takes an integer array as input and two indices, and swaps the values present at those indices in the array
void swap(int arr[], int index1, int index2){
	int temp;
	temp=arr[index1];
	arr[index1]=arr[index2];
	arr[index2]=temp;
}
