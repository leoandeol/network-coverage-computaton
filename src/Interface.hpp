#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <vector>
#include "Network.hpp"

/** The class handling the UI */
class Interface
{
public:
	/**
	   \brief Default constructor
	*/
	Interface();
	/**
	   \brief Default destructor
	*/
	~Interface();
	/**
	   \brief Displays the main menu and calling other subfunctions when asked
	*/
	void menu();
	/**
	   \brief Starts a graph creator, to write graphs manually
	   \return The id of the new graph
	*/
	int create_graph_terminal();
	/**
	   \brief Imports a graph from a .dot file located in the data subfolder
	   \param s The filename
	   \return 0 in case of success else -1
	 */
	int import_graph(std::string s ="import");
	/**
	   \brief Exports a graph to a .dot file located in the data subfolder
	   \param s The filename
	   \param i The id of the graph to export
	 */
	void export_graph(int i,std::string s ="export");
	/**
	   \brief Exports a graph to a .dot file located in the data subfolder
	   \return The id of the new graph
	 */
	int create();
	bool is_connected(int id);
	void color_path(int id, std::string& source, std::string& destination, std::string color=std::string("red"));
	std::vector<std::string> shortest_path(int id, std::string& source, std::string& target);
	int minimum_spanning_tree(int id, std::string name);
	int partial_tree(int id, std::string& source, std::vector<std::string>& targets, std::string color = std::string("red"));
private:
	std::vector<Network<Routeur, Cable>* > networks;
	const std::string DATA_FOLDER = "data/";
	const std::string FILE_EXTENSION = ".dot";
};

#endif
