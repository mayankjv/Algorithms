/**You are in an infinite 2D grid where you can move in any of the 8 directions :
*     (x,y) to 
*    (x+1, y), 
*    (x - 1, y), 
*    (x, y+1), 
*    (x, y-1), 
*    (x-1, y-1), 
*    (x+1,y+1), 
*    (x-1,y+1), 
*    (x+1,y-1) 
*You are given a sequence of points and the order in which you need to cover the points.
* Give the minimum number of steps in which you can achieve it. You start from the first point. 
*/
/**
 *
 * @author Mayank
 */
import java.util.*;

public class MinSteps {
    public static int coverPoints(int[] x, int[] y) {
        int steps=0;
        for(int i=1;i<x.length;i++){
            steps+=Math.max(Math.abs(x[i]-x[i-1]),Math.abs(y[i]-y[i-1]));
        }
        return steps;
    }
    public static void main(String args[]){
        int[] X={0,1,1};
        int[] Y={0,1,2};
        System.out.println(coverPoints(X,Y));
    }
}
