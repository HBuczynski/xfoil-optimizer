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


    virtual void AddCommand(std::string command) override
    {
        commands_.push_back(command);
    }

    virtual void Run() override;
    virtual void Terminate() override;
    virtual Status PollStatus() override
    {
        if(status_ == Running)
        {
            process_->waitForReadyRead(TIMEOUT_SHORT);
            process_->waitForBytesWritten(TIMEOUT_SHORT);
        }
        return status_;
    }
    virtual std::string const GetProgramOutput() override
    {
        return programOutput_;
    }
    virtual std::string const GetExePath() override
    {
        return exePath_;
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
    std::string programOutput_;
    std::vector<std::string> commands_;
    const int TIMEOUT_SHORT = 10;
    const int TIMEOUT_LONG = 100;
};

