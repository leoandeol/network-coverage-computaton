#include <iostream>
#include <utility>
#include <algorithm>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

#include "Interface.hpp"

int main(int,char**)
{
	Interface i;
	int id = i.create_graph_terminal();
	i.export_graph(id);
	return 0;
}
