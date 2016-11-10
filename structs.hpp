#ifndef STRUCTS_HPP
#define STRUCTS_HPP

typedef struct Routeur {
  unsigned int id;
  bool isMulticast;
} Routeur;

typedef struct Cable {
  unsigned int id;
  unsigned int length;
  struct Routeur* routeur1;
  struct Routeur* routeur2;
} Cable;

#endif
