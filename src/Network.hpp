#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream> // std::cout
#include <fstream> // std::i/ofstream
#include <utility>
#include <algorithm> // std::find
#include <string> // std::string
#include <unordered_map>
#include <boost/graph/graph_traits.hpp> // vertex and edge descriptors
#include <boost/graph/adjacency_list.hpp> // adjacency_list
#include <boost/graph/dijkstra_shortest_paths.hpp> // djikstra shortest paths
#include <boost/graph/graphviz.hpp> // import/export .dot
#include <boost/graph/kruskal_min_spanning_tree.hpp> //krustal minimum tree

#include "structs.hpp"

/** The class handling the network representation (graph) */
template <class Vertex = Default_Vertex, class Edge = Default_Edge> class Network {
	
	typedef boost::adjacency_list<boost::vecS,
								  boost::vecS,
								  boost::undirectedS,
								  Vertex,
								  Edge, NetworkInfo> network_graph_t;


	typedef typename boost::graph_traits<network_graph_t>::vertex_descriptor vertex_t;
	typedef typename boost::graph_traits<network_graph_t>::edge_descriptor edge_t;
	typedef typename boost::property_map<network_graph_t,boost::vertex_index_t>::type IndexMap;

	typedef typename std::unordered_map<std::string, vertex_t> vertex_list_t;
	typedef typename std::unordered_map<std::string, edge_t> edge_list_t;
	

	/**< The typedef for an undirected network graph*/
	typedef boost::adjacency_list<boost::vecS,
								  boost::vecS,
								  boost::undirectedS,
								  Vertex,
								  Edge, NetworkInfo> undirected_network_graph_t;

	/**< The typedef for the edge_descriptor of an undirected network graph*/
	typedef typename boost::graph_traits<undirected_network_graph_t>::edge_descriptor u_edge_t;
	
public:
	/** 
		\brief Default Constructor, calls the other constructor with default parameters
	*/
	Network() : Network(NetworkInfo("DefaultGraphPropertyName","DefaultGraphPropertyLocation"))
	{
		
	}
	/**
	   \brief Constructor
	   \param i struct containing informations about the graph such as its name
	*/
	Network(NetworkInfo i) : network_graph(i), vertex_list(), vertex_exist(), edge_list()
	{
		dp = boost::dynamic_properties(boost::ignore_other_properties);

		dp.property("color", boost::get(&Routeur::color, network_graph));
		dp.property("label", boost::get(&Routeur::name, network_graph));

		dp.property("label", boost::get(&Cable::length, network_graph));
		dp.property("color", boost::get(&Cable::color, network_graph));
	
		/**< The property length linked to label is added for undirected networks */
		dp.property("color", boost::get(&Cable::color, undirected_network_graph));
		dp.property("label", boost::get(&Cable::length, undirected_network_graph));
	}
	
	/**
	   \brief Destructor
	*/
	~Network()
	{

	}
	
	/**
	   \brief Creates a new routeur and returns its id
	   \return The new routeur's name or -1 if there was an error
	*/
	std::string add_routeur()
	{
		static unsigned int id_count = 0;
		Routeur r;
		r.name = std::to_string(id_count);
		vertex_t v_desc = add_vertex(r,network_graph);
		vertex_list[r.name] = v_desc;
		id_count++;
		return r.name;
	}
	/**
	   \brief Creates a new routeur with a set name and returns its id
	   \param name The new routeur's name
	   \return 0 in case of success, else -1
	*/
	
	int add_routeur(std::string& name)
	{
		Routeur r;
		r.name = name;
		vertex_t v_desc = add_vertex(r,network_graph);
		vertex_list[name] = v_desc;
		return 0;
	}
	/**
	   \brief Creates a new cable between two routeurs, and returns its id
	   \param id1 A routeur's name
	   \param id2 Another routeur's name
	   \param length The length of the cable
	   \param come_back True or false if you want to have a->b and b->a
	   \return 0 in case of success, else -1
	*/
	
	int add_cable(std::string& id1,std::string& id2, int length = 1, bool come_back = true)
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
		c.length = length;
		auto tmp1 = add_edge(vertex_list[id1], vertex_list[id2], c, network_graph);

		std::string nom1 = create_edge_name(id1, id2);
		std::pair<std::string, edge_t> t1 = {nom1, tmp1.first};
		edge_list.insert(t1);
    
		return (tmp1.second==false)?0:-1;
	}
	
	
	/**
	   \brief Gives the value of an attribute of an element, of type Structure
	   \param id The element's name
	   \return A reference to the attribute's value
	*/
	template <typename Structure, typename Attribute>
	Attribute& get_attribute(std::string& id)
	{
		return boost::get(&Structure::Attribute,network_graph,vertex_list[id]);
	}
	
	/**
	   \brief Sets the value of an attribute of an element, of type Structure
	   \param id The element's name
	   \param value The new value of the attribute
	*/
	template <typename Structure, typename Attribute>
	void set_attribute(std::string& id, Attribute value)
	{
		boost::put(&Structure::Attribute,network_graph,vertex_list[id], value);
	}
	
	/**
	   \brief Gives the name of the network
	   \return A string which contains the name of the network
	*/
	std::string get_network_name()
	{
		return network_graph[boost::graph_bundle].name;
	}
	/**
	   \brief Change the name of the network
	*/
	void set_network_name(std::string name){	
		network_graph[boost::graph_bundle].name = name;
	}
	/**
	   \brief Gives a pointer to the cable with the given ID
	   \param id The cable's name
	   \return A pointer to the wanted cable, or nullptr if non-existent
	*/
	int remove_routeur(std::string& id)
	{
		return 0;
	}
	
	/**
	   \brief Removes the cable with the given ID
	   \param id The cable's name
	   \return 0 if successfully cable, else -1
	*/
	int remove_cable(std::string& id)
	{
		return 0;
	}
	
	/**
	   \brief calculates the shortest path between two routeurs of the network
	   \param source The source's name
	   \param destination The destination's name
	   \return a vector that represents the path between those routeurs
	*/
	std::vector<std::string> get_path(std::string &source,std::string &destination)
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

	/**
	   \brief Loads a graph in the DOT format, from the path given as parameter
	   \param path The path to the .dot file
	   \return 0 if the file was loaded successfully, else -1
	*/
	int load_from_file(std::string& path)
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
	
	/**
	   \brief Saves a graph in the DOT format, to the path given as parameter
	   \param path The path to the wanted .dot file
	*/
	void save_to_file(std::string& path)
	{
		std::ofstream out(path,std::ofstream::out);
		write_graphviz_dp(out, network_graph, dp, "label");
		out.close();
	}

	/**
	   \brief Return a boolean if the graph is connected or not
	   \return true if the graph is connected, else return false
	*/
	bool is_connected()
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
				for(typename edge_list_t::iterator current = edge_list.begin(); vertex_list.size() != checked.size() && current != edge_list.end();++current){
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
	
	/**
	   \brief Print the name of all the verteces which are in in the unordered_map
    */
	void readAll_vertex()
	{
		typename vertex_list_t::iterator vertex = vertex_list.begin();
		
		for(; vertex != vertex_list.end(); ++vertex){
			Routeur c = network_graph[vertex->second];
			std::cout << c.name << std::endl;
		}
	}
	
	/**
	   \brief Print the name of all the edges which are in in the unordered_map
    */
	void readAll_edge()
	{
		typename edge_list_t::iterator edge = edge_list.begin();
		for(; edge != edge_list.end(); ++ edge){
			std::cout << edge->first << std::endl;
		}
	}

	/**
	   \brief Calculate a partial minimum tree from a source to targets
	   \param source The string name of the source 
	   \param targets A vector containing the targets
	   \param tree An empty network which will be the partial minimum tree
	   \return The tree as a Network
	*/
	Network* partial_minimum_tree(std::vector<std::string> source, std::vector<std::string> targets, Network<Routeur, Cable>* tree)
	{
		//!< Takahashi Matsuyama algorithm implementation
		typedef std::vector<std::string> path;

		
		if(targets.empty() || source.empty()){
			return tree;
		}
		path p(0);
		path test;
		path::iterator theChosenOne;

<<<<<<< HEAD
//			std::cout << *it << std::endl;
//			std::cout << "Targets size :" << targets.size() << std::endl;
//			std::cout << "Source size :" << source.size() << std::endl;
	
		//!< We choose the first smallest path from a source to a target
		for(path::iterator it = targets.begin(); it != targets.end(); ++it){
		//			std::cout << *it << std::endl;
		//			std::cout << "Targets size :" << targets.size() << std::endl;
		//			std::cout << "Source size :" << source.size() << std::endl;
		//!< We choose the first path, the smallest possible
		for(; it != targets.end(); ++it){
>>>>>>> 4194a37e977eb1bc676c3add3540d0a33dcfbd47
			for(int unsigned i = 0; i < source.size(); i++){	
				test = get_path(source.at(i), *it);
				//				std::cout << "test" << std::endl;
				if(p.size() == 0 || test.size() < p.size()){
					p = test;
					theChosenOne=it;
				}
			}
		}
<<<<<<< HEAD
//		std::cout << *theChosenOne << "b" << std::endl;
//		std::cout << std::endl;
//		path::iterator IT = p.begin();
//		for(; IT != p.end(); ++IT){
//			std::cout << *IT << std::endl;
//		}

		//!< The smallest path take a source and a target, we remove the target from the list
		targets.erase(theChosenOne);
//		std::cout << std::endl;

		//!< The smallest path is added to the tree (the network)
=======
		//		std::cout << *theChosenOne << "b" << std::endl;
		//		std::cout << std::endl;
		//		path::iterator IT = p.begin();
		//		for(; IT != p.end(); ++IT){
		//			std::cout << *IT << std::endl;
		//		}
		targets.erase(theChosenOne);
		//		std::cout << std::endl;
>>>>>>> 4194a37e977eb1bc676c3add3540d0a33dcfbd47
		tree->add_path(p);
		
		//!< Is added the path's routers to the list of source
		source.insert(source.end(), ++p.begin(),p.end());	
	
		return partial_minimum_tree(source, targets, tree);
	}

	/**
	   \brief Add a path to the current network
	   \param path A vector of string containing the name of the routers ordered
	*/
	void add_path(std::vector<std::string> &path)
	{
		std::vector<std::string>::iterator it, it2;
		it = path.begin();
		it2 = it+1;
		//	std::cout << "it2" << *it2 << std::endl;
		//	std::cout << "it" << *it << std::endl;
		for(; it2!=path.end()&&it != path.end(); ++it, ++it2){
			add_routeur(*it);
			if(it!=it2){
				add_routeur(*it2);
				add_cable(*it,*it2);
			}
		}
	}

	/**
	   \brief Create the edge's name used in the edge_list_t
	   \brief The source and the target verteces are extracted to create a name following the format
	   \brief source.name->target.name
	   \param e An edge_t
	   \return source.name->target.name
	*/
	
	std::string create_edge_name(edge_t e)
	{
		vertex_t source = boost::source(e, network_graph);
		vertex_t target = boost::target(e, network_graph);
		Vertex s = network_graph[source];
		Vertex t = network_graph[target];

		std::string edge_name = s.name+"->"+t.name;

		return edge_name;
	}

	/**
	   \brief Create the edge's name using the source and the target vertex names following the format
	   \brief source->target 
	   \param source The name of the source
	   \param target The name of the target
	   \return a string : source->target
	*/
	std::string create_edge_name(std::string source, std::string target)
	{
		std::string edge_name = source+"->"+target;
		return edge_name;
	}

	/**
	   \brief Color the path you want, changing the routeur::color and cable::color in the graph
	   \param path A vector containing a list of vector names ordered from the source to the target
	   \param color The color of the path
    */
	void color_path(std::vector<std::string> &path, std::string &color)
	{
		std::string name;
		Vertex r, r2;
		for(std::vector<std::string>::iterator it = path.begin(); it != path.end(); ++it){
			r = network_graph[vertex_list[*it]];
			network_graph[vertex_list[*it]].color = color;
			if(it != --path.end() && it != path.end()){
				r2 = network_graph[vertex_list[*(std::next(it, 1))]];
				name = create_edge_name(r.name,r2.name);
				network_graph[edge_list[name]].color = color;
			}
		}
	}

	/**
	   \brief Reset the colors of all the routers and cables
	*/
	void clean_all_colors()
	{
		
		for(typename vertex_list_t::iterator v = vertex_list.begin(); v != vertex_list.end(); ++v){
			network_graph[v->second].color = "";
		}
		for(typename edge_list_t::iterator e = edge_list.begin(); e != edge_list.end(); ++e){
			network_graph[e->second].color = "";
		}
	}

	/**
	   \brief Reset all the color added previously (on the routeur and the cable)
	   \param path The path (source to target ordered) you want to reset the color
	*/
	void clean_all_colors(std::vector<std::string> &path)
	{
		std::string color = "";
		color_path(path, color);
	}
	/**
	   \brief Take edges name and change their color
	   \param edges A list of string containing the edge names
	   \param color The color
	*/
	void color_list_edges(std::vector<std::string> &edges, std::string color){
		
		for(std::vector<std::string>::iterator it = edges.begin(); it < edges.end(); ++it){
			network_graph[edge_list[*it]].color = color;	
		}
	}
	/**
	   \brief Take a list of vertex, the source and the targets and change their colors
	   \param verteces A list of vertex names
	   \param source The name of the source you want to highlight
	   \param targets A list of target name you want to highlight
	   \param color The color	
	*/
	void color_list_verteces(std::vector<std::string> &verteces, std::string color, std::string& source, std::vector<std::string>& targets){
	
		for(std::vector<std::string>::iterator it = verteces.begin(); it < verteces.end(); ++it){
			if(*it == source){
				network_graph[vertex_list[*it]].color = "chartreuse";
			}else if(std::find(targets.begin(), targets.end(), *it) != targets.end()){
				network_graph[vertex_list[*it]].color = "aquamarine";
			}
			else
				network_graph[vertex_list[*it]].color = color;	
		}
	}

	/**
	   \brief Gives a list of edges
	   \return A vector of string with the name of the edges
	*/
	std::vector<std::string> get_all_edges()
	{
	
		std::vector<std::string> l;
		for(typename edge_list_t::iterator it = edge_list.begin(); it!=edge_list.end(); ++it){
			l.push_back(it->first);
		}
		return l;
	}
	/*
	  void conversionCsvInDot(string read, string write = "CSV_convert.dot",char separator = ',', string graphName = "graphName", bool digraph = false)){//false = graph; true = digraph)){

	  ifstream fichierR(read.c_str(), ios::in);//opening of reading file
	  ofstream fichierW(write.c_str(), ios::out | ios::app);//opening of writing file

	  if(fichierR) { // test opening file succeed
	  if(fichierW) { // test opening file succeed

	  string typeGraph; // "graph" or "digraph" depends parameter
	  string flux; // "--" or "->" depends of parameter

	  if(!digraph){//assignment of typeGraph and flux
	  typeGraph = "graph";
	  flux = " -- ";
	  }
	  else{ typeGraph = "digraph"; flux = " -> ";}

	  fichierW << typeGraph << " " << graphName << " {\n\t"; // writing of the first line

	  string contentS; //read string storage
	  char contentC; //read char storage

	  getline(fichierR, contentS);
	  getline(fichierR, contentS);
	  getline(fichierR, contentS);
	  getline(fichierR, contentS);
	  getline(fichierR, contentS);//5 lines leading

	  int nbSeparatorFind;

	  while(fichierR){

	  nbSeparatorFind = 0;//number of Separator already found in a line, useful to know where you are in a sentence
	  fichierR.get(contentC);
	  while(contentC != '\n'){//for each line

	  if(contentC == separator){//when a Separator is found...
	  nbSeparatorFind++;
	  switch(nbSeparatorFind){

	  case 1:
	  fichierW << flux;
	  break;
	  case 2:
	  fichierW << " [label=";
	  break;
	  default:
	  fichierW << contentC;
	  break;
	  }
	  }
	  else{//if the char is not a Separator, just write it
	  fichierW << contentC;
	  }

	  fichierR.get(contentC);//reading of the next char
	  if(contentC == '\n'){
	  fichierW << "];\n\t";//if it's the end of the line we write this
	  }
	  }
	  }
	  fichierW << '}';//end of the file

	  fichierR.close();
	  fichierW.close();
	  }
	  else{
	  cerr << "Error, file opening/creation impossible !" << endl;
	  }
	  }
	  else{
	  cerr << "Error, file opening impossible !" << endl;
	  }
	  }

	  //pré-requis : 1 lignes d'entête (n=55)
	  //same number of label values(cost) and segment
	  //Mandatory syntaxe : Edges = {<1,3>,<2,3>, <3,1>, <3,2>, <3,6>,...   }
	  //                    Cost = [5 3 5 1 2 1 1 2 5 4 2....   ]

	  void conversionDatInDot(string read, string write = "CSV_convert.dot", string graphName = "graphName", bool digraph = false){//false = graph; true = digraph)){

	  ifstream fichierR(read.c_str(), ios::in);//opening of reading file
	  ofstream fichierW(write.c_str(), ios::out | ios::app);//opening of writing file
	  ifstream fichierRLabel(read.c_str(), ios::in);//opening of reading label values file

	  if(fichierR) { // test opening file succeed
	  if(fichierW) { // test opening file succeed

	  string typeGraph; // "graph" or "digraph" depends parameter
	  string flux; // "--" or "->" depends of parameter

	  if(!digraph){//assignment of typeGraph and flux
	  typeGraph = "graph";
	  flux = " -- ";
	  }
	  else{ typeGraph = "digraph"; flux = " -> ";}

	  fichierW << typeGraph << " " << graphName << " {\n\t"; // writing of the first line

	  string contentS; //read string storage
	  char contentC; //read char storage
	  string fullLabel = ""; //label of each segment
	  char label;//each char of fullLabel

	  fichierRLabel.get(label);
	  while(label != '['){//reaching label values
	  fichierRLabel.get(label);
	  }
	  fichierRLabel.get(label);

	  getline(fichierR, contentS);//entête

	  fichierR.get(contentC);
	  while(contentC != '}'){//while this is not end of file
	  //while this is not the end of values list
	  while(contentC != '<'){//while we didn't find a starting value...
	  fichierR.get(contentC);//...we moving curseur forward
	  }
	  fichierR.get(contentC);
	  while(contentC != ','){//while this is not the end of the first value...
	  fichierW << contentC;//...we write numbers...
	  fichierR.get(contentC);//...then we move forward.
	  }
	  fichierW << flux;
	  fichierR.get(contentC);
	  while(contentC != '>'){//while this is not the end of the second value...
	  fichierW << contentC;//...we write numbers...
	  fichierR.get(contentC);//...then we move forward.
	  }

	  while(label != ' '){//fullLabel constructing
	  fullLabel += label;
	  fichierRLabel.get(label);
	  }
	  fichierRLabel.get(label);//move to the next label

	  fichierW << " [label=" << fullLabel << "];\n\t";//end of line
	  fichierR.get(contentC);
	  fullLabel = "";//resetting of fullLabel

	  }
	  fichierW << '}';

	  fichierR.close();
	  fichierW.close();
	  fichierRLabel.close();
	  }
	  else{
	  cerr << "Error, file opening/creation impossible !" << endl;
	  }
	  }
	  else{
	  cerr << "Error, file opening impossible !" << endl;
	  }
	  }*/




	/**
	   \brief Gives a list of verteces
	   \return A vector of string with the name of the verteces
	*/
	std::vector<std::string> get_all_verteces()
	{
		
		std::vector<std::string> l;
		for(typename vertex_list_t::iterator it = vertex_list.begin(); it!=vertex_list.end(); ++it){
			l.push_back(it->first);
		}
		return l;
	}

	/**
	   \brief Convert the network graph into an undirected network graph
	*/
	void convert_to_undirected_graph(){

		//!< First of all, we copy the verteces in the network_graph into the undirected_network_graph	
		for(typename vertex_list_t::iterator vertex_it = vertex_list.begin(); vertex_it != vertex_list.end(); ++vertex_it){
			Vertex c = network_graph[vertex_it->second];
			add_vertex(c, undirected_network_graph);
		}
	
		
		//!< Copying the edges
		//!< The list will contain the couple already added
		std::vector<std::string> couple;
		std::string n1, n2;
		for(typename edge_list_t::iterator edge_it = edge_list.begin(); edge_it != edge_list.end(); ++edge_it){
			vertex_t source = boost::source(edge_it->second, network_graph);
			vertex_t target = boost::target(edge_it->second, network_graph);
			
			Edge c = network_graph[edge_it->second];
			Vertex s(network_graph[source]), t(network_graph[target]);
			//!< Creating the 2 names a->b and b->a
			n2 = create_edge_name(t.name, s.name); 
			n1 = create_edge_name(s.name, t.name);
			//!< If we don't find a->b, we add it to the network
			if(find(couple.begin(), couple.end(), n1) == couple.end()){
				add_edge(source, target, c, network_graph);
				//!< We add the contrary b->a which is exactly the same edge as a->b (undirected edge)
				couple.push_back(n2);
			}
		}
	}

	/*
	  \brief Calculate a minimum spanning tree
	  \return #Suppose to return Network which is a minimum spanning tree
	*/
	//Cette fonction sera modifié pour renvoyé un objet Network
	void minimum_tree(std::string path){
	
		//!< This function will convert the bidirectionnal adjacency list to an undirectedS adjacency list. 	
		//Discuter de la manière de faire, on garde le bidirectionnel et on construit un undirected, ou on passe en undirected ?
		convert_to_undirected_graph();
		
		IndexMap id_map = boost::get(boost::vertex_index, network_graph);
	
		std::vector<vertex_t> predecessors(boost::num_vertices(network_graph));
		std::vector<int> distances(boost::num_vertices(network_graph));
	
		//!< Kruskal minimum spannin tree function save a spate of edges in the list used in the second parameter. 
		std::vector<u_edge_t> spanning_tree;

		kruskal_minimum_spanning_tree(undirected_network_graph, std::back_inserter(spanning_tree), boost::weight_map(boost::get(&Cable::length,undirected_network_graph))
									   .distance_map(boost::make_iterator_property_map(distances.begin(),id_map))
									   .predecessor_map(boost::make_iterator_property_map(predecessors.begin(),id_map)));
	

		//!< In this moment, we color the edge in the main graph and to export it
		// La future fonction ne colorera pas le graph, elle renverra un objet Network contenant l'arbre
		// Coloration des edges pour vérification du résultat
		for(typename std::vector<u_edge_t>::iterator it = spanning_tree.begin(); it != spanning_tree.end();++it){
			
			network_graph[*it].color = "purple";
		}
	
		//!< Exportation of the graph 
		// L'exportatin est la pour tester la fonction
		std::ofstream out(path,std::ofstream::out);
		write_graphviz_dp(out, network_graph, dp, "label");
		out.close();
	}

private:
	network_graph_t network_graph;/**< The adjacency list adapted to our struct*/
	undirected_network_graph_t undirected_network_graph; /**< The adjacency list for an undirected graph*/
	vertex_list_t vertex_list;/**< The list of vertex descriptors, of network_graph's vertices*/
    std::vector<bool> vertex_exist;/**< A boolean array used to check if the vertex at the said coordinates exist, because the array can be wider than the number of vertices it contains */
	edge_list_t edge_list;/**< The list of edge descriptors, of network_graph's edges*/
	boost::dynamic_properties dp;/**< The dynamic properties of our graph, to link the structs to the import/export format*/
};

#endif
