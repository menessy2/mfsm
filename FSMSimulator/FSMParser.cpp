
#include "FSMParser.h"


FSMParser::FSMParser(std::string filename,std::ostream& o,std::istream& i,bool is_IO_string) : 
	o_console(o), i_console(i) , is_IO_from_string(is_IO_string) {
		in.open(filename.c_str(), std::ios::in);
		this->filename = GeneralParser::split_filename(filename);
		if ( ! in )
			throw EXCEPTION("File can't be opened");
		
	}



FSM *FSMParser::parse_file(MFSM *parent_msfm){
		
		if ( ! is_fsm_name_correct() )
			throw EXCEPTION("FSM machine name does not match the filename or Wrong FSM header");

		fsm->set_parent_msfsm(parent_msfm);

		get_variables();
		get_states();
		get_transitions();

		return fsm;
	}

bool FSMParser::is_fsm_name_correct(){
		std::string fsm_const,fsm_name;
		in >> fsm_const >> fsm_name;
		if ( ( fsm_const == "FSM" ) && ( fsm_name == filename ) ){
			fsm = new FSM(fsm_name,o_console,i_console,is_IO_from_string);
			return true;
		}

		if ( is_IO_from_string )
			o_string << "Expected Header: FSM " << filename << std::endl;
		else
			o_console << "Expected Header: FSM " << filename << std::endl; 

		return false;
	}

void FSMParser::get_variables(){
		std::string var;
		char comma;
		
		in >> var;
		long _rollback = in.tellg();
		if ( var != "VAR" ){
			in.seekg( _rollback+1 , std::ios::beg); 
			return;
		}

		bool potential_exit=true;
		unsigned long long back_=0;
		while( true ) {						
			in >> var;

			if ( var == "," ){
				potential_exit=false;
				continue;
			} else {
				bool res = GeneralParser::has_char(var,',');
				if ( ! potential_exit && res )
					throw EXCEPTION("Syntax Error in VAR");
				else if ( potential_exit && res )
					potential_exit = false;
				else
					potential_exit = true;
			}

			if ( (var.size()>=6) && ( var.substr(0,6) == "States" ) && potential_exit )
				break;

			if ( fsm->mfsm != NULL && fsm->mfsm->is_variable_available(var) )		// check if the variable is shared accross multiple fsm(s)
				fsm->add_variable(var,true);
			else
				fsm->add_variable(var,false);

			back_ = in.tellg();
		}

		in.seekg(back_, std::ios::beg); 
	}




void FSMParser::get_states(){
		std::string var,line;
		char dummy;

		in >> var;

		if ( var == "States:"){
			 
		} else if ( var == "States"){
			in >> dummy;
			if ( dummy != ':' )
				throw EXCEPTION("Syntax Error: State must be followed by \':\'");
			
		} else    // state section not present in file
			return;

		unsigned long long file_pos=0;
		std::string temp;

		while(true){
			
			line = "";
			while ( in >> temp ){
				line += temp + ' ';
				GeneralParser::has_char(temp,',');
				if ( ( temp == "Transitions" ) || ( temp == "Transitions:" ) )
					goto exit;
				if ( ( temp == "wait" ) || ( temp == "end" ) )
					break;
			}
			int name_pos = line.find(':');										
			std::string state_name = line.substr( 0, name_pos );					

			fsm->add_state(state_name,line.substr(name_pos+1));
			//file_pos=in.tellg();
			
		}
exit:
		//in.seekg(file_pos, std::ios::beg);		// Unfortunately , tellg does not work correctly at all
		for( int j=0;j<temp.size();j++)				// that's why unget is used instead
			in.unget();
	}



void FSMParser::get_transitions(){
		std::string var,line;
		char dummy;
		in >> var;
		if ( var == "Transitions:"){
			 
		} else if ( var == "Transitions"){
			in >> dummy;
			if ( dummy != ':' )
				throw EXCEPTION("Error while parsing State");
			
		} else    // Transitions section not present in file
			return;

		char _ctemp=in.get();
		while ( ( _ctemp =='\n' ) || ( _ctemp == ' ' ) ){   // reach next line
			_ctemp=in.get();
		}
		in.unget();

		while ( ! in.eof() ) {

			std::string temp,temp2,temp3;

			temp = GeneralParser::get_line(in);
			if ( temp == "" )
				break;
			std::tr1::cmatch res;
			std::tr1::regex rx("(.+),(.+),(.+)");
			std::tr1::regex_search(temp.c_str(), res, rx);

			std::string source = return_string(std::string(res[1]));
			std::string destination = return_string(std::string(res[2]));
			int edge = return_int(res[3]);

			fsm->add_edge(source,destination,edge);
		}

	}

FSMParser::~FSMParser() {
	in.close();
}

