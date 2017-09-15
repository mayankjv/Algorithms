/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Logan
 */
public class LongestCommonSubstring {
    public static void main(String args[]){
        String s1="bacdlgzxy";
        String s2="xzycdlpqr";
        longestCommon(s1,s2);
        
    }
    public static void longestCommon(String s1, String s2){
        int m=s1.length();
        int n=s2.length();
        int dp[][]= new int[m][n];
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(s1.charAt(i)==s2.charAt(j)){
                    if(i==0||j==0){
                        dp[i][j]=1;
                    }
                    else{
                        dp[i][j]=dp[i-1][j-1]+1;
                    }
                }
                else{
                    if(i==0||j==0){
                        if(i==0&&j==0)
                            dp[i][j]=0;
                        else if(i==0)
                            dp[i][j]=dp[i][j-1];
                        else
                            dp[i][j]=dp[i-1][j];
                    }
                    else{
                        dp[i][j]=Math.max(dp[i-1][j],dp[i][j-1]);
                    }
                }
            }
        }
        int i,j;
        String res="";
        for(i=m-1,j=n-1;i>0&&j>0;){
            int curr=dp[i][j];
            if(dp[i-1][j]==curr)
                i--;
            else if(dp[i][j-1]==curr)
                j--;
            else{
                res+=s1.charAt(i);
                i--;
                j--;
            }
        }
        for(i=res.length()-1;i>=0;i--)
            System.out.print(res.charAt(i));
    }
}
