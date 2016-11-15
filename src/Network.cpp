#include "Network.hpp"

Network::Network()
{
  dp = boost::dynamic_properties(boost::ignore_other_properties);
  
  dp.property("id", boost::get(&Routeur::id, network_graph));
  dp.property("name", boost::get(&Routeur::name, network_graph));
  dp.property("isMulticast", boost::get(&Routeur::isMulticast, network_graph));
  
  dp.property("id", boost::get(&Cable::id, network_graph));
  dp.property("name", boost::get(&Cable::name, network_graph)); 
  dp.property("length", boost::get(&Cable::length, network_graph));
}

Network::~Network()
{

}

int Network::add_routeur(Routeur&)
{
  return 0;
}

int Network::add_cable(Cable&)
{
  return 0;
}

int Network::add_cable(unsigned int id1, unsigned int id2)
{
  if(id1>=vertex_list.size())
    {
      Routeur r;
      r.id = id1;
      r.name = "add_cable";
      r.isMulticast = true;
      auto tmp = boost::add_vertex(r, network_graph);
      vertex_list.push_back(tmp);
    }
  if(id2>=vertex_list.size())
    {
      Routeur r;
      r.id = id2;
      r.name = "add_cable";
      r.isMulticast = true;
      auto tmp = boost::add_vertex(r, network_graph);
      vertex_list.push_back(tmp);
    }
  Cable c;
  c.id = 42;
  c.name = "add_cable";
  c.length= 42;
  auto tmp = boost::add_edge(vertex_list[id1], vertex_list[id2], c, network_graph);
  edge_list.push_back(tmp.first);
  return 0;
}

Routeur* Network::get_routeur(unsigned int)
{
  return NULL;
}

Cable* Network::get_cable(unsigned int)
{
  return NULL;
}

int Network::remove_routeur(unsigned int)
{
  return 0;
}

int Network::remove_cable(unsigned int)
{
  return 0;
}

int Network::load_from_file(std::string path)
{
  std::ifstream in(path);
  if(!read_graphviz(in, network_graph, dp, "name"))
    {
      std::cerr << "Error while reading the graph at : " << path << std::endl;
      return -1;
    }
  return 0;
} 

int Network::save_to_file(std::string path)
{
  std::ofstream out(path);
  write_graphviz_dp(std::cout, network_graph, dp, "name");
  // write returns void
  /* {
      std::cerr << "Error while writing the graph at : " << path << std::endl;
      return -1;
    }*/
  return 0;
}
