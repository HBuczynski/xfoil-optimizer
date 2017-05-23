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
    void CreateHandlerObjectSavesGeometry();
    void RunSimulationTestResultsFile();
};

SimulationHandler_tests::SimulationHandler_tests()
{

}
void SimulationHandler_tests::CreateHandlerObjectSavesGeometry()
{
    SimulationHandler handler(1213);
}

void SimulationHandler_tests::RunSimulationTestResultsFile()
{

}


QTEST_MAIN(SimulationHandler_tests)

#include "tst_simulation_handler_tests.moc"
