#ifndef RECONFIGURATIONCALCULATOR_H
#define RECONFIGURATIONCALCULATOR_H

#include <QVector>

class ReconfigurationCalculator
{
public:
    ReconfigurationCalculator(const QVector<int> &_hosts, const QVector<int> &_processes);

    QVector <int> possibleConfiguration();
    QVector <QVector<int> > allPossibleConfigurations();

    QVector<int> nextConfiguration();
    void resetNext();

private:
    void pushProcess();
    void popProcess();

private:
    const QVector<int> m_hosts;
    const QVector<int> m_processes;

    QVector<int> m_hostsRam;
    QVector<int> m_processesInHostsStack;
    int m_currentProcess;
    int m_currentHost;
};

#endif // RECONFIGURATIONCALCULATOR_H
