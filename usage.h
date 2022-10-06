#ifndef USAGE_H
#define USAGE_H
#include <map>
#include <unordered_map>
#include <set>
#include <string>
#include <cctype>
#include <iostream>

class Usage {
// Adapters: two hashtable maps and one heap map
private:
   enum flag{WORD, NUMBER, CHAR};
   struct greaterValue
   {  typedef std::pair<std::string,std::pair<unsigned int, unsigned int>> T;
      typedef std::pair<std::string,unsigned int> R;
      bool operator() (const T& lhs, const T& rhs) const
      {
	 if (lhs.second.first != rhs.second.first)
	    return lhs.second.first > rhs.second.first;

	 return lhs.second.second < rhs.second.second;
      }
      bool operator() (const R& lhs, const R& rhs) const
      {
	 if (lhs.second != rhs.second)
	    return lhs.second > rhs.second;

	 return lhs.first < rhs.first;
      }
   };
public:
   // default constructor is USELESS here!
   explicit Usage(std::istream&);   // takes in the input stream and converts it
   void takeIstream(std::istream&); // takes in the input stream and converts it
   void printStats() const;   // Prints top ten from each map
private:
   void addUsage(const std::string&, unsigned int);
   void addChar(const std::string&);
   bool isWord(const std::string& str);
   bool isNumber(const std::string& str);
   void printStats(std::unordered_map<std::string, 
	 std::pair<unsigned int, unsigned int>>, std::string) const;
   void addUsage(std::unordered_map<std::string,std::pair<unsigned int,
	 unsigned int>>&, const std::string&, unsigned int);
   flag stateOf(char c) const;

   std::unordered_map<std::string,
   std::pair<unsigned int,unsigned int>> wordMap, numberMap;
   // pair<0> is occurances, pair<1> is order
   std::map<std::string, unsigned int> charMap;
   // int is occurances, no need for order for ASCII conversion
};

#endif // USAGE_H
