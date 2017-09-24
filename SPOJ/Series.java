/*
 * First line contains an integer T(the number of test cases),
 * Each test case consists of two lines,
 * The first line contains two space separarted integers N(Length of Sequence), C(Amount of numbers you are to find to compute the sequence)
 * You have to find the polynomial associated with each sequence and print the next C numbers of each sequence.
 */

/**
 *
 * @author Mayank
 */
import java.util.*;
public class Series {
    public static void main(String args[]){
        Scanner sc= new Scanner(System.in);
        int t= sc.nextInt();
        ArrayList<ArrayList<Integer>> result= new ArrayList<ArrayList<Integer>>();
        for(int i=0;i<t;i++){
            int n=sc.nextInt();
            int c=sc.nextInt();
            ArrayList<Integer> a= new ArrayList<Integer>();
            for(int j=0;j<n;j++){
                a.add(sc.nextInt());
            }
            ArrayList<ArrayList<Integer>> al= new ArrayList<ArrayList<Integer>>();
            ArrayList<Integer> temp= new ArrayList<Integer>();
            temp=a;
            al.add(a);
            while(!sameOrOne(temp)){
                ArrayList<Integer> av=new ArrayList<Integer>();
                for(int k=1;k<temp.size();k++){
                    av.add(temp.get(k)-temp.get(k-1));
                }
                temp=av;
                al.add(temp);
            }
            int last=al.size()-1;
            for(int j=0;j<c;j++){
                int num=al.get(last).get(0);
                al.get(last).add(num);
                for(int k=last-1;k>=0;k--){
                    int l=al.get(k).get(al.get(k).size()-1);
                    al.get(k).add(num+l);
                    num+=l;
                }
                        
            }
            ArrayList<Integer> res= new ArrayList<Integer>();
            for(int j=n;j<n+c;j++)
                res.add(al.get(0).get(j));
            result.add(res);
        }
        for(int i=0;i<result.size();i++){
            for(int j=0;j<result.get(i).size();j++)
                System.out.print(result.get(i).get(j)+" ");
            System.out.println("");
       }
    }
    public static boolean sameOrOne(ArrayList<Integer> al){
        if(al.size()==1)
                return true;
        int num=al.get(0);
        for(int i=1;i<al.size();i++)
            if(al.get(i)!=num)
                return false;
        return true;
    }
}
