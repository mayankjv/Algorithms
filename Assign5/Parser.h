#ifndef PARSER_INCLUDE
#define PARSER_INCLUDE


struct param{
	
	char section[30];
	char key[30];
	int value;
};


class PARSER{

	private:
		struct param config_parameter[25];
		FILE *fp;
		
	public:
	
	int get_int_value(char* section_name ,char* param_name);
	virtual void parse_config_file(char* config_filename);
	//int read_from_config(char* config_line);
	void close();

};

#endif
