/**
 *
 * @author Logan
 */
import java.util.*;

class MergeSort1 {
    public static void mergeSort(int[] arr){
        mergeS(arr, 0 , arr.length-1);
    }
    public static void mergeS(int[] arr, int start, int end){
        if(start<end){
            int mid=(start+end)/2;
            mergeS(arr,start,mid);
            mergeS(arr,mid+1,end);
            merge(arr,start,end,mid);
        }
    }
    public static void merge(int[] arr, int start, int end, int mid){
        int size1=mid-start+1;
        int size2=end-mid;
        int[] L= new int[size1];
        int[] R=new int[size2];
        int temp[]= new int[size1+size2];
        int i,j,k=0;
        for(i=0;i<size1;i++)
            L[i]=arr[start+i];
        for(i=0;i<size2;i++)
            R[i]=arr[mid+1+i];
        i=0;j=0;
        while(i<size1&&j<size2){
            if(L[i]<=R[j])
                temp[k++]=L[i++];
            else{
                temp[k++]=R[j++];
            }
        }
        while(i<size1)
            temp[k++]=L[i++];
        while(j<size2)
            temp[k++]=R[j++];
        for(i=0;i<temp.length;i++)
            arr[start+i]=temp[i];
    }
    public static void main(String args[]){
        int arr[]={2,7,9,4,1,-2,0,-37,24,863,342,64,64};
        mergeSort(arr);
        for(int i:arr)
                System.out.print(i+" ");
    }
}
