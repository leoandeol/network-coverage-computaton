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
//	int id = i.create();
	//i.export_graph(id);
	std::cout << "Please enter the name of the file you wanna import" << std::endl;
	std::string name;
	std::cin >> name;
	std::cout <<std::endl;
	int id = i.import_graph(name);

	bool boule = i.is_connected(id);
	
	if(boule){
		std::cout << "Le graphe est bien connecté. " << std::endl;
	}else{
		std::cout << "Le graphe n'est pas connecté. " << std::endl;
	}

	return id;
}
