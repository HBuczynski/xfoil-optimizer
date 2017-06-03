#include <QString>
#include <QtTest>
#include <QThread>
#include "xfoil/simulation.h"
#include "optimizer/simulation_results.h"
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
private:
    Config::SimulationParams params;
};

SimulationHandler_tests::SimulationHandler_tests()
{
        params.viscousEnable = false;
}

void SimulationHandler_tests::LoadNACAProfileWithHandlerObject()
{
    Geometry profile = SimulationHandler::GetNACAAirfoil("0012");
    QVERIFY(profile.GetPoints().size() > 0);
}

void SimulationHandler_tests::CreateHandlerObjectSavesGeometry()
{
    SimulationHandler handler(SimulationHandler::GetNACAAirfoil("0012"),params);
    QVERIFY(utility::fileExists((handler.proxy_->GetExePath() + "/" + handler.InstantiateFilename("geometry.dat")).c_str()));
}

void SimulationHandler_tests::RunSimulationTestResultsFile()
{
    SimulationHandler *handler = new SimulationHandler(SimulationHandler::GetNACAAirfoil("0012"), params);
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
    SimulationHandler *handler = new SimulationHandler(testGeom, params);
    handler->Run();
    while(handler->PollStatus() == SimulationHandler::Running);
    QVERIFY(testGeom.GetResults().GetPolarPointCount() != 0);
    delete handler;
}

void SimulationHandler_tests::NotRunningSimulationThrows()
{
    SimulationHandler handler(SimulationHandler::GetNACAAirfoil("0012"),params);
}
void SimulationHandler_tests::DeleteHandlerObectCleansTemporaryFiles()
{
    //Todo test also results file//
    SimulationHandler *handler = new SimulationHandler(SimulationHandler::GetNACAAirfoil("0012"), params);
    std::string path = handler->proxy_->GetExePath() + "/" + handler->InstantiateFilename("geometry.dat");
    QVERIFY(utility::fileExists(path));
    delete handler;
    QVERIFY(!utility::fileExists(path));

}
void SimulationHandler_tests::CreateSimulationSchedulerSpawnsNewProcess()
{
    SimulationScheduler *sched = new SimulationScheduler(params);
    Geometry testGeom = SimulationHandler::GetNACAAirfoil("0012");
    sched->AddTask(Task(&testGeom));
    sched->WaitForFinished();
    delete sched;

}

void SimulationHandler_tests::CalculatingTheSameGeometryObjectTwiceDoesNotDoubleDataPoints()
{
    SimulationScheduler *sched = new SimulationScheduler(params);
    Geometry testGeom = SimulationHandler::GetNACAAirfoil("0012");
    sched->AddTask(Task(&testGeom));
    sched->WaitForFinished();
    int points = testGeom.GetResults().GetPolarPointCount();
    sched->AddTask(Task(&testGeom));
    sched->WaitForFinished();
    delete sched;
    QVERIFY(points == testGeom.GetResults().GetPolarPointCount());
}

void SimulationHandler_tests::HandleMultipleParallelSimulations()
{
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
        sched->AddTask(Task(&(testGeom[i])));
    }

    sched->WaitForFinished();
    delete sched;
    for(int i = 0; i < 10; ++i)
    {
        //std::cout<<testGeom[i].GetResults().IsCalculated();
        QVERIFY(testGeom[i].GetResults().IsCalculated());
    }
}

QTEST_MAIN(SimulationHandler_tests)

#include "tst_simulation_handler_tests.moc"
