#pragma once

#include <qprocess.h>
#include <chrono>
#include "simulation_proxy.h"
#include "utility/config.h"

//!  IO stream interface using QT Qprocess API
/*!
  QT based implementation for handling process command inputs
*/
class QSimulationProxy : public QObject, public SimulationProxy
{
    Q_OBJECT
public:
    typedef std::chrono::steady_clock::time_point TimePoint;
    typedef std::chrono::steady_clock Clock;
    //using TimeCast = std::chrono::duration_cast<std::chrono::milliseconds>();

    explicit QSimulationProxy(const Config::SimulationParams &params, QObject *parent = 0);
    virtual ~QSimulationProxy() override
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
            TimePoint currentTime = Clock::now();
            process_->waitForReadyRead(TIMEOUT_SHORT);
            process_->waitForBytesWritten(TIMEOUT_SHORT);

            if(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime_).count() > params_.xfoilTimeout * 1000)
            {
                status_ = Error;
                Terminate();
            }
        }
        return status_;
    }
    virtual std::string const GetProgramOutput() override
    {
        return programOutput_;
    }
    virtual std::string const GetExePath() override
    {
        return params_.xfoilExecutablePath;
    }
private:
private Q_SLOTS:
    void error(QProcess::ProcessError error);
    void finished(int exitCode, QProcess::ExitStatus status);
    void stateChanged(QProcess::ProcessState state);
    void read();
private:
    const Config::SimulationParams params_;
    Status status_;
    QProcess * process_;
    //TMP configuration variables, TODO - move to config file as they are common to sims
    //std::string exePath_ = "C:\\Users\\Kub\\Documents\\workspace\\xfoil-optimizer\\xfoil\\win32";
    //std::string exePath_ = "C:\\Users\\Hubert\\Documents\\STUDIA_INFA\\semestr_IV\\ZPR_Zaawansowany_C++\\Projekt\\xfoil-optimizer\\xfoil\\win32";
    std::string programOutput_;
    std::vector<std::string> commands_;
    TimePoint startTime_;

    //int execution_timeout =30000;
    const int TIMEOUT_SHORT = 10;
    const int TIMEOUT_LONG = 100;
};

