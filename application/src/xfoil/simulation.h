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

    SimulationHandler(Geometry &geom, const Config::SimulationParams &params):
        params_(params),
        geometry_(geom),
        id_(++id_total),
        status_(Idle)
    {
        proxy_ = new QSimulationProxy(params);
        SaveGeometry();
    }
    ~SimulationHandler()
    {
        //Tidy up//
        DeleteGeometry();
        if(status_ != Idle)
            DeleteResults();
        if(proxy_->PollStatus() != QSimulationProxy::NotRunning)
            proxy_->Terminate();

        delete proxy_;
    }
    static Geometry GetNACAAirfoil(std::string code)
    {

        //Validate code//
        if(code.length() > 4)
            throw std::invalid_argument("Code invalid");
        else if(!std::all_of(code.begin(), code.end(), ::isdigit))
            throw std::invalid_argument("Code invalid");
        Config::SimulationParams params;
        QSimulationProxy tmpproxy(params);
        tmpproxy.AddCommand("NACA 0012");
        tmpproxy.AddCommand("SAVE NACA0012.dat");
        tmpproxy.AddCommand("\r\n");
        tmpproxy.Run();
        tmpproxy.Terminate();
        std::string filepath = tmpproxy.GetExePath() + "/NACA0012.dat";
        Geometry retGeom(filepath);
        utility::removeFile(filepath);

        return retGeom;
    }
    void Run();
    Status PollStatus();
private:
    void ReadResults();
    void SaveGeometry();
    void DeleteGeometry();
    void DeleteResults();
    std::string InstantiateFilename(std::string filename);
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
    explicit SchedulerWorker(std::queue<Task> &taskQueue, QMutex &mutex,Config::SimulationParams params,QObject *parent = 0):
        params_(params),
        taskQueue_(taskQueue),
        queueMutex_(mutex)
    {
    }

Q_SIGNALS:
    //void bufferFillCountChanged(int cCount);
    void finishedWork();
    void updateIdleState(bool state);

    void error(QString str);
public Q_SLOTS:
    void stop()
    {
        //Finish up all the tasks//
        bool finished = false;
        while(!finished)
        {
            finished = true;
            for(int i = 0; i < params_.parallelSimulations; ++i)
            {
                if(handlers[i] != nullptr)
                {
                    int timeout = 1000;//delay of 10s//
                    while(handlers[i]->PollStatus() == SimulationHandler::Running)
                    {
                        if(--timeout < 0)
                            break;
                        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
                        QThread::msleep(10);
                    }
                    delete handlers[i];
                    handlers[i] = nullptr;
                    handlerStatus_[i] = SimulationHandler::NotExisting;
                }
            }
        }

        delete [] handlers;
        delete [] handlerStatus_;
        emit error(QString("Hello from error"));
        emit finishedWork();
    }
    void start()
    {
        //Initialize pointers for handler objects//
        handlers = new SimulationHandler*[params_.parallelSimulations];
        handlerStatus_ = new SimulationHandler::Status[params_.parallelSimulations];
        for(int i = 0; i < params_.parallelSimulations; ++i)
        {
            handlers[i] = nullptr;
            handlerStatus_[i] = SimulationHandler::NotExisting;
        }
        //Start timer to periodically call update on thread//
        timer = new QTimer(this);
        timer->setInterval(100);
        timer->connect(timer, SIGNAL(timeout()), this, SLOT(process()));
        timer->start();
    }
    void addTask(Task task)
    {
        std::cout<<"Adding task" << std::endl;
        taskQueue_.push(task);
    }

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
    SimulationScheduler(Config::SimulationParams params,QObject *parent = 0):
        params_(params)
    {
        //Initialize handler state array//
        handlerStatus_ = new SimulationHandler::Status[params_.parallelSimulations];
        for(int i =0; i < params_.parallelSimulations; ++i)
        {
            handlerStatus_[i] = SimulationHandler::NotExisting;
        }
        //Initailize worker thread//
        //workerEnable_ = true;
        workerIdle = true;
        workerThread = new QThread;

        worker_ = new SchedulerWorker(taskQueue_, queueMutex_,params,parent);
        QObject::connect(worker_, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
        QObject::connect(workerThread, SIGNAL(started()), worker_, SLOT(start()));
        QObject::connect(worker_, SIGNAL(finishedWork()), workerThread, SLOT(quit()));
        QObject::connect(worker_, SIGNAL(finishedWork()), worker_, SLOT(deleteLater()));
        QObject::connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));

        //My Signals and slots//
        QObject::connect(this, SIGNAL(stopWorker()), worker_, SLOT(stop()), Qt::QueuedConnection);
        //QObject::connect(this, SIGNAL(emitTask(Task)), worker_, SLOT(addTask(Task)), Qt::QueuedConnection);
        QObject::connect(workerThread, SIGNAL(finished()), this, SLOT(workerFinished()), Qt::QueuedConnection);
        QObject::connect(worker_, SIGNAL(updateIdleState(bool)), this, SLOT(updateState(bool)), Qt::DirectConnection);

        worker_->moveToThread(workerThread);
        workerThread->start();
      // workerThread_ = new std::thread (&SimulationScheduler::ConsumeTask, this);

    }
    ~SimulationScheduler()
    {
        //Terminate worker thread//
        Q_EMIT stopWorker();
        delete[] handlerStatus_;
    }


    void AddTask(Task task)
    {
        QMutexLocker locker(&queueMutex_);
        taskQueue_.push(task);
    }
    void AddBatchTask(std::vector<Task> &input)
    {
        QMutexLocker locker(&queueMutex_);
        for(const auto &e:input)
            taskQueue_.push(e);
    }

    void WaitForFinished()
    {
        while(!worker_->IsTasksFinished())
        {
            QThread::msleep(10);
        }
    }

    bool IsTasksFinished() const
    {
        return worker_->IsTasksFinished();
    }

signals:
    void stopWorker();
    void emitTask(Task task);

public slots:
    void updateState(bool state)
    {
        //std::cout<<"Updated state\r\n";
        workerIdle = state;
    }
    void workerFinished()
    {
        std::cout<<"Finished thread\r\n";
    }
    void errorString(QString str)
    {
        std::cout<<str.toStdString();
    }

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
