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
	std::cout << "Menu :" << std::endl << "Type a number to start its related routine" << std::endl << "\t1 : Create a graph\n\t2 : Import a graph\n\t3 : Export a graph\n\t4 : Exit" << std::endl;
	int input;
	std::string tmp;
	std::cin >> tmp;
	input = stoi(tmp);
	//TODO
}
/*
int Interface::create_graph_terminal()
{
  int id = networks.size();
  Network* n = new Network();

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
      
      //conversion des chiffres entrés de String vers Integer
      int i1 = std::stoi(input1,nullptr);
      int i2 = std::stoi(input2,nullptr);

      n->add_cable(i1,i2);
    }
  
  networks.push_back(n);
  
  return id;
}*/

int Interface::import_graph(std::string name)
{
  std::string path = DATA_FOLDER + name + FILE_EXTENSION;
  Network* n = new Network();
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
  networks[id]->save_to_file(path);
}

void Interface::color_path(int id, std::string& source, std::string& destination, std::string& color){

	std::vector<std::string> path = networks[id]->get_path(source, destination);
	
	networks[id]->color_path(path, color);
	std::string name = networks[id]->get_network_name()+ " - " + source + "->" + destination;
	export_graph(id, name);
	networks[id]->clean_all_colors(path);
}
int Interface::create(){
	
	int id = networks.size();
	Network* net = new Network();

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
/**/
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


bool Interface::is_connected(int id){
	
	return networks[id]->is_connected();
}
void Interface::display_shortest_path(int id, std::string& source, std::string& target){

	std::vector<std::string> path = networks[id]->get_path(source, target);
	
	std::vector<std::string>::iterator it;
	for(it = path.begin(); it != path.end(); ++it){
		std::cout << *it << std::endl;
	}
}
void color_tree(int id, std::string source, std::vector<std::string> targets){
	std::vector<std::string> sources;
	sources.push_back(source);
	std::vector<std::vector<std::string>> tree;
	tree = networks[id].minimun_tree(sources, targets, tree);
	networks[id].color_tree(tree, "red");
	export_graph(id, name);
}
