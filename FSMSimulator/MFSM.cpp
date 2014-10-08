

#include "MFSM.h"


MFSM::MFSM(std::string &_mfsm_name,std::ostream& o,std::istream& i): mfsm_name(_mfsm_name) , os(o) , is(i) {}



bool MFSM::is_variable_available(std::string& var){
	return ( shared_variables.count(var) > 0 );
}

void MFSM::add_variable(std::string& var){
	shared_variables[var] = std::make_pair(0,true);
}


void MFSM::add_fsm(FSM *fsm){
	fsm_machines.push_back(fsm);
}

/*
long *MFSM::get_variable_pointer(std::string& var){
	return &shared_variables[var];
}
*/

void MFSM::execute(){

	os << "-----------------------------------------------\n";
	os << "------------Starting MFSM - " << mfsm_name << std::endl;

	for(int i=0;i<fsm_machines.size();i++){
		std::string result="",temp;
		os << "Enter transition inputs, seperated by spaces and ended with ';' , for " << 
			fsm_machines[i]->get_fsm_name() << " :" << std::endl;
		do{
			is >> temp;
			if ( temp == ";" )
				break;
			bool mybool = GeneralParser::has_char(temp,';');
			result += temp + " ";
			if ( mybool )
				break;
		} while ( true );
		fsm_machines[i]->flag_input_from_terminal(result);
	}
	os << "-----------------------------------------------\n";
	os << "-----------------[ START EXEC ]----------------\n";
	std::vector<std::thread> thread_pool;	
	for(int i=0;i<fsm_machines.size();i++){
		thread_pool.push_back(std::thread(  & FSM::execute , fsm_machines[i]  ));
		//fsm_machines[i]->execute();
	}
	
	
	for( auto& element : thread_pool ){
		element.join();
	}
	//system("cls");
	os << "-----------------------------------------------\n";
	os << "-----------------[ START EXEC ]----------------\n";
	for(int i=0;i<fsm_machines.size();i++){
		os << fsm_machines[i]->output() << std::endl;
	}
	os << "------------Ending MFSM - " << mfsm_name << std::endl; 
	os << "-----------------------------------------------\n";
}


VAR_PTR_FSM MFSM::get_element_ptr(std::string &var){
	for(VAR_PTR_FSM i=shared_variables.begin();i!=shared_variables.end();++i){
		if ( i->first == var )
			return i;
	}
}