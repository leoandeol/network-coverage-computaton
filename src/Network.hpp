#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream> // std::cout
#include <fstream> // std::i/ofstream
#include <utility>
#include <algorithm> // std::find
#include <string> // std::string
#include <boost/graph/graph_traits.hpp> // vertex and edge descriptors
#include <boost/graph/adjacency_list.hpp> // adjacency_list
#include <boost/graph/dijkstra_shortest_paths.hpp> // djikstra shortest paths
#include <boost/graph/graphviz.hpp> // import/export .dot

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
  /**
     \brief Constructor
     \param i struct containing informations about the graph such as its name
  */
  Network(NetworkInfo& i);
  /**
     \brief Destructr
  */
  ~Network();
  /**
     \brief Creates a new routeur and returns its id
     \return The new routeur's ID or -1 if there was an error
  */
  int add_routeur();
  /**
     \brief Creates a new routeur with a set name and returns its id
     \param s The new routeur's name
     \return The new routeur's ID or -1 if there was an error
  */
  int add_routeur(std::string& s);
  /**
     \brief Creates a new cable between two routeurs, and returns its id
     \param id1 A routeur's ID
     \param id2 Another routeur's ID
     \return The new cable's ID or -1 if there was an error (non existent routeur or identical routeurs for exemple)
  */
  int add_cable(unsigned int id1,unsigned int id2);
  /**
     \brief Gives a pointer to the routeur with the given ID
     \param id The routeur's ID
     \return A pointer to the wanted routeur, or nullptr if non-existent
   */
  Routeur* get_routeur(unsigned int id);
  /**
     \brief Gives a pointer to the cable with the given ID
     \param id The cable's ID
     \return A pointer to the wanted cable, or nullptr if non-existent
   */
  Cable* get_cable(unsigned int id);
  /**
     \brief Removes the routeur with the given ID
     \param id The routeur's ID
     \return 0 if successfully removed, else -1
   */
  int remove_routeur(unsigned int id);
  /**
     \brief Removes the cable with the given ID
     \param id The cable's ID
     \return 0 if successfully cable, else -1
   */
  int remove_cable(unsigned int id);
  /**
     \brief Loads a graph in the DOT format, from the path given as parameter
     \param s The path to the .dot file
     \return 0 if the file was loaded successfully, else -1
  */
  int load_from_file(std::string& s);
  /**
     \brief Saves a graph in the DOT format, to the path given as parameter
     \param s The path to the wanted .dot file
  */
  void save_to_file(std::string& s);
private:
  network_graph_t network_graph;/**< The adjacency list adapted to our struct*/
  vertex_list_t vertex_list;/**< The list of vertex descriptors, of network_graph's vertices*/
  //TO FIX : static id counter
  std::vector<bool> vertex_exist;/**< A boolean array used to check if the vertex at the said coordinates exist, because the array can be wider than the number of vertices it contains */
  edge_list_t edge_list;/**< The list of edge descriptors, of network_graph's edges*/
  boost::dynamic_properties dp;/**< The dynamic properties of our graph, to link the structs to the import/export format*/
  unsigned bool default_routeur_is_multicast = true;/**< Default value for is_multicast when creating a new routeur*/
  unsigned int default_cable_length = 1;/**< Default value for length when creating a new cable*/
};

#endif
