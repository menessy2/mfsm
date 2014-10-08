

#include "MFSMParser.h"



MFSMParser::MFSMParser(std::string &filename,std::ostream& o,std::istream& i) : os(o) , is(i) {
		in.open(filename.c_str(), std::ios::in);
		this->filename = GeneralParser::split_filename(filename);
		if ( ! in )
			throw EXCEPTION("File can't be opened");
}


MFSM *MFSMParser::parse_file(){

	if ( ! is_mfsm_name_correct() )
			throw EXCEPTION("MFSM machine name does not match the filename or Wrong MFSM header");

	get_common_variables();
	get_machines();

	return Mfsm;
}


bool MFSMParser::is_mfsm_name_correct() {
		std::string mfsm_const,mfsm_name;
		in >> mfsm_const >> mfsm_name;
		if ( ( mfsm_const == "MFSM" ) && ( mfsm_name == filename ) ){
			Mfsm = new MFSM(mfsm_name,os,is);
			return true;
		}
		os << "Expected Header: FSM " << filename << std::endl; 
		return false;
	}



void MFSMParser::get_common_variables(){
		std::string var;
		char comma;
		
		in >> var;
		long _rollback = in.tellg();
		if ( var != "COMVAR" ){
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
				//if ( ! potential_exit && ! res )
				//	throw EXCEPTION("Syntax Error in COMVAR");
				if ( potential_exit && res )
					potential_exit = false;
				else if ( ! res )
					potential_exit = true;
			}

			if ( (var.size()>=8) && ( var.substr(0,8) == "machines" ) && potential_exit )
				break;

			Mfsm->add_variable(var);
			back_ = in.tellg();
		}

		//in.seekg(back_, std::ios::beg);
		for(int i=0;i<var.size();i++)
			in.unget();
	}


void MFSMParser::get_machines(){

	std::string var,line;
		char dummy;
		in >> var;
		if ( var == "machines:"){
			 
		} else if ( var == "machines"){
			in >> dummy;
			if ( dummy != ':' )
				throw EXCEPTION("Error while parsing Machines Section");
			
		} else    // Machines section not present in file
			return;

		char _ctemp=in.get();
		while ( ( _ctemp =='\n' ) || ( _ctemp == ' ' ) ){   // reach next line
			_ctemp=in.get();
		}
		in.unget();

		while ( ! in.eof() ) {

			std::string fsm_name;

			in >> fsm_name;
			if ( fsm_name == "" )
				break;
			
			FSMParser parser(fsm_name,os,is,true);
			FSM *fsm = parser.parse_file(Mfsm);

			Mfsm->add_fsm(fsm);
		}

}


MFSMParser::~MFSMParser(){
	in.close();
}