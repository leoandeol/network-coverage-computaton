#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <vector>
#include "Network.hpp"

class Interface
{
public:
  Interface();
  ~Interface();
  int create_graph_terminal();
  int import_graph(std::string="import");
  void export_graph(int,std::string="export");
  int create();
  bool is_connected(int id);
  void display_shortest_path(int id, std::string& source, std::string& target);
  void color_path(int id, std::string& source, std::string& destination, std::string& color);
private:
  std::vector<Network*> networks;
  const std::string DATA_FOLDER = "data/";
  const std::string FILE_EXTENSION = ".dot";
};

#endif
