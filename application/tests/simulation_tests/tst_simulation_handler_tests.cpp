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
    void DeleteHandlerObectCleansTemporaryFiles();
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
    QVERIFY(utility::fileExists((handler.proxy_->GetExePath() + "/" + handler.InstantiateFilename("geometry.dat")).c_str()));
}

void SimulationHandler_tests::RunSimulationTestResultsFile()
{
    SimulationHandler *handler = new SimulationHandler(SimulationHandler::GetNACAAirfoil("0012"));
    handler->Run();
    while(handler->PollStatus() == SimulationHandler::Running);
    std::string resultPath = handler->proxy_->GetExePath() + "/" + handler->InstantiateFilename("result.txt");
    QVERIFY(utility::fileExists(resultPath));
    delete handler;
    QVERIFY(!utility::fileExists(resultPath));
}
void SimulationHandler_tests::NotRunningSimulationThrows()
{
    SimulationHandler handler(SimulationHandler::GetNACAAirfoil("0012"));
}
void SimulationHandler_tests::DeleteHandlerObectCleansTemporaryFiles()
{
    //Todo test also results file//
    SimulationHandler *handler = new SimulationHandler(SimulationHandler::GetNACAAirfoil("0012"));
    std::string path = handler->proxy_->GetExePath() + "/" + handler->InstantiateFilename("geometry.dat");
    QVERIFY(utility::fileExists(path));
    delete handler;
    QVERIFY(!utility::fileExists(path));

}

QTEST_MAIN(SimulationHandler_tests)

#include "tst_simulation_handler_tests.moc"
