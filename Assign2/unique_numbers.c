//This program takes the size of an array and the array as input from the user and
//displays only the elements that occur just once in the array.
// the approach used is to sort the elements and if any two consecutive elements are equal, do not print them.
#include<stdio.h>
#include<stdlib.h>

//Quicksort algorithm to sort the array
void quicksort(int *arr,int first,int last){
   int i, j, pivot, temp;

   if(first<last){
      pivot=first;
      i=first;
      j=last;

      while(i<j){
         while(arr[i]<=arr[pivot]&&i<last)
            i++;
         while(arr[j]>arr[pivot])
            j--;
         if(i<j){
            temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
         }
      }

      temp=arr[pivot];
      arr[pivot]=arr[j];
      arr[j]=temp;
      quicksort(arr,first,j-1);
      quicksort(arr,j+1,last);

   }
}
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
