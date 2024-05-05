#include "package.h"

namespace barwa {
	inline void package::set_record( const std::string& record, const std::string& value ) {
		content[record] = value;
	}

	inline void package::set_content( const pack_type& package ) {
		content = package;
	}

	inline const std::string package::get_record( const std::string& record ) {
		if ( content.find( record ) != content.end() )
			return content[record];
		else
			return "";
	}

	inline const pack_type package::get_content() {
		return content;
	}

	inline void package::clear() {
		content.clear();
	}
}