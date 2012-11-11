#include "rule.hpp"

#include <stdexcept>

using std::invalid_argument;


rule::rule( object val_1, object val_2, object result, string operation )
	: val_1( val_1 ), val_2( val_2 ), result( result ), operation( operation ) {}

rule::rule( string str, string operation )
	: operation( operation ) {
	size_t pos1, pos2;
	pos1 = str.find( this->operation );
	if( pos1 == string::npos ) {
		throw invalid_argument( "operator not found" );
	}
	val_1 = object( str.substr( 0, pos1 ) );
	pos1 += this->operation.size();
	pos2 = str.find( "=", pos1 );
	if( pos2 == string::npos ) {
		throw invalid_argument( "equality-sign not found" );
	}
	val_2 = object( str.substr( pos1, pos2 - pos1 ) );
	result = object( str.substr( pos2 + 1 ) );
}


ostream &operator<<( ostream &stream, rule r ) {
	stream << r.val_1 << " " << r.operation << " " << r.val_2 << " = " << r.result;
	return stream;
}

