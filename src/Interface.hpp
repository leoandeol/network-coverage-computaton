#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <vector>
#include <dirent.h>
#include <sys/types.h>
#include <iostream>
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
	int create_graph_terminal(std::string s);
	/**
	   \brief Imports a graph from a .dot file located in the data subfolder
	   \param s The filename
	   \return The id of the graph in case of success else -1
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

	/**
	  \brief Return 1 if the vertex is in the graph, else -1
	  \return 1 if the vertex is in the graph, else -1
	*/
	int is_in(int id, std::string name);


	bool is_connected(int id);
	
	/**
	   \brief Color a path in a network in a color (red by default)
	   \param id The network id
	   \param source The name of the vertex source
	   \param destination The name of the vertex target
	   \param color The name of the color
	*/
	void color_path(int id, std::string& source, std::string& destination, std::string color=std::string("red"));
	/**
	   \brief Display the path, displaying the verteces from the source to the target on the screen
  	   \param id The network's id
	   \param source The name of the vertex source
	   \param target The name of the vertex target
	   \return A vector containing the name of the verteces ordered from the source to the target
	*/
	std::vector<std::string> shortest_path(int id, std::string& source, std::string& target);
	std::vector<std::string> shortest_path2(int id, std::string& source, std::string& target);

	/**
	   \brief Calculate a minimum spanning tree of a graph (creating a new network added in the list)
	   \param id The id of the graph
	   \return Return the id of the minimum spanning tree network. 
	*/
	
	int minimum_spanning_tree(int id);
	/**
	  \brief Create a partial tree
	  \return The id of the tree
	*/
	int partial_tree(int id, std::string& source, std::vector<std::string>& targets, int color = 0);
	/**
	  \brief Computes the cycles of the graph
	  \param id The network's id
	  \return The id of the network that contains the cycles
	*/
	int get_cycles(int id);

	/**
	  \brief Computes a version of the graph without the disabled routeurs
	  \param id The network's id
	  \return The id of the cleant network
	*/
	int get_clean_graph(int id);
	
	/**
	  \brief Allows the user to edit its graph
	  \param id The network's id
	*/
	void edit_graph(int id);
	
	/**
	  \brief Allows the user to edit the graph's verteces
	  \param id The network's id
	  \return 0 if everything was allright
	*/
	int edit_verteces(int id);
	
	/**
	  \brief Allows the user to edit the graph's edges
	  \param id The network's id
	  \return 0 if everything was allright
	*/
	int edit_edges(int id);
	
	/**
	  \brief Allows the user to edit the Multicast capacity of a routeur
	  \param id The network's id
	  \return 0 if everything was allright
	*/
	void edit_MC(int id);
	
	/**
	  \brief Allows the user to edit the state of a routeur
	  \param id The network's id
	  \return 0 if everything was allright
	*/
	void edit_Vstate(int id);
	
	/**
	  \brief Allows the user to edit the state of an edge
	  \param id The network's id
	  \return 0 if everything was allright
	*/
	void edit_Estate(int id);

private:
	std::vector<Network<Routeur, Cable>* > networks;
	const std::string DATA_FOLDER = "data/";
	const std::string FILE_EXTENSION = ".dot";
};

#endif
