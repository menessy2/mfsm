

#ifndef GRAPH_H
#define GRAPH_H

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

#endif