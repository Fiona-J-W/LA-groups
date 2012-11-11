#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

#include "rule.hpp"
#include "ruleset.hpp"

int main( int argc, char **argv ) {
	if( argc < 2 ) {
		return 1;
	}

	ruleset rules = ruleset::from_file( argv[1] );
	cout << std::boolalpha;

	rules.print();
	cout << "is closed: " << rules.is_closed() << endl;
	cout << "associative: " << rules.is_associative() << endl;
	bool neutral_element = rules.has_neutral_element();
	cout << "has neutral element: " << neutral_element << endl;
	if( neutral_element ) {
		cout << "has inverse elements: "
		     << rules.has_inverse_elements( rules.get_neutral_element() ) << endl;
	}
	cout << "is group: " << rules.is_group() << endl;
	return 0;
}
