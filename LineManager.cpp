#include<iostream>
#include<fstream>
#include<algorithm>
#include"LineManager.h"
using namespace std;
namespace sdds {
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
    {
            try {
                ifstream filex(file);
                if (filex) {
                    while (!filex.eof()) {
                        std::string tempHolder1, workSpace, nextWorkSpace;
                        std::string::size_type x{};

                        std::getline(filex, tempHolder1);

                        x = tempHolder1.find('|');

                        if (x != std::string::npos) {
                            workSpace = tempHolder1.substr(0, x);
                            nextWorkSpace = tempHolder1.substr(x + 1);
                        }
                        else {
                            workSpace = tempHolder1;
                            nextWorkSpace = "End Of Line";
                        }

                        copy_if(stations.begin(), stations.end(), back_inserter(m_activeLine), [&](Workstation* ws) {
                            return ws->getItemName() == workSpace;
                            });

                        auto it = find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
                            return ws->getItemName() == nextWorkSpace;
                            });

                        if (it != stations.end()) {
                            m_activeLine.back()->setNextStation(*it);
                        }
                        else {
                            m_activeLine.back()->setNextStation(nullptr);
                        }
                    }

                    for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *it1) {
                        bool found = false;
                        for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *it2) {
                            if (it2->getNextStation() != nullptr) {
                                string temp1 = it1->getItemName();
                                string temp2 = it2->getNextStation()->getItemName();

                                if ((it1)->getItemName() == it2->getNextStation()->getItemName()) {
                                    found = true;
                                }
                            }
                            });
                        if (found == false) {
                            m_firstStation = it1;
                            return;
                        }

                        });
                    m_cntCustomerOrder = g_pending.size();
                }
            }
            catch (...) {
                throw("Error in Constructor");
            }

        
	}
    void LineManager::reorderStations()
    {
        Workstation* temp = m_firstStation;
        bool firstTime = true;

        transform(m_activeLine.begin(), m_activeLine.end(), m_activeLine.begin(), [&](Workstation* ws) {
            if (firstTime == false) {
                temp = temp->getNextStation();
                return temp;
            }
            firstTime = false;
            return m_firstStation;
            });
    }

    bool LineManager::run(std::ostream& os)
    {
        static int iterationCounter = 1;
        os << "Line Manager Iteration: " << iterationCounter++ << endl;

        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }
        for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
            ws->fill(os);
        });

        for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
            ws->attemptToMoveOrder();
        });

        return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
    }

    void LineManager::display(std::ostream& os) const
    {
        for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
            ws->display(os);
            });
    }
}