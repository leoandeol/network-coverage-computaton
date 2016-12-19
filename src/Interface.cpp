#include "Interface.hpp"

Interface::Interface()
{

}

Interface::~Interface()
{

}

void Interface::menu()
{
	std::cout << "**********************************************************************" << std::endl;
	std::cout << "* Network Coverage Cycles & Partial Spanning trees computation       *" << std::endl;
	std::cout << "* By Léo Andéol, Lothair Kizardjian, Cyril Govin                     *" << std::endl;
	std::cout << "**********************************************************************" << std::endl;
	int input;
	bool cont = true;
	std::string s;
	int id;
	do
	{
		std::cout << "Menu :" << std::endl << "Type a number to start its related routine" << std::endl << "\t1 : Create a graph\n\t2 : Import a graph\n\t3 : Export a graph\n\t4 : Create a test graph\n\t5 : Exit" << std::endl;	
		std::cin >> s;
		input = stoi(s);
		switch(input)
		{
		case 1:
			id = create_graph_terminal();
			std::cout << "The created graph is associated with the ID : " << id << std::endl;
			break;
		case 2:
			std::cout << "What's the name of the file to import (without the extension, and the file should be located in the data folder) ?" << std::endl;
		    std::cin >> s;
			id = import_graph(s);
			std::cout << "The created graph is associated with the ID : " << id << std::endl;
			break;
		case 3:
			std::cout << "What's the name of the file to export (without the extension, and the file will be located in the data folder) ?" << std::endl;
		    std::cin >> s;
			std::cout << "What's the ID of the graph to export ?" << std::endl;
		    std::cin >> id;
			export_graph(id,s);
			break;
		case 4:
			id = create();
			std::cout << "The created graph is associated with the ID : " << id << std::endl;
			break;
		case 5:
			cont=false;
			break;
		}
	} while(cont);
}

int Interface::create_graph_terminal()
{
	int id = networks.size();
	Network<Routeur,Cable>* n = new Network<Routeur,Cable>();

	std::string input1, input2;
	std::cout << "Network creation assistant" << std::endl;
	std::cout << "Type in \"done\" anytime to finish the creation" << std::endl;
	
	while(true)
    {
		
		//Ex: 1 -> 2
	  
		std::cout << "Node 1 : ";
		//rentrer un chiffre
		std::cin >> input1;
		if(input1=="done") break;

		std::cout << "Node 2 : ";
		//rentrer chiffre
		std::cin >> input2;
		if(input2=="done") break;

		n->add_cable(input1,input2);
    }
  
	networks.push_back(n);
  
	return id;
}

int Interface::import_graph(std::string name)
{
	std::string path = DATA_FOLDER + name + FILE_EXTENSION;
	NetworkInfo info(name, path);
	Network<Routeur,Cable>* n = new Network<Routeur,Cable>(info);
	int i = networks.size();
	//todo test if found
	n->load_from_file(path);
	/*
	  std::vector<std::string> l = n->get_all_edges();
	  std::vector<std::string>::iterator it = l.begin();
	  for(; it != l.end(); ++it){
	  if(){

	  }
	  }
	*/
	networks.push_back(n);
	return i;
}

void Interface::export_graph(int id, std::string name)
{
  std::string path = DATA_FOLDER + name + std::to_string(id) + FILE_EXTENSION;
  static const std::string command = "mkdir data && dot -Tpng ";
  networks[id]->save_to_file(path);
}

int Interface::create()
{	
	int id = networks.size();
	Network<Routeur,Cable>* net = new Network<Routeur,Cable>();

	std::string A = "A";
	std::string B = "B";
	std::string C = "C";
	std::string D = "D";
	std::string E = "E";
	std::string F = "F";
	std::string G = "G";
	std::string Z = "Z";

	net->add_routeur(A);
	net->add_routeur(B);
	net->add_routeur(C);
	net->add_routeur(D);
	net->add_routeur(E);
	net->add_routeur(F);
	net->add_routeur(G);
	net->add_routeur(Z);
	
	net->add_cable(A, B);
	net->add_cable(A, C);
	net->add_cable(A, D);
	net->add_cable(A, E);
	net->add_cable(A, F);
	net->add_cable(A, G);
	net->add_cable(B, C);
	net->add_cable(B, D);
	net->add_cable(B, F);
	net->add_cable(F, B);
	net->add_cable(E, F);
	net->add_cable(G, B);
	net->add_cable(D, E);
	
	networks.push_back(net);
	
	return id;
}


bool Interface::is_connected(int id)
{	
	return networks[id]->is_connected();
}

void Interface::display_shortest_path(int id, std::string& source, std::string& target)
{

	std::vector<std::string> path = networks[id]->get_path(source, target);
	
	std::vector<std::string>::iterator it;
	for(it = path.begin(); it != path.end(); ++it){
		std::cout << *it << std::endl;
	}
}

void Interface::color_tree(int id, std::string& source, std::vector<std::string>& targets, std::string color)
{
	std::vector<std::string> sources;
	sources.push_back(source);
	std::string name = networks[id]->get_network_name()+"-SpanningTree";

	Network<Routeur, Cable>* tree = new Network<Routeur,Cable>();

	tree = networks[id]->partial_minimum_tree(sources, targets, tree);
	int id2 = networks.size();
	networks.push_back(tree);
		
	std::vector<std::string> edges,verteces;
	edges = networks[id2]->get_all_edges();
	verteces = networks[id2]->get_all_verteces();
	
	networks[id]->color_list_verteces(verteces, color,  source, targets);
	networks[id]->color_list_edges(edges, color);

	export_graph(id, name);
}

void Interface::color_path(int id, std::string& source, std::string& destination, std::string& color)
{
	std::vector<std::string> path = networks[id]->get_path(source, destination);
	
	networks[id]->color_path(path, color);
	std::string name = networks[id]->get_network_name()+ " - " + source + "->" + destination;

	networks[id]->clean_all_colors(path);
}
void Interface::minimum_spanning_tree(int id, std::string name){
  	std::string path = DATA_FOLDER + name + std::to_string(id) + FILE_EXTENSION;
	networks[id]->minimum_tree(path);
}
