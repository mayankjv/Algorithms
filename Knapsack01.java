
import java.util.*;
class Knapsack01{
    public static void main(String args[]){
        int[] value={22,20,5,30,24,54,31,32,18,25};
        int[] wt={4,2,3,5,5,6,9,7,8,10};
        int res= knapSack(value,wt,30);
        System.out.println(res);
    }
    public static int knapSack(int[] value, int[] wt, int maxWeight){
        int[][] dp= new int[value.length+1][maxWeight+1];
        for(int i=0;i<=value.length;i++){
            for(int j=0;j<=maxWeight;j++){
                if(i==0||j==0){
                        dp[i][j]=0;
                        continue;
                }
                else if(j<=wt[i-1]){
                    dp[i][j]=dp[i-1][j];
                    continue;
                }
                else{
                    dp[i][j]=Math.max(dp[i-1][j],value[i-1]+dp[i-1][j-wt[i-1]]);
                }
            }
        }
        return dp[value.length][maxWeight];
    }
}
