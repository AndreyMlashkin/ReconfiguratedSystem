#include <iostream>

#include <QCoreApplication>
#include <QVector>
#include <QDebug>

#include "reconfigurationcalculator.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if(argc > 1)
        freopen(argv[1], "r", stdin);

    QVector<int> hosts;
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        int weght;
        cin  >> weght;
        hosts << weght;
    }

    QVector<int> processes;
    int m;
    cin >> m;
    for(int i = 0; i < m; ++i)
    {
        int weght;
        cin >> weght;
        processes << weght;
    }


    ReconfigurationCalculator calculator(hosts, processes);
    qDebug() << calculator.possibleConfiguration();

    return a.exec();
}
