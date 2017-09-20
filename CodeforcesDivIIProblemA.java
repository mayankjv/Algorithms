import java.util.*;
/*
 * This is one of the problems from Codeforces Round #435 (Div. 2)
 * 
 * the MEX of a set of integers is defined in the problem statement as 
 * the minimum non-negative integer that doesn't exist in it.
 * Given a set of integers and a number n.
 * We can add numbers to the set or remove numbers from the set in order to make the MEX of the given set n.
 * We have to return the minimum no. of such operations(addition/removal) required.
 * 
 */

/**
 *
 * @author Logan
 */
public class Mex {
    public static void main(String args[]){
        Scanner sc= new Scanner(System.in);
        int n= sc.nextInt();
        int num=sc.nextInt();
        HashSet<Integer> hs= new HashSet<Integer>();
        int arr[]= new int[n];
        for(int i=0;i<n;i++){
            arr[i]=sc.nextInt();
            hs.add(arr[i]);
        }
        int i=0;
        for(i=0;i<n;i++)
            if(!hs.contains(i))
                break;
        int mex=i;
        int count=0;
        //System.out.println("MEX: "+mex);
        if(mex<num){
            for(i=mex;i<num;i++)
                if(!hs.contains(i))
                    count++;
            if(hs.contains(num))
                count++;
        }
        if(mex>num){
            count=1;
                
        }
        System.out.println(count);
    }
}
