/*
* Name - Anuj Verma
* Seneca Email - averma100@myseneca.ca
* Seneca Student ID - 180483216
* Date of completion - 2023/07/29
*/
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.


#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <string>

namespace sdds {
   class Station {
      int s_stationID{};
      std::string s_nameOfItem{};
      std::string s_descriptionOfStation{};
      unsigned s_nextSerialNumber{};
      unsigned s_itemsInStock{};

      static size_t m_widthField;
      static size_t id_generator;

   public:
      Station(const std::string& s);
      const std::string& getItemName() const;
      size_t getNextSerialNumber();
      size_t getQuantity() const;
      void updateQuantity();
      void display(std::ostream& os, bool full) const;
   };
}
#endif // !SDDS_STATION_H
