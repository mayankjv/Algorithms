/*this program finds the nth largest number from a given array of numbers
the algorithm used for the same is a slight optimisation of heap sort */

//I am making an asumption that all the elements of the array are unique
#include<stdio.h>
#include<stdlib.h>

//function declarations
void Heapify(int a[],int size, int curr); 
void swap(int arr[], int idx1, int idx2);
void buildMinHeap(int arr[],int size);
int nthlargest(int arr[],int size,int n);

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
int main(){
    int size,n;
    printf("Enter the size of the array:");
    scanf("%d",&size);
    int *arr= (int*)malloc(size*sizeof(int));  //dynamic memory allocation to the array
    printf("Enter the elements of the array:");
    //Taking input
    for(int i=0;i<size;i++)
        scanf("%d",&arr[i]);
    printf("Enter the values of N:");
    scanf("%d",&n);
    printf("The required number is: %d\n",nthLargest(arr,size,n));

}
