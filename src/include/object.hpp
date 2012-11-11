#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string>
#include <ostream>

using std::string;
using std::ostream;

/**
 * @brief The object class
 */
class object {
	public:
		/**
		 * @brief constructs an object in an invalid state
		 */
		object();

		/**
		 * @brief constructs a valid object
		 * @param name the name of the object
		 */
		object( string name );

		/**
		 * @brief get the name of the object
		 * @return the name
		 */
		string get_name() const;

		/**
		 * @brief compares two objects for equality
		 * @param other the other object
		 * @return whether the objects are equal
		 */
		bool operator==( const object &other ) const;

		/**
		 * @brief compares two objects for unequality
		 * @param other the other object
		 * @return whether the objects are unequal
		 */
		bool operator!=( const object &other ) const;

		/**
		 * @brief orders two objects based on their name (needed for some containers)
		 * @param other another object
		 * @return whether *this is in some way smaller than another object
		 */
		bool operator<( const object &other ) const;
	private:
		/**
		 * @brief the name of the object
		 */
		string _name;
};

/**
 * @brief writes an object to a stream
 * @param stream the stream
 * @param o the object that will be written
 * @return the original stream
 */
ostream &operator<<( ostream &stream, object o );



#endif // OBJECT_HPP
