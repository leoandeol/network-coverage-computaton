#include "Interface.hpp"

Interface::Interface()
{

}

Interface::~Interface()
{

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
  networks.push_back(n);
  return i;
}

void Interface::export_graph(int id, std::string name)
{
  std::string path = DATA_FOLDER + name + std::to_string(id) + FILE_EXTENSION;
  networks[id]->save_to_file(path);
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

