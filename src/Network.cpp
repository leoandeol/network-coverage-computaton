#include "Network.hpp"

Network::Network() : vertex_list(2),edge_list(2)
{
  dp = boost::dynamic_properties(boost::ignore_other_properties);
  
  dp.property("node_id", boost::get(boost::vertex_index, network_graph));
  dp.property("label", boost::get(&Routeur::name, network_graph));
  dp.property("isMulticast", boost::get(&Routeur::isMulticast, network_graph));
  
  dp.property("edge_id", boost::get(&Cable::id, network_graph));
  dp.property("label", boost::get(&Cable::length, network_graph));
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
  //if(id1>=vertex_list.size())
  //  {
  
  //Initialisation du routeur 1
  Routeur r;
  r.id = id1;
  r.name = std::string("add_cabler1");
  r.isMulticast = true;
  //Transformation du routeur en sommet (dans un graphe) + ajout dans la liste de sommet vertex_list en 1ere position
  //+ ajouteur au graph
  auto tmp = add_vertex(r, network_graph);
  vertex_list[0]=tmp;
  //  }
  //if(id2>=vertex_list.size())
  //  {
  
  //Initialisation du routeur 2
  Routeur r2;
  r2.id = id2;
  r2.name = "add_cabler2";
  r2.isMulticast = true;
  //Transformation du routeur en sommet (dans un graphe) + ajout dans la liste de sommet vertex_list en 2e position
  //+ ajouteur au graph
  auto tmp2 = add_vertex(r2, network_graph);
  vertex_list[1]=tmp2;
  //  }
  
  //Initialisation du "cable" liant le routeur 1 et le routeur 2
  Cable c;
  c.id = 42;
  c.length= 420;
  
  //Liaison des deux routeurs dans vertex_list via c
  //+Ajout dans le graph
  auto tmp3 = add_edge(vertex_list[0], vertex_list[1], c, network_graph);
  edge_list.push_back(tmp3.first);
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
  if(!read_graphviz(in, network_graph, dp, "node_id"))
    {
      std::cerr << "Error while reading the graph at : " << path << std::endl;
      return -1;
    }
  return 0;
} 

int Network::save_to_file(std::string path)
{
  std::cout << path << std::endl;
  std::ofstream out(path);
  write_graphviz_dp(std::cout, network_graph, dp, "node_id");
  // write returns void
  /* {
      std::cerr << "Error while writing the graph at : " << path << std::endl;
      return -1;
    }*/
  return 0;
}
