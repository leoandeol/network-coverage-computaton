#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <string>
#include <boost/graph/adjacency_list.hpp>

typedef struct NetworkInfo
{
  std::string name;
  std::string location;
  NetworkInfo(std::string s, std::string l)
  {
    name = s;
    location = l;
  }
} NetworkInfo;

/**
   Default structs
*/

typedef struct Default_Vertex
{
	std::string name;
	bool is_working;
} Default_Vertex;

typedef struct Default_Edge
{
	bool is_working;
} Default_Edge;

/**
   Implementation for our project
*/

typedef struct Routeur : Default_Vertex {
  bool is_multicast;
  std::string color;
} Routeur;

typedef struct Cable : Default_Edge {
	std::string color;
	unsigned int length;
} Cable;




/**
   Custom visitor implementing the "working" parameter
*/
class custom_dijkstra_visitor : public boost::default_dijkstra_visitor
{
    public:
	template <typename Graph, typename Vertex = Default_Vertex>
	void initialize_vertex(Vertex u, const Graph & g) const
	{
		if(!g[u].is_working){
			std::cout << "Routeur " << g[u].name << " non fonctionnel. " << std::endl;
			
		}
	}
};


#endif
