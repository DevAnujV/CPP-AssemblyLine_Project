/*
* Name - Anuj Verma
* Seneca Email - averma100@myseneca.ca
* Seneca Student ID - 180483216
* Date of completion - 2023/07/29
*/
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"

using namespace std;

namespace sdds {

   size_t CustomerOrder::m_widthField = {};

   CustomerOrder::CustomerOrder(const std::string& CustOrdrStr)
   {
      Utilities util;
      //util.setDelimiter('|');
      bool continues = true;
      size_t lengthToken = 0;

         m_name = util.extractToken(CustOrdrStr, lengthToken, continues);
         m_product = util.extractToken(CustOrdrStr, lengthToken, continues);
         vector<string> tempItems;
     
         while (continues) {
            string tempToken = util.extractToken(CustOrdrStr, lengthToken, continues);
            m_cntItem++;
            tempItems.push_back(tempToken);
         }
         if (CustomerOrder::m_widthField < util.getFieldWidth()) {
            CustomerOrder::m_widthField = util.getFieldWidth();
         }

         vector<string>::iterator it = tempItems.begin();

         m_lstItem = new Item * [m_cntItem];

         for (size_t i = 0; i < m_cntItem; i++) {
            m_lstItem[i] = new Item(*it++);
         }
   }

   CustomerOrder::CustomerOrder(const CustomerOrder& co) {
      throw "exc";
   }

   CustomerOrder::CustomerOrder(CustomerOrder&& co)noexcept {
      *this = move(co);
   }

   CustomerOrder& CustomerOrder::operator=(CustomerOrder&& co)noexcept {
      if (this != &co) {
         if (co.m_cntItem > 0) {

            // removing memeory before deep copy
            for (size_t i = 0; i < m_cntItem; i++) {
               delete m_lstItem[i];
            }
            delete[] m_lstItem;

            // shallow copy
            m_name = co.m_name;
            m_product = co.m_product;
            m_cntItem = co.m_cntItem;
            CustomerOrder::m_widthField = co.m_widthField;

            //deep copy
            m_lstItem = co.m_lstItem;
            co.m_lstItem = nullptr;
            //co.m_widthField = 0;
            co.m_cntItem = 0;
         }
      }
      return *this;
   }

   CustomerOrder::~CustomerOrder() {
      
      for (size_t i = 0; i < m_cntItem; i++) {
         delete m_lstItem[i];
      }
      delete[] m_lstItem;
   }

   bool CustomerOrder::isOrderFilled() const {
      
      vector<Item>tempVectForAnyOf;
      for (size_t i = 0; i < m_cntItem; i++) {
         tempVectForAnyOf.push_back(*(m_lstItem[i]));
      
      }
      if (any_of(tempVectForAnyOf.begin(), tempVectForAnyOf.end(), [](const Item& i) { return !i.m_isFilled; })) {
         return false; // if any single item in an order is not filled i will return false
      }
         return true;
   }

   //bool CustomerOrder::isItemFilled(const std::string& itemName) const {
   //   vector<Item>tempVectForAnyOf;
   //   for (size_t i = 0; i < m_cntItem; i++) {
   //      tempVectForAnyOf.push_back(*(m_lstItem[i]));

   //   }
   //   bool itemThere = false;

   //   return any_of(tempVectForAnyOf.begin(), tempVectForAnyOf.end(), [&](const Item& i) {
   //      if (i.m_itemName == itemName) {
   //         itemThere = true;
   //         if (i.m_isFilled == true) {
   //            return true;
   //         }
   //         else {
   //            return false; // Return false when the condition is not met
   //         }
   //      }
   //      if ((*(tempVectForAnyOf.end() - 1)).m_itemName == i.m_itemName && itemThere == false) {
   //         return true;
   //      }
   //      return false;
   //      }
   //   );
   //}
 

   bool CustomerOrder::isItemFilled(const std::string& itemName) const
   {
       for (size_t i = 0; i < m_cntItem; i++) {
           if (m_lstItem[i]->m_itemName == itemName) {
               if (!m_lstItem[i]->m_isFilled) {
                   return false;
               }
           }
       }
       return true;
   }

   void CustomerOrder::fillItem(Station& station, std::ostream& os) {

      size_t i = 0;
      //vector<Item>tempVectForAnyOf;
      for (i = 0; i < m_cntItem; i++) {
         //tempVectForAnyOf.push_back(*(m_lstItem[i]));

         if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {
            if (station.getQuantity() >= 1) {
              
                  station.updateQuantity();

                  m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                  m_lstItem[i]->m_isFilled = true;

                  cout << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
                  break;

               
            }
            else {
                  cout << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
               }
            
         }
      }

   }

   void CustomerOrder::display(std::ostream& os) const {
      os << m_name << " - " << m_product << endl;
      for (size_t i = 0; i < m_cntItem; i++) {
         os  << '[' << right << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber << "] " << left << setw(CustomerOrder::m_widthField - 1) << setfill(' ') << m_lstItem[i]->m_itemName << "- ";
         
         m_lstItem[i]->m_isFilled ? os << "FILLED" : os << "TO BE FILLED";
         os << endl;
      }
   }


}