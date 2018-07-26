#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

static int cnt=0; //variable that maintains the count of unique IP addresses generated so far
static int current=0; //variable that is used to know which index of the buffer pool is to be used as the new node
static int index=0;//Index upto which elements are stored in the free_pool
pthread_mutex_t lock;

int free_pool[10000]; // an array that will store the indices of the buffer pool that are cleaned up.

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
	time_t added;
	struct node* next;
	struct node* prev;
};


//a function that generates random ip addresses,
//this function first selects a random subnet and generates 10000 hosts corresponding the subnet and then generates another random subnet 
// and generates another 10000 hosts coresponding the same and so on.
struct ip generate_ip(struct ip random){
	if(cnt==0){
		random.s.subnet1=(rand()%255);
		random.s.subnet2=(rand()%255);
	}
	random.h.host1=(rand()%255);
	random.h.host2=(rand()%255);
/*	if(random.h.host1==40){
		random.h.host2=(rand()%15);
	}
	else
		random.h.host2=(rand()%255);*/
	cnt++;
	return random;
}


//this function accepts ip addresses and inserts them in the lookuo table
void insert_ip(struct node lookup_table[], struct node buffer[],struct ip new_ip){
	if(current>=10000){
		if(index<=0){
			//printf("\nCannot be allocated!!\n");
			return;
		}
		else{
	        	struct node* new= &lookup_table[(new_ip.s.subnet1*256+new_ip.s.subnet2+1)];
        		struct node* pre=NULL;
        		while(new->next!=NULL){
               			if(new->add.host1==new_ip.h.host1 && new->add.host2==new_ip.h.host2){
                       			(new->count)++;
					new->last_active=time(NULL);
                       			return;
               			}
               			pre=new;
               			new= new->next;
        		}
        		buffer[free_pool[index-1]].add.host1= new_ip.h.host1;
        		buffer[free_pool[index-1]].add.host2= new_ip.h.host2;
        		buffer[free_pool[index-1]].count=1;
        		buffer[free_pool[index-1]].add1.subnet1=new_ip.s.subnet1;
        		buffer[free_pool[index-1]].add1.subnet2=new_ip.s.subnet2;
        		new->next=&buffer[free_pool[index-1]];
        		new->prev=pre;
        		buffer[free_pool[index-1]].next=NULL;    
        		buffer[free_pool[index-1]].last_active=time(NULL);
			buffer[free_pool[index-1]].added=time(NULL);
			index--;
		//	printf("\ninserted from free_pool!\n Current free_pool size: %d",index);		
		}
		return ;
	}
	struct node* new= &lookup_table[(new_ip.s.subnet1*256+new_ip.s.subnet2+1)];
	struct node* pre=NULL;
	while(new->next!=NULL){
		if(new->add.host1==new_ip.h.host1 && new->add.host2==new_ip.h.host2){
			(new->count)++;
			new->last_active= time(NULL);
			return;
		}
		pre=new;
		new= new->next;
	}
	buffer[current].add.host1= new_ip.h.host1;
	buffer[current].add.host2= new_ip.h.host2;
	buffer[current].count=1;
	buffer[current].add1.subnet1=new_ip.s.subnet1;
	buffer[current].add1.subnet2=new_ip.s.subnet2;
	new->next=&buffer[current];
	new->prev=pre;
	buffer[current].next=NULL;
	buffer[current].prev=new;	
	buffer[current].last_active=time(NULL);
	buffer[current++].added= time(NULL);
//	printf("\n Inserted\n");
}



void *display(void *arg){
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
	pthread_mutex_lock(&lock);
	while(1){	
		struct node *buffer= (struct node*)arg;
		for(int i =0;i<current;i++){
			if(buffer[i].count==0)
				continue;
			printf("%d.%d.%d.%d has used %d packets\n",buffer[i].add1.subnet1,buffer[i].add1.subnet2,buffer[i].add.host1,buffer[i].add.host2,buffer[i].count);
		}
	}
	pthread_mutex_unlock(&lock);
}


void* cleanup(void *arg){

pthread_mutex_lock(&lock);
while(1){
	if(index>=10000){
		//printf("Free_pool Full!!!\n");
		pthread_mutex_unlock(&lock);
		break; 
	}
	struct node *buffer= (struct node*)arg;
	for(int i=0;i<current;i++){
		if(difftime(time(NULL),buffer[i].last_active)>=1.0){
	        	buffer[i].add.host1= -1;
       			buffer[i].add.host2= -1;
       			buffer[i].count=0;
       			buffer[i].add1.subnet1=-1;
        		buffer[i].add1.subnet2=-1;
			if(buffer[i].prev!=NULL)
        			buffer[i].prev->next=buffer[i].next;
			if(buffer[i].next!=NULL)
				buffer[i].next->prev=buffer[i].prev;
        		free_pool[index++]=i;
			if(index>=10000){
				pthread_mutex_unlock(&lock);
				break;
			}
			
		//	printf("\n Node at index %d in the Buffer pool free       Life=%d\n",current,(int)difftime(time(NULL),buffer[i].added));
		}
	}
}
pthread_mutex_unlock(&lock);
}



int power(int num){
	int res=1;
	for(int i=0;i<num;i++)
		res=res*2;
	return res;
}

int main(){
	struct node buffer[10000];
	struct ip temp;
//	printf("Enter the number of bits in Subnet: ");
	int subnet=16;
//	scanf("%d",&subnet);
        struct node lookup_table[(power(subnet))];
	pthread_t pth,clean;
	pthread_create(&clean,NULL,cleanup,(void *)buffer);
	pthread_create(&pth,NULL,display,(void *)buffer);
	while(1){
		sleep(0.5);
		temp = generate_ip(temp);
		insert_ip(lookup_table,buffer,temp);	
//		cleanup((void *) buffer);	
	}
	return 0;
}
