#include <QString>
#include <QtTest>
#include <QThread>
#include "xfoil/simulation.h"
#include "xfoil/simulation_results.h"
#include "optimizer/geometry.h"

#include <iostream>
class SimulationHandler_tests : public QObject
{
    Q_OBJECT

public:
    SimulationHandler_tests();

private Q_SLOTS:
    void LoadNACAProfileWithHandlerObject();
    void CreateHandlerObjectSavesGeometry();
    void RunSimulationTestResultsFile();
    void NotRunningSimulationThrows();
};

SimulationHandler_tests::SimulationHandler_tests()
{

}
void SimulationHandler_tests::LoadNACAProfileWithHandlerObject()
{
    Geometry profile = SimulationHandler::GetNACAAirfoil("0012");
    QVERIFY(profile.GetPoints().size() > 0);
}

void SimulationHandler_tests::CreateHandlerObjectSavesGeometry()
{
    SimulationHandler handler(SimulationHandler::GetNACAAirfoil("0012"));
}

void SimulationHandler_tests::RunSimulationTestResultsFile()
{
    QVERIFY(utility::fileExists("lol.txt"));
}
void SimulationHandler_tests::NotRunningSimulationThrows()
{
    SimulationHandler handler(SimulationHandler::GetNACAAirfoil("0012"));
}

QTEST_MAIN(SimulationHandler_tests)

#include "tst_simulation_handler_tests.moc"
