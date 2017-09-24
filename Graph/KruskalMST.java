/**
 * the implementation of DisjointSet can be found in another file in the same folder.
 *
 * @author Mayank
 */
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;

public class KruskalMST{
    public static void main(String args[]){
        Edge[] edges= new Edge[5];
        int noOfVertices=4;
        int[] src={1,2,1,4,1};
        int[] dest={2,3,4,3,3};
        int[] weight={1,4,3,2,10};
        for(int i=0;i<5;i++){
            edges[i]= new Edge(src[i],dest[i],weight[i]);
        }
        Arrays.sort(edges, new Comparator<Edge>(){
            @Override
            public int compare(Edge e1, Edge e2){
                return e1.weight-e2.weight;
            }
        });
        DisjointSet ds= new DisjointSet();
        for(int i=1;i<=noOfVertices;i++){
            ds.makeSet(i);
        }
        int k=0;
        Edge[] result= new Edge[noOfVertices-1];
        for(int i=0;i<5;i++){
            if(ds.findSet(edges[i].src).id!=ds.findSet(edges[i].dest).id){
                result[k++]=edges[i];
                ds.union(edges[i].src,edges[i].dest);
                if(k==result.length)
                    break;
            }
        }
        for(int i=0;i<result.length;i++){
            System.out.println(result[i].src+"-->"+result[i].dest+"="+result[i].weight);
        }
    }
}

class Edge{
    int src, dest, weight;
    Edge(int src,int dest, int weight){
        this.src= src;
        this.dest= dest;
        this.weight=weight;
    }
}
