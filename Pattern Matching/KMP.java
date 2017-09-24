/**
* The Knuth Morris Pratt algorithm for patterm searching.
* Time Complexity O(m+n), where m and n are the lengthhs of the Text and the Pattern.
*
* @author Mayank
*/
import java.util.*;

class KMP{
    public static void main(String args[]){
        String text="abcghidefghi";
        String pattern="ghi";
        int result[]=kmp(text.toCharArray(),pattern.toCharArray());
        if(result.length==0)
            System.out.println("Pattern Not Found!");
        else{
            System.out.println("Following occurances of the Pattern found:");
            for(int i=0;i<result.length;i++){
                int j=pattern.length()+result[i]-1;
                System.out.println("Starting at index "+result[i]+" and ending at index "+j);
            }          
        }
    }
    public static int[] kmp(char[] text, char[] pattern){
        int[] temp=calculateTemporaryArray(pattern);
        int i=0,j=0;
        ArrayList<Integer> res= new ArrayList<Integer>();
        while(i<text.length&&j<pattern.length){
            if(text[i]==pattern[j]){
                i++;
                j++;
                if(j==pattern.length){
                    res.add(i-pattern.length);
                    j=0;
                }
            }
            else{
                if(j!=0){
                    j=temp[j-1];
                }
                else
                    i++;
            }
        }
        int ret[]= new int[res.size()];
        i=0;
        for(Integer k:res)
            ret[i++]=k;
        return ret;
    }
    public static int[] calculateTemporaryArray(char[] pattern){
        int size=pattern.length;
        int[] res= new int[size];
        res[0]=0;
        int index=0;
        for(int i=1;i<size;i++){
            if(pattern[i]==pattern[index]){
                res[i]=index+1;
                index++;
            }
            else{
                if(index!=0){
                    index=res[index-1];
                }
                else
                    res[i]=index+1;
            }
        }
        return res;
    }
}
