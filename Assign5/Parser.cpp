//INI PARSER
#include<stdio.h>
#include<string.h>
#include "PARSER.h"


int PARSER :: get_int_value(char* section_name ,char* param_name){
	for(int i=0;i<current_entries;i++){
		if(strcmp(config_parameter[i].section,section_name)==0){
			if(strcmp(config_parameter[i].key,param_name)==0)
				return config_parameter[i].value;			
		}		
	}
	return -1;
}		

void PARSER :: close(){
	fclose(fp);	
}

