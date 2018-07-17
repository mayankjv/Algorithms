
#include<stdio.h>
#include<stdlib.h>

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
	int *arr= (int*)malloc(size*sizeof(int));
	printf("Enter the elements of the array:");
	for(int i=0;i<size;i++)
		scanf("%d",&arr[i]);
	quicksort(arr,0,size-1);
	for(int i=0;i<size;){
		if(arr[i]==arr[i+1]){
			int temp=arr[i];
			while(arr[i]==temp && i<size)
				i++;
		}
		else{
			printf("%d ",arr[i]);
			i++;
		}
	}
}
