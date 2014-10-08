

#ifndef FSMPARSER_H
#define FSMPARSER_H


#include <fstream>
#include <string>
#include <regex>

#include "common.h"
//#include "FSM.h"
#include "GeneralParser.h"

class FSM;
class MFSM;

typedef std::match_results<const char*> cmatch;

class FSMParser {
private:
	std::ifstream in; // input from file
	std::string filename;
	FSM *fsm;			// Pointer to the constructed FSM object from the parsed file

	bool is_IO_from_string; // if true , use the sstream below
	std::istringstream i_string;
	std::ostringstream o_string;
											// else
	std::ostream& o_console;						// STDOUT FOR PRINTING THE EVENTS
	std::istream& i_console;						// STDIN FOR GETTING INPUT FROM USER

public:

	FSMParser(std::string filename,std::ostream& o,std::istream& i,bool is_IO_string);
	FSM *parse_file(MFSM *parent_msfm) ;						
	bool is_fsm_name_correct() ;			// compares the given fsm name with the filename
	void get_variables() ;					// extracting the VAR section and feed it to the FSM object
	void get_states();						// extracting the States section and feed it to the FSM object
	void get_transitions();					// extracting the Transitions section and feed it to the FSM object
	
	~FSMParser();
};


#endif