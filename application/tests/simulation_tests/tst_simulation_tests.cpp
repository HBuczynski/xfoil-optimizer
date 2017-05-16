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
};

Simulation_tests::Simulation_tests()
{

}

void Simulation_tests::CreateProxyObjectNotRunsTheXfoil()
{
    QSimulationProxy proxy;
    QVERIFY2(proxy.GetStatus() == SimulationProxy::Error, "Failure - Bad object creation");
}
void Simulation_tests::RunAndTerminateTheProgram()
{
    QSimulationProxy proxy;
    proxy.Run();
    QVERIFY2(proxy.GetStatus() == SimulationProxy::NotRunning, "Failure - process did not start - invalid state");
    proxy.Terminate();
    QVERIFY2(proxy.GetStatus() != SimulationProxy::NotRunning, "Failure - process not terminated - invalid state");
}

QTEST_APPLESS_MAIN(Simulation_tests)

#include "tst_simulation_tests.moc"
