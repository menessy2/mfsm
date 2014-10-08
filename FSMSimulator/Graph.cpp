
#include "Graph.h"

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
