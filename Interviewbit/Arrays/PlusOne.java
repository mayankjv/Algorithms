/*
* Given a non-negative number represented as an array of digits,
* add 1 to the number ( increment the number represented by the digits ).
* The digits are stored such that the most significant digit is at the head of the list.
* Example:
* If the vector has [1, 2, 3]
* the returned vector should be [1, 2, 4]
* as 123 + 1 = 124.
*
*/

/**
 *
 * @author Mayank
 */
import java.util.*;
public class PlusOne {
 public static ArrayList<Integer> plusOne(ArrayList<Integer> a) {
 
    int num;
    int carry=1;
    int n=a.size();
    for(int i=n-1;i>=0;i--){
        num=a.get(i);
        num+=carry;
        carry=0;
        
        if(num==10){
            num=0;
            carry=1;
        }
        a.set(i,num);
    }
    ArrayList<Integer> result= new ArrayList<Integer>();
    if(carry==1){
        result.add(1);
    }
    for(int A:a){
        if(A==0&&result.size()==0)
        continue;
        result.add(A);
    }
    return result;
 }
        public static void main(String args[]){
            ArrayList<Integer> al= new ArrayList<Integer>();
            al.add(9);
            al.add(9);
            al.add(9);
            ArrayList<Integer> result=plusOne(al);
            for(Integer i:result)
                System.out.print(i+" ");
        }
}
