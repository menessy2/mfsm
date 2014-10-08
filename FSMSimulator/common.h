

#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <hash_map>
#include <sstream>

typedef stdext::hash_map<std::string, long> Variables_HASHMAP;		// USED IN FSM CLASS TO HOLD THE SYMBOL TABLE
typedef stdext::hash_map<std::string, std::pair<long,bool>> Variables_HASHMAP_FSM;
typedef Variables_HASHMAP::iterator VAR_PTR;						// USED IN State CLASS TO HOLD A PTR TO ELEMENTS IN THE SYMBOL TABLE
typedef Variables_HASHMAP_FSM::iterator VAR_PTR_FSM;


class EXCEPTION {
public:
	EXCEPTION (char *e){
		std::cout << "Exception: " << e << std::endl;
		exit(1);
	}
};


void get_first_occurence(std::string &command,int& first);

void get_last_occurence(std::string &command,int& last);

bool is_digits(const std::string &str);

int return_int(std::string str);

std::string return_string(std::string &str);

#endif 