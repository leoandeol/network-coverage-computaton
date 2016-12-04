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

typedef struct Routeur {
  std::string name;
  std::string color;
  bool is_multicast;
} Routeur;

typedef struct Cable {
  unsigned int length;
  std::string color;
} Cable;

#endif
