#include "ruleset.hpp"

#include "util.hpp"

#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <iostream>

using std::cout;
using std::invalid_argument;
using std::domain_error;
using std::ifstream;
using std::make_tuple;
using std::max;
using std::endl;

ruleset::ruleset( string op ) {
	operation = op;
}

ruleset::ruleset( initializer_list<rule> rules ) {
	vector<rule> tmp;
	for( auto r: rules ) {
		tmp.push_back( r );
	}
	init( tmp );
}

ruleset::ruleset( const vector<rule>& rules ) {
	init( rules );
}

void ruleset::init( vector<rule> rules ) {
	if( rules.empty() ) {
		throw invalid_argument( "no rules were provided" );
	}
	operation = rules.begin()->operation;
	for( rule r: rules ) {
		if( r.operation != operation ) {
			throw invalid_argument( "different operations in ruleset" );
		}
		this->rules[r.val_1][r.val_2] = r.result;
		used_objects.insert( r.val_1 );
		used_objects.insert( r.val_2 );
		used_objects.insert( r.result );
	}
}

const map<object, map<object, object> > & ruleset::get_rule_table() {
	return rules;
}

object ruleset::get( object key1, object key2 ) {
	if( rules.count( key1 ) ) {
		if( rules[key1].count( key2 ) ) {
			return rules[key1][key2];
		}
	}
	return object( "" );
}

ruleset ruleset::from_file( const string &filename ) {
	ifstream file( filename );
	string line;
	vector<rule> rules;
	while( getline( file, line ) ) {
		rules.emplace_back( line );
	}
	return ruleset( rules );
}

bool ruleset::is_closed() {
	for( auto i: used_objects ) {
		if( !rules.count( i ) ) {
			return false;
		}
		for( auto j: used_objects ) {
			if( !rules[i].count( j ) ) {
				return false;
			}
		}
	}
	return true;
}

bool ruleset::is_associative() {
	if( !is_closed() ) {
		return false;
	}
	for( auto i: used_objects ) {
		for( auto j: used_objects ) {
			for( auto k: used_objects ) {
					if( rules[i][ rules[j][k] ] != rules[ rules[i][j] ][k] ) {
					return false;
				}
			}
		}
	}
	return true;
}

vector<tuple<object, object, object> > ruleset::get_non_associative() {
	vector<tuple<object, object, object> > returnlst;
	for( auto i: used_objects ) {
		for( auto j: used_objects ) {
			for( auto k: used_objects ) {
				if( get( i, get( j, k ) ) != get( get( i, j ), k ) ) {
					returnlst.emplace_back( make_tuple( i, j, k ) );
				}
			}
		}
	}
	return returnlst;
}

bool ruleset::is_commutative(){
	for(auto i: used_objects){
		for(auto j: used_objects){
			if( get(i,j) != get(j,i) ){
				return false;
			}
		}
	}
	return true;
}

set<object> ruleset::get_cyclic_subgroup(object o){
	if(! used_objects.count(o) ){
		throw std::invalid_argument("object is not part of the group");
	}
	set<object> returnlst;
	object tmp = o;
	while( returnlst.insert(tmp).second ){
		tmp = get(tmp, o);
	}
	return returnlst;
}

bool ruleset::is_cyclic(){
	if( !is_group() ){
		return false;
	}
	unsigned int element_count = used_objects.size();
	for(auto o: used_objects){
		if( get_cyclic_subgroup(o).size() == element_count ){
			return true;
		}
	}
	return false;
}

bool ruleset::is_group() {
	if( !is_associative() ) return false;
	try {
		return has_inverse_elements( get_neutral_element() );
	} catch( domain_error &e ) {
		return false;
	}
}

object ruleset::get_neutral_element() {
	for( auto candidat: used_objects ) {
		for( auto x: used_objects ) {
			if( rules[candidat][x] != x || rules[x][candidat] != x ) {
				goto next_candidat;
			}
		}
		return candidat;
	next_candidat:
		;
	}
	throw domain_error( "neutral element does not exist" );
}

bool ruleset::has_neutral_element() {
	try {
		get_neutral_element();
		return true;
	} catch( domain_error &e ) {
		return false;
	}
}

bool ruleset::has_inverse_elements( object neutral_element ) {
	if( !is_closed() ) {
		return false;
	}
	for( auto element: used_objects ) {
		bool found_inverse = false;
		for( auto x: used_objects ) {
			if( rules[element][x] == neutral_element && rules[x][element] == neutral_element ) {
				found_inverse = true;
				break;
			}
		}
		if( !found_inverse ) {
			return false;
		}
	}
	return true;
}

void ruleset::print() {
	size_t max_length = 0;
	for( auto o: used_objects ) {
		max_length = max( max_length, u8len( o.get_name() ) );
	}
	auto ws_helper = []( int n ) {
		for( int i = 0; i < n; ++i ) {
			cout << " ";
		}
	};
	ws_helper( max_length );
	cout << " | ";
	for( auto o: used_objects ) {
		ws_helper( max_length - u8len( o.get_name() ) );
		cout << o << " | ";
	}
	cout << "\n";
	for( unsigned int i = 0; i < max_length + 1; ++i ) {
		cout << "-";
	}
	cout << "+";
	for( unsigned int i = 0; i < used_objects.size(); ++i ) {
		for( unsigned int j = 0; j < max_length + 2; ++j ) {
			cout << "-";
		}
		cout << "+";
	}
	cout << "\n";
	for( auto o1: used_objects ) {
		cout << o1;
		ws_helper( max_length - u8len( o1.get_name() ) );
		cout << " | ";
		for( auto o2: used_objects ) {
			object tmp = get( o1, o2 );
			ws_helper( max_length - u8len( tmp.get_name() ) );
			cout << tmp << " | ";
		}
		cout << "\n";
	}
	cout << endl;
}




ostream &operator<<( ostream &stream, ruleset &rules ) {
	for( auto & i: rules.used_objects ) {
		for( auto & j: rules.used_objects ) {
			stream << rule( i, j, rules.get( i, j ), rules.operation ) << "\n";
		}
	}
	return stream;
}
