#include "script.h"

namespace barwa {
	script::script() {
		package_available = false;
	}

	script::~script() {
        for ( std::vector<std::string*> *v : code ) {
		    for ( std::string* l : *v )
			    delete l;
            delete v;
        }
	}

	bool script::load( const std::string& path ) {
		// clearing
        for ( std::vector<std::string*>* v : code ) {
            for ( std::string* l : *v )
                delete l;
            delete v;
        }
		code.clear();

		// opening the file
		std::ifstream file( path );
		if ( !file.is_open() )
			return false;

		// preprocessing
        std::vector<std::string*>* ptr;
		std::string line, token, quoted_token;
		char c;
		while ( getline( file, line ) ) {
            ptr = new std::vector<std::string*>;
			std::stringstream ss( line );
			while( ss >> token ) {
				// if it is a comment, delete it
				if ( token.substr( 0, 2 ) == "//" )
					break;

				// if we starting with a string we tokenizing the whole string
				if ( token[0] == '"' ) {
					quoted_token = token;
					while ( ss.get( c ) ) {
						quoted_token += c;
						if ( c == '\"' )
							break;
					}
					ptr->push_back( new std::string( quoted_token ) );
					continue;
				}

                ptr->push_back( new std::string( token ) );
			}

			// pushin
            if ( ptr->size() )
                code.push_back( ptr );
            else
                delete ptr;
            
            // probably not necessary but I'll leave
            // it there just in case it will be
			/*
                for( std::string *l : ptr )
                    delete l;
                delete ptr;
            */
		}

		file.close();
		return true;
	}

	bool script::load( const script& other ) {
		// do not delete anything if we are copying empty script
		if ( !other.code.size() )
			return false;

		// clearing
        for ( std::vector<std::string*>* v : code ) {
            for ( std::string* l : *v )
                delete l;
            delete v;
        }
		code.clear();

		// coping
        std::vector<std::string*>* ptr;
        for ( std::vector<std::string*>* v : other.code ) {
            ptr = new std::vector<std::string*>;
            code.push_back( ptr );
            for ( std::string* l : *v )
                ptr->push_back( new std::string( *l ) );
        }

		return true;
	}

	inline bool script::load_package( const package &other ) {
		// loading the package
		if ( other.content.size() ) {
			pack = other;
			package_available = true;
			return true;
		} else return false;
	}
}