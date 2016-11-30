#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream> // std::cout
#include <fstream> // std::i/ofstream
#include <utility>
#include <algorithm> // std::find
#include <string> // std::string
#include <unordered_map>
#include <boost/graph/graph_traits.hpp> // vertex and edge descriptors
#include <boost/graph/adjacency_list.hpp> // adjacency_list
#include <boost/graph/dijkstra_shortest_paths.hpp> // djikstra shortest paths
#include <boost/graph/graphviz.hpp> // import/export .dot

#include "structs.hpp"

typedef boost::adjacency_list<boost::vecS,
			      boost::vecS,
			      boost::bidirectionalS,
			      Routeur,
			      Cable, NetworkInfo> network_graph_t;

typedef boost::graph_traits<network_graph_t>::vertex_descriptor vertex_t;
typedef boost::graph_traits<network_graph_t>::edge_descriptor edge_t;
typedef boost::property_map<network_graph_t,boost::vertex_index_t>::type IndexMap;
typedef boost::iterator_property_map<vertex_t*,IndexMap,vertex_t,vertex_t&>PredecessorMap;
typedef boost::iterator_property_map<unsigned int*,IndexMap,unsigned int,unsigned int&>DistanceMap;

typedef std::unordered_map<std::string, vertex_t> vertex_list_t;
typedef std::unordered_map<std::string, edge_t> edge_list_t;

class Network {
public:
  /** 
      \brief Default Constructor, calls the other constructor with default parameters
  */
  Network();
  /**
     \brief Constructor
     \param i struct containing informations about the graph such as its name
  */
  Network(NetworkInfo i);
  /**
     \brief Destructr
  */
  ~Network();
  /**
     \brief Creates a new routeur and returns its id
     \return The new routeur's name or -1 if there was an error
  */
  std::string add_routeur();
  /**
     \brief Creates a new routeur with a set name and returns its id
     \param s The new routeur's name
     \return 0 in case of success, else -1
  */
  int add_routeur(std::string& s);
  /**
     \brief Creates a new cable between two routeurs, and returns its id
     \param id1 A routeur's name
     \param id2 Another routeur's name
     \return 0 in case of success, else -1
  */
  int add_cable(std::string& id1,std::string& id2);
  /**
     \brief Gives the value of an attribute of an element, of type Structure
     \param id The element's name
     \return A reference to the attribute's value
   */
  template<typename Structure, typename Attribute>
  Attribute& get_attribute(std::string& id);
  /**
     \brief Sets the value of an attribute of an element, of type Structure
     \param id The element's name
     \param value The new value of the attribute
  */
  template <typename Structure, typename Attribute>
  void set_attribute(std::string& id, Attribute value);
  /**
     \brief Gives a pointer to the cable with the given ID
     \param id The cable's name
     \return A pointer to the wanted cable, or nullptr if non-existent
   */
  int remove_routeur(std::string& id);
  /**
     \brief Removes the cable with the given ID
     \param id The cable's name
     \return 0 if successfully cable, else -1
   */
  int remove_cable(std::string& id);
  /**
    \brief calculates the shortest path between two routeurs of the network
    \param source The source's name
    \param destination The destination's name
    \return a vector that represents the path between those routeurs
  */
  std::vector<std::string> get_path(std::string source,std::string destination);
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

  /**
    \brief Return a boolean if the graph is connected or not
    \param No parameters
    \return true if the graph is connected, else return false
  */
  bool is_connected();
private:
  network_graph_t network_graph;/**< The adjacency list adapted to our struct*/
  vertex_list_t vertex_list;/**< The list of vertex descriptors, of network_graph's vertices*/
  //TO FIX : static id counter
  std::vector<bool> vertex_exist;/**< A boolean array used to check if the vertex at the said coordinates exist, because the array can be wider than the number of vertices it contains */
  edge_list_t edge_list;/**< The list of edge descriptors, of network_graph's edges*/
  boost::dynamic_properties dp;/**< The dynamic properties of our graph, to link the structs to the import/export format*/
  bool default_routeur_is_multicast = true;/**< Default value for is_multicast when creating a new routeur*/
  unsigned int default_cable_length = 1;/**< Default value for length when creating a new cable*/
};

#endif
