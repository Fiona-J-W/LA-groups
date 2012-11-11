#ifndef RULE_HPP
#define RULE_HPP

#include "object.hpp"

#include <string>
#include <ostream>

using std::string;
using std::ostream;

/**
 * @brief The rule struct
 */
struct rule {
	public:
		/**
		 * @brief ctor that takes the values directly
		 * @param val_1 the first operand to the operation
		 * @param val_2 the second operand to the operation
		 * @param result the result of the operation
		 * @param operation the name of the operation
		 */
		rule( object val_1, object val_2, object result, string operation = "°" );

		/**
		 * @brief ctor that creates a rule from a string
		 * @param str string that descripes the rule in the format „a op b = c“
		 *            where op is the name of the operation
		 * @param operation the name of the operation 
		 */
		rule( string str, string operation = "°" );

		/**
		 * @brief the first operand
		 */
		object val_1;

		/**
		 * @brief the second operand
		 */
		object val_2;

		/**
		 * @brief the result of the operation
		 */
		object result;

		/**
		 * @brief the name of the operation
		 */
		string operation;
};

/**
 * @brief writes a rule to a stream
 * @param stream the stream
 * @param r the rule to be written
 * @return the original stream
 */
ostream &operator<<( ostream &stream, rule r );


#endif // RULE_HPP
