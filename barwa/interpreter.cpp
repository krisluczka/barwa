#include "script.h"

namespace barwa {
	bool script::run() {
		vars variables;

		// lines of code
		for ( std::vector<std::string*>* line : code ) {
			if ( *line->at( 0 ) == "test" ) {
				//std::cout << "test";
			}

			// anything else must be a variable name!
			else if ( line->size() > 1 && *line->at( 1 ) == "=" ) {
				// if the variable doesn't exist we create it
				if ( variables.find( *line->at( 0 ) ) == variables.end() )
					variables[*line->at( 0 )] = new std::string;

				// taking only the expression tokens
				std::vector<std::string*> expressions( line->begin() + 2, line->end() );

				// evaluating the expression
				*variables[*line->at( 0 )] =
					std::to_string( evaluate( preprocess_expression( variables, expressions ) ) );
			}
		}

		// remember to clean up after yourself!
		for ( const auto& pair : variables ) {
			delete pair.second;
		}

		return true;
	}
}