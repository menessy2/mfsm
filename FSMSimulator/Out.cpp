

#include "Out.h"


Out::Out(std::string &command,FSM *_fsm,State *_s,std::ostream& os,std::istream& is,std::ostringstream& os2,std::istringstream& is2,bool is_IO_string) : Commands(_fsm,_s,os,is,os2,is2,is_IO_string)  {
		encode(command);
	}


int Out::execute() {

		std::lock_guard<std::mutex> lock(i_mutex2);
		std::string str_symb;
		unsigned long long inst = data & 0xFF;
		if( inst == PRINT_S ){
			str_symb = s->use_string_symbol( data >> 8 );
			if ( is_IO_from_string )
				o_string << str_symb << '\n';
			else{
				o_console << str_symb << '\n';
				o_string << str_symb << '\n';
			}
		}
		else if ( inst == PRINT_V ) {
			long result = s->get_variable_value( data >> 8 );
			if ( is_IO_from_string )
				o_string << result << '\n';
			else{
				o_console << result << '\n';
				o_string << result << '\n';
			}
		} else
			throw "Invalid Function operand" ;
		return 0;
	}


void Out::encode(std::string &command) {

		if ( command.substr(0,3) != "out" )
			throw EXCEPTION("Unknown Instruction");

		int start=3,end;
		get_first_occurence(command,start);
		get_last_occurence(command,end);

		if ( (command[start] == '"') && (command[end] == '"') ) {
			unsigned long int string_index = s->add_string_symbol( command.substr(start+1,end-start-1) );
			data = ( string_index << 8 ) | PRINT_S ;
		} else if ( fsm->is_variable_available( command.substr(start,(end-start)+1) ) ){
			unsigned long int string_index = s->use_variable( command.substr(start,(end-start)+1) ) ;
			data = ( string_index << 8 ) | PRINT_V ;
		} else
			throw EXCEPTION("Unknow Parameter for OUT instruction");
		
	}




