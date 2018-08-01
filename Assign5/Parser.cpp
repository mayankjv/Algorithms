//INI PARSER
#include<stdio.h>
#include<string.h>
#include "PARSER.h"
#include "JsonParser.h"
#include "INI_Parser.h"


int PARSER :: get_int_value(char* param_name){
	//printf("%s\n",param_name);
	for(int i=0;config_parameter[i].value!=-1;i++){
			if(strcmp(config_parameter[i].key,param_name)==0)
				return config_parameter[i].value;			
	}
	return -1;
}		
/*
void PARSER :: show(){
	for(int i=0;i<current_entries;i++){
		printf("%d\n",config_parameter[i].key);	
	}	
}
*/
/*
void PARSER :: parse_config_file(char* config_filename){
	if(config_filename[strlen(config_filename)-1]=='i' || config_filename[strlen(config_filename)-1]=='I'){
		INI_Parser parse= new INI_Parser();
		parse_config_file(config_filename);
	}
	else if(config_filename[strlen(config_filename)-1]=='n' || config_filename[strlen(config_filename)-1]=='N'){
		JsonParser parse= new JsonParser();
		parse_config_file(config_filename);	
	}
	else{
		return;
	}
}
*/

PARSER* Factory :: getParser(char* file_name){
	//if(file_name[(int)strlen(file_name)-1]=='i' || file_name[(int)strlen(file_name)-1]=='I'){
		return new INI_Parser;		
//	}
/*	else if(file_name[strlen(file_name)-1]=='n' || file_name[strlen(file_name)-1]=='N'){
		return new JsonParser;		
	}
*/
//	return NULL;
}
