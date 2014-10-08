
#ifndef RUN_H
#define RUN_H

#include "Commands.h"
#include "FSM.h"
#include "FSMParser.h"
#include <thread>

class Run : public Commands {

private:

	//std::string command_string; // redundant string
	unsigned long long data;

public:

	Run(std::string &command,FSM *_fsm,State *_s,std::ostream& os,std::istream& is,std::ostringstream& os2,std::istringstream& is2,bool is_IO_string);
	virtual int execute() ;
	virtual void encode(std::string &command);

};


#endif