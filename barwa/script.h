#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace barwa {
	class script {
		public:
			~script();

			/*
				Loading script from a file
			*/
			bool load( const std::string& );

			/*
				Loading script from another script
			*/
			bool load( const script& );

			/*
				Executing script
			*/
			bool run();

		private:
			/*
				Preprocessed lines of code
			*/
			std::vector <std::string*> code;
	};
}