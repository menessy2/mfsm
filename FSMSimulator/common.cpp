

#include "common.h"



void get_first_occurence(std::string &command,int& first){
		while ( command[first++] == ' ' );
		--first;
	}

void get_last_occurence(std::string &command,int& last){
		last = command.length() - 1;
		while ( command[last--] == ' ' );
		++last;
	}

int return_int(std::string str){
	int start_index=0,last_index;
	get_first_occurence(str,start_index);
	get_last_occurence(str,last_index);
	return atoi(str.substr(start_index,(last_index-start_index)+1).c_str());
}

bool is_digits(const std::string &str) {
    return str.find_first_not_of("0123456789") != std::string::npos;
}

std::string return_string(std::string &str){
	std::string result;
	std::istringstream iss(str);
	iss >> result;
	return result;
}




