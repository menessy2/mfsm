#ifndef GParser
#define GParser

#include "common.h"

#include "MFSMParser.h"

#include "MFSM.h"


//class MFSMParser;

class MFSM;

class GeneralParser {

private:
	bool fsm_or_mfsm;
	FSM *fsm;
	MFSM *mfsm;
	
	std::string filename;
	std::ostream& os;
	std::istream& is;

public:
	GeneralParser(std::string &filename,std::ostream& o,std::istream& i);
	bool is_fsm();
	
	//FSM *return_fsm();
		
	//MSFM *return_mfsm();
	
	~GeneralParser();

	static std::string& split_filename(std::string& str);		// returns the filename ( without extensions ) from file path
	static bool has_char(std::string& str,char _char);			// return true if _char is a suffix/prefix in str , it then removes _char from str
	static std::string get_line(std::istream& in);


};








#endif