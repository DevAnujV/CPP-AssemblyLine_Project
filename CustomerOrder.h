/*
* Name - Anuj Verma
* Seneca Email - averma100@myseneca.ca
* Seneca Student ID - 180483216
* Date of completion - 2023/07/29
*/
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.


#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include "Station.h"
#include<string>

namespace sdds {

   class CustomerOrder {
		
		struct Item
		{
			std::string m_itemName;
			size_t m_serialNumber{ 0 }; // this will make sure that the item is filled or not
			bool m_isFilled{ false };

			Item(const std::string& src) : m_itemName(src) {};
		};

		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{};
		Item** m_lstItem{};

	public:
		static size_t m_widthField;

		CustomerOrder() = default;
		CustomerOrder(const std::string& CustOrdrStr);
		CustomerOrder(const CustomerOrder& co);
		CustomerOrder& operator=(const CustomerOrder& co) = delete;
		CustomerOrder(CustomerOrder&& co) noexcept;
		CustomerOrder& operator=(CustomerOrder&& co) noexcept;
		~CustomerOrder();

		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;

   };

}

#endif // !SDDS_CUSTOMERORDER_H
