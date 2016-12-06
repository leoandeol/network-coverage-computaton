#include <iostream>
#include <utility>
#include <algorithm>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

#include "Interface.hpp"

int main(int,char**)
{
	Interface i;
	
//	i.menu();
	int id = i.import_graph("cesnet");
	std::string source = "Olomouc";
	std::vector<std::string> targets;
	targets.push_back("Usti");
	targets.push_back("Pardubice");
	targets.push_back("Pilsem");
	i.color_tree(id, source, targets);
	return 0;
}
