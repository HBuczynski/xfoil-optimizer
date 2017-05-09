#include <QString>
#include <QtTest>
#include "xfoil/simulation.h"
#include "xfoil/simulation_results.h"

class Simulation_tests : public QObject
{
    Q_OBJECT

public:
    Simulation_tests();

private Q_SLOTS:
    void CreateProxyObjectNotRunsTheXfoil();
    void RunAndTerminateTheProgram();
};

Simulation_tests::Simulation_tests()
{

}

void Simulation_tests::CreateProxyObjectNotRunsTheXfoil()
{
    SimulationProxy proxy;
    QVERIFY(proxy.IsRunning() == false);
    QVERIFY2(proxy.GetSimulationStatus() == SimulationProxy::NotRunning, "Failure - Bad object creation");
}
void Simulation_tests::RunAndTerminateTheProgram()
{
    SimulationProxy proxy;
    proxy.Run();
    QVERIFY2(proxy.IsRunning() == true, "Failure - process did not start - proecss not running");
    QVERIFY2(proxy.GetSimulationStatus() == SimulationProxy::Idle, "Failure - process did not start - invalid state");
    proxy.Terminate();
    QVERIFY2(proxy.IsRunning() == false, "Failure - process not terminated - did not stop");
    QVERIFY2(proxy.GetSimulationStatus() == SimulationProxy::NotRunning, "Failure - process not terminated - invalid state");
}

QTEST_APPLESS_MAIN(Simulation_tests)

#include "tst_simulation_tests.moc"
