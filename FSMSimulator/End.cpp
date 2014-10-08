

#include "Commands.h"

End::End(std::string &command,FSM *_fsm,State *_s,std::ostream& os,std::istream& is,std::ostringstream& os2,std::istringstream& is2,bool is_IO_string) : Commands(_fsm,_s,os,is,os2,is2,is_IO_string)  {
		encode(command);
	}

int End::execute() {
	std::string str_symb;
	unsigned long long inst = data & 0xFF;
	if( inst == END ){
		if ( is_IO_from_string )
			o_string << "State execution finished & FSM " << s->get_fsm_name() << " reached END\n";
		else{
			o_console << "State execution finished & FSM " << s->get_fsm_name() << " reached END\n";
			o_string << "State execution finished & FSM " << s->get_fsm_name() << " reached END\n";
		}
		return 1; 
	}
	else
		throw EXCEPTION("Invalid Function operand");	
}


void End::encode(std::string &command){
	if ( command.substr(0,3) != "end" )
		throw EXCEPTION("Unknown Instruction");

	data = END ;
}