


#include "Add.h"


Add::Add(std::string &command,FSM *_fsm,State *_s,std::ostream& os,std::istream& is,std::ostringstream& os2,std::istringstream& is2,bool is_IO_string) : Commands(_fsm,_s,os,is,os2,is2,is_IO_string)  {
		encode(command);
	}


int Add::execute() {

	std::lock_guard<std::mutex> lock(i_mutex);
	std::string str_symb;
	unsigned long long inst = data & 0xFF;
	unsigned int second_op = ( data >> 8 ) & 0xFFFF;
	unsigned int third_op =  ( data >> 24 ) & 0xFFFF;
	unsigned int first_op = ( data >> 40 );

	long result;
	if( inst == CONCAT_INT_vv )
		result = s->get_variable_value(second_op) + s->get_variable_value(third_op);
	else if (  inst == CONCAT_INT_vi )
		result = s->get_variable_value(second_op) + third_op;
	else if ( inst == CONCAT_INT_iv ) 
		result = second_op + s->get_variable_value(third_op);
	else if ( inst == CONCAT_INT_ii ) 
		result = second_op + third_op;
	else
		throw EXCEPTION("Invalid Function operand") ;	

	s->set_variable_value(first_op,result);
}

void Add::encode(std::string &command) {

	int left_assig,first_=0,last_;
	bool is_second_op_VAR,is_third_op_VAR;

	if ( (left_assig=command.find("="))==-1 )
		throw EXCEPTION("Syntax Error in Add instruction");
	
	std::string first_op = command.substr(first_,left_assig);
	get_first_occurence(first_op,first_);
	get_last_occurence(first_op,last_);
	first_op = first_op.substr(first_,(last_-first_)+1);

	if ( (first_=command.find("+",left_assig+1))==-1)
		throw EXCEPTION("Syntax Error in Add instruction");
	int _plus_ = first_+1;
	std::string second_op = command.substr(left_assig+1,first_-left_assig-1);
	get_first_occurence(second_op,(first_=0));
	get_last_occurence(second_op,last_);
	second_op = second_op.substr(first_,(last_-first_)+1);

	std::string third_op = command.substr(_plus_,command.size()-_plus_);
	get_first_occurence(third_op,(first_=0));
	get_last_occurence(second_op,last_);
	third_op = third_op.substr(first_,(last_-first_)+1);


	is_second_op_VAR = is_digits(second_op);
	is_third_op_VAR = is_digits(third_op);


	if ( is_second_op_VAR && is_third_op_VAR )
		data = ( s->use_variable(first_op) << 40 ) | ( s->use_variable(third_op) << 24 ) | ( s->use_variable(second_op) << 8 ) | CONCAT_INT_vv;
	else if ( is_second_op_VAR )
		data = ( s->use_variable(first_op) << 40 ) | ( atoi(third_op.c_str()) << 24 ) | ( s->use_variable(second_op) << 8 ) | CONCAT_INT_vi;
	else if ( is_third_op_VAR )
		data = ( s->use_variable(first_op) << 40 ) | ( s->use_variable(third_op) << 24 ) | ( atoi(second_op.c_str()) << 8 ) | CONCAT_INT_iv;
	else
		data = ( s->use_variable(first_op) << 40 ) | ( atoi(third_op.c_str()) << 24 ) | ( atoi(second_op.c_str()) << 8 ) | CONCAT_INT_ii;
	
}