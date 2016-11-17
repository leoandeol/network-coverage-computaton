#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <string>

typedef struct Routeur {
	unsigned int id;
	std::string name;
	bool isMulticast;
} Routeur;

typedef struct Cable {
	unsigned int id;
	unsigned int length;
} Cable;

#endif
