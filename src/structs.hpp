#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <string>

typedef struct NetworkInfo
{
  std::string name;
  std::string location;
} NetworkInfo;

typedef struct Routeur {
	unsigned int id;
	std::string name;
	bool is_multicast;
} Routeur;

typedef struct Cable {
	unsigned int id;
	unsigned int length;
} Cable;

#endif
