class PalindromicPartition {
    public static int minCut(String A) {
        int n=A.length();
        int cut[]= new int[n];
        boolean isPal[][]= new boolean[n][n];
        for(int i=1;i<n;i++){
            int min=i;
            for(int j=0;j<=i;j++){
                if((A.charAt(i)==A.charAt(j))&&(i<=j+1||isPal[j+1][i-1])){
                    isPal[i][j]=true;
                    if(j<1)
                        min=Math.min(min,0);
                    else
                        min=Math.min(min,1+cut[j-1]);
                }
            }
            cut[i]=min;
        }
        return cut[n-1];
    }
    public static void main(String args[]){
        String s="aabbbc";
        System.out.println(minCut(s));
    }
}
