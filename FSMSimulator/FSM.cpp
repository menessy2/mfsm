
#include "FSM.h"


template<class NODE,class EDGE>
Graph<NODE,EDGE>::Graph(bool (*comp_node)(NODE,NODE),bool (*comp_edge)(EDGE,EDGE) ){
	fp_compare_node = comp_node;
	fp_compare_edge = comp_edge;
}

template<class NODE,class EDGE>
size_t Graph<NODE,EDGE>::add_vertex(NODE node){
		std::vector<SpecialNode<NODE,EDGE>> vec;
		vec.push_back( SpecialNode<NODE,EDGE>(node) );
		data.push_back(vec);
		return data.size()-1;
	}

template<class NODE,class EDGE>
size_t Graph<NODE,EDGE>::is_vertex_available(NODE v){
		
		
		for(size_t c_j=0;c_j<data.size();c_j++){
			
			if ( (*fp_compare_node)(v,data[c_j][0].node)  )
				return c_j;
				
			c_j++;
		}
		return -1;
	}

template<class NODE,class EDGE>
Graph<NODE,EDGE>& Graph<NODE,EDGE>::add_edge(NODE &from,NODE &to,EDGE &edge){
		size_t from_node;

		if ( ( from_node = is_vertex_available(from) ) == -1 )
			from_node = add_vertex(from);
		if (  is_vertex_available(to) == -1 )
			add_vertex(to);
		
		SpecialNode<NODE,EDGE> second_vertex(to,edge);
		
		data[from_node].push_back(second_vertex);
		return *this;
	}


template<class NODE,class EDGE>
NODE* Graph<NODE,EDGE>::destination_node(NODE &n,EDGE &e){
		size_t temp = is_vertex_available(n);
		if ( temp == -1 )
			throw "Node is not present"; //
		
		for(auto& each_neighbor : data[temp] ) {
			if ( (*fp_compare_edge)(e,each_neighbor.edge) ) {
				return &each_neighbor.node;
			}
		}
		throw "No neighbor is connected from such edge";
	}

template<class NODE,class EDGE>
Graph<NODE,EDGE>::~Graph(){
		for( auto& i : data ){
			i.clear();
		}
	}
	




////////////////////////////////////////////




bool compare_nodes(State_ptr s1,State_ptr s2){
	std::string t1 = s1->get_state_name();
	std::string t2 = s2->get_state_name();
	return t1.compare(t2) == 0;
}

bool compare_edge(int e1,int e2){
	return e1 == e2;
}

FSM::FSM(std::string& fsm_name,std::ostream& o,std::istream& i, bool is_IO_string) : 
	o_console(o) , i_console(i) , is_IO_from_string(is_IO_string) {
	this->fsm_name = fsm_name;
	is_initialized = false;
	states = new Graph<State_ptr,int>(compare_nodes,compare_edge);
}



void FSM::execute(){
	int result,edge;
	
	if ( is_IO_from_string ) {
		o_string << "-----------------------------------------------\n";
		o_string << "------------Starting FSM - " << fsm_name << std::endl; 
		o_string << "Starting @ state " << current_state->get_state_name() << std::endl;
	} else {
		o_console << "-----------------------------------------------\n";
		o_console << "------------Starting FSM - " << fsm_name << std::endl; 
		o_console << "Starting @ state " << current_state->get_state_name() << std::endl;
		o_string << "-----------------------------------------------\n";
		o_string << "------------Starting FSM - " << fsm_name << std::endl; 
		o_string << "Starting @ state " << current_state->get_state_name() << std::endl;
	}
	current_state->execute_state();

	while( true ) {
		//os << "Current State: " << current_state->get_state_name() << '\n';

		if ( is_IO_from_string ) {
			i_string >> edge;
		} else {
			o_console << "-----------------------------" << std::endl;
			o_console << "Please input the next state: ";
			i_console >> edge;
		}
		try {
			State_ptr dst = reach_destination(current_state,edge);
			reset(dst);
			if ( (result=dst->execute_state())==1)  // return 1 if it reached the END instruction
				break;
		} catch ( ... ) {
			if ( is_IO_from_string ) {
				o_string << "No connection with such link\n";
			} else {
				o_console << "No connection with such link\n";
				o_string << "No connection with such link\n";
			}
			continue;
		}
		
		
	}

	if ( is_IO_from_string ) {
		o_string << "------------Ending FSM - " << fsm_name << std::endl; 
		o_string << "-----------------------------------------------\n";
	} else {
		o_console << "------------Ending FSM - " << fsm_name << std::endl; 
		o_console << "-----------------------------------------------\n";
		o_string << "------------Ending FSM - " << fsm_name << std::endl; 
		o_string << "-----------------------------------------------\n";
	}			

}


std::string FSM::output(){
	return o_string.str();
}

void FSM::flag_input_from_terminal(std::string& str){
	is_IO_from_string = true;
	i_string.str(str);
}

std::string& FSM::get_fsm_name(){
	return fsm_name;
}

void FSM::reset(State_ptr starting_state){
	this->current_state = starting_state;
}


void FSM::add_variable(std::string var,bool is_shared){
	variables_table[var] = std::make_pair(0,is_shared);
}


void FSM::set_parent_msfsm(MFSM *_mfsm)  {
	this->mfsm = _mfsm;
}

bool FSM::is_variable_available(std::string var){
	if ( mfsm != nullptr && mfsm->is_variable_available(var) )
		return true;
	return ( variables_table.count(var) > 0 );
}

/*
long* FSM::get_variable_pointer(std::string var){
	if ( mfsm->is_variable_available(var) )
		return mfsm->get_variable_pointer(var);

	return &std::get<0>(variables_table[var]);
}
*/

void FSM::add_state(std::string &state_name,std::string& commands){
	State new_state(state_name,this);
	states_vector.push_back(new_state);
	State *_state_ = &states_vector.back();
	Commands::Commands_encode(commands,this,_state_,o_console,i_console,o_string,i_string,is_IO_from_string);
	if ( ! is_initialized ){
		is_initialized = true;
		reset(states_vector.begin());
	}
}


void FSM::add_edge(std::string s1,std::string s2,int edge){
	State_ptr state_1 = get_state_pointer(s1);
	State_ptr state_2 = get_state_pointer(s2);
	states->add_edge(state_1,state_2,edge);
}


State_ptr FSM::get_state_pointer(std::string var){
	State_ptr result= states_vector.begin();
	int counter = -1;
	for(auto& temp: states_vector ){
		counter++;
		if ( temp.get_state_name() == var ){
			std::advance(result,counter);
			return result;
		}
	}
	throw EXCEPTION("State not available in the FSM");
}

State_ptr FSM::reach_destination(State_ptr source,int edge){
	return *(states->destination_node(source,edge));
}

VAR_PTR_FSM FSM::get_variables_begin(){
	return variables_table.begin();
}

VAR_PTR_FSM FSM::get_variables_end(){
	return variables_table.end();
}



