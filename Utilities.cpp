/*
* Name - Anuj Verma
* Seneca Email - averma100@myseneca.ca
* Seneca Student ID - 180483216
* Date of completion - 2023/07/29
*/
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.


#include <functional>
#include <string>
#include "Utilities.h"

using namespace std;

namespace sdds {

   char Utilities::m_delimiter = 0;

   void Utilities::setFieldWidth(size_t newWidth)
   {
      m_widthField = newWidth;
   }

   size_t Utilities::getFieldWidth() const
   {
      return m_widthField;
   }

   std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
   {
      std::string token;
      std::string::size_type n1;

      n1 = str.find(m_delimiter, next_pos);

      if (n1 != std::string::npos &&  n1 - next_pos <= 1) {
         more = false;
         throw("invalid delimitor place");
      }

      else if (n1 != std::string::npos) {
         token = str.substr(next_pos, (n1 - next_pos));

         // update next pos
         next_pos = ++n1;
         // set more to ture
         more = true;

      }

      else {
         token = str.substr(next_pos); // read file till the end if there is no delimitor
         more = false;

      }

      // updates the m_widthField
      if (m_widthField < token.length()) {
         m_widthField = token.length();
      }

      // to erase spaces
      token.erase(token.begin(), find_if(token.begin(), token.end(), bind1st(not_equal_to<char>(), ' ')));
      token.erase(std::find_if(token.rbegin(), token.rend(), bind1st(not_equal_to<char>(), ' ')).base(), token.end());

      return token;
   }

   void Utilities::setDelimiter(char newDelimiter)
   {
      Utilities::m_delimiter = newDelimiter;
   }

   char Utilities::getDelimiter()
   {
      return Utilities::m_delimiter;
   }

}