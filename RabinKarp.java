/**
* Rabin Karp Algorithm for Pattern matching that uses hashing.
* Time Complexity: O(mn).
*
* @author Mayank
*/
import java.util.*;

class RabinKarp{
    public static void main(String args[]){
        String text="abcbcglx";
        String pattern="bcf";
        int m=text.length();
        int n=pattern.length();
        int hashOfPattern=calculateHash(pattern);
        //System.out.println("Hash of Pattern:"+hashOfPattern);
        for(int i=0;i<=(m-n);i++){
            int hs=calculateHash(text.substring(i,i+n));
            //System.out.println("Hash"+i+":"+hs);
            if(hs==hashOfPattern){
                if((text.substring(i,i+n)).compareTo(pattern)==0)
                    i++;
                    System.out.println("Found at Position:"+i);
                    return;
            }
        }
        System.out.println("Pattern Not Found!");
    }
    public static int calculateHash(String s){
        char[] ch= s.toCharArray();
        int prime=29;
        int hash=0;
        for(int i=0;i<ch.length;i++){
            hash+=ch[i]*Math.pow(prime, i);
        }
        return hash;
    }
}
