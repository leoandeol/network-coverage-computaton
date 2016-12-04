#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <string>

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
} Default_Vertex;

typedef struct Default_Edge
{

} Default_Edge;

/**
   Implementation for our project
*/

typedef struct Routeur : Default_Vertex {
  bool is_multicast;
} Routeur;

typedef struct Cable : Default_Edge {
  unsigned int length;
  std::string color;
} Cable;

#endif
