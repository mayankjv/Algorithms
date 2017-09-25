/**
* Given an even number ( greater than 2 ),
* return two prime numbers whose sum will be equal to given number.
* NOTE A solution will always exist.
* Example:
* Input : 4
* Output: 2 + 2 = 4
*/
import java.util.*;
public class PrimeSum {
    public static ArrayList<Integer> primesum(int a) {
        ArrayList<Integer> res= new ArrayList<Integer>();
        for(int i=2;i<a-1;i++)
        {
            if(isPrime(i)==1){
                if(isPrime(a-i)==1){
                    res.add(i);
                    res.add(a-i);
                    return res;
                }
            }
        }
        return res;
    }
    static int isPrime(int a){
        if(a<=1)
            return 0;
        for(int i=2;i<=(int)Math.sqrt(a);i++){
            if(a%i==0)
                return 0;
        }
        return 1;
    }
    public static void main(String args[]){
        ArrayList<Integer> result= new ArrayList<Integer>();
        result=primesum(8);
        for(int i=0;i<result.size();i++)
            System.out.print(result.get(i)+" ");
    }
}
