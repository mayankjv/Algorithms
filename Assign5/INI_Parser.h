#ifndef INI_PARSER_INCLUDE
#define INI_PARSER_INCLUDE

#include "PARSER.h"

static int current_entries=0;

class INI_Parser : public PARSER{
	
	private:
		FILE *fp;
	public:
		int read_from_config(char* config_line);
		void parse_config_file(char* config_filename);

};

#endif
