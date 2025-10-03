#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    /*meant for product name, book author, and clothing brand
        keyword is length >=2,  any punctuation splits the keyword -> you get multiple keywords, so check for only alphanumeric
        store keywords in a set (dictionary for only keys), no need to store any values
        needs to be case-insensitive, probably convert to lowercase
    */

    set<string> setOfKeys;        //this will hold our keywords for easy searching
    string key;                   //I will be storing possible keys in here to then add to the set

    for(size_t i = 0; i < rawWords.size(); ++i){

        unsigned char checker = static_cast<unsigned char>(rawWords[i]);        //this loop basically just walks every char in rawWord, taking one so we can check is alphanum
                                                                                //use unsigned for cctype
        if(isalnum(checker)){               //checks alphanum
            key.push_back(rawWords[i]);         //if it is add to possible key
        }else{                                  //otherwise we ran into a punctuation so we check if our resulting key is valid
            if(key.size() < 2){                 //not valid
                key.clear();                    //throw it away
            }else{
                setOfKeys.insert(convToLower(key)); //otherwise add it to the set and make sure it in lowercase (so it is case-insensitive)
                key.clear();                            //cleanup for next key
            }
        }        
    }

    if(key.size() >= 2){        
        setOfKeys.insert(convToLower(key));  //if the loop ends without hitting a punctuation, there is a possibility that we could lose a key, this is to check for that
    }

    return setOfKeys;


}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
