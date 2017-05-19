#include <QString>
#include <QtTest>
#include "xfoil/simulation.h"
#include "xfoil/simulation_proxy.h"
#include "xfoil/qsimulation.h"
#include "xfoil/simulation_results.h"

class Simulation_tests : public QObject
{
    Q_OBJECT

public:
    Simulation_tests();

private Q_SLOTS:
    void CreateProxyObjectNotRunsTheXfoil();
    void RunAndTerminateTheProgram();
    void RunAndEnterMenuThenTerminate();
};

Simulation_tests::Simulation_tests()
{

}

void Simulation_tests::CreateProxyObjectNotRunsTheXfoil()
{
    QSimulationProxy proxy;
    QVERIFY2(proxy.GetStatus() == SimulationProxy::NotRunning, "Failure - Bad object creation");
}
void Simulation_tests::RunAndTerminateTheProgram()
{
    QSimulationProxy proxy;
    proxy.Run();
    QVERIFY2(proxy.GetStatus() != SimulationProxy::NotRunning, "Failure - process did not start - invalid state");
    proxy.Terminate();
    QVERIFY2(proxy.GetStatus() == SimulationProxy::NotRunning, "Failure - process not terminated - invalid state");
}
void Simulation_tests::RunAndEnterMenuThenTerminate()
{
    QSimulationProxy proxy;
    proxy.AddCommand("NACA 0012");
    proxy.AddCommand("OPER");
    proxy.AddCommand("ALFA 0.0");
    proxy.AddCommand("CPWR test.dat");
    proxy.Run();
    QVERIFY2(proxy.GetStatus() != SimulationProxy::NotRunning, "Failure - process did not start - invalid state");
    proxy.Terminate();
    QVERIFY2(proxy.GetStatus() == SimulationProxy::NotRunning, "Failure - process not terminated - invalid state");
}

QTEST_APPLESS_MAIN(Simulation_tests)

#include "tst_simulation_tests.moc"
