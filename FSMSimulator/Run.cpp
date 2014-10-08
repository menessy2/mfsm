

#include "Run.h"


Run::Run(std::string &command,FSM *_fsm,State *_s,std::ostream& os,std::istream& is,std::ostringstream& os2,std::istringstream& is2,bool is_IO_string) : Commands(_fsm,_s,os,is,os2,is2,is_IO_string)  {
		encode(command);
	}


int Run::execute() {
	std::string str_symb;
	unsigned long long inst = data & 0xFF;
	if( inst == RUN ){
		std::string fsm_name = s->get_fsm_name( data >> 8 ) ;
		try {
			if ( fsm_name.substr(fsm_name.size()-5,4) != ".fsm" )
				fsm_name = fsm_name + ".fsm";
		} catch ( ... ) {}
	
		if ( is_IO_from_string ){
			o_console << " [[ WARNING ]] nested invocations of FSMs detected, input must be entered inline" << std::endl;
			is_IO_from_string = false;
		}

		FSMParser parser(fsm_name,o_console,i_console,is_IO_from_string);
		FSM *fsm_ = parser.parse_file(NULL);
		
		if ( fsm_->mfsm )
			o_string << fsm_->output();
		fsm_->execute();
		delete fsm_;
		return 0; 
	}
	else
		throw EXCEPTION("Invalid Function operand");	
}

void Run::encode(std::string &command) {
	if ( command.substr(0,3) != "run" )
		throw EXCEPTION("Unknown Instruction");
	
	int start_=3,final_;
	get_first_occurence(command,start_);
	get_last_occurence(command,final_);
	size_t pos = s->use_fsm(command.substr(start_,(final_-start_)+1));

	data = ( pos << 8 ) | RUN;
}

