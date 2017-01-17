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
	std::string s, t, i;
	std::vector<std::string> targets;
	int id;
	char c;
	do
	{
		std::cout << "Menu :" << std::endl << "Type a number to start its related routine" << std::endl << "\t0 : List of the current graphs\n\t1 : Graph creation\n\t2 : Graph importation\n\t3 : Graph exportation\n\t4 : Shortest-path algorithm\n\t5 : Shortest-path algorithm colouring\n\t6 : Partial tree for multicasting\n\t7 : Minimum spanning tree\n\t8 : Minimum cycles computation\n\t9 : Removing routeurs and cables that aren't working\n\t10 : Edit graph\n\t11 : Exit" << std::endl;
		std::cin >> s;
		input = stoi(s);
		switch(input)
		{
		case 0:
			std::cout << "List of the current graph : " << std::endl;
			std::cout << "ID - name of the network" << std::endl;
			if(networks.size() != 0){
				for(unsigned int y = 0; y < networks.size(); y++){
					std::cout << y << " - " << networks.at(y)->get_network_name() << std::endl;
				} 
			}
			else{
				std::cout << "There are no graphs you are working on. " << std::endl;
			}
			break;
		case 1:
			std::cout << "What's the name of the graph ?" << std::endl;
			std::cin >> s;
			id = create_graph_terminal(s);
			std::cout << "The created graph is associated with the ID : " << id << std::endl;
			break;
		case 2:
			std::cout << "What's the name of the file to import (without the extension, and the file should be located in the data folder) ?" << std::endl;
		    std::cin >> s;
			id = import_graph(s);
			if(id == -1){
				std::cout << "Error, please make sure you have entered the right name. (Located in the data folder) " << std::endl;
			}
			else
				std::cout << "The imported graph is associated with the ID : " << id << std::endl;
			break;
		case 3:
			std::cout << "What's the name of the file to export (without the extension, and the file will be located in the data folder) ?" << std::endl;
		    std::cin >> s;
			std::cout << "What's the ID of the graph to export ?" << std::endl;
		    std::cin >> id;
			if(networks.size() == 0 || id < 0 || id > static_cast<int>(networks.size())){
				std::cout << "The graph id is incorrect. Please check the list of the graph running task number 0. " << std::endl; 
			}	
			else{
				export_graph(id,s);
			}
			break;
		case 4:
			std::cout << "What's the id of the graph ?" << std::endl;
			std::cin >> i;
			id = stoi(i); 
			if(networks.size() == 0 || id < 0 || id > static_cast<int>(networks.size())){
				std::cout << "The graph id is incorrect. Please check the list of the graph running task number 0. " << std::endl; 
				break;
			}
			else{
				std::cout << "What's the name of the source vertex ?" << std::endl;
				std::cin >> s;
				if(is_in(id, s) == -1){
					std::cout << "The vertex has not been found in the graph. Please make sure this is the correct name. " << std::endl;
				}else{
					std::cout << "What's the name of the target vertex ?" << std::endl;
					std::cin >> t;
					if(is_in(id, t)==-1){
						std::cout << "The vertex has not been found in the graph. Please make sure this is the correct name. " << std::endl;
					}
					else{
						std::cout << std::endl << std::endl;
					
						std::cout << "Following the shortest path to go from " << s << " to " << t << std::endl;
						shortest_path(id, s, t);
					}
				}
			}
			break;
		case 5:
			std::cout << "What's the id of the graph ?" << std::endl;
			std::cin >> i;
			id = stoi(i); 
			if(networks.size() == 0 || id < 0 || id > static_cast<int>(networks.size())){
				std::cout << "The graph id is incorrect. Please check the list of the graph running task number 0. " << std::endl; 
				break;
			}else{
				std::cout << "What's the name of the source vertex ?" << std::endl;
				std::cin >> s;
				if(is_in(id, s) == -1){
					std::cout << "The vertex has not been found in the graph. Please make sure this is the correct name. " << std::endl;
				}else{
					std::cout << "What's the name of the target vertex ?" << std::endl;
					std::cin >> t;
					if(is_in(id, s) == -1){
						std::cout << "The vertex has not been found in the graph. Please make sure this is the correct name. " << std::endl;
					}else{
						color_path(id, s, t);	
						std::cout << "The path has been colored in the graph and exported. Check the data folder for the results. (The colored in the graph are reset to normal)" << std::endl;	
					}
				}
			}
			break;
		case 6:
			std::cout << "What's the id of the graph ?" << std::endl;
			std::cin >> i;
			id = std::stoi(i);
			if(networks.size() == 0 || id < 0 || id > static_cast<int>(networks.size())){
				std::cout << "The graph id is incorrect. Please check the list of the graph running task number 0. " << std::endl; 
			}	
			else{
				std::cout << "What's the name of the source vertex ?" << std::endl;
				std::cin >> s;
				if(is_in(id, s) == -1){
					std::cout << "The vertex has not been found in the graph. Please make sure this is the correct name. " << std::endl;
				}else{
					int test = 1;	
					while(1){
						std::cout << "What's the name of the target vertex ? (Make sure the vertex are in the graph, enter \"done\" to end the list of targets)" << std::endl;
						std::cin >> t;
						if(t == "done"){break;}
						test = is_in(id, t);
						if(test == -1){
							std::cout << "The vertex has not been found in the graph. Please make sure this is the correct name. " << std::endl;
							break;
						}else{
							targets.push_back(t);
						}
					}
					if(test == 1){
						std::cout << "Do you want to color the partial tree in the network ? yes=1 & no=0" << std::endl;
						std::cin >> i;
						if(stoi(i) == 1){
						std::cout << "You just say yes. The program will export the graph with the id " << id << " and will color the partial tree calculated. " << std::endl;
						std::cout << "The source is colored in green wheares the targets are colored in blue. Please check the data folder for the result (.dot & .png provided). " << std::endl;
							id = partial_tree(id, s, targets, 1);
						}
						else{
							id = partial_tree(id, s, targets);
						}
					std::cout << "The partial graph created is associated with the ID : " << id << std::endl;
					}
				}
			}
			targets.clear();
			break;
		case 7:
			std::cout << "What's the id of the graph ?" << std::endl;
			std::cin >> i;
			id = stoi(i);
			if(networks.size() == 0 || id < 0 || id > static_cast<int>(networks.size())){
				std::cout << "The graph id is incorrect. Please check the list of the graph running task number 0. " << std::endl; 
			}
			else{
				id = minimum_spanning_tree(id);

				std::cout << "The minimum spaning tree created from " << stoi(i) << " is associated with the ID : " << id << std::endl;
			}

			break;
		case 8:
			std::cout << "What's the id of the graph ?" << std::endl;
			std::cin >> i;
			id = std::stoi(i);
			if(networks.size() == 0 || id < 0 || id > static_cast<int>(networks.size())){
				std::cout << "The graph id is incorrect. Please check the list of the graph running task number 0. " << std::endl; 
			}else{
				id = get_cycles(id);
			
				std::cout << "The network which contains the cycle of the graph" << stoi(i) << " is associated with the ID : " << id << std::endl;
			}
			break;
		case 9:
			std::cout << "What's the id of the graph ?" << std::endl;
			std::cin >> i;
			id = std::stoi(i);
			if(networks.size() == 0 || id < 0 || id > static_cast<int>(networks.size())){
				std::cout << "The graph id is incorrect. Please check the list of the graph running task number 0. " << std::endl; 
			}else{
				id = get_clean_graph(id);
				std::cout << "The network which contains the clean network" << stoi(i) << " is associated with the ID : " << id << std::endl;
			}
			
			
			break;
		case 10:
			std::cout << "What's the id of the graph ?" << std::endl;
			std::cin >> i;
			id = std::stoi(i);
			if(networks.size() == 0 || id < 0 || id > static_cast<int>(networks.size())){
				std::cout << "The graph id is incorrect. Please check the list of the graph running task number 0. " << std::endl; 
			}
			else{
				edit_graph(id);
			}
			break;
		case 11:
			cont = false;
			break;
		}
		std::cin.clear();
		std::cin.get();
		std::cin.get();
		std::cout << std::endl << std::endl;
	} while(cont);
}


int Interface::create_graph_terminal(std::string s)
{
	
	int id = networks.size();
	Network<Routeur,Cable>* n = new Network<Routeur,Cable>();
	n->set_network_name(s);

	std::string input1, input2, input3, input4, input5;
	std::cout << "Network creation assistant" << std::endl;
	std::cout << "Type in \"done\" anytime to finish the creation" << std::endl;
	
	networks.push_back(n);
	
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

		if(n->routeur_exists(input1)==-1)
		  {
			std::cout << " MulticastCapable (true or false) ? " << std::endl;
			std::cin >> input3;
			n->add_routeur(input1,input3);
		  }
		if(n->routeur_exists(input2)==-1)
		  {
			std::cout << " MulticastCapable (true or false) ? " << std::endl;
			std::cin >> input4;
		    n->add_routeur(input2,input4);
		  }
		
		std::cout << "Cable length" << std::endl;
		std::cin >> input5;
		
		n->add_cable(input1,input2,std::stoi(input5));
    }
  
  
	return id;
}

int Interface::import_graph(std::string name)
{
	std::string path = DATA_FOLDER + name + FILE_EXTENSION;
	NetworkInfo info(name, path);
	Network<Routeur,Cable>* n = new Network<Routeur,Cable>(info);
	int i = networks.size();
	if(access(path.c_str(),R_OK) == -1)
	{
		std::cerr << "Can't access the said file" << std::endl;
		return -1;
	}
	n->load_from_file(path);
	networks.push_back(n);
	return i;
}

void Interface::export_graph(int id, std::string name)
{
	std::string path = DATA_FOLDER + networks[id]->get_network_name() + std::to_string(id) + FILE_EXTENSION;
	static const std::string command = "mkdir data";

	// Test if the folder can be accessed
	if(access("data",X_OK))
	{
		system(command.c_str());
		// sleeps 100ms to make sure the system has created the folder, else it may bug
		usleep(100000);
	}
	networks[id]->save_to_file(path);
	std::string img_path = DATA_FOLDER + name + std::to_string(id) + ".png";
	std::string transform = "dot -Tpng \""+path+"\" > \""+img_path+"\"";
	system(transform.c_str());
}

int Interface::is_in(int id, std::string name){
	return networks[id]->contains(name);
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


std::vector<std::string> Interface::shortest_path(int id, std::string& source, std::string& target)
{

	std::vector<std::string> path = networks[id]->get_path(source, target);
	
	std::vector<std::string>::iterator it;
	for(it = path.begin(); it != path.end(); ++it){
		std::cout << *it << std::endl;
	}
	return path;
}
std::vector<std::string> Interface::shortest_path2(int id, std::string& source, std::string& target)
{
	std::cout << "Shortest path 2nd version" << std::endl;
	std::vector<std::string> path = networks[id]->get_path2(source, target);
	
	std::vector<std::string>::iterator it;
	for(it = path.begin(); it != path.end(); ++it){
		std::cout << *it << std::endl;
	}
	return path;
}


int Interface::partial_tree(int id, std::string& source, std::vector<std::string>& targets, int color)
{
	int id2 = networks.size();
	//!< Needed a vector of sources for the function
	std::vector<std::string> sources;
	sources.push_back(source);
	//!< Create the name of the tree
	std::string name = networks[id]->get_network_name()+"-PartialTree:"+source+"->"+targets.at(0);
	for(std::vector<std::string>::iterator it = ++targets.begin(); it != targets.end(); ++it){
		name = "-" + name+ *it;
	}
	//!< Creation of the futur tree
	Network<Routeur, Cable>* tree = new Network<Routeur,Cable>();

	//!< Partial_minimum_tree return the tree, adding the verteces and edges to the tree	
	tree = networks[id]->partial_minimum_tree(sources, targets, tree);

	//!< Setting the name of the tree
	tree->set_network_name(name);

	if(color == 1){
		std::string s;
		std::cout << std::endl << "What's the name of the colored graph to export ? (without the extension, and the file will be located in the data folder) ?" << std::endl;

		std::cin >> s;

		std::vector<std::string> verteces = tree->get_all_verteces();	
		std::vector<std::string> edges = tree->get_all_edges();	
		networks[id]->color_list_verteces(verteces, "red", source, targets);
		networks[id]->color_list_edges(edges, "red");
		export_graph(id, s);
		networks[id]->color_list_verteces(verteces, "", source, targets);
		networks[id]->color_list_edges(edges, "");
	
	}



	tree->color_source(source);
	tree->color_targets(targets);

	//!< Adding it to the network list
	networks.push_back(tree);

	return id2;
}

void Interface::color_path(int id, std::string& source, std::string& destination, std::string color)
{
	std::vector<std::string> path = networks[id]->get_path(source, destination);
	
	networks[id]->color_path(path, color);
	std::string name = networks[id]->get_network_name()+ "-" + source + "--" + destination;
	export_graph(id, name);
	networks[id]->clean_all_colors(path);
}

int Interface::minimum_spanning_tree(int id){
	Network<Routeur,Cable>* min_tree;
	min_tree = networks[id]->minimum_tree();
	
	int id2 = networks.size();
	networks.push_back(min_tree);

	return id2;
}

int Interface::get_cycles(int id){
	Network<Routeur,Cable>* cycles;
	cycles = networks[id]->get_cycles();
	
	int id2 = networks.size();
	networks.push_back(cycles);
		
	return id2;
}

int Interface::get_clean_graph(int id)
{
	auto n = networks[id]->get_clean_graph();
	int id2 = networks.size();

	networks.push_back(n);

	return id2;
}

int Interface::edit_graph(int id)
{	
	std::string option;
	int	optionINT;	
	auto n = networks[id];
	std::cout << "\t ---------------------------------- " << std::endl;
	std::cout << "\t -- Welcome to the graph editor. -- " << std::endl;
	std::cout << "\t ---------------------------------- " << std::endl;
	bool loop = true;
	do{
		std::cout << "\t1 : Edit the verteces\n\t2 : Edit the edges\n\t3 : Exit" << std::endl;
		std::cin >> option;
		optionINT = std::stoi(option);
		switch(optionINT){
			case 1:
				n->edit_verteces();
				break;
			case 2:
				n->edit_edges();
				break;
			case 3:
				loop = false;
				break;
		}
	}while(loop);
	return 0;
}


