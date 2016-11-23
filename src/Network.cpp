#include "Network.hpp"

// CLASS

Network::Network(NetworkInfo&) : vertex_list(), vertex_exist(), edge_list()
{
  dp = boost::dynamic_properties(boost::ignore_other_properties);
  
  dp.property("node_id", boost::get(&Routeur::id, network_graph));
  dp.property("label", boost::get(&Routeur::name, network_graph));
  dp.property("isMulticast", boost::get(&Routeur::isMulticast, network_graph));
  
  dp.property("edge_id", boost::get(&Cable::id, network_graph));
  dp.property("label", boost::get(&Cable::length, network_graph));
}

Network::~Network()
{

}

int Network::add_routeur()
{
  static unsigned int id_count = 0;
  Routeur r;
  r.id = id_count;
  r.name = std::to_string(r.id);
  r.is_multicast=default_routeur_is_multicast;
  vertex_t v_desc = add_vertex(r,network_graph);
  vertex_list.push_back(v_desc);
  id_count++;
  return r.id;
}

int Network::add_routeur(std::string& name)
{
  int id = add_routeur();
  vertex_list[id].name = name;
  return id;
}

int Network::add_cable(unsigned int id1, unsigned int id2)
{
  static int id_count = 0;

  unsigned int nb_vert = vertex_list.size();
  
  if((id1>=nb_vert||id2>=nb_vert))
    {
      std::cerr << "Routeur " << id1 << " or " << id2 << " do not exist." << std::endl;
      return -1;
    }
  if(id1==id2)
    {
      std::cerr << "Trying to link routeur " << id1 << "with itself; reflexivity is forbidden" << std::endl;
      return -1;
    }
  
  Cable c;
  c.id=count;
  c.length=default_cable_length;
  
  auto tmp1 = add_edge(vertex_list[id1], vertex_list[id2], c, network_graph);
  edge_list.push_back(tmp1.first);
  auto tmp2 = add_edge(vertex_list[id2], vertex_list[id1], c, network_graph);
  edge_list.push_back(tmp2.first);
  count++;
  
  return (tmp1.second==false||tmp2.second==false)?c.id:-1;
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
  if(!read_graphviz(in, network_graph, dp))
    {
      std::cerr << "Error while reading the graph at : " << path << std::endl;
      return -1;
    }
  in.close();
  return 0;
} 

int Network::save_to_file(std::string path)
{
  std::ofstream out(path,std::ofstream::out);
  write_graphviz_dp(out, network_graph, dp);
  out.close();
  return 0;
}
