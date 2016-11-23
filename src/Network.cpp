#include "Network.hpp"

// CLASS

Network::Network() : vertex_list(10), vertex_exist(10), edge_list()
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

//TODO remove that and use the one by reference, because more the the id needs to be passed
int Network::add_routeur(unsigned int id)
{
	if(id>(vertex_list.size()-1))
	{
		vertex_list.resize(id);
		vertex_exist.resize(id);
	}
	if(vertex_exist[id]==false)
	{
		Routeur r;
		r.id = id;
		r.name = std::to_string(id);
		r.isMulticast = true;
		vertex_list[id]=add_vertex(r,network_graph);
		vertex_exist[id]=true;
		return 0;
	}
	else
	{
		return -1;
	}
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
	static int count = 1;

	add_routeur(id1);
	add_routeur(id2);
	
	Cable c;
	c.id=count;
	//TBD
	c.length=1;

	auto tmp1 = add_edge(vertex_list[id1], vertex_list[id2], c, network_graph);
	edge_list.push_back(tmp1.first);
	auto tmp2 = add_edge(vertex_list[id2], vertex_list[id1], c, network_graph);
	edge_list.push_back(tmp2.first);
	count++;
	
	return (tmp1.second==false||tmp2.second==false)?0:-1;
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
