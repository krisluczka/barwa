#pragma once
#ifndef SCRIPT_H
#define SCRIPT_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include "package.h"

namespace barwa {
	typedef std::map<std::string, std::string*> vars;

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

			/*
				Evaluating math equation
			*/
			const inline bool is_operator( const char );
			const inline int_fast8_t precedence( const char );
			const inline long double apply_operation( const long double, const long double, const char );
			std::string preprocess_expression( vars&, std::vector<std::string*>& );
			long double evaluate( const std::string& );
	};
}

#endif