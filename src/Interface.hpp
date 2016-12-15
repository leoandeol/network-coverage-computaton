#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <vector>
#include "Network.hpp"

class Interface
{
public:
	Interface();
	~Interface();
	void menu();
	int create_graph_terminal();
	int import_graph(std::string="import");
	void export_graph(int,std::string="export");
	int create();
	bool is_connected(int id);
	void color_path(int id, std::string& source, std::string& destination, std::string& color);
	void color_tree(int id, std::string source, std::vector<std::string> targets);
	void display_shortest_path(int id, std::string& source, std::string& target);
private:
	std::vector<Network<Routeur, Cable>* > networks;
	const std::string DATA_FOLDER = "data/";
	const std::string FILE_EXTENSION = ".dot";
};

#endif
