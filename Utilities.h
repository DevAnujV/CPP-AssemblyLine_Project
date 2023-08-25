/*
* Name - Anuj Verma
* Seneca Email - averma100@myseneca.ca
* Seneca Student ID - 180483216
* Date of completion - 2023/07/29
*/
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.


#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <string>

namespace sdds {
   class Utilities {

      size_t m_widthField = 1; // Instance Variable - specifies the length of the token extracted; used for display purposes

      // Class Variable
      static char m_delimiter; // separates the tokens in any given std::string object. All Utilities objects in the system share the same delimiter.

   public:

      void setFieldWidth(size_t newWidth); // sets the field width of the current object to the value of parameter newWidth
      size_t getFieldWidth() const; // returns the field width of the current object

      std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

      static void setDelimiter(char newDelimiter);
      static char getDelimiter();
   };

}
#endif // !SDDS_UTILITIES_H
