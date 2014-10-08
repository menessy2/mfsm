#ifndef WAIT_H
#define WAIT_H

#include "Commands.h"

class Wait : public Commands {

private:

	//std::string command_string; // redundant string
	unsigned long long data;

public:

	Wait(std::string &command,FSM *_fsm,State *_s,std::ostream& os,std::istream& is,std::ostringstream& os2,std::istringstream& is2,bool is_IO_string);
	virtual int execute() ;
	virtual void encode(std::string &command);

};
#endif 