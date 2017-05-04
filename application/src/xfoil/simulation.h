#pragma once

#include <vector>
#include <qprocess.h>
#include "xfoil/simulation_results.h"
#include "optimizer/geometry.h"
//!  Class controlling execution of external simulation tools
/*!
  Controls multiple instances of xfoil optimizer running in parallel
*/
class SimulationScheduler
{
public:
private:
	const int _parallelInstances = 4;
    std::vector<Geometry*> tasks;



};

//!  IO stream interface proxy for external optimizer
/*!
  A more elaborate class description. [TODO]
*/
class SimulationProxy : public QObject
{
    Q_OBJECT
public:
    explicit SimulationProxy(QObject *parent = 0);
    ~SimulationProxy()
    {
        if(results_ != nullptr)
            delete results_;
        if(started_ && process_->state() != QProcess::NotRunning)
        {
            process_->kill();
        }
    }

    enum Status
    {
        NotRunning,
        Running,
        Finished,
        NotConverged,
        Error
    };

    void Run();
    Status GetStatus()
    {
        return status_;
    }

    SimResults GetResults();

Q_SIGNALS:
    void feedbackLog(QString log);
//public Q_SLOTS:
//    void launch(QString program, QStringList argList);
private:
private Q_SLOTS:
    void error(QProcess::ProcessError error);
    void finished(int exitCode, QProcess::ExitStatus status);
    void stateChanged(QProcess::ProcessState state);
private:
    std::string workingDirectory_;
    SimResults *results_;
    Status status_;
    bool started_;
    Geometry geometry_;
    QProcess * process_;
    //TMP configuration variables, TODO - move to config file as they are common to sims
    std::string exePath_ = "C:\Users\Kub\Documents\workspace\xfoil-optimizer\xfoil\win32\xfoil.exe";
};
