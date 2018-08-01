#ifndef PARSER_INCLUDE
#define PARSER_INCLUDE



struct param{
	
	char section[30];
	char key[30];
	int value;
};


class PARSER{


	protected:
		struct param config_parameter[25];
		
	public:
		int get_int_value(char* param_name);
		virtual void parse_config_file(char* config_filename)=0;
//		int read_from_config(char* config_line);
//		void close();

};

class Factory{

	public:
		PARSER *getParser(char* file_name);

};
#endif
