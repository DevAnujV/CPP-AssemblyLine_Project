#include <iostream>
#include "Workstation.h"
using namespace std;
namespace sdds {

	std::deque<CustomerOrder> g_pending{};
	std::deque<CustomerOrder> g_completed{};
	std::deque<CustomerOrder> g_incomplete{};

	Workstation::Workstation(const std::string& str) : Station(str)
	{
	}
	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder()
	{
		if (!m_orders.empty()) {
			if ((m_orders.front().isItemFilled(this->getItemName())) || 
				(!m_orders.front().isItemFilled(this->getItemName()) && this->getQuantity() < 1)) {
				if (m_pNextStation != nullptr) {
					*m_pNextStation += move(m_orders.front());
				}
				else {
					if (m_orders.front().isOrderFilled()) {
						g_completed.push_back(move(m_orders.front()));
					}
					else {
						g_incomplete.push_back(move(m_orders.front()));
					}
				}
				m_orders.pop_front();
				return true;

			}
		}
		return false;
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(move(newOrder));
		return *this;
	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}

	void Workstation::display(std::ostream& os) const
	{
		if (m_pNextStation != nullptr) {
			os << this->getItemName() << " --> " << m_pNextStation->getItemName() << std::endl;
		}
		else {
			os << this->getItemName() << " --> " << "End of Line" << endl;
		}
	}

}