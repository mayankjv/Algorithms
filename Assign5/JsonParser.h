#ifndef _JsonParser_h
#define _JsonParser_h

#include "Parser.h"

class JsonParser : public Parser
{
	public:
		int parse_config_file(struct pair*,char*);
	//	int convert_value_to_int(char*);
	//	int get_int_value(int,struct pair*,char*);
};
#endif
