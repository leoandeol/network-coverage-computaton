#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <fstream> //std::i/ofstream
#include <utility>
#include <algorithm> // std::find
#include <string> // std::string
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graphviz.hpp>

#include "structs.hpp"

typedef boost::adjacency_list<boost::vecS,
							  boost::vecS,
							  boost::bidirectionalS,
							  Routeur,
							  Cable> network_graph_t;

typedef boost::graph_traits<network_graph_t>::vertex_descriptor vertex_t;
typedef boost::graph_traits<network_graph_t>::edge_descriptor edge_t;

typedef std::vector<vertex_t> vertex_list_t;
typedef std::vector<edge_t> edge_list_t;

class Network {
public:
	Network();
	~Network();
	int add_routeur(unsigned int);
	int add_routeur(Routeur&);
	int add_cable(Cable&);
	int add_cable(unsigned int,unsigned int);
	Routeur* get_routeur(unsigned int);
	Cable* get_cable(unsigned int);
	int remove_routeur(unsigned int);
	int remove_cable(unsigned int);
	int load_from_file(std::string);
	int save_to_file(std::string);
private:
	network_graph_t network_graph;
	vertex_list_t vertex_list;
	std::vector<bool> vertex_exist;
	edge_list_t edge_list;
	boost::dynamic_properties dp;
};

#endif
