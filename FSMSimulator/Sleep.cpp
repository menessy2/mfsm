


#include "Sleep.h"


Sleep::Sleep(std::string &command,FSM *_fsm,State *_s,std::ostream& os,std::istream& is,std::ostringstream& os2,std::istringstream& is2,bool is_IO_string) : Commands(_fsm,_s,os,is,os2,is2,is_IO_string)  {
		encode(command);
	}


int Sleep::execute() {
	std::string str_symb;
	unsigned long long inst = data & 0xFF;
	if( inst == SLEEP ){
		int sleep_time = ( data >> 8 ) ;
		if (is_IO_from_string )
			o_string << "Sleeping for " << sleep_time << " seconds ...\n" ;
		else{
			o_console << "Sleeping for " << sleep_time << " seconds ...\n" ;
			o_string << "Sleeping for " << sleep_time << " seconds ...\n" ;
		}
		
		std::this_thread::sleep_for(std::chrono::seconds(sleep_time));
		return 0; 
	}
	else
		throw EXCEPTION("Invalid Function operand");	
}

void Sleep::encode(std::string &command) {
	if ( command.substr(0,5) != "sleep" )
		throw EXCEPTION("Unknown Instruction");
	
	int sleep_time = return_int( command.substr(5,command.size()-5) );

	data = ( sleep_time << 8 ) | SLEEP;
}