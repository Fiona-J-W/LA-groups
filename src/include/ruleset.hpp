#ifndef RULESET_HPP
#define RULESET_HPP

#include "object.hpp"
#include "rule.hpp"

#include <map>
#include <set>
#include <initializer_list>
#include <string>
#include <ostream>
#include <vector>
#include <tuple>

using std::ostream;
using std::string;
using std::map;
using std::set;
using std::vector;
using std::tuple;
using std::initializer_list;


/**
 * @brief The ruleset class
 *
 * This class contains a set of rules and objects, that might
 * represent a group.
 *
 * @author Florian Weber
 */
class ruleset {
	public:
		/**
		 * @brief the default ctor
		 * @param op the operation in this ruleset
		 */
		ruleset( string op = "°" );
		
		/**
		 * @brief ctor
		 * @param rules a list of rules that will set up everything
		 */
		ruleset( initializer_list<rule> rules );
		
		/**
		 * @copydoc ruleset::ruleset(initializer_list<rule> rules)
		 */
		ruleset( const vector<rule>& rules );
		
		/**
		 * @brief virtual default-destructor
		 */
		virtual ~ruleset() = default;
		
		/**
		 * @brief create a ruleset from some file
		 * @param filename
		 * @return a new ruleset
		 */
		static ruleset from_file( const string &filename );
		
		/**
		 * @brief get a reference to the internal rule-table
		 * @return the reference
		 */
		const map<object, map<object, object> >& get_rule_table();
		
		/**
		 * @brief evaluate two objects
		 * @param key1 the left object
		 * @param key2 the right object
		 * @return the result of the evaluation
		 */
		object get( object key1, object key2 );
		
		/**
		 * @brief check, whether the operation is closed
		 * @return true if it is, false otherwise
		 */
		bool is_closed();
		
		/**
		 * @brief check whether the operation is associative
		 * @return true if it is, false otherwise
		 */
		bool is_associative();
		
		/**
		 * @brief get the list of all non-associative rules
		 * @return a vector of 3-tuples of object
		 */
		vector<tuple<object, object, object> > get_non_associative();
		
		/**
		 * @brief check whether all rules are commutative
		 * @return true if they are, false otherwise
		 */
		bool is_commutative();
		
		/**
		 * @brief get the cyclic subgroup of an element
		 * @param o the element
		 * @return the cyclic subgroup of o
		 * @throw std::invalid_argument if o is not an element of the ruleset
		 */
		set<object> get_cyclic_subgroup(object o);
		
		/**
		 * @brief check whether the ruleset is a cyclic group
		 * @return true if *this is a cyclic group
		 */
		bool is_cyclic();
		
		/**
		 * @brief check whether the ruleset represents a group
		 * @return true if it is a group, false otherwise
		 */
		bool is_group();
		
		/**
		 * @brief get the neutral element, if one exists
		 * @return the neutral element
		 * @throws std::domain_error, if no element exists
		 */
		object get_neutral_element();
		
		/**
		 * @brief check whether the ruleset contains a neutral element
		 * @return true if it does
		 * @note this is in no way faster than get_neutral_element()
		 */
		bool has_neutral_element();
		
		/**
		 * @brief check whether all objects have an inverse one
		 * @param neutral_element the neutral element that has to be created
		 * @return true if all objects have an inverse object
		 */
		bool has_inverse_elements( object neutral_element );
		
		/**
		 * @brief prints the ruleset as table
		 */
		void print();
		
	protected:
		/**
		 * @brief initialize a ruleset from a list of rules
		 * @param rules the rules
		 */
		void init( vector<rule> rules );
		
		/**
		 * @brief a map of the rules
		 */
		map<object, map<object, object> > rules;
		
		/**
		 * @brief the set of all objects used by the ruleset
		 */
		set<object> used_objects;
		
		/**
		 * @brief the operation that is used by the ruleset
		 * @note this is primarily a cosmetic field
		 */
		string operation;
		
		// enable complete access to the streamwriter:
		friend ostream &operator<<( ostream &stream, ruleset &rules );
};

/**
 * @brief writes a ruleset to a stream
 * @param stream the stream
 * @param rules the ruleset to be written
 * @return the original stream
 */
ostream &operator<<( ostream &stream, ruleset &rules );

#endif // RULES_HPP
