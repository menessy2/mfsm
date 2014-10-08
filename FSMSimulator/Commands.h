

#ifndef COMMANDS_H
#define COMMANDS_H

#define PRINT_S 0x70
#define PRINT_V 0x71
#define SLEEP 0x60
#define END 0x90
#define WAIT 0x91
#define RUN 0x50

#define CONCAT_INT_vi 0x10
#define CONCAT_INT_iv 0x11
#define CONCAT_INT_vv 0x12
#define CONCAT_INT_ii 0x13

#include "FSM.h"
#include "State.h"
#include <mutex> 
#include <sstream>

class FSM;
class State;

class Commands {

protected:

	FSM *fsm;
	State *s;

	bool is_IO_from_string; // if true , use the sstream below
	std::istringstream& i_string;
	std::ostringstream& o_string;
											// else
	std::ostream& o_console;						// STDOUT FOR PRINTING THE EVENTS
	std::istream& i_console;						// STDIN FOR GETTING INPUT FROM USER

public:

	Commands(FSM *_fsm,State *_s,std::ostream& o,std::istream& i,std::ostringstream& os2,std::istringstream& is2,bool is_IO_string);
	static void Commands_encode(std::string &commands,FSM *_fsm,State *_s,std::ostream& os,std::istream& is,std::ostringstream& os2,std::istringstream& is2,bool is_IO_string); // core function for converting string to instruction objects having opcodes
	virtual int execute() = 0;									// Any instructions should implement that function for semantic execution
	virtual void encode(std::string &command) = 0;				// Any instructions should implement that function for encoding to opcode

};

#include "Add.h"
#include "Sleep.h"
#include "Wait.h"
#include "Run.h"
#include "Out.h"
#include "End.h"

#endif