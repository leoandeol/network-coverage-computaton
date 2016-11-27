#include "Interface.hpp"

Interface::Interface()
{

}

Interface::~Interface()
{

}

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
}

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
