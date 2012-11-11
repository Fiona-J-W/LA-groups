#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
using std::string;

/**
 * @brief strip all surrounding whitespace from a string
 * @param str the string
 * @return the stripped string
 */
string strip( string str );

/**
 * @brief counts the number of codepoints in an utf8-string
 * @param str the utf8-string
 * @return the number of unicode-codepoints
 */
size_t u8len( const string &str );


#endif // UTIL_HPP
