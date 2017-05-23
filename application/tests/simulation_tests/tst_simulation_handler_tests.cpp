#include <QString>
#include <QtTest>
#include <QThread>
#include "xfoil/simulation.h"
#include "xfoil/simulation_results.h"

#include <iostream>
class SimulationHandler_tests : public QObject
{
    Q_OBJECT

public:
    SimulationHandler_tests();

private Q_SLOTS:
};

SimulationHandler_tests::SimulationHandler_tests()
{

}



QTEST_MAIN(SimulationHandler_tests)

#include "tst_simulation_handler_tests.moc"
