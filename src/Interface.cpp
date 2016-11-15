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
  Network n;

  std::string input1, input2;

  std::cout << "Network creation assistant" << std::endl;
  std::cout << "Type \"done\" anytime to finish the creation" << std::endl;
	
  while(true)
    {

      std::cout << "Origin node : ";
      std::cin >> input1;
      if(input1=="done") break;

      std::cout << "Destination node : ";
      std::cin >> input2;
      if(input2=="done") break;
      
      int i1 = std::stoi(input1,nullptr);
      int i2 = std::stoi(input2,nullptr);

      n.add_cable(i1,i2);
    }
	
  networks.push_back(n);
  return id;
}

int Interface::export_graph(int id, std::string name)
{
  name += std::to_string(id);
  name += FILE_EXTENSION;
  return networks[id].save_to_file(DATA_FOLDER+name);
}
