#include <iostream>
#include <utility>
#include <algorithm>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

#include "Interface.hpp"

/*! \mainpage Test Documentation
 *
 * \section intro_sec Introduction
 *
 * NCC is a 3rd term project realized by Léo Andeol, Lothair Kizardjian, Cyril Govin & Guillaume Chafiol
 * with Dr. Molnar as tutor, concerning computating network cycles, trees and paths as backup for the said networks
 *
 * \section install_sec Installation
 *
 * \subsection tools_subsec Tools required
 * - libboost-graph(-dev if you want to compile it) & all its dependencies
 * - doxygen to generate the doc (even if the repo should always be up to date)
 *
 * \subsection compiling Compiling the program
 * 
 * Run "make" to build the normal binary, and "make debug" to build the debug version which can be used with gdb 
 *
 * \subsection gen_docs Generation the docs
 * 
 * You need to have doxygen installed, and then simply run "doxygen doxygen.cfg"
 *
 * \subsection running Running the program
 * 
 *  Simply run ./main in a terminal
 *
 * \section copyright Copyright and License
 * 
 * GNU GPL (c) Léo Andeol, Lothair Kizardjian, Cyril Govin & Guillaume Chafiol
 *
 */

int main(int,char**)
{
	Interface i;
	i.menu();
	return 0;
}
