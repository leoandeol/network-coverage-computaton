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
  unsigned int length;
  std::string color;
} Cable;

#endif
