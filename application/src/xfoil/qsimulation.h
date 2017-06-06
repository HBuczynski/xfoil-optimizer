#pragma once

#include <qprocess.h>
#include <chrono>
#include "simulation_proxy.h"
#include "utility/config.h"

/**
*	@file qsimulation.h
*	@brief  QT based implementation for handling process command inputs
*	@author Jakub Polaczek & Hubert Buczyński
*	@date 05/06/2017
*/

//!  \class QSimulationProxy
//! IO stream interface using QT Qprocess API
/*!
Simulation Proxy implementation using Qprocess. The proxy spawns new child process with xfoil and monitors its execution.
There is no way of implementing reliable two way communication thus we hte process awaits timeout or termination
and interprets the results
*/
class QSimulationProxy : public QObject, public SimulationProxy
{
    Q_OBJECT
public:
    typedef std::chrono::steady_clock::time_point TimePoint;
    typedef std::chrono::steady_clock Clock;
    //using TimeCast = std::chrono::duration_cast<std::chrono::milliseconds>();

    explicit QSimulationProxy(const Config::SimulationParams &params, QObject *parent = 0);

    virtual ~QSimulationProxy() override;

    virtual void addCommand(std::string command) override;
    virtual void run() override;
    virtual void terminate() override;
    virtual Status pollStatus() override;
    virtual std::string const getProgramOutput() override;
    virtual std::string const getExePath() override;

private Q_SLOTS:
    void error(QProcess::ProcessError error);
    void finished(int exitCode, QProcess::ExitStatus status);
    void stateChanged(QProcess::ProcessState state);
    void read();

private:
    const Config::SimulationParams params_;
    Status status_;
    QProcess * process_;
    std::string programOutput_;
    std::vector<std::string> commands_;
    TimePoint startTime_;

    const int TIMEOUT_SHORT = 10;
    const int TIMEOUT_LONG = 100;
};

