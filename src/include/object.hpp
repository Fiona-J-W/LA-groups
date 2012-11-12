#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string>
#include <ostream>
#include <unordered_map>

using std::unordered_map;
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
		 * @brief the id of the object
		 */
		int id;
		
		/**
		 * @brief a hashmap that saves the names of all objects
		 */
		static unordered_map<int, string> name_map;
		
		/**
		 * @brief a hashmap that saves the names of all objects
		 */
		static unordered_map<string, int> id_map;
		
		/**
		 * @brief the last used id
		 */
		static int last_id;
};

/**
 * @brief writes an object to a stream
 * @param stream the stream
 * @param o the object that will be written
 * @return the original stream
 */
ostream &operator<<( ostream &stream, object o );



#endif // OBJECT_HPP
