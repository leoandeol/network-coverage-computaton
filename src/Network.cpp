#include "Network.hpp"

template <class Vertex, class Edge> 
Network<Vertex,Edge>::Network() : Network(NetworkInfo("GraphPropertyName","GraphPropertyLocation"))
{
}

template <class Vertex, class Edge> 
Network<Vertex,Edge>::Network<(NetworkInfo n) : network_graph(0,n), vertex_list(), vertex_exist(), edge_list()
{
	dp = boost::dynamic_properties(boost::ignore_other_properties);

	dp.property("color", boost::get(&Routeur::color, network_graph));
	dp.property("label", boost::get(&Routeur::name, network_graph));
	dp.property("is_multicast", boost::get(&Routeur::is_multicast, network_graph));

	dp.property("label", boost::get(&Cable::length, network_graph));
	dp.property("color", boost::get(&Cable::color, network_graph));
}

	template <class Vertex, class Edge> 
	Network<Vertex,Edge>::~Network()
	{

	}

template <class Vertex, class Edge> 
std::string Network<Vertex,Edge>::add_routeur()
{
	static unsigned int id_count = 0;
	Routeur r;
	r.name = std::to_string(id_count);
	vertex_t v_desc = add_vertex(r,network_graph);
	vertex_list[r.name] = v_desc;
	id_count++;
	return r.name;
}

template <class Vertex, class Edge> 
int Network<Vertex,Edge>::add_routeur(std::string& name)
{
	Routeur r;
	r.name = name;
	vertex_t v_desc = add_vertex(r,network_graph);
	vertex_list[name] = v_desc;
	return 0;
}

template <class Vertex, class Edge> 
int Network<Vertex,Edge>::add_cable(std::string& id1, std::string& id2)
{
  
	typename vertex_list_t::const_iterator r1 = vertex_list.find(id1);
	typename vertex_list_t::const_iterator r2 = vertex_list.find(id2);
	typename vertex_list_t::const_iterator end = vertex_list.end();
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

	auto tmp1 = add_edge(vertex_list[id1], vertex_list[id2], c, network_graph);

	std::string nom1 = create_edge_name(id1, id2);
	std::pair<std::string, edge_t> t1 = {nom1, tmp1.first};
	edge_list.insert(t1);

	auto tmp2 = add_edge(vertex_list[id2], vertex_list[id1], c, network_graph);

	std::string nom2 = create_edge_name(id2, id1);
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
void Network<Vertex,Edge>::set_attribute(std::string& id, Attribute value)
{
	boost::put(&Structure::Attribute,network_graph,vertex_list[id], value);
}

template <class Vertex, class Edge> 
std::string Network<Vertex,Edge>::get_network_name(){
	return network_graph[boost::graph_bundle].name;
}

template <class Vertex, class Edge> 
int Network<Vertex,Edge>::remove_routeur(std::string&)
{
	return 0;
}

template <class Vertex, class Edge> 
int Network<Vertex,Edge>::remove_cable(std::string&)
{
	return 0;
}

std::vector<std::string> Network<Vertex, Edge>::get_path(std::string &source, std::string &destination)
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
	
	path.push_back(destination);

    for(vertex_t u = predecessors[end_node]; u != end_node ; end_node =u, u=predecessors[end_node])
    {
		path.push_back(network_graph[u].name);
    }

	std::reverse(path.begin(), path.end());

    return path;
}
  
std::vector<std::string> Network<Vertex,Edge>::get_all_edges(){
	typename edge_list_t::iterator it = edge_list.begin();
	std::vector<std::string> l;
	for(; it!=edge_list.end(); ++it){
		l.push_back(it->first);
	}
	return l;
}
void Network<Vertex,Edge>::color_path(std::vector<std::string> &path, std::string &color)
{
	std::vector<std::string>::iterator it = path.begin();
	std::string name;
	Routeur r, r2;
	for(; it != path.end(); ++it){
		r = network_graph[vertex_list[*it]];
		network_graph[vertex_list[*it]].color = color;
		if(it != --path.end() && it != path.end()){
			r2 = network_graph[vertex_list[*(std::next(it, 1))]];
			name = create_edge_name(r.name,r2.name);
			network_graph[edge_list[name]].color = color;
		}
	}
}
void Network<Vertex,Edge>::clean_all_colors(){
	typename vertex_list_t::iterator v = vertex_list.begin();
	typename edge_list_t::iterator e = edge_list.begin();
	for(; v != vertex_list.end(); ++v){
		network_graph[v->second].color = "";
	}
	for(; e != edge_list.end(); ++e){
		network_graph[e->second].color = "";
	}
}
void Network<Vertex,Edge>::clean_all_colors(std::vector<std::string> &path)
{
	std::string color = "";
	color_path(path, color);
}

int Network<Vertex,Edge>::load_from_file(std::string& path)
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
	std::pair<typename boost::graph_traits<network_graph_t>::vertex_iterator, typename boost::graph_traits<network_graph_t>::vertex_iterator> it = boost::vertices(network_graph);

	for(; it.first != it.second; ++it.first){
		Routeur r = network_graph[*it.first];
		std::pair<std::string, vertex_t> v = {r.name, *it.first};
		vertex_list.insert(v);
	}
	std::cout << "Number of verteces in the list : " << vertex_list.size() << std::endl;
	std::cout << "Number of verteces in the network : " << boost::num_vertices(network_graph) << std::endl << std::endl;


	//!< Insering the verteces in the vertex_list_t
	std::pair<typename boost::graph_traits<network_graph_t>::edge_iterator, typename boost::graph_traits<network_graph_t>::edge_iterator> it2 = boost::edges(network_graph);

	for(; it2.first != it2.second; ++it2.first){
		//!<In order to name the edge
		//!<We capture the source and the target of the edge
		//!<To access to their name
		//!< Following the format : "source.name->target.name"
		

		network_graph[*it2.first].length = 1;	
	
		std::string edge_name = create_edge_name(*it2.first);
		std::pair<std::string, edge_t> e = {edge_name, *it2.first};
		edge_list.insert(e);
	}
	std::cout << "Number of edges in the list : " << edge_list.size() << std::endl;
	std::cout << "Number of edges in the network: " << boost::num_edges(network_graph) << std::endl <<std::endl <<std::endl;


	in.close();
	return 0;
}

void Network<Vertex,Edge>::save_to_file(std::string& path)
{
	std::ofstream out(path,std::ofstream::out);
	write_graphviz_dp(out, network_graph, dp, "label");
	out.close();
}


bool Network<Vertex,Edge>::is_connected()
{

	std::cout << "Control of the network connection: " << std::endl<<std::endl;

	if(vertex_list.empty()){
		return false;
	}
	std::vector<std::string> checked;

	typename vertex_list_t::iterator vertex = vertex_list.begin();
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


template <class Vertex, class Edge> 
void Network<Vertex,Edge>::readAll_vertex(){

	typename vertex_list_t::iterator vertex = vertex_list.begin();

	for(; vertex != vertex_list.end(); ++vertex){
		Routeur c = network_graph[vertex->second];
		std::cout << c.name << std::endl;
	}
}

template <class Vertex, class Edge> 
void Network<Vertex,Edge>::readAll_edge(){
	typename edge_list_t::iterator edge = edge_list.begin();
	for(; edge != edge_list.end(); ++ edge){
		std::cout << edge->first << std::endl;
	}
}

template <class Vertex, class Edge> 
std::string Network<Vertex,Edge>::create_edge_name(edge_t e){

	vertex_t source = boost::source(e, network_graph);
	vertex_t target = boost::target(e, network_graph);
	Routeur s = network_graph[source];
	Routeur t = network_graph[target];

	std::string edge_name = s.name+"->"+t.name;

	return edge_name;
}

template <class Vertex, class Edge> 
std::string Network<Vertex,Edge>::create_edge_name(std::string source, std::string target){
	
	std::string edge_name = source+"->"+target;
	return edge_name;
}

template <class Vertex, class Edge> 
std::vector<std::vector<std::string>> Network<Vertex,Edge>::minimum_tree(std::vector<std::string> &source, std::vector<std::string> &targets, std::vector<std::vector<std::string>>& tree){
//!< Implémentation de Takahashi Matsuyama
	typedef std::vector<std::string> path;
	if(source.empty() && !targets.empty()){
		return NULL;
	}
	if(targets.empty()){
		return tree;
	}	

	path p, test;
	path::iterator theChosenOne;
	path::iterator it = targets.begin();

	//!< We choose the first path, the smallest possible
	for(; it != targets.end(); ++it){
		test = get_path(source.at(0), *it);
		if(test.size() < p.size()){
			p = test;
			theChosenOne=it;
		}
	}
	targets.erase(theChosenOne);
	
	tree.push_back(p);
	source.erase(p.begin());
	
	source.insert(source.end(), p.begin()+1, p.end()-1);
	
	return minimum_tree(source, targets, tree);
}


  void color_tree(std::vector<std::vector<std::string>> &tree, std::string &color){

	std::vector<std::vector<std::string>>::iterator it;
	for(it = tree.begin(); it != tree.end(); ++it){
		color_path(*it, color);
	}
}






















