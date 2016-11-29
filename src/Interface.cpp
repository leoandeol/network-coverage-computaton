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
std::cout <<path <<std::endl;
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
//	std::string Z = "Z";

	int a = net->add_routeur(A);
	int b = net->add_routeur(B);
	int c = net->add_routeur(C);
	int d = net->add_routeur(D);
	int e = net->add_routeur(E);
	int f = net->add_routeur(F);
	int g = net->add_routeur(G);
//	int z = net->add_routeur("Z");

	net->add_cable(a, b);
	net->add_cable(b, a);
	net->add_cable(a, c);
	net->add_cable(a, d);
	net->add_cable(a, e);
	net->add_cable(a, f);
	net->add_cable(a, g);
	net->add_cable(b, c);
	net->add_cable(b, d);
	net->add_cable(b, f);
	net->add_cable(f, b);
	net->add_cable(b, d);
	net->add_cable(c, b);
	net->add_cable(e, f);
	net->add_cable(g, b);
	net->add_cable(d, e);
	
	networks.push_back(net);
	
	return id;
}




