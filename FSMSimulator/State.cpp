
#include "State.h"
// Little Endian


State::State(std::string st_name,FSM *_fsm) : state_name(st_name) , fsm(_fsm) {}

void State::setCommands(std::vector<Commands*>* inst) {
	instructions = inst;
} 


size_t State::add_string_symbol(std::string& temp){
		strings_data.push_back(temp);
		return strings_data.size() - 1;
	}

std::string& State::use_string_symbol(unsigned long long symbol) {
		return strings_data[symbol];
}

long State::get_variable_value(unsigned long long symbol) {
	return variables_table[symbol]->second.first;
}


void State::set_variable_value(unsigned long long symbol,long var){
	variables_table[symbol]->second.first = var;
}


size_t State::use_variable(std::string &t_string){

		std::vector<VAR_PTR_FSM>::iterator it;
		size_t counter = 0;
		for(it=variables_table.begin();it!=variables_table.end();it++){
			if ( (*it)->first == t_string )
				return counter;
			counter++;
		}
		
		bool is_written = false;
		
		for(VAR_PTR_FSM i=fsm->get_variables_begin();i!=fsm->get_variables_end();++i){
			if ( i->first == t_string ){
				if ( i->second.second )
					variables_table.push_back(fsm->mfsm->get_element_ptr(t_string));
				else
					variables_table.push_back(i);

				is_written = true;
				break;
			}
		}
		
		if ( ! is_written )
			throw EXCEPTION("Variable introduced not present in FSM");
		return variables_table.size() - 1;

}

int State::execute_single_instruction(unsigned int n_instruction){
		return (*instructions)[n_instruction]->execute();
	}

int State::execute_state(){
		for(unsigned int i=0;i<instructions->size();i++){
			int result_state = execute_single_instruction(i);
			if ( result_state == 1 ){
				return 1;						// 1 stands for END STATE
			} else if ( result_state == 2 )
				break;							// 2 stands for WAIT STATE
		}
		return 0;
	}


std::string State::get_state_name(){
	return state_name;
}


size_t State::use_fsm(std::string &t_string) {

	for(int i=0;i<fsm_list.size();i++){
		if ( fsm_list[i] == t_string )
			return i;
	}
	fsm_list.push_back(t_string);
	return fsm_list.size() - 1;
}


std::string& State::get_fsm_name(int n){
	return fsm_list[n];
}

std::string& State::get_fsm_name(){
	return fsm->get_fsm_name();
}

