/**
*
*@author Mayank
*/
import java.util.*;

class ActivitySelection{
    static class Meeting{
        int start;
        int end;
        int id;
        Meeting(int start, int end,int id){
            this.start=start;
            this.end=end;
            this.id=id;
        }
    }
    public static void main(String args[]){
        Meeting[] meetings= new Meeting[8];
        int[] start={75250, 50074, 43659, 8931, 11273, 27545, 50879, 77924};
        int[] end={112960, 114515, 81825, 93424, 54316, 35533, 73383, 160252};
        for(int i=0;i<meetings.length;i++){
            meetings[i]= new Meeting(start[i],end[i],i+1);
        }
        Arrays.sort(meetings, new Comparator<Meeting>(){
            @Override
            public int compare(Meeting m1, Meeting m2){
                return m1.end-m2.end;
            }
        });
        int currentEndTime=meetings[0].end;
//        int noOfMeetings=1;
        ArrayList<Integer> result= new ArrayList<Integer>();
        result.add(meetings[0].id);
        for(int i=1;i<meetings.length;i++){
            if(meetings[i].start>=currentEndTime){
//                noOfMeetings++;
                result.add(meetings[i].id);
                currentEndTime=meetings[i].end;
            }
        }
        for(Integer in:result){
            System.out.print(in+" ");
        }
        
    }
}
