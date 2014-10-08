

#ifndef MFSMPARSER_H
#define MFSMPARSER_H


#include <fstream>
#include <string>
#include <regex>

#include "common.h"
#include "MFSM.h"
#include "FSMParser.h"

class MFSM;

class MFSMParser {
private:
	std::ifstream in; // input from file
	std::string filename;
	MFSM *Mfsm;			// Pointer to the constructed MFSM object from the parsed file

	std::ostream& os;	// stdout to be passed to MFSM object
	std::istream& is;	// stdin to be passed to MFSM object


public:
	MFSMParser(std::string &filename,std::ostream& o,std::istream& i);
	MFSM *parse_file();
	bool is_mfsm_name_correct();
	void get_common_variables();
	void get_machines();

	~MFSMParser();

};


#endif


