#include <QString>
#include <QtTest>
#include <QThread>
#include "xfoil/simulation.h"
#include "xfoil/simulation_proxy.h"
#include "xfoil/qsimulation.h"
#include "xfoil/simulation_results.h"

#include <iostream>
class QSimulationProxy_tests : public QObject
{
    Q_OBJECT

public:
    QSimulationProxy_tests();

private Q_SLOTS:
    void CreateProxyObjectNotRunsTheXfoil();
    void RunAndTerminateTheProgram();
    void EnterMenuAndTerminate();
    void RunASimulationAndRemoveResultsFile();
    void RunMultipleParallelSimulations();
    //void RunSequenceSimulation();

};

QSimulationProxy_tests::QSimulationProxy_tests()
{

}

void QSimulationProxy_tests::CreateProxyObjectNotRunsTheXfoil()
{
    QSimulationProxy proxy;
    QVERIFY2(proxy.PollStatus() == SimulationProxy::NotRunning, "Failure - Bad object creation");
}
void QSimulationProxy_tests::RunAndTerminateTheProgram()
{
    QSimulationProxy proxy;
    proxy.Run();
    QVERIFY2(proxy.PollStatus() != SimulationProxy::NotRunning, "Failure - process did not start - invalid state");
    proxy.Terminate();
    QVERIFY2(proxy.PollStatus() == SimulationProxy::Finished, "Failure - process not terminated - invalid state");
}
void QSimulationProxy_tests::EnterMenuAndTerminate()
{
    QSimulationProxy proxy;
    proxy.AddCommand("PLOP");
    proxy.AddCommand("G F");
    proxy.AddCommand("\r\n");
    proxy.AddCommand("NACA 0012");
    proxy.AddCommand("OPER");
    proxy.Run();
    QVERIFY2(proxy.PollStatus() != SimulationProxy::NotRunning, "Failure - process did not start - invalid state");
    proxy.Terminate();
    QVERIFY2(proxy.PollStatus() == SimulationProxy::Finished, "Failure - process not terminated - invalid state");
}

void QSimulationProxy_tests::RunASimulationAndRemoveResultsFile()
{
    QSimulationProxy proxy;
    proxy.AddCommand("PLOP");
    proxy.AddCommand("G F");
    proxy.AddCommand("\r\n");
    proxy.AddCommand("NACA 0012");
    proxy.AddCommand("OPER");
    proxy.AddCommand("ALFA 0.0");
    proxy.AddCommand("CPWR test.dat");

    //proxy.AddCommand("\r\n");
    //proxy.AddCommand("QUIT");

    proxy.Run();
    std::cout<<"Run()\r\n";
    QVERIFY2(proxy.PollStatus() != SimulationProxy::NotRunning, "Failure - process did not start - invalid state");
    proxy.Terminate();

    std::cout<<"Terminte()\r\n";
    QVERIFY2(proxy.PollStatus() == SimulationProxy::Finished, "Failure - process not terminated - invalid state");


    QString resFile = QString::fromStdString(proxy.GetExePath() + "/test.dat");
    QVERIFY(QFile::exists(resFile));
    QFile::remove(resFile);
    QVERIFY(!QFile::exists(resFile));

}
void QSimulationProxy_tests::RunMultipleParallelSimulations()
{
    const unsigned int simCount = 8;
    QSimulationProxy proxy[simCount];
    char fnamebuf[32];
    for(unsigned int i = 0; i < simCount; ++i)
    {
        proxy[i].AddCommand("PLOP");
        proxy[i].AddCommand("G F");
        proxy[i].AddCommand("\r\n");
        proxy[i].AddCommand("NACA 0012");
        proxy[i].AddCommand("OPER");
        proxy[i].AddCommand("ALFA 0.0");
        snprintf(fnamebuf,sizeof(fnamebuf),"test%d.dat",i);
        proxy[i].AddCommand("CPWR " + std::string(fnamebuf));
        //proxy[i].AddCommand("\r\n");
        //proxy[i].AddCommand("QUIT");
    }
    for(unsigned int i = 0; i < simCount; ++i)
    {
            proxy[i].Run();
            QVERIFY(proxy[i].PollStatus() != SimulationProxy::NotRunning);

    }
    //Wait for all processes to finish or timeout//
    bool finished = false;
    for(int retries = 0; retries < 10; ++retries)
    {
        for(unsigned int i = 0; i < simCount; ++i)
        {
            finished = true;//Reset flag
                if(proxy[i].PollStatus() == SimulationProxy::Running)
                {
                    finished =false;
                }
        }
        if(finished)
            break;
    }
    QVERIFY(finished);
    for(unsigned int i = 0; i < simCount; ++i)
    {
            proxy[i].Terminate();
            QVERIFY(proxy[i].PollStatus() == SimulationProxy::Finished);
    }
    for(unsigned int i = 0; i < simCount; ++i)
    {
        snprintf(fnamebuf,sizeof(fnamebuf),"test%d.dat",i);
        QString resFile = QString::fromStdString(proxy[i].GetExePath() + "/" + std::string(fnamebuf));
        QVERIFY(QFile::exists(resFile));
        QFile::remove(resFile);
        QVERIFY(!QFile::exists(resFile));
    }
}

QTEST_MAIN(QSimulationProxy_tests)

#include "tst_qsimulationproxy_tests.moc"
