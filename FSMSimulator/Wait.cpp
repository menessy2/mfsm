

#include "Wait.h"


Wait::Wait(std::string &command,FSM *_fsm,State *_s,std::ostream& os,std::istream& is,std::ostringstream& os2,std::istringstream& is2,bool is_IO_string) : Commands(_fsm,_s,os,is,os2,is2,is_IO_string)  {
		encode(command);
	}


int Wait::execute() {
	std::string str_symb;
	unsigned long long inst = data & 0xFF;
	if( inst == WAIT ){
		if ( is_IO_from_string )
			o_string << "State execution finished in FSM " << s->get_fsm_name() << std::endl;
		else {
			o_console << "State execution finished in FSM " << s->get_fsm_name() << std::endl;
			o_string << "State execution finished in FSM " << s->get_fsm_name() << std::endl;
		}
		return 2; 
	}
	else
		throw EXCEPTION("Invalid Function operand");	
}

void Wait::encode(std::string &command) {
	if ( command.substr(0,4) != "wait" )
		throw EXCEPTION("Unknown Instruction");

	data = WAIT ;
}