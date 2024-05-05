#pragma once
#ifndef PACKAGE_H
#define PACKAGE_H
#include <iostream>
#include <string>
#include <map>
#include <vector>

namespace barwa {
	typedef std::map<std::string, std::string> pack_type;
	 
	class package {
		friend class script;

		public:
			/*
				Sets a record to a given value
			*/
			inline void set_record( const std::string&, const std::string& );

			/*
				Sets a package to a given package
			*/
			inline void set_content( const pack_type& );

			/*
				Returns a single record from a package
			*/
			inline const std::string get_record( const std::string& );
			
			/*
				Returns whole package
			*/
			inline const pack_type get_content();

			/*
				Clears whole package
			*/
			inline void clear();

		private:
			pack_type content;
	};
}


#endif