#include <QString>
#include <QtTest>
#include <QThread>
#include "xfoil/simulation.h"
#include "xfoil/simulation_proxy.h"
#include "xfoil/qsimulation.h"
#include "optimizer/simulation_results.h"

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
    void GenerateNACAProfile();
    //void RunSequenceSimulation();
private:
    Config::SimulationParams params;
};

QSimulationProxy_tests::QSimulationProxy_tests()
{
    //Set up params paths here//
}

void QSimulationProxy_tests::CreateProxyObjectNotRunsTheXfoil()
{
    QSimulationProxy proxy(params);
    QVERIFY2(proxy.PollStatus() == SimulationProxy::NotRunning, "Failure - Bad object creation");
}
void QSimulationProxy_tests::RunAndTerminateTheProgram()
{
    QSimulationProxy proxy(params);
    proxy.Run();
    QVERIFY2(proxy.PollStatus() != SimulationProxy::NotRunning, "Failure - process did not start - invalid state");
    proxy.Terminate();
    QVERIFY2(proxy.PollStatus() == SimulationProxy::Finished, "Failure - process not terminated - invalid state");
}
void QSimulationProxy_tests::EnterMenuAndTerminate()
{
    QSimulationProxy proxy(params);
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
    QSimulationProxy proxy(params);
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
    std::vector<QSimulationProxy*> proxyBuf;
    for(int i = 0; i < simCount; ++i)
    {
        proxyBuf.push_back(new QSimulationProxy(params));
    }
    char fnamebuf[32];
    int i = 0;
    for(auto proxy : proxyBuf)
    {
        proxy->AddCommand("PLOP");
        proxy->AddCommand("G F");
        proxy->AddCommand("\r\n");
        proxy->AddCommand("NACA 0012");
        proxy->AddCommand("OPER");
        proxy->AddCommand("ALFA 0.0");
        snprintf(fnamebuf,sizeof(fnamebuf),"test%d.dat",i);
        proxy->AddCommand("CPWR " + std::string(fnamebuf));
        ++i;
    }
    for(auto  proxy:proxyBuf)
    {
            proxy->Run();
            QVERIFY(proxy->PollStatus() != SimulationProxy::NotRunning);

    }
    //Wait for all processes to finish or timeout//
    bool finished = false;
    for(int retries = 0; retries < 10; ++retries)
    {
        for(auto  proxy:proxyBuf)
        {
            finished = true;//Reset flag
                if(proxy->PollStatus() == SimulationProxy::Running)
                {
                    finished =false;
                }
        }
        if(finished)
            break;
    }
    QVERIFY(finished);
    for(auto  proxy:proxyBuf)
    {
            proxy->Terminate();
            QVERIFY(proxy->PollStatus() == SimulationProxy::Finished);
    }
    i = 0;
    for(auto proxy:proxyBuf)
    {
        snprintf(fnamebuf,sizeof(fnamebuf),"test%d.dat",i);
        QString resFile = QString::fromStdString(proxy->GetExePath() + "/" + std::string(fnamebuf));
        QVERIFY(QFile::exists(resFile));
        QFile::remove(resFile);
        QVERIFY(!QFile::exists(resFile));
        ++i;
    }
}
void QSimulationProxy_tests::GenerateNACAProfile()
{
    //TODO - throw if this breaks//
    QSimulationProxy proxy(params);
    proxy.AddCommand("NACA 0012");
    proxy.AddCommand("SAVE NACA0012.dat");
    proxy.AddCommand("\r\n");
    proxy.Run();
    QVERIFY2(proxy.PollStatus() != SimulationProxy::NotRunning, "Failure - process did not start - invalid state");
    proxy.Terminate();
    QVERIFY2(proxy.PollStatus() == SimulationProxy::Finished, "Failure - process not terminated - invalid state");
    QString resFile = QString::fromStdString(proxy.GetExePath() + "/NACA0012.dat");
    QVERIFY(QFile::exists(resFile));
    QFile::remove(resFile);
    QVERIFY(!QFile::exists(resFile));
}

QTEST_MAIN(QSimulationProxy_tests)

#include "tst_qsimulationproxy_tests.moc"
