#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


static int cnt=0; //variable that maintains the count of unique IP addresses generated so far
static int current=0; //variable that is used to know which index of the buffer pool is to be used as the new node

//structure to store the host part of the ip address
struct host{
	int host1;
	int host2;
};

//structure to store the subnet part of the ip
struct subnet{
	int subnet1;
	int subnet2;
};

//structure that stores the complete IP address(both subnet as well as host parts)
struct ip{
	struct subnet s;
	struct host h;
};


//nodes of linked list that will contain host address, count of packets used by that particular ip, last activity time of the ip and the pointer to the next node
struct node{
	struct host add;
	struct subnet add1;
	int count;
	time_t last_active;
	struct node* next;
};






//a function that generates random ip addresses,
//this function first selects a random subnet and generates 10000 hosts corresponding the subnet and then generates another random subnet 
// and generates another 10000 hosts coresponding the same and so on.
struct ip generate_ip(struct ip random){
	if(cnt==10000 || cnt==0){
		random.s.subnet1=(rand()%255);
		random.s.subnet2=(rand()%255);
		cnt=0;
	}
	random.h.host1=(rand()%40);
	if(random.h.host1==40){
		random.h.host2=(rand()%15);
	}
	else
		random.h.host2=(rand()%255);
	cnt++;
	return random;
}

//this function accepts ip addresses and inserts them in the lookuo table
void insert_ip(struct node lookup_table[], struct node buffer[],struct ip new_ip){
	struct node* new= &lookup_table[(new_ip.s.subnet1*256+new_ip.s.subnet2+1)];
	while(new->next!=NULL){
		if(new->add.host1==new_ip.h.host1 && new->add.host2==new_ip.h.host2){
			(new->count)++;
			return;
		}
		new= new->next;
	}
	buffer[current].add.host1= new_ip.h.host1;
	buffer[current].add.host2= new_ip.h.host2;
	buffer[current].count=1;
	buffer[current].add1.subnet1=new_ip.s.subnet1;
	buffer[current].add1.subnet2=new_ip.s.subnet2;
	new->next=&buffer[current];
	buffer[current++].next=NULL;	
}
void display(struct node lookup_table[], struct node buffer[]){
/*	struct node* curr;
	for(int i=0;i<65536;i++){
		curr= &lookup_table[i];
		if(curr->next==NULL)
			continue;
		struct subnet s;
		s.subnet2=i%256;
		s.subnet1=i/256;
		while(curr!=NULL){
			printf("%d.%d.%d.%d\n",s.subnet1,s.subnet2,curr->add.host1,curr->add.host2);
			curr= curr->next;
		}
	}
*/
	for(int i =0;i<current;i++){
			printf("%d.%d.%d.%d has used %d packets\n",buffer[i].add1.subnet1,buffer[i].add1.subnet2,buffer[i].add.host1,buffer[i].add.host2,buffer[i].count);
	}
}
int main(){
	struct node lookup_table[65536];
	struct node buffer[10000];
	struct ip temp;
	for(int i=0;i<10000;i++){
		temp = generate_ip(temp);
		insert_ip(lookup_table,buffer,temp);		
	}
	display(lookup_table, buffer);
	return 0;
}
