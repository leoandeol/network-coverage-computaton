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

std::string Network::add_routeur()
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
  
  vertex_list_t::const_iterator r1 = vertex_list.find(id1);
  vertex_list_t::const_iterator r2 = vertex_list.find(id2);
  vertex_list_t::const_iterator end = vertex_list.end();
  // to fix
  if((r1==end||r2==end))
    {
      std::cerr << "Routeur " << id1 << " or " << id2 << " does not exist." << std::endl;
      return -1;
    }
  if(r1==r2)
    {
      std::cerr << "Trying to link routeur " << id1 << "with itself; reflexivity is forbidden" << std::endl;
      return -1;
    }

  Cable c;
  c.length=default_cable_length;

  auto tmp1 = add_edge(vertex_list[id1], vertex_list[id2], c, network_graph);

  std::string nom1 = id1+ "->"+id2;
  std::pair<std::string, edge_t> t1 = {nom1, tmp1.first};
  edge_list.insert(t1);

  auto tmp2 = add_edge(vertex_list[id2], vertex_list[id1], c, network_graph);

  std::string nom2 = id2+ "->"+id1;
  std::pair<std::string, edge_t> t2 = {nom2, tmp2.first};
  edge_list.insert(t2);

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

/*std::vector<std::string> Network::get_path(std::string &source, std::string &destination)
{
    vertex_t start_node = vertex_list[source];
    vertex_t end_node = vertex_list[destination];

    IndexMap id_map = boost::get(boost::vertex_index,network_graph);

    std::vector<vertex_t> predecessors(boost::num_vertices(network_graph));
    std::vector<int> distances(boost::num_vertices(network_graph));

    boost::dijkstra_shortest_paths(network_graph,start_node,boost::weight_map(boost::get(&Cable::length,network_graph))
				   .distance_map(boost::make_iterator_property_map(distances.begin(),id_map))
				   .predecessor_map(boost::make_iterator_property_map(predecessors.begin(),id_map)));

    typedef std::vector<std::string> path_t;
    path_t path;

    for(vertex_t u = predecessors[end_node]; u != end_node ; end_node =u, u=predecessors[end_node])
      {
	path.push_back(network_graph[u].name);
      }

    return path;
}
*/
int Network::load_from_file(std::string& path)
{

std::cout << "Conversion of the file in network: " << std::endl <<std::endl;

  std::ifstream in(path);
  if(!read_graphviz(in, network_graph, dp, "label"))
    {
      std::cerr << "Error while reading the graph at : " << path << std::endl;
      return -1;
    }
	//!< We put the edges and the vertices in their unordered_map edge_list and vertex_list

	//!< Inserting the verteces in the vertex_list_t
	std::pair<boost::graph_traits<network_graph_t>::vertex_iterator, boost::graph_traits<network_graph_t>::vertex_iterator> it = boost::vertices(network_graph);

	for(; it.first != it.second; ++it.first){
		Routeur r = network_graph[*it.first];
		std::pair<std::string, vertex_t> v = {r.name, *it.first};
		vertex_list.insert(v);
	}
	std::cout << "Number of verteces in the list : " << vertex_list.size() << std::endl;
	std::cout << "Number of verteces in the network : " << boost::num_vertices(network_graph) << std::endl << std::endl;


	//!< Insering the verteces in the vertex_list_t
	std::pair<boost::graph_traits<network_graph_t>::edge_iterator, boost::graph_traits<network_graph_t>::edge_iterator> it2 = boost::edges(network_graph);

	for(; it2.first != it2.second; ++it2.first){
		//!<In order to name the ege
		//!<We capture the source and the target of the edge
		//!<To access to their name
		//!< Following the format : "source.name->target.name"
		vertex_t source = boost::source(*it2.first, network_graph);
		vertex_t target = boost::target(*it2.first, network_graph);
		Routeur s = network_graph[source];
		Routeur t = network_graph[target];

		std::string edge_name = s.name+"->"+t.name;
		std::pair<std::string, edge_t> e = {edge_name, *it2.first};
		edge_list.insert(e);
	}
	std::cout << "Number of edges in the list : " << edge_list.size() << std::endl;
	std::cout << "Number of edges in the network: " << boost::num_edges(network_graph) << std::endl <<std::endl <<std::endl;


  in.close();
  return 0;
}

void Network::save_to_file(std::string& path)
{
  std::ofstream out(path,std::ofstream::out);
  write_graphviz_dp(out, network_graph, dp, "label");
  out.close();
}


bool Network::is_connected()
{

	std::cout << "Control of the network connection: " << std::endl;

	if(vertex_list.empty()){
		return false;
	}
	std::vector<std::string> checked;

	vertex_list_t::iterator vertex = vertex_list.begin();
	checked.push_back(network_graph[vertex->second].name);

	for(vertex = vertex_list.begin(); vertex_list.size() != checked.size() && vertex != vertex_list.end(); ++vertex){

		Routeur c = network_graph[vertex->second];
		
		if(std::find(checked.begin(), checked.end(), c.name) != checked.end()){
			for(edge_list_t::iterator current = edge_list.begin(); vertex_list.size() != checked.size() && current != edge_list.end();++current){
				vertex_t source = boost::source(current->second, network_graph);
				Routeur s = network_graph[source];
				if(c.name == s.name){ 
					vertex_t target = boost::target(current->second, network_graph);
					Routeur t = network_graph[target];
		
					if(std::find(checked.begin(), checked.end(), t.name) == checked.end()){
						checked.push_back(t.name);
					}
				}
			}
		}
	}

	std::cout << "Total number of checked verteces : " << checked.size() << std::endl;
	std::cout << "Total number of verteces : " << vertex_list.size() << std::endl <<std::endl;

	std::cout << std::endl<< std::endl<< std::endl<< std::endl;

	readAll_vertex();

	std::cout << std::endl<< std::endl<< std::endl<< std::endl;

	readAll_edge();

	return (vertex_list.size() == checked.size());
}


void Network::readAll_vertex(){

	vertex_list_t::iterator vertex = vertex_list.begin();

	for(; vertex != vertex_list.end(); ++vertex){
		Routeur c = network_graph[vertex->second];
		std::cout << c.name << std::endl;
	}
}

void Network::readAll_edge(){
	edge_list_t::iterator edge = edge_list.begin();
	for(; edge != edge_list.end(); ++ edge){
		std::cout << edge->first << std::endl;
	}
}
