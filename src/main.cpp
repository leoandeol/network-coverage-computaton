#include <iostream>
#include <utility>
#include <algorithm>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

#include "Interface.hpp"

int main(int,char**)
{
	Interface i;
	//int id = i.create_graph_terminal();
	//i.export_graph(id);
	int id = i.create();
	//i.export_graph(id);
//	std::string name;
//	std::cin >> name;
//	int id2 = i.import_graph("cesnet");
	bool boule = i.is_connected(id);
	
	if(boule){
		std::cout << "Le graphe est bien connecté. " << std::endl;
	}else{
		std::cout << "Le graphe n'est pas connecté. " << std::endl;
	}

	return 0;
}
