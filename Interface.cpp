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

		n.add_cable(input1,input2);
	}
	
	networks.push_back(n);
	return id;
}

int Interface::export_graph(int id, std::string name = "export")
{
	name += id;
	networks[id].save_to_file(DATA_FOLDER+name+FILE_EXTENSION);
}
