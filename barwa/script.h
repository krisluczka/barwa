#pragma once
#ifndef SCRIPT_H
#define SCRIPT_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <variant>
#include "package.h"

namespace barwa {
	typedef std::variant<int_fast64_t, long double, std::string, bool> var;

	class script {
		public:
			script();
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
				Loading a package
			*/
			inline bool load_package( const package& );

			/*
				Executing script
			*/
			bool run();

		private:
			/*
				Preprocessed lines of code
			*/
			std::vector<std::vector<std::string*>*> code;

			/*
				Package info
			*/
			package pack;
			bool package_available;
	};
}

#endif