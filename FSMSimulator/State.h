#ifndef STATE_H
#define STATE_H

#include <thread>         // std::this_thread::sleep_for
#include <chrono>		  // ie std::chrono::seconds(1)


#include "common.h"
#include "Commands.h"

class FSM;
class Commands;

class State {

private:

	bool is_state_ending_fsm;
	std::string state_name;
	std::vector<std::string> strings_data;				// holds strings of the current state
	std::vector<std::string> fsm_list;					// holds fsm strings to be executed on that state
	std::vector<Commands*> *instructions;				// vector of pointers to the opcodes of the instructions
	std::vector<VAR_PTR_FSM> variables_table;				// vector of pointers to the SYMBOL TABLE elements present in the fsm
	FSM *fsm;

public:

	State(std::string st_name,FSM* _fsm);
	std::string get_state_name();
	std::string &use_string_symbol(unsigned long long symbol);	// return strings_data[n]
	std::string &get_fsm_name(int n);							// return fsm_list[n]
	void setCommands(std::vector<Commands*>* inst);				// set inst pointer to actual instructions allocated for the current state
	void set_variable_value(unsigned long long symbol,long var);
	size_t add_string_symbol(std::string& temp);
	size_t use_variable(std::string &t_string);
	size_t use_fsm(std::string &t_string);
	int execute_single_instruction(unsigned int n_instruction);
	int execute_state();										// execute whole instructions of that state
	long get_variable_value(unsigned long long symbol);
	std::string& State::get_fsm_name();
};

#endif