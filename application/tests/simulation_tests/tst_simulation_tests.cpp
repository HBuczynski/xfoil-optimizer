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
    void CreateAndExitApplication();
};

Simulation_tests::Simulation_tests()
{

}

void Simulation_tests::CreateAndExitApplication()
{
    SimulationProxy proxy;
    //proxy.Run();
    QVERIFY2(proxy.GetStatus() == SimulationProxy::Running, "Failure");
}

QTEST_APPLESS_MAIN(Simulation_tests)

#include "tst_simulation_tests.moc"
