#include "script.h"

namespace barwa {
	script::~script() {
		for ( std::string* l : code )
			delete l;
	}

	bool script::load( const std::string& path ) {
		// clearing
		for ( std::string* l : code )
			delete l;
		code.clear();

		// opening the file
		std::ifstream file( path );
		if ( !file.is_open() )
			return false;

		// preprocessing
		std::string line, token;
		std::string *line_of_code;
		while ( getline( file, line ) ) {
			line_of_code = new std::string("");

			std::stringstream ss( line );
			while( ss >> token ) {
				// if it is a comment, delete it
				if ( token.substr( 0, 2 ) == "//" )
					break;
				*line_of_code += token + " ";
			}

			if ( *line_of_code != "" )
				code.push_back( line_of_code );
			else
				delete line_of_code;
		}

		file.close();
		return true;
	}

	bool script::load( const script& other ) {
		// do not delete anything if we are copying empty script
		if ( !other.code.size() )
			return false;

		// clearing
		for ( std::string* l : code )
			delete l;
		code.clear();

		// coping
		for ( std::string* l : other.code )
			code.push_back( new std::string( *l ) );

		return true;
	}

	inline bool script::load_package( package* other ) {
		// loading the package
		if ( other->content.size() ) {
			delete pack;
			pack = new package;

			*pack = *other;
		} else return false;
	}

	bool script::run() {
		return true;
	}
}