import java.util.*;
import java.lang.*;
import java.io.*;
 
class KruskalMST{
    static class Edge implements Comparable<Edge>{
        int src, dest, weight;
        public int compareTo(Edge compareEdge){
            return this.weight-compareEdge.weight;
        }
        Edge(int src, int dest, int weight){
            this.src=src;
            this.dest=dest;
            this.weight=weight;
        }
        Edge(){
        }
    };
    
    class DisjointSet{
        int parent, rank;
        DisjointSet(int i){
            parent=i;
            rank=0;
        }
    };
    int V, E;    
    static Edge edge[];
    KruskalMST(int v, int e){
        V = v;
        E = e;
        edge = new Edge[E];
        for (int i=0; i<e; ++i)
            edge[i] = new Edge();
    }
    int findSet(DisjointSet DisjointSets[], int i){
        if (DisjointSets[i].parent != i)
            DisjointSets[i].parent = findSet(DisjointSets, DisjointSets[i].parent);
 
        return DisjointSets[i].parent;
    }
    void Union(DisjointSet DisjointSets[], int val1, int val2){
        int root1 = findSet(DisjointSets, val1);
        int root2 = findSet(DisjointSets, val2);
        if (DisjointSets[root1].rank < DisjointSets[root2].rank)
            DisjointSets[root2].parent = root2;
        else if (DisjointSets[root1].rank > DisjointSets[root2].rank)
            DisjointSets[root2].parent = root1;
        else{
            DisjointSets[root2].parent = root1;
            DisjointSets[root1].rank++;
        }
    }
    void KruskalMST(){
        Edge result[] = new Edge[V];
        int e = 0;
        int i = 0;
        for (i=0; i<V; ++i)
            result[i] = new Edge();
        Arrays.sort(edge);
        DisjointSet DisjointSets[] = new DisjointSet[V];
        for(i=0; i<V; ++i)
            DisjointSets[i]=new DisjointSet(i);
        i = 0;
        while (e < V - 1){
            Edge next_edge = new Edge();
            next_edge = edge[i++];
            int x = findSet(DisjointSets, next_edge.src);
            int y = findSet(DisjointSets, next_edge.dest);
            if (x != y){
                result[e++] = next_edge;
                Union(DisjointSets, x, y);
            }
        }
        System.out.println("Following are the edges in the constructed MST");
        for (i = 0; i < e; ++i)
            System.out.println(result[i].src+" --> "+result[i].dest+" Weight: "+
                               result[i].weight);
    }
    public static void main (String[] args){
        int V = 4;  // Number of vertices in graph
        int E = 5;  // Number of edges in graph
        int src[]={0,1,2,3,3};
        int dest[]={1,2,3,0,1};
        int weight[]={1,1,1,3,5};
        KruskalMST graph = new KruskalMST(V, E);
        for(int i=0;i<E;i++)
            graph.edge[i]=new Edge(src[i],dest[i],weight[i]);
        graph.KruskalMST();
    }
}