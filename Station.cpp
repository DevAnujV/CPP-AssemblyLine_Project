/*
* Name - Anuj Verma
* Seneca Email - averma100@myseneca.ca
* Seneca Student ID - 180483216
* Date of completion - 2023/07/29
*/
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include <string>
#include <iomanip>
#include "Utilities.h"
#include "Station.h"

using namespace std;

namespace sdds {

   size_t Station::m_widthField = 0;
   size_t Station::id_generator = 0;

   Station::Station(const std::string& s)
   {
      bool more = true;
      size_t nextPosition = 0;
      Utilities localUtilityObject;
      s_stationID = ++Station::id_generator; // adding the id to station and incrementing. Starting at 0

      s_nameOfItem = localUtilityObject.extractToken(s, nextPosition, more);
      s_nextSerialNumber = stoi((localUtilityObject.extractToken(s, nextPosition, more)));
      s_itemsInStock = stoi((localUtilityObject.extractToken(s, nextPosition, more)));

      Station::m_widthField = localUtilityObject.getFieldWidth();

      s_descriptionOfStation = localUtilityObject.extractToken(s, nextPosition, more);
   }

   const std::string& Station::getItemName() const
   {
      return s_nameOfItem;
   }

   size_t Station::getNextSerialNumber()
   {
      return s_nextSerialNumber++;
   }

   size_t Station::getQuantity() const
   {
      return s_itemsInStock;
   }

   void Station::updateQuantity()
   {
      if (s_itemsInStock - 1 >= 0) {
         s_itemsInStock--;
      }
   }

   void Station::display(std::ostream& os, bool full) const
   {
      os << setw(3) << setfill('0') << s_stationID << " | ";
      os.setf(ios::left);
      os << setfill(' ') << setw(m_widthField) << s_nameOfItem;
      os.unsetf(ios::left);
      os << "| " << setw(6) << setfill('0') << s_nextSerialNumber << " | ";

      if (full) {
         os << setfill(' ') << setw(4) << s_itemsInStock << " | " << s_descriptionOfStation;
      }
      os << endl;
   }

}