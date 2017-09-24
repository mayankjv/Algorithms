/**
*
* @author Mayank
*/

import java.util.*;

class Problem1{
  public static void main(String args[]){
	  int[] numbers=new int[1000];
	  int num=0;
  	Scanner sc=new Scanner(System.in);
		for(int i=0;;i++){
			numbers[i]=sc.nextInt();
			if(numbers[i]==42){
				num=i;
				break;
			}
		}
		for(int i=0;i<num;i++){
			System.out.println(numbers[i]);
		}
  }
}
