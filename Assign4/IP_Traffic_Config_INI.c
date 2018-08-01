#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>


#define MAX_CONFIG_VARIABLE_LEN 25
#define CONFIG_LINE_buffer_len 100


static int cnt=0; //variable that maintains the count of unique IP addresses generated so far
static int current=0; //variable that is used to know which idx of the buffer pool is to be used as the new node
static int idx=0;//idx upto which elements are stored in the free_pool



int ip_unprocessed=0;
int buffer_len=10000,ip_interval=1,no_of_ip=10000,ip_type=2,print_interval=5,cleanup_timeout=3,subnet=16,no_of_iterations=1;
int *free_pool; // an array that will store the indices of the buffer pool that are cleaned up.
pthread_mutex_t lock,lock_print,lock_clean;


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
//	struct ip random;
//    srand(time(NULL));
	random.s.subnet1=(rand()%255);
	random.s.subnet2=(rand()%255);
	random.h.host1=(rand()%255);
	random.h.host2=(rand()%255);
/*	if(random.h.host1==40){
		random.h.host2=(rand()%15);
	}
	else
		random.h.host2=(rand()%255);*/
	//cnt++;
	return random;
}



//this function accepts ip addresses and inserts them in the lookuo table
void insert_ip(struct node lookup_table[], struct node buffer[],struct ip new_ip){
	if(current>=buffer_len){
		if(idx<=0){
			//printf("\nCannot be allocated!!\n");
			ip_unprocessed++;
			return;
		}
		else{
				//pthread_mutex_lock(&lock);
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
        		buffer[free_pool[idx-1]].add.host1= new_ip.h.host1;
        		buffer[free_pool[idx-1]].add.host2= new_ip.h.host2;
        		buffer[free_pool[idx-1]].count=1;
        		buffer[free_pool[idx-1]].add1.subnet1=new_ip.s.subnet1;
        		buffer[free_pool[idx-1]].add1.subnet2=new_ip.s.subnet2;
        		new->next=&buffer[free_pool[idx-1]];
        		new->prev=pre;
        		buffer[free_pool[idx-1]].next=NULL;    
        		buffer[free_pool[idx-1]].last_active=time(NULL);
			buffer[free_pool[idx-1]].added=time(NULL);
			//pthread_mutex_unlock(&lock);
			idx--;
			//printf("\ninserted from free_pool!\n Current free_pool size: %d",idx);		
		}
		return ;
	}
	//pthread_mutex_lock(&lock);
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
	//pthread_mutex_unlock(&lock);
	//printf("\n Inserted\n");
}





void *display(void *arg){
    FILE *fp;
    char file_name[50];
	while(1){
        sprintf(file_name,"ip_dump_%u.csv",(unsigned)time(NULL));  //(unsigned long)time(NULL)
        fp=fopen(file_name,"w+");
        fprintf(fp,"IP, count, Last Active\n");	
		struct node *buffer= (struct node*)arg;
        //pthread_mutex_lock(&lock_print);
		for(int i =0;i<current;i++){
			if(buffer[i].count==0)
				continue;
            fprintf(fp,"%d.%d.%d.%d, %d, %d\n",buffer[i].add1.subnet1,buffer[i].add1.subnet2,buffer[i].add.host1,buffer[i].add.host2,buffer[i].count,(int)buffer[i].last_active);
			printf("%d.%d.%d.%d has used %d packets\n",buffer[i].add1.subnet1,buffer[i].add1.subnet2,buffer[i].add.host1,buffer[i].add.host2,buffer[i].count);
		}
        fclose(fp);
		//pthread_mutex_unlock(&lock_print);
		sleep(print_interval);
	}
	
}



void* cleanup(void *arg){
	printf("Cleanup Thread Active Now !!\n");
	while(1){
	//	printf("Cleaning\n");
		if(idx>=buffer_len){
			//printf("Free_pool Full!!!\n");
			//pthread_mutex_unlock(&lock);
			continue;
		}
		struct node *buffer= (struct node*)arg;
		for(int i=0;i<current;i++){
	        //if(pthread_mutex_trylock(&lock_clean)==0){
    	        if((int)difftime(time(NULL),buffer[i].last_active)>=cleanup_timeout){
    	        		printf("%d.%d.%d.%d Deleted !",buffer[i].add1.subnet1,buffer[i].add1.subnet2,buffer[i].add.host1,buffer[i].add.host2);
        	            buffer[i].add.host1= -1;
            	        buffer[i].add.host2= -1;
                	    buffer[i].count=0;
                    	buffer[i].add1.subnet1=-1;
                    	buffer[i].add1.subnet2=-1;
                    	if(buffer[i].prev!=NULL)
	                        buffer[i].prev->next=buffer[i].next;
    	                if(buffer[i].next!=NULL)
        	                buffer[i].next->prev=buffer[i].prev;
            	        free_pool[idx++]=i;
                	    if(idx>=buffer_len){
                    	    //pthread_mutex_unlock(&lock);
                        	break;
	                    }
    	        }
    	    	//pthread_mutex_unlock(&lock_clean);
        //	}
//			printf("\n Node at idx %d in the Buffer pool free       Life=%d\n",current,(int)difftime(time(NULL),buffer[i].added));
    	}
	}
	//sleep(1);
}
int ch=0;
int ch1=0;

struct ip same_subnet(struct ip random){
	if(ch1==0){
		random.h.host1=(rand()%255);
		random.h.host2=(rand()%255);
		ch1=1;
		return random;
	}
	random.h.host2++;
	return random;
	
}
struct ip seq_ip(struct ip seq){
    if(ch==0){
        seq.s.subnet1=0;
        seq.s.subnet2=0;
        seq.h.host1=0;
        seq.h.host2=0;
        ch=1;
        return seq;
    }
    seq.h.host2++;
    if(seq.h.host2==256){
        seq.h.host1++;
        seq.h.host2=0;
    }
    return seq;
}

int power(int num){
	int res=1;
	for(int i=0;i<num;i++)
		res=res*2;
	return res;
}

int read_from_config(char* config_line) {
    char prm_name[MAX_CONFIG_VARIABLE_LEN];
    int val;
    sscanf(config_line, "%s %d\n", prm_name, &val);
    return val;
}



void read_config_file(char* config_filename) {
    FILE *fp;
    char buf[CONFIG_LINE_buffer_len];

    if ((fp=fopen(config_filename, "r")) == NULL) {
        fprintf(stderr, "Failed to open config file %s", config_filename);
        exit(EXIT_FAILURE);
    }
    while(! feof(fp)) {
        fgets(buf, CONFIG_LINE_buffer_len, fp);
        if (buf[0] == '#' || strlen(buf) < 4) {
            continue;
        }
        if (strstr(buf, "BUFFER_SIZE ")) {
            buffer_len = read_from_config(buf);
        }
        if (strstr(buf, "IP_GENERATION_INTERVAL ")) {
            ip_interval = read_from_config(buf);
        }
        if (strstr(buf, "NUMBER_OF_IP ")) {
            no_of_ip = read_from_config(buf);
        }
        if (strstr(buf, "IP_TYPES ")) {
            ip_type = read_from_config(buf);
        }
        if(strstr(buf, "PRINT_INTERVAL ")){
            print_interval = read_from_config(buf);
        }
        if(strstr(buf, "CLEANUP_TIME_OUT ")){
            cleanup_timeout = read_from_config(buf);
        }
        if(strstr(buf, "SUBNET_MASK ")){
        	subnet = read_from_config(buf);
        }
        if(strstr(buf, "NO_OF_ITERATIONS ")){
        	no_of_iterations = read_from_config(buf);
        }
    }
    fclose(fp);
    return;
    //printf("Cleanup Time= %d\n",cleanup_timeout);
}




int main(int argc, char *argv[]){
	struct ip temp;
	int arr[buffer_len];
	free_pool=arr;
	struct node buffer[buffer_len];
	printf("cleanup_timeout\n");
	read_config_file(argv[1]);
//	srand(time(0));
//	printf("Enter the number of bits in Subnet: ");
//	scanf("%d",&subnet);
//	printf("Buffer Size:");
//	scanf("%d",&buffer_len);
//	printf("\nInsert IP interval:");
//	scanf("%d",&insert_interval);
//	printf("\nNumber of IPs to be inserted:");
//	scanf("%d",&n);
//	printf("\n1. Same Subnet, Different Hosts\n2.Random IPs\nEnter Choice: ");
//	scanf("%d",&choice);
//	printf("Enter Print Interval: ");
//	scanf("%d",&print_interval);
    struct node lookup_table[(power(subnet))];
	pthread_t pth,clean;
	pthread_create(&clean,NULL,cleanup,(void *)buffer);
	pthread_create(&pth,NULL,display,(void *)buffer);
	int i=0;
	while(i<no_of_iterations){
		switch(ip_type){
			case 1:
	//				printf("FIRST!\n");
					temp.s.subnet1=0;
					temp.s.subnet2=0;
           		 	for(int i=0;i<no_of_ip;i++){
                		temp=same_subnet(temp);
                		insert_ip(lookup_table,buffer,temp);
            		}
            		printf("\nSwitch %d",i);
                	break;
			case 2:
//					printf("SECOND!\n");
            		for(int i=0;i<no_of_ip;i++){
                		temp=generate_ip(temp);
                		insert_ip(lookup_table,buffer,temp);
		            }
					break;
        	case 3:
            		for(int i=0;i<no_of_ip;i++){
                		temp=seq_ip(temp);
                		insert_ip(lookup_table,buffer,temp);
            		}
            		break;
		}
		printf("\nIteration %d now %d sleep",i,ip_interval);
		sleep(ip_interval);
		i++;
//		printf("inserting\n");
	}
}

