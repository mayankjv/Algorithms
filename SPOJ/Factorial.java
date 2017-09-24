/*
* In order to find Trailing zeros, all we need to find is powers of 2s and 5s as their multiplication results in a trailing zero
* Since the number of 5s will be less than the number of 2s, there the number or trailing zeros will be equal 
* to the number of 5s (Pay attention to the fact that 25 produces 2 5s, 125 produces 3 5s and so on).
*/
/**
*
* @author Mayank
*/
import java.util.*;
import java.io.*;

public class Factorial {
    public static void main(String args[]){
        Scanner sc= new Scanner(System.in);
        int num;
        for(int t=sc.nextInt();t>0;t--){
            num=sc.nextInt();
            int count=0;
            for(int i=5;num/i>=1;i*=5)
                count+=num/i;
            System.out.println(count);
        }
    }
}
