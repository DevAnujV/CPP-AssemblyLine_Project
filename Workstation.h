#ifndef _SDDS_WORKSTATION_H
#define _SDDS_WORKSTATION_H
#include "CustomerOrder.h"
#include <deque>
namespace sdds {
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

	class Workstation: public Station {
		Workstation* m_pNextStation;
		std::deque<CustomerOrder> m_orders;
	public:
		Workstation(const std::string& str);
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		Workstation& operator+=(CustomerOrder&& newOrder);
		Workstation* getNextStation() const;
		void setNextStation(Workstation* station = nullptr);
		void display(std::ostream& os) const;

		Workstation(const Workstation& ws) = delete;
		Workstation& operator=(const Workstation& ws) = delete;
		Workstation(Workstation&& ws) = delete;
		Workstation& operator=(Workstation&& ws) = delete;
	};
}
#endif
