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
    Geometry profile = SimulationHandler::getNACAAirfoil("0012");
    QVERIFY(profile.getPoints().size() > 0);
}

void SimulationHandler_tests::CreateHandlerObjectSavesGeometry()
{
    Geometry geom = SimulationHandler::getNACAAirfoil("0012");
    SimulationHandler handler(geom,params);
    QVERIFY(utility::fileExists((handler.proxy_->getExePath() + "/" + handler.instantiateFilename("geometry.dat")).c_str()));
}

void SimulationHandler_tests::RunSimulationTestResultsFile()
{
    Geometry geom = SimulationHandler::getNACAAirfoil("0012");
    SimulationHandler *handler = new SimulationHandler(geom, params);
    handler->run();
    while(handler->pollStatus() == SimulationHandler::Running);
    std::string resultPath = handler->proxy_->getExePath() + "/" + handler->instantiateFilename("result.txt");
    QVERIFY(utility::fileExists(resultPath));
    delete handler;
    QVERIFY(!utility::fileExists(resultPath));
}
void SimulationHandler_tests::RunSimulationResultsAreLoaded()
{
    Geometry testGeom = SimulationHandler::getNACAAirfoil("0012");
    SimulationHandler *handler = new SimulationHandler(testGeom, params);
    handler->run();
    while(handler->pollStatus() == SimulationHandler::Running);
    QVERIFY(testGeom.getResults().getPolarPointCount() != 0);
    delete handler;
}

void SimulationHandler_tests::NotRunningSimulationThrows()
{
    Geometry geom = SimulationHandler::getNACAAirfoil("0012");
    SimulationHandler handler(geom,params);
}
void SimulationHandler_tests::DeleteHandlerObectCleansTemporaryFiles()
{
    //Todo test also results file//
    Geometry geom = SimulationHandler::getNACAAirfoil("0012");
    SimulationHandler *handler = new SimulationHandler(geom, params);
    std::string path = handler->proxy_->getExePath() + "/" + handler->instantiateFilename("geometry.dat");
    QVERIFY(utility::fileExists(path));
    delete handler;
    QVERIFY(!utility::fileExists(path));

}
void SimulationHandler_tests::CreateSimulationSchedulerSpawnsNewProcess()
{
    SimulationScheduler *sched = new SimulationScheduler(params);
    Geometry testGeom = SimulationHandler::getNACAAirfoil("0012");
    sched->addTask(Task(&testGeom));
    sched->waitForFinished();
    delete sched;

}

void SimulationHandler_tests::CalculatingTheSameGeometryObjectTwiceDoesNotDoubleDataPoints()
{
    SimulationScheduler *sched = new SimulationScheduler(params);
    Geometry testGeom = SimulationHandler::getNACAAirfoil("0012");
    sched->addTask(Task(&testGeom));
    sched->waitForFinished();
    int points = testGeom.getResults().getPolarPointCount();
    sched->addTask(Task(&testGeom));
    sched->waitForFinished();
    delete sched;
    QVERIFY(points == testGeom.getResults().getPolarPointCount());
}

void SimulationHandler_tests::HandleMultipleParallelSimulations()
{
    std::stringstream ss;
    SimulationScheduler *sched = new SimulationScheduler(params);

    Geometry testGeom[10];
    for(int i = 2; i < 12; ++i)
    {
        ss<<std::setfill('0') << std::setw(4) << i;
        testGeom[i-2] = SimulationHandler::getNACAAirfoil(ss.str());
        ss.str("");
        ss.clear();
    }
    std::vector<Task> inputPopulation;
    for(int i = 0; i < 10; ++i)
    {
        inputPopulation.push_back(Task(&(testGeom[i])));
    }
    sched->addBatchTask(inputPopulation);
    sched->waitForFinished();
    delete sched;
    for(int i = 0; i < 10; ++i)
    {
        //std::cout<<testGeom[i].GetResults().IsCalculated();
        QVERIFY(testGeom[i].getResults().isCalculated());
    }
}

QTEST_MAIN(SimulationHandler_tests)

#include "tst_simulation_handler_tests.moc"
