#include "util.hpp"

string strip( string str ) {
	size_t pos = 0;
	while( str[pos] == ' ' || str[pos] == '\t' ) {
		++pos;
	}
	str.erase( 0, pos );
	if( str == "" ) {
		return "";
	}
	pos = str.size() - 1;
	while( str[pos] == ' ' || str[pos] == '\t' ) {
		//str[pos] = 0;
		--pos;
	}
	str.erase( pos + 1 );
	return str;
}

size_t u8len( const std::string &str ) {
	size_t returnval = 0;
	for( const auto c: str ) {
		if( ( ~c ) & ( 1 << 7 ) ) {
			++returnval;
		} else if( ( c & ( 1 << 7 ) ) && ( c & ( 1 << 6 ) ) ) {
			++returnval;
		}
	}
	return returnval;
}
