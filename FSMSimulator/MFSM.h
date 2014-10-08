#ifndef MFSM_H
#define MFSM_H

#include <string>
#include <vector>
#include "common.h"
#include <thread>
#include "FSM.h"

class FSM;

class MFSM{
private:
	std::string mfsm_name;
	Variables_HASHMAP_FSM shared_variables;
	std::vector<FSM*> fsm_machines;
	std::ostream& os;						// STDOUT FOR PRINTING THE EVENTS
	std::istream& is;						// STDIN FOR GETTING INPUT FROM USER

public:
	MFSM(std::string &mfsm_name,std::ostream& o,std::istream& i);
	bool is_variable_available(std::string& var);
	void execute();
	void add_variable(std::string& var);
	void add_fsm(FSM *fsm);

	VAR_PTR_FSM get_element_ptr(std::string &var);

	//long *get_variable_pointer(std::string& var);

};

class FSM;

#endif 