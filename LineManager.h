#ifndef _SDDS_LINEMANAGER_H
#define _SDDS_LINEMANAGER_H
#include "Workstation.h"
#include <vector>
namespace sdds {


	class LineManager  {
		std::vector <Workstation*> m_activeLine; //the collection of workstations for the current assembly line.
		size_t m_cntCustomerOrder; //the total number of CustomerOrder objects
		Workstation* m_firstStation; //points to the first active station on the current line
	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void reorderStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;

	};
}
#endif

