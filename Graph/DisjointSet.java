/**
*
*
* @author Mayank
*/
import java.util.*;

public class DisjointSet{
    HashMap<Integer,Node> map = new HashMap<Integer,Node>();
    class Node{
        int id;
        Node parent;
        int rank;
        Node(int id){
            this.id=id;
        }
    }
    public void makeSet(int id){
        Node node= new Node(id);
        node.parent=node;
        node.rank=1;
        map.put(id, node);
    }
    public boolean union(int src, int dest){
        Node parent1=findSet(src);
        Node parent2=findSet(dest);
        if(parent1.id==parent2.id)
            return false;
        if(parent1.rank>=parent2.rank){
            parent1.rank=(parent1.rank==parent2.rank)?(parent1.rank+1):parent1.rank;
            parent2.parent=parent1;
        }
        else
            parent1.parent= parent2;
        return true;
    }
    public Node findSet(int id){
        return findSet(map.get(id));
    }
    public Node findSet(Node node){
        if(node.parent==node)
            return node.parent;
        node.parent=findSet(node.parent);
        return node.parent;
    }
    public static void main(String args[]){
        DisjointSet ds = new DisjointSet();
        ds.makeSet(1);
        ds.makeSet(2);
        ds.makeSet(3);
        ds.makeSet(4);
        ds.makeSet(5);
        ds.makeSet(6);
        ds.makeSet(7);

        ds.union(1, 2);
        ds.union(2, 3);
        ds.union(4, 5);
        //ds.union(6, 7);
        ds.union(5, 6);
       // ds.union(3, 7);

        System.out.println(ds.findSet(1).id);
        System.out.println(ds.findSet(2).id);
        System.out.println(ds.findSet(3).id);
        System.out.println(ds.findSet(4).id);
        System.out.println(ds.findSet(5).id);
        System.out.println(ds.findSet(6).id);
        System.out.println(ds.findSet(7).id);
    }

}
