
#include "reconfigurationcalculator.h"


ReconfigurationCalculator::ReconfigurationCalculator(const QVector<int>& _hosts, const QVector<int>& _processes)
    : m_hosts(_hosts),
      m_processes(_processes),
      m_hostsRam(_hosts),
      m_processesInHostsStack(),
      m_currentProcess(0),
      m_currentHost(0)
{}

QVector<int> ReconfigurationCalculator::possibleConfiguration()
{
    return nextConfiguration();
}

QVector<QVector<int> > ReconfigurationCalculator::allPossibleConfigurations()
{
    resetNext();

    QVector<QVector<int> > ans;
    forever
    {
        const QVector<int> configuration = nextConfiguration();
        if(configuration.isEmpty())
            break;
        ans << configuration;

    }
    return ans;
}

QVector<int> ReconfigurationCalculator::nextConfiguration()
{
    if(!m_processesInHostsStack.isEmpty())
        popProcess();

    while(m_currentProcess < m_processes.size())
    {
        while(m_currentHost < m_hostsRam.size())
        {
            int processRam = m_processes.at(m_currentProcess);
            int hostRam = m_hostsRam.at(m_currentHost);

            if(hostRam >= processRam)
            {
                pushProcess();
                break;
            }
            ++m_currentHost;
        }
        bool placeForProcessIsFound = m_processesInHostsStack.size() - 1 == m_currentProcess;
        if(placeForProcessIsFound)
            m_currentHost = 0; // go to the next process
        else if(!m_processesInHostsStack.isEmpty())
        {
            popProcess();
            continue;
        }
        else
            return QVector<int>();
        ++m_currentProcess;
    }
    return m_processesInHostsStack;
}

void ReconfigurationCalculator::resetNext()
{
    m_hostsRam = m_hosts;
    m_processesInHostsStack.resize(0);
    m_currentProcess = 0;
    m_currentHost = 0;
}

void ReconfigurationCalculator::pushProcess()
{
    int processRam = m_processes.at(m_currentProcess);
    m_hostsRam[m_currentHost] -= processRam;
    m_processesInHostsStack << m_currentHost;
}

void ReconfigurationCalculator::popProcess()
{
    m_currentProcess = m_processesInHostsStack.size() - 1;
    m_currentHost = m_processesInHostsStack.back();
    m_processesInHostsStack.pop_back();
    m_hostsRam[m_currentHost] += m_processes.at(m_currentProcess);
    ++m_currentHost;
}
