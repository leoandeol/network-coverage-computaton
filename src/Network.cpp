#include "Network.hpp"

Network::Network() : Network(NetworkInfo("GraphPropertyName","GraphPropertyLocation"))
{
}

Network::Network(NetworkInfo n) : network_graph(0,n), vertex_list(), vertex_exist(), edge_list()
{
  dp = boost::dynamic_properties(boost::ignore_other_properties);

  dp.property("label", boost::get(&Routeur::name, network_graph));
  dp.property("is_multicast", boost::get(&Routeur::is_multicast, network_graph));

  dp.property("label", boost::get(&Cable::length, network_graph));
}

Network::~Network()
{

}

std::string& Network::add_routeur()
{
  static unsigned int id_count = 0;
  Routeur r;
  r.name = std::to_string(id_count);
  r.is_multicast=default_routeur_is_multicast;
  vertex_t v_desc = add_vertex(r,network_graph);
  vertex_list[r.name] = v_desc;
  id_count++;
  return r.name;
}

int Network::add_routeur(std::string& name)
{
  Routeur r;
  r.name = name;
  r.is_multicast=default_routeur_is_multicast;
  vertex_t v_desc = add_vertex(r,network_graph);
  vertex_list[name] = v_desc;
  return 0;
}

int Network::add_cable(std::string& id1, std::string& id2)
{
  unsigned int nb_vert = vertex_list.size();

  // to fix
  if((id1>=nb_vert||id2>=nb_vert))
    {
      std::cerr << "Routeur " << id1 << " or " << id2 << " does not exist." << std::endl;
      return -1;
    }
  if(id1==id2)
    {
      std::cerr << "Trying to link routeur " << id1 << "with itself; reflexivity is forbidden" << std::endl;
      return -1;
    }

  Cable c;
  c.length=default_cable_length;

  auto tmp1 = add_edge(vertex_list[id1], vertex_list[id2], c, network_graph);
  edge_list.push_back(tmp1.first);
  auto tmp2 = add_edge(vertex_list[id2], vertex_list[id1], c, network_graph);
  edge_list.push_back(tmp2.first);

  return (tmp1.second==false||tmp2.second==false)?0:-1;
}

template <typename Structure, typename Attribute>
Attribute& Network::get_attribute(std::string& id)
{
  return boost::get(&Structure::Attribute,network_graph,vertex_list[id]);
}

template <typename Structure, typename Attribute>
void Network::set_attribute(std::string& id, Attribute value)
{
  boost::put(&Structure::Attribute,network_graph,vertex_list[id], value);
}

int Network::remove_routeur(std::string&)
{
  return 0;
}

int Network::remove_cable(std::string&)
{
  return 0;
}
/*
std::vector<unsigned int> Network::get_path(unsigned int source, unsigned int destination)
{
    vertex_t start_node = vertex_list[source];
    vertex_t end_node = vertex_list[destination];

    std::vector<vertex_t> predecessors(boost::num_vertices(network_graph));
    std::vector<unsigned int> distances(boost::num_vertices(network_graph));

    boost::dijkstra_shortest_paths(network_graph,start_node,boost::weight_map(boost::get(&Cable::length,network_graph))
				   .distance_map(boost::make_iterator_property_map(distances.begin(),boost::get(boost::vertex_index,network_graph)))
				   .predecessor_map(boost::make_iterator_property_map(predecessors.begin(),boost::get(boost::vertex_index,network_graph))));

    typedef std::vector<unsigned int> path_t;
    path_t path;

    for(vertex_t u = end_node;)
}*/

int Network::load_from_file(std::string& path)
{
  std::ifstream in(path);
  if(!read_graphviz(in, network_graph, dp, "label"))
    {
      std::cerr << "Error while reading the graph at : " << path << std::endl;
      return -1;
    }
std::cout << "Reussi ?" << std::endl;
  in.close();
  return 0;
}

void Network::save_to_file(std::string& path)
{
  std::ofstream out(path,std::ofstream::out);
  write_graphviz_dp(out, network_graph, dp, "label");
  out.close();
}
