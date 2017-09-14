import java.util.*;

class FractionalKnapsack{
    static class Item{
        int val;
        int weight;
        float ratio;
        Item(int val, int weight){
            this.val=val;
            this.weight= weight;
            this.ratio=(float)val/(float)weight;
        }
    }
    public static void main(String args[]){
        Item[] items= new Item[4];
        int maxWeight=60;
        int[] values={280,100,120,120};
        int[] weights={40,10,20,24};
        for(int i=0;i<items.length;i++){
            items[i]= new Item(values[i],weights[i]);
        }
        Arrays.sort(items, new Comparator<Item>(){
            @Override
            public int compare(Item i1, Item i2){
                float f1=i1.ratio;
                float f2=i2.ratio;
                if(f1<f2)
                    return 1;
                else
                     return -1;
            }
        });
        int currentWeight=0;
        float maxProfit=0.0f;
        for(int j=0;j<items.length;j++){
            if(currentWeight+items[j].weight<=maxWeight){
                maxProfit+=items[j].val;
                currentWeight+=items[j].weight;
            }
            else{
                int weightToBeAdded=maxWeight-currentWeight;
                maxProfit+=(float)weightToBeAdded* items[j].ratio;
                break;
            }
        }
        maxProfit=(float)((Math.round(maxProfit)*100.0)/100.0);
        System.out.println(maxProfit);
    }
}