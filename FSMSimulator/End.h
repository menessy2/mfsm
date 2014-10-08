
#ifndef END_H
#define END_H

#include "Commands.h"

class End : public Commands {

private:

	//std::string command_string; // redundant string
	unsigned long long data;

public:

	End(std::string &command,FSM *_fsm,State *_s,std::ostream& os,std::istream& is,std::ostringstream& os2,std::istringstream& is2,bool is_IO_string);
	virtual int execute() ;
	virtual void encode(std::string &command);

};
#endif 