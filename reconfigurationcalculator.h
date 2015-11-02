#ifndef RECONFIGURATIONCALCULATOR_H
#define RECONFIGURATIONCALCULATOR_H

#include <QVector>

class ReconfigurationCalculator
{
public:
    ReconfigurationCalculator(const QVector<int> &_hosts, const QVector<int> &_processes);

    QVector <int> possibleConfiguration() const;
    QVector <QVector<int> > allPossibleConfigurations();

private:


private:
    QVector<int> m_hosts;
    QVector<int> m_processes;
};

#endif // RECONFIGURATIONCALCULATOR_H
