#include <QStack>
#include "reconfigurationcalculator.h"

class ReconfigurationCalculatorPrivate
{
public:
ReconfigurationCalculatorPrivate(const QVector<int>& _hosts, const QVector<int>& _processes)
    : m_hosts(_hosts),
      m_processes(_processes),
      m_hostsRam(_hosts),
      m_processesInHosts(),
      m_currentProcess(0),
      m_currentHost(0)
{}

QVector<int> nextConfiguration()
{
    while(m_currentProcess < m_processes.size())
    {
        while(m_currentHost < m_hostsRam.size())
        {
            int processRam = m_processes.at(m_currentProcess);
            int hostRam = m_hostsRam.at(m_currentHost);

            if(hostRam >= processRam)
            {
                // push process
                m_hostsRam[m_currentHost] -= processRam;
                m_processesInHosts << m_currentHost;
                break;
            }
            ++m_currentHost;
        }
        bool placeForProcessIsFound = m_processesInHosts.size() - 1 == m_currentProcess;
        if(placeForProcessIsFound)
            m_currentHost = 0; // go to the next process
        else if(!m_processesInHosts.isEmpty())
        {
            // pop process
            m_currentProcess = m_processesInHosts.size() - 1;
            m_currentHost = m_processesInHosts.back();
            m_processesInHosts.pop_back();
            m_hostsRam[m_currentHost] += m_processes.at(m_currentProcess);
            ++m_currentHost;
            continue;
        }
        else
            return QVector<int>();
        ++m_currentProcess;
    }
    return m_processesInHosts;
}

private:
    const QVector<int> m_hosts;
    const QVector<int> m_processes;

    QVector<int> m_hostsRam;
    QVector<int> m_processesInHosts;
    int m_currentProcess;
    int m_currentHost;
};


ReconfigurationCalculator::ReconfigurationCalculator(const QVector<int>& _hosts, const QVector<int>& _processes)
    : m_hosts(_hosts),
      m_processes(_processes)
{}

QVector<int> ReconfigurationCalculator::possibleConfiguration() const
{
/*    QVector<int> processesInHosts;
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
                processesInHosts << j;
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
            j = processesInHosts.back();
            processesInHosts.pop_back();
            hostsRam[j] += m_processes.at(i);
            ++j;
            continue;
        }
        else
            return QVector<int>();

        ++i;
    }
    return processesInHosts;*/
    ReconfigurationCalculatorPrivate pCalc(m_hosts, m_processes);
    return pCalc.nextConfiguration();
}

QVector<QVector<int> > ReconfigurationCalculator::allPossibleConfigurations()
{

}
