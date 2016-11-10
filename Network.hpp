#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <utility>
#include <algorithm>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <string>

#include "structs.hpp"

typedef boost::adjacency_list<boost::vecS,
			      boost::vecS,
			      boost::bidirectionalS,
				Routeur,
				Cable> network_graph_t;

class Network {
public:
  Network();
  Network(int);
  ~Network();
  int addRouteur(Routeur&);
  int addCable(Cable&);
  Routeur* getRouteur(int);
  Cable* getCable(int);
  int removeRouteur(int);
  int removeRouteur(Routeur&);
  int removeCable(int);
  int removeCable(Cable&);
  int loadFromFile(std::string&);
  int saveToFile(std::string&);
private:
  network_graph_t graph;
};

#endif
