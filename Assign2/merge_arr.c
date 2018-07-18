//This program takes two unsorted arrays as input and merges their elements to form a new sorted array, the approach is to first sort the two arrays and then merge them 
// to obtain a single sorted array. The sorting technique used is Quicksort.

#include<stdio.h>
#include<stdlib.h>

//Function declarations
void quicksort(int arr[], int start, int end);
void swap(int arr[], int index1, int index2);
void merge(int arr[],int arr1[], int arr2[], int size1, int size2);



int main(){
	int size1,size2;
	printf("Enter the size of the first array:");
	scanf("%d",&size1);
	int *arr1= (int*)malloc(size1*(sizeof(int)));
	printf("Enter the elements of first array");
	for(int i=0;i<size1;i++)
		scanf("%d",&arr1[i]);
	printf("Enter the size of the second array:");
	scanf("%d",&size2);
	int *arr2=(int*)malloc(size2*sizeof(int));
	printf("Enter the elements of the second array:");
	for(int i=0;i<size2;i++)
		scanf("%d",&arr2[i]);
	quicksort(arr1,0,size1-1);
	quicksort(arr2,0,size2-1);
	int *arr= (int*)malloc((size1+size2)*(sizeof(int)));
	merge(arr,arr1,arr2,size1,size2);
	printf("The Merged sorted array is as follows:");
	for(int i=0;i<size1+size2;i++)
		printf("%d ",arr[i]);

}
//This fuction takes two sorted arrays as inputs along with their sizes and a third array in which the third array will be stored. And merges the two arrays into the third one
void merge(int arr[],int arr1[],int arr2[], int size1, int size2){
	int i=0, j=0, k=0; //i for the index of the first array, j for the index of the second array and k for the third array.
	while(i<size1 && j<size2){ //while there are still elements left in both the arrays
		if(arr1[i]<=arr2[j]) //append the smaller one to the third array
			arr[k++]=arr1[i++];
		else
			arr[k++]=arr2[j++];
	}
	if(i<size1){ //if elements are still remaining in the first array append them in the third array in the same order they are.
		for(;i<size1;i++)
			arr[k++]=arr1[i];
	}
	if(j<size2){ //for elements remaining in the second array if any. 
		for(;j<size2;j++)
			arr[k++]=arr2[j];
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
