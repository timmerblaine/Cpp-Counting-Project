#include "usage.h"

Usage::Usage(std::istream& is) 
// takes in the input stream and converts it
{
   takeIstream(is);
}

void Usage::takeIstream(std::istream& is)
// takes in the input stream and converts it
// WORKS PERFECTLY FUCK YEAH!!
{
   flag state = CHAR;
   unsigned int orderCounter = 0;
   char curr;
   std::string active;

   while (is.peek() != EOF) {
      ++orderCounter;
      is.get(curr);      
      addChar(std::string (1, curr));

      if (std::isalpha(curr)) {
         curr = tolower(curr);
         if (state == WORD) {
            active.push_back(curr);
         }
         else {
            active.assign(1, curr);
         }
         state  = WORD;
      }
      else if (std::isdigit(curr)) {
         if (state == NUMBER) {
            active.push_back(curr);
         }
         else {
            active.assign(1, curr);
	 }
         state = NUMBER;
      }
      else 
         state = CHAR;
      // Should ONLY become CHAR state if non-alphanum character
      
      if (stateOf(is.peek()) != state && state != CHAR) {
         addUsage(active, orderCounter);
      }
   }
}

void Usage::printStats() const
// Prints top ten from each map
{
   int charShown;
   charMap.size() >= 10 ? charShown = 10: charShown = charMap.size();

   std::cout << "Total " << charMap.size() << " different characters, ";
   std::cout << charShown << " most used characters:\n";
   std::set<std::pair<std::string,unsigned int>, greaterValue> set(charMap.begin(), charMap.end());
   auto setItr = set.begin();
   for (int i = 0; i < charShown; i++) {
      std::cout << "No. " << i << ": ";
      if (setItr->first == "\n")
         std::cout << "\\n";
      else
         std::cout << setItr->first;
      std::cout << "\t\t" << setItr->second << "\n";
      ++setItr;
   }
   std::cout << std::endl;
   printStats(wordMap, "word");
   printStats(numberMap, "numbers");
    
}

void Usage::printStats(std::unordered_map<std::string, 
	std::pair<unsigned int, unsigned int>> map, std::string type) const
{
   std::set<std::pair<std::string,std::pair<unsigned int, unsigned int>>, 
	greaterValue> set(map.begin(), map.end());
   int numShown;
   map.size() > 10 ? numShown = 10 : numShown = map.size();

   std::cout << "Total " << map.size() << " different " << type << ", ";
   std::cout << numShown << " most used " << type << ":\n";

   auto itr = set.begin();
   for (int i = 0; i < numShown; i++) 
   {
      std::cout << "No. " << i << ": " << itr->first << "\t\t" << itr->second.first << "\n";
      itr++;
   }
   std::cout << std::endl;
}

void Usage::addChar(const std::string& input)
{
   if (charMap.find(input) == charMap.end())
      charMap.insert(std::pair<std::string,unsigned int>(input, 1));
   else {
      auto orderedItr = charMap.find(input);
      ++(orderedItr->second);
   } 
}

void Usage::addUsage(const std::string & input, unsigned int order)
{  	
   if (isWord(input)) 
      addUsage(wordMap, input, order);  
   if (isNumber(input))
      addUsage(numberMap, input, order);
}

void Usage::addUsage(std::unordered_map<std::string,std::pair<unsigned int,
	unsigned int>>& map, const std::string& input, unsigned int order)
{
   unsigned int temp;
   if (map.find(input) == map.end()) 
      map.insert(std::pair<std::string,std::pair<unsigned int,
	 	unsigned int>>(input, std::make_pair(1,order)));
   
   else {
      auto itr = map.find(input);
      ++(itr->second.first);
   }
}

bool Usage::isWord(const std::string& str)
{
   for (auto x : str)
      if (!std::isalpha(x))
         return false;
   return true;
}

bool Usage::isNumber(const std::string& str)
{
   for (auto x : str)
      if (!std::isdigit(x))
         return false;
   return true;
}

Usage::flag Usage::stateOf(char c) const
{
   if (std::isalpha(c))
      return WORD;
   if (std::isdigit(c))
      return NUMBER;
   return CHAR;
}  // if c == EOF, return CHAR, preventing duplicates and adding words and nums
