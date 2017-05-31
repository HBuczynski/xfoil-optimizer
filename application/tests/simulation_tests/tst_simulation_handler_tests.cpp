#include <QString>
#include <QtTest>
#include <QThread>
#include "xfoil/simulation.h"
#include "xfoil/simulation_results.h"
#include "optimizer/geometry.h"
#include "utility/config.h"

#include <iostream>
#include <sstream>
#include <iomanip>
class SimulationHandler_tests : public QObject
{
    Q_OBJECT

public:
    SimulationHandler_tests();

private Q_SLOTS:
    void LoadNACAProfileWithHandlerObject();
    void CreateHandlerObjectSavesGeometry();
    void RunSimulationTestResultsFile();
    void RunSimulationResultsAreLoaded();
    void NotRunningSimulationThrows();
    void DeleteHandlerObectCleansTemporaryFiles();
    void CreateSimulationSchedulerSpawnsNewProcess();
    void CalculatingTheSameGeometryObjectTwiceDoesNotDoubleDataPoints();
    void HandleMultipleParallelSimulations();
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
void SimulationHandler_tests::RunSimulationResultsAreLoaded()
{
    Geometry testGeom = SimulationHandler::GetNACAAirfoil("0012");
    SimulationHandler *handler = new SimulationHandler(testGeom);
    handler->Run();
    while(handler->PollStatus() == SimulationHandler::Running);
    QVERIFY(testGeom.GetResults().GetPolarPointCount() != 0);
    delete handler;
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
void SimulationHandler_tests::CreateSimulationSchedulerSpawnsNewProcess()
{
    Config::Optimization::SimulationParams params;
    SimulationScheduler *sched = new SimulationScheduler(params);
    Geometry testGeom = SimulationHandler::GetNACAAirfoil("0012");
    sched->AddTask(SimulationScheduler::Task(&testGeom));
    delete sched;

}
void SimulationHandler_tests::CalculatingTheSameGeometryObjectTwiceDoesNotDoubleDataPoints()
{
    Config::Optimization::SimulationParams params;
    SimulationScheduler *sched = new SimulationScheduler(params);
    Geometry testGeom = SimulationHandler::GetNACAAirfoil("0012");
    sched->AddTask(SimulationScheduler::Task(&testGeom));
    while(!testGeom.GetResults().IsCalculated());
    int points = testGeom.GetResults().GetPolarPointCount();
    sched->AddTask(SimulationScheduler::Task(&testGeom));
    delete sched;
    QVERIFY(points == testGeom.GetResults().GetPolarPointCount());
}

void SimulationHandler_tests::HandleMultipleParallelSimulations()
{
    Config::Optimization::SimulationParams params;
    std::stringstream ss;
    SimulationScheduler *sched = new SimulationScheduler(params);
    Geometry testGeom[10];
    for(int i = 2; i < 12; ++i)
    {
        ss<<std::setfill('0') << std::setw(4) << i;
        testGeom[i-2] = SimulationHandler::GetNACAAirfoil(ss.str());
        ss.str("");
        ss.clear();

    }
    for(int i = 0; i < 10; ++i)
    {
        sched->AddTask(SimulationScheduler::Task(&(testGeom[i])));
    }

    while(!sched->IsTasksFinished())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete sched;

    for(int i = 0; i < 10; ++i)
    {
        std::cout<<testGeom[i].GetResults().IsCalculated();
        QVERIFY(testGeom[i].GetResults().IsCalculated());
    }
}

QTEST_APPLESS_MAIN(SimulationHandler_tests)

#include "tst_simulation_handler_tests.moc"
