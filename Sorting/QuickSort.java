/**
*
*
* @author Mayank
*
*/
import java.util.*;

public class QuickSort {
    public static void main(String args[]){
        int arr[]={11,19,0,-1,5,6,16,-3,6,0,14,18,7,21,18,-6,-8};
        quickSort(arr,0,arr.length-1);
        for(int i:arr)
            System.out.print(i+" ");
    }
    public static void swap(int[] arr, int i, int j){
        int temp=arr[i];
        arr[i]=arr[j];
        arr[j]=temp;
    }
    public static void quickSort(int []arr, int start, int end){
        if(start<end){
            int p=partition(arr,start, end);
            quickSort(arr,start,p-1);
            quickSort(arr,p+1,end);
        }
        
    }
    public static int partition(int[] arr,int start, int end){
        int p=start;
        int i=start+1;
        int j=end;
        while(i<=j){
            if(arr[i]<=arr[p]){
                i++;
                continue;
            }
            if(arr[j]>arr[p]){
                j--;
                continue;
            }
            swap(arr,i,j);
            i++;j--;
        }
        if(arr[p]>arr[j]){
            swap(arr,j,p);
            return j;
        }
        return p;
    }
}
