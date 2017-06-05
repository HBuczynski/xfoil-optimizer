#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <exception>
//#include <cstdio>

#include "optimizer/simulation_results.h"
//#include "optimizer/geometry.h"
#include "xfoil/simulation_proxy.h"
#include "xfoil/qsimulation.h"
#include "utility/utility.h"
#include "utility/config.h"
//#include "utility/configuration_reader.h"

#include <qthread.h>
#include <qtimer.h>
#include <qmutex.h>
//#include <thread>
#include <queue>
//#include <mutex>

/**
*	@file simulation.h
*	@brief This header file contains tools to maintain communication with external program - XFOIL.
*	@author Jakub Polaczek & Hubert Buczyński
*	@date 05/06/2017
*/


//!  Class controlling execution single simulation tool using proxy interface
/*!
  Controls single instance of xfoil optimizer
*/
class SimulationHandler
{
    friend class SimulationHandler_tests;
public:
    enum Status
    {
        Idle,
        Running,
        Finished,
        Error,
        NotExisting
    };

    SimulationHandler(Geometry &geom, const Config::SimulationParams &params);
    ~SimulationHandler();

    static Geometry getNACAAirfoil(std::string code);
    void run();
    Status pollStatus();

private:
    void readResults();
    void saveGeometry();
    void deleteGeometry();
    void deleteResults();
    std::string instantiateFilename(std::string filename);

    const int id_;
    SimulationProxy *proxy_;
    Geometry &geometry_;
    Status status_;
    static unsigned int id_total;
    const Config::SimulationParams params_;
};


struct Task
{
    Task(Geometry * geom):
        geometry(geom),
        handlerAssigned(-1)
    {

    }
    Geometry * geometry;
    int handlerAssigned = -1;
};


class SchedulerWorker : public QObject
{
    Q_OBJECT
public:
    explicit SchedulerWorker(std::queue<Task> &taskQueue, QMutex &mutex,Config::SimulationParams params,QObject *parent = 0);

Q_SIGNALS:
    //void bufferFillCountChanged(int cCount);
    void finishedWork();
    void updateIdleState(bool state);

    void error(QString str);
public Q_SLOTS:
    void stop();
    void start();
    void addTask(Task task);

    void process();
    bool IsTasksFinished();
private:

    QTimer * timer;
    Config::SimulationParams params_;
    std::queue<Task> &taskQueue_;
    QMutex &queueMutex_;
    SimulationHandler::Status *handlerStatus_;
    SimulationHandler **handlers;
};

//!  Class controlling execution of external simulation tools
/*!
  Controls multiple instances of xfoil optimizer running in parallel
  Runs a thread that polls and initiates all xfoil proxy instances
  Has an internal queue for requests
*/
class SimulationScheduler : public QObject
{
    Q_OBJECT
public:
    SimulationScheduler(Config::SimulationParams params,QObject *parent = 0);
    ~SimulationScheduler();

    void addTask(Task task);
    void addBatchTask(std::vector<Task> &input);
    void waitForFinished();
    bool isTasksFinished() const;

signals:
    void stopWorker();
    void simulationFinished();

public slots:
    void updateState(bool state);
    void workerFinished();
    void errorString(QString str);

private:

    const Config::SimulationParams params_;
    std::vector<Geometry*> tasks;
    std::queue<Task> taskQueue_;
    SimulationHandler::Status *handlerStatus_;
    QMutex queueMutex_;
    QThread *workerThread;
    SchedulerWorker *worker_;
    bool workerIdle;
};
