#include "Commands.h"



Commands::Commands(FSM *_fsm,State *_s,std::ostream& o,std::istream& i,std::ostringstream& os2,std::istringstream& is2,bool is_IO_string) : 
	fsm(_fsm) , s(_s) , o_console(o) , i_console(i) , o_string(os2) , i_string(is2) , is_IO_from_string(is_IO_string) {}

void Commands::Commands_encode(std::string &commands,FSM *_fsm,State *_s,std::ostream& os,std::istream& is,std::ostringstream& os2,std::istringstream& is2,bool is_IO_string){
		std::vector<Commands*> *instructions = new std::vector<Commands*>;
		int end=-1,start;
		while( end < (int)(commands.size()-1) ){
			start = end + 1;
			end = commands.find(',',end+1);
			if ( end == -1 )
				end = commands.size()-1;
			get_first_occurence(commands,start);
			
			Out *_out;
			Wait *_wait;
			End *_end;
			Sleep *_sleep;
			Add *_add;
			Run *_run;

			switch( commands[start] ){
			case 'o': // out
			case 'O':
				_out = new Out(commands.substr(start,end-start),_fsm,_s,os,is,os2,is2,is_IO_string);
				instructions->push_back(_out);
				break;
			case 'r': // run
			case 'R':
				_run = new Run(commands.substr(start,end-start),_fsm,_s,os,is,os2,is2,is_IO_string);
				instructions->push_back(_run);
				break;
			case 's':	// sleep
			case 'S':
				_sleep = new Sleep(commands.substr(start,end-start),_fsm,_s,os,is,os2,is2,is_IO_string);
				instructions->push_back(_sleep);
				break;
			case 'w': // wait
				_wait = new Wait(commands.substr(start,end-start),_fsm,_s,os,is,os2,is2,is_IO_string);
				instructions->push_back(_wait);
				break;
			case 'e': // end
				_end = new End(commands.substr(start,end-start),_fsm,_s,os,is,os2,is2,is_IO_string);
				instructions->push_back(_end);
				break;
			default:  // add
				_add = new Add(commands.substr(start,end-start),_fsm,_s,os,is,os2,is2,is_IO_string);
				instructions->push_back(_add);
			}
		}
		_s->setCommands(instructions);
	}
