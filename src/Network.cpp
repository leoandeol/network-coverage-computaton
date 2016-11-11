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

int Network::add_routeur(Routeur& r)
{
  
}

int Network::add_routeur(std::string& name)
{

}

int Network::add_cable(Cable& c)
{
	
}

int Network::add_cable(Routeur& src, Routeur& dest)
{

}

int Network::add_cable(std::string& src, std::string& dest)
{
	
}

Routeur* Network::get_routeur(int id)
{

}

Cable* Network::get_cable(int id)
{

}

int Network::remove_routeur(int id)
{

}

int Network::remove_routeur(Routeur& r)
{

}

int Network::remove_cable(int id)
{

}

int Network::remove_cable(Cable& c)
{

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
	if(!write_graphviz_dp(out, network_graph, dp, "name"))
	{
		std::cerr << "Error while writing the graph at : " << path << std::endl;
		return -1;
	}
	return 0;
}
