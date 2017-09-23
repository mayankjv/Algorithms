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
