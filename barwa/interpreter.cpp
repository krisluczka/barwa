#include "script.h"

namespace barwa {
	bool script::run() {
		std::map<std::string, var*> variables;

		// lines of code
		for ( std::vector<std::string*>* line : code ) {
			if ( *line->at( 0 ) == "test" ) {
				//std::cout << "test";
			}

			// anything else must be a variable name!
			else {
				// i will rewrite this i promise!
				if ( *line->at(1) == "=" ) {
					if ( variables.find( *line->at( 0 ) ) == variables.end() )
						variables[*line->at( 0 )] = new var;

					*variables[*line->at( 0 )] = *line->at( 2 );
				}
			}
		}

		// remember to clean up after yourself!
		for ( const auto& pair : variables ) {
			std::visit( []( auto&& arg ) { std::cout << arg << std::endl; }, *pair.second );
			delete pair.second;
		}

		return true;
	}
}