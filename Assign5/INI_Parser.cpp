#include<stdio.h>
#include<string.h>
#include "INI_Parser.h"

int INI_Parser :: read_from_config(char* config_line) {
	char prm_name[30];
	int val;
    	sscanf(config_line, "%s %d\n", prm_name, &val);
    	return val;
}

void INI_Parser :: parse_config_file(char* config_filename) {
  	char buf[100];
   	if ((fp=fopen(config_filename, "r")) == NULL) {
  	     	fprintf(stderr, "Failed to open config file %s", config_filename);
        	return;
   	 }
	char sec[30]="NA";
   	while(! feof(fp)) {
      		fgets(buf, 100, fp);
        	if (buf[0] == '#' || strlen(buf) < 4) {
            		continue;
        	}
		else if (buf[0]!='['){
			int i=1;
			while(buf[0]=']'){
				sec[i-1]=buf[i];
			}	
		}
  	 	else if (strstr(buf, "BUFFER_SIZE ")) {
			strcpy(config_parameter[current_entries].section,sec);
			strcpy(config_parameter[current_entries].key,"BUFFER_SIZE");
       		     	config_parameter[current_entries].value = read_from_config(buf);
			current_entries++;
       		 }
  	 	 else if (strstr(buf, "IP_GENERATION_INTERVAL ")) {
                        strcpy(config_parameter[current_entries].section,sec);
                        strcpy(config_parameter[current_entries].key,"IP_GENERATION_INTERVAL");
       		     	config_parameter[current_entries].value = read_from_config(buf);
			current_entries++;
       		 }
       		 else if (strstr(buf, "NUMBER_OF_IP ")) {
                        strcpy(config_parameter[current_entries].section,sec);
                        strcpy(config_parameter[current_entries].key,"NUMBER_OF_IP");
                        config_parameter[current_entries].value = read_from_config(buf);
			current_entries++;
       		 }
        	else if (strstr(buf, "IP_TYPES ")) {
                        strcpy(config_parameter[current_entries].section,sec);
                        strcpy(config_parameter[current_entries].key,"IP_TYPES");
                        config_parameter[current_entries].value = read_from_config(buf);
			current_entries++;
       		 }
       		 else if (strstr(buf, "PRINT_INTERVAL ")){
                        strcpy(config_parameter[current_entries].section,sec);
                        strcpy(config_parameter[current_entries].key,"PRINT_INTERVAL");
                        config_parameter[current_entries].value = read_from_config(buf);
			current_entries++; 
	       	}
        	else if (strstr(buf, "CLEANUP_TIME_OUT ")){
                        strcpy(config_parameter[current_entries].section,sec);
                        strcpy(config_parameter[current_entries].key,"CLEANUP_TIME_OUT");
                        config_parameter[current_entries].value = read_from_config(buf);
			current_entries++;
        	}
        	else if (strstr(buf, "SUBNET_MASK ")){
                        strcpy(config_parameter[current_entries].section,sec);
                        strcpy(config_parameter[current_entries].key,"SUBNET_MASK");
                        config_parameter[current_entries].value = read_from_config(buf);
			current_entries++;
        	}
        	else if (strstr(buf, "NO_OF_ITERATIONS ")){
                        strcpy(config_parameter[current_entries].section,sec);
                        strcpy(config_parameter[current_entries].key,"NO_OF_ITERATIONS");
                        config_parameter[current_entries].value = read_from_config(buf);
			current_entries++;
        	}
    	}
    	return;
}
