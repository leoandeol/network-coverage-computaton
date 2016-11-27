#include "Network.hpp"

Network::Network(NetworkInfo& n) : vertex_list(), vertex_exist(), edge_list()
{
  (boost::get(&NetworkInfo, network_graph))[network_graph].name = n.name;
  (boost::get(&NetworkInfo, network_graph))[network_graph].location = n.location;

  dp = boost::dynamic_properties(boost::ignore_other_properties);

  dp.property("node_id", boost::get(&Routeur::id, network_graph));
  dp.property("label", boost::get(&Routeur::name, network_graph));
  dp.property("is_multicast", boost::get(&Routeur::is_multicast, network_graph));

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
  boost::get(&Routeur,network_graph,vertex_list[id]).name = name;
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
  c.id=id_count;
  c.length=default_cable_length;

  auto tmp1 = add_edge(vertex_list[id1], vertex_list[id2], c, network_graph);
  edge_list.push_back(tmp1.first);
  auto tmp2 = add_edge(vertex_list[id2], vertex_list[id1], c, network_graph);
  edge_list.push_back(tmp2.first);
  id_count++;

  return (tmp1.second==false||tmp2.second==false)?c.id:-1;
}

Routeur* Network::get_routeur(unsigned int id)
{
  return (boost::get(&Routeur,network_graph,vertex_list[id]));
}

Cable* Network::get_cable(unsigned int id)
{
  return (boost::get(&Cable,network_graph,edge_list[id]));
}

int Network::remove_routeur(unsigned int)
{
  return 0;
}

int Network::remove_cable(unsigned int)
{
  return 0;
}

std::vector<unsigned> get_path(unsigned int source, unsigned int destination)
{
    vertex_t start_node = vertex_list[source];
    vertex_t end_node = vertex_list[destination];

    std::vector<vertex_t> predecessors(boost::num_vertices(network_graph_t));
    std::vector<int> distances(boost::num_vertices(network_graph_t));

    IndexMap indexMap = boost::get(boost::vertex_index,network_graph_t);
    PredecessorMap predecessorMap(&predecessors[0],indexMap);
    DistanceMap distanceMap(&distances[0],indexMap);

    boost::dijkstra_shortest_paths(my_graph, start_node, boost::distance_map(distanceMap).predecessor_map(predecessorMap));
    std::vector<edge_t> path;

    path = boost::get_edge_path(end_node,predecessorMap);

    return boost::segment_list_from_edges(path);
}

int Network::load_from_file(std::string& path)
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

void Network::save_to_file(std::string& path)
{
  std::ofstream out(path,std::ofstream::out);
  write_graphviz_dp(out, network_graph, dp);
  out.close();
  return 0;
}
