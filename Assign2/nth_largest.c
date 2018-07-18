/*this program finds the nth largest number from a given array of numbers
the algorithm used for the same is a slight optimisation of heap sort */

//I am making an asumption that all the elements of the array are unique
#include<stdio.h>
#include<stdlib.h>

//function declarations
void Heapify(int a[],int size, int curr); 
void swap(int arr[], int idx1, int idx2);
void quicksort(int arr[], int start, int end);
void buildMinHeap(int arr[],int size);
int nthlargest(int arr[],int size,int n);
int remove_duplicates(int arr[], int size);

int main(){
    int size,n;
    printf("Enter the size of the array:");
    scanf("%d",&size);
    int *arr= (int*)malloc(size*sizeof(int));  //dynamic memory allocation to the array
    printf("Enter the elements of the array:");
    //Taking input
    for(int i=0;i<size;i++)
	scanf("%d",&arr[i]);
    quicksort(arr,0,size-1);
    int size_new=remove_duplicates(arr, size);
    printf("Enter the values of N:");
    scanf("%d",&n);
    //printf("New Size=%d",size_new); debug statement
    if(size_new<n){
	printf("There are few unique numbers in the array!");
    }
    else
    printf("The required number is: %d\n",nthLargest(arr,size_new,n));

}



int remove_duplicates(int arr[], int size){
	int k=0;    	
	for(int i=0;i<size;){
		if(i==size-1){
			arr[k++]=arr[i++];
			continue;
		}
		else if(arr[i]==arr[i+1]){  //checking if the currect element is equal to the next element
			int temp=arr[i];
			while(arr[i]==temp && i<size)	//skipping all the elements that are equal to the current element
				i++;
			arr[k++]=temp;	
		}
		else{ //If the two adjacent elements are not equal then print the current element.
			arr[k++]=arr[i++];
		}
	}
	return k;
}

//function takes an array and two indexes as input and swaps the numbers at the two indexes.
void swap(int arr[], int idx1, int idx2){
    int temp=arr[idx1];
    arr[idx1]=arr[idx2];
    arr[idx2]=temp;
}

//This function takes an array, its size and the current as input and minimum heapyfies the arr
void Heapify(int arr[], int size, int curr)
{
    int left = 2*curr; //left child
    int right = 2*curr+1; //right child
    int smallest = curr; //initializing the smallest with currect
    // in next 4 lines finding the smallest element 
    if(left<size && arr[left]<arr[smallest])
        smallest = left;
    if(right<size && arr[right]<arr[smallest])
        smallest = right;
    //if new smallest element found, swapping it with root and calling heapify again 
    if(smallest!=curr)
    {
        swap(arr,curr,smallest);
        Heapify(arr,size,smallest);
    }
     
}

//this function is used to build minimum heap of arr upto size .
void buildHeap(int arr[], int size) {
    for(int i=size/2;i>=0;i--)
        Heapify(arr,size,i);
         
}


//this function uses the other functions and calculates the nth largest number in the array
int nthLargest(int arr[], int size, int n)
{
    int minHeap[n]; //an array to store heap
    int i; //iterator variable
    for(i=0;i<n;i++)
        minHeap[i] = arr[i]; //initializing heap eith input
    buildHeap(minHeap,n); //bulding heap of first n elements
    //iterating over the other elements
    for(i=n;i<size;i++)
    {   //inserting an element in the heap only if the element is larger than the root element because smaller elements are of no use to us
        if(arr[i]>minHeap[0])
        {
            minHeap[0]=arr[i];
            Heapify(minHeap,n,0);
        }
    }
    return minHeap[0];
}






//recursive function for quicksort, which takes an array as input and the boundary indices which are to be sorted
void quicksort(int arr[], int start, int end){
	if(start<end){
		int pivot= start; // taking the first element as the pivot everytime quicksort is called
		int first=start; //this will be the running variable that will store the left bound during traversal
		int last=end;   //this will be the running variable that will store the right bound during traversal
		while(first<last){
			while(arr[first]<=arr[pivot] && first<end) //skip all the elements starting at the beginning that are smaller than or equal to the pivot element
				first++;
			while(arr[last]>arr[pivot] )  //skip all the elements starting at the end that are greater than pivot element
				last--;
			if(first<last){
				swap(arr, first ,last); //swap the elements that first and the last index because the at this point of time the element at last is smaller than pivot and the one at first is larger than pivot element
			}
		}
		swap(arr,pivot,last); // swap in order to send pivot to its position
		quicksort(arr,start,last-1); //call quicksort for the left side of pivot elemet
		quicksort(arr,last+1,end); //call quicksort for the right side of the pivot element.
		
	}
}
