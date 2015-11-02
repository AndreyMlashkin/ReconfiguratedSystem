#include <QStack>
#include "reconfigurationcalculator.h"

ReconfigurationCalculator::ReconfigurationCalculator(const QVector<int> _hosts, const QVector<int> _processes)
    : m_hosts(_hosts),
      m_processes(_processes)
{}

QVector<int> ReconfigurationCalculator::possibleConfiguration() const
{
    QStack<int> processesInHosts;
    QVector<int> hostsRam = m_hosts;

    int i = 0;  // current process
    int j = 0;  // current host

    while(i < m_processes.size())
    {
        while(j < hostsRam.size())
        {
            int processRam = m_processes.at(i);
            int hostRam = hostsRam.at(j);

            if(hostRam >= processRam)
            {
                // push process
                hostsRam[j] -= processRam;
                processesInHosts.push(j);
                break;
            }
            ++j;
        }

        bool placeForProcessIsFound = processesInHosts.size() - 1 == i;
        if(placeForProcessIsFound)
            j = 0; // go to the next process
        else if(!processesInHosts.isEmpty())
        {
            // pop process
            i = processesInHosts.size() - 1;
            j = processesInHosts.pop();
            hostsRam[j] += m_processes.at(i);
            ++j;
            continue;
        }
        else
            return QVector<int>();

        ++i;
    }
    return processesInHosts.toList().toVector();
}
