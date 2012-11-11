#include "object.hpp"
using namespace std;

#include "util.hpp"

object::object() {
}

object::object( string name )
	: _name( strip( name ) ) {}

string object::get_name() const {
	return _name;
}

bool object::operator== ( const object &other ) const {
	return _name == other._name;
}

bool object::operator!= ( const object &other ) const {
	return _name != other._name;
}

bool object::operator< ( const object &other ) const {
	return _name < other._name;
}

std::ostream &operator<<( std::ostream &stream, object o ) {
	stream << o.get_name();
	return stream;
}

