

#include "GeneralParser.h"


GeneralParser::GeneralParser(std::string &filename,std::ostream& o,std::istream& i) : os(o) , is(i) {
	std::string type;
	this->filename = filename;
	std::ifstream in;
	in.open(filename.c_str(), std::ios::in);
	in >> type;
	if ( type == "FSM" )
		fsm_or_mfsm = true;
	else
		fsm_or_mfsm = false;
	in.close();
}


bool GeneralParser::is_fsm(){
	return fsm_or_mfsm;
}

/*
FSM *GeneralParser::return_fsm(){
	FSMParser parser(filename,os,is);
	return parser.parse_file(NULL);
}*/

/*
MSFM *GeneralParser::return_mfsm(){
	MFSMParser parser(filename,os,is);
	return parser.parse_file();
}
*/

bool GeneralParser::has_char(std::string& str,char _char){
	if ( str[0] == _char ){
		str = str.substr(1,str.size()-1);
		return true;
	}
	if ( str[str.size()-1] == _char ){
		str = str.substr(0,str.size()-1);
		return true;
	}
	return false;
}


std::string GeneralParser::get_line(std::istream& in){
	std::string result;
	char temp;
	while ( ((temp=in.get())!='\n') && in.good() )
		result += temp;
	return  result;
}


std::string& GeneralParser::split_filename(std::string& str) {
		//str = str.substr(0,str.size()-4);
		int found = str.find_last_of("/\\");
		int found2 = str.find_last_of(".");
		str = str.substr(found+1,found2-found-1);
		return str;
	}



GeneralParser::~GeneralParser(){
}