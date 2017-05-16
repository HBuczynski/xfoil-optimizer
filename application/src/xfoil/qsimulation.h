#pragma once

#include <qprocess.h>
#include "simulation_proxy.h"

//!  IO stream interface using QT Qprocess API
/*!
  QT based implementation for handling process command inputs
*/
class QSimulationProxy : public QObject, public SimulationProxy
{
    Q_OBJECT
public:
    explicit QSimulationProxy(QObject *parent = 0);
    ~QSimulationProxy()
    {
        if(process_->state() != QProcess::NotRunning)
        {
            process_->kill();
        }
    }



    virtual void Run() override;
    virtual void Terminate() override;
    virtual Status const GetStatus() override
    {
        return status_;
    }

private:
private Q_SLOTS:
    void error(QProcess::ProcessError error);
    void finished(int exitCode, QProcess::ExitStatus status);
    void stateChanged(QProcess::ProcessState state);
    void read();
private:
    std::string workingDirectory_;
    Status status_;
    QProcess * process_;
    //TMP configuration variables, TODO - move to config file as they are common to sims
    std::string exePath_ = "C:\\Users\\Kub\\Documents\\workspace\\xfoil-optimizer\\xfoil\\win32";
    const int TIMEOUT_MS = 1500;
};

