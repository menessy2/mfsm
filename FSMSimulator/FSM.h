#ifndef FSM_H
#define FSM_H

#include <string>
#include <vector>
#include <sstream>
//#include "Graph.h"
#include "common.h"
#include "State.h"
#include "MFSM.h"

class MFSM;

class State;
typedef std::list<State>::iterator State_ptr;

template<class NODE,class EDGE>
class SpecialNode {
public:
	NODE node;
	EDGE edge;
	SpecialNode(NODE n)  : node(n) {}
	SpecialNode(NODE n,EDGE e)  : node(n) , edge(e) {}
};


template<class NODE,class EDGE>
class Graph {

private:

	std::vector< std::vector<SpecialNode<NODE,EDGE> > > data;
	bool (*fp_compare_node)(NODE,NODE); 
	bool (*fp_compare_edge)(EDGE,EDGE);

public:
	Graph(bool (*comp_node)(NODE,NODE),bool (*comp_edge)(EDGE,EDGE) );
	size_t add_vertex(NODE node);
	size_t is_vertex_available(NODE v);
	Graph &add_edge(NODE &from,NODE &to,EDGE &edge);
	NODE* destination_node(NODE &n,EDGE &e);
	~Graph();	
};

//template<class NODE,class EDGE>
//class Graph;

bool compare_nodes(State_ptr s1,State_ptr s2);
bool compare_edge(int e1,int e2);

class FSM {
private:
	std::string fsm_name;
	//Variables_HASHMAP ;			// THIS HOLDS THE SYMBOL TABLES ASSOCIATED WITH THE VALUES OF THE VARIABLES
	Variables_HASHMAP_FSM variables_table;
	Graph<State_ptr,int> *states;			// GRAPH DATA STRUCTURE FOR STORING THE FEASIBLE TRANSITIONS AMONG STATES WITH DIFFERENT EDGES
	std::list<State> states_vector;			// VECTOR HOLDING ALL STATES BELONGING TO THAT FSM
	State_ptr current_state;				// POINTER TO THE CURRENT STATE THE FSM RESIDES IN
	bool is_initialized;
	
	bool is_IO_from_string; // if true , use the sstream below
	std::istringstream i_string;
	std::ostringstream o_string;
											// else
	std::ostream& o_console;						// STDOUT FOR PRINTING THE EVENTS
	std::istream& i_console;						// STDIN FOR GETTING INPUT FROM USER

public:
	MFSM *mfsm;
	FSM(std::string& fsm_name,std::ostream& o,std::istream& i,bool is_IO_string);
	void flag_input_from_terminal(std::string& str);
	void add_variable(std::string var,bool is_shared);
	void set_parent_msfsm(MFSM *_mfsm);
	void execute();															// EXECUTE THE WHOLE FSM 
	std::string FSM::output();
	void add_edge(std::string s1,std::string s2,int edge);					// ADD EDGE FROM S1 TO S2 , EDGE NAME IS EDGE
	void reset(State_ptr starting_state);									// READJUST THE PTR OF 'current_state'
	void add_state(std::string &state_name,std::string& commands);			// Add state
	bool is_variable_available(std::string var);
	//long *get_the_variable_pointer(std::string var);
	State_ptr get_state_pointer(std::string var);
	State_ptr reach_destination(State_ptr source,int edge);
	std::string& get_fsm_name();

	VAR_PTR_FSM get_variables_begin();					// GET PTR TO THE START OF THE SYMBOL TABLE
	VAR_PTR_FSM get_variables_end();					// GET PTR TO THE END OF THE SYMBOL TABLE
};

#endif