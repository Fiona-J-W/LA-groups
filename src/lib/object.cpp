#include "object.hpp"
using namespace std;

#include "util.hpp"

//put the static objects here:
int object::last_id = 0;
unordered_map<int, string> object::name_map = {{-1, ""}};
unordered_map<string, int> object::id_map = {{"", -1}};
//////////////////////////////////////////

object::object() {
	
}

object::object( string name ) {
	name = strip(name);
	auto tmp = id_map.find(name);
	if( tmp == id_map.end() ){
		id = ++last_id;
		id_map[name] = last_id;
		name_map[id] = name;
	}
	else{
		id = tmp->second;
	}
}

string object::get_name() const {
	return name_map[id];
}

bool object::operator== ( const object &other ) const {
	return id == other.id;
}

bool object::operator!= ( const object &other ) const {
	return id != other.id;
}

bool object::operator< ( const object &other ) const {
	return id < other.id;
}

std::ostream &operator<<( std::ostream &stream, object o ) {
	stream << o.get_name();
	return stream;
}

