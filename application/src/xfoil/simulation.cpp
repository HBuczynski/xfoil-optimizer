#include "xfoil/simulation.h"
#include <QDebug>
using std::ifstream;
unsigned int SimulationHandler::id_total = 0;

SimulationHandler::SimulationHandler(Geometry &geom, const Config::SimulationParams &params):
    params_(params),
    geometry_(geom),
    id_(++id_total),
    status_(Idle)
{
    proxy_ = new QSimulationProxy(params);
    saveGeometry();
}

SimulationHandler::~SimulationHandler()
{
    //Tidy up//
    deleteGeometry();
    if(status_ != Idle)
        deleteResults();
    if(proxy_->pollStatus() != QSimulationProxy::NotRunning)
        proxy_->terminate();

    delete proxy_;
}

Geometry SimulationHandler::getNACAAirfoil(std::string code)
{

    //Validate code//
    if(code.length() > 4)
        throw std::invalid_argument("Code invalid");
    else if(!std::all_of(code.begin(), code.end(), ::isdigit))
        throw std::invalid_argument("Code invalid");
    Config::SimulationParams params;
    QSimulationProxy tmpproxy(params);
    tmpproxy.addCommand("NACA 0012");
    tmpproxy.addCommand("SAVE NACA0012.dat");
    tmpproxy.addCommand("\r\n");
    tmpproxy.run();
    tmpproxy.terminate();
    std::string filepath = tmpproxy.getExePath() + "/NACA0012.dat";
    Geometry retGeom(filepath);
    utility::removeFile(filepath);

    return retGeom;
}

void SimulationHandler::readResults()
{
    std::ifstream infile(proxy_->getExePath() + "/" + instantiateFilename("result.txt"));
    if(infile.good())
    {
        //Read file contents
        std:: string line;
        bool failure = false;
        for(int i = 0; i < 12; ++i)//Skip intro lines - no real content//
        {
            if(!getline(infile, line))
            {
                //File was too short wtf//
                std::cout<<"File was too short, failed to interpret"<<std::endl;
                failure = true;
                break;
            }
            else
            {}
            // std::cout<<line<<std::endl;
        }
        if(geometry_.simResults_.calculated_ == true)
        {
            //Clear previous results from the structure
            geometry_.simResults_.results_.clear();
            geometry_.simResults_.calculated_ = false;
        }
        while(getline(infile, line))
        {
            if(line.find("*") != std::string::npos)
                continue;
            //Read 7 double parameters in a single line//
            std::string::size_type sz;
            SimResults::ResultEntry resLine;
            //Can cause exception throws out of range
            resLine.alfa = std::stod(line,&sz);
            line = line.substr(sz);
            resLine.cl = std::stod(line,&sz);
            line = line.substr(sz);
            resLine.cd = std::stod(line,&sz);
            line = line.substr(sz);
            resLine.cdp = std::stod(line,&sz);
            line = line.substr(sz);
            resLine.cm = std::stod(line,&sz);
            line = line.substr(sz);
            resLine.xtr_top = std::stod(line,&sz);
            line = line.substr(sz);
            resLine.xtr_bottom = std::stod(line,&sz);
            geometry_.simResults_.results_.push_back(resLine);
        }
        geometry_.simResults_.calculated_ = true;
       // qDebug()<<"Loading results";
        infile.close();
    }
    else
    {
        qDebug()<<"Invalid data file";
        throw std::invalid_argument("Invalid data file");
    }


}
std::string SimulationHandler::instantiateFilename(std::string filename)
{
    std::string result;
    std::string::size_type idx = filename.find_last_of('.');
    if(idx != std::string::npos)
    {
        //Found externsion can add number
        result = filename.substr(0,idx);
        result += std::to_string(id_) + filename.substr(idx);
    }
    else
    {
        result = filename + std::to_string(id_);
    }
    //std::cout<< result<<std::endl;
    return result;
}
void SimulationHandler::saveGeometry()
{
    geometry_.save((std::string)(proxy_->getExePath() + "\\" + instantiateFilename("geometry.dat")));
}

void SimulationHandler::deleteGeometry()
{
   std::remove((proxy_->getExePath() + "/" + instantiateFilename("geometry.dat")).c_str());
}
void SimulationHandler::deleteResults()
{
    std::remove((proxy_->getExePath() + "/" + instantiateFilename("result.txt")).c_str());
}


void SimulationHandler::run()
{
    if(status_ != Idle)
        throw std::invalid_argument("Invaid state - simulation running?");
    std::stringstream ss;
    proxy_->addCommand("PLOP");
    proxy_->addCommand("G F");
    proxy_->addCommand("\r\n");
    proxy_->addCommand("LOAD " + instantiateFilename("geometry.dat"));
    proxy_->addCommand("OPER");
    //Viscous settings//
    if(params_.viscousEnable)
    {
        ss << "VISC "<<params_.reynoldsNo;
        proxy_->addCommand(ss.str());//Set viscous flow reynolds number
        ss.str("");
        ss.clear();
    }
    proxy_->addCommand("PACC");
    proxy_->addCommand("");//do not save tmp
    proxy_->addCommand("");//do not save polar
    proxy_->addCommand("ITER");
    //Iteration settings//
    ss << params_.iterationLimit;
    proxy_->addCommand(ss.str());
    ss.str("");
    ss.clear();
    //TODO precision settings//
    proxy_->addCommand("ASEQ -10.0 -2.0 1.0");
    proxy_->addCommand("ASEQ -2.0 2.0 0.2");
    proxy_->addCommand("ASEQ 2.0 15.0 0.5");
    proxy_->addCommand("PACC");//Disable polar accumulation

    proxy_->addCommand("PWRT 1");
    proxy_->addCommand(instantiateFilename("result.txt"));

    //proxy_->AddCommand("CPWR " + InstantiateFilename("result.txt"));
    proxy_->run();
    status_ = Running;
    //Check if proxy really started - state error if it didnt//
    if(proxy_->pollStatus() == SimulationProxy::NotRunning)
        status_ = Error;//TODO add log message
    //std::cout <<"Running";

}
SimulationHandler::Status SimulationHandler::pollStatus()
{
    if(status_ != Error && status_ != Finished)//Final states check
       {
        SimulationProxy::Status proxy_status = proxy_->pollStatus();
        switch(proxy_status)
        {
            case SimulationProxy::NotRunning:
                status_ = Idle;
            break;
            case SimulationProxy::Running://Verify timeout TODO//
                //std::cout <<"...";
                status_ = Running;
            break;
            case SimulationProxy::Error:
                //std::cout <<"ERR";
                status_ = Error;
            break;
            case SimulationProxy::Finished:
                //qDebug()<<"FIN";
                readResults();
                status_ = Finished;
            break;
        default:
            break;
        }
    }
    return status_;
}

SchedulerWorker::SchedulerWorker(std::queue<Task> &taskQueue, QMutex &mutex, Config::SimulationParams params, QObject *parent):
    params_(params),
    taskQueue_(taskQueue),
    queueMutex_(mutex)
{

}

void SchedulerWorker::stop()
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
                while(handlers[i]->pollStatus() == SimulationHandler::Running)
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
    delete timer;
    emit error(QString("Hello from error"));
    emit finishedWork();
}

void SchedulerWorker::start()
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

void SchedulerWorker::addTask(Task task)
{
    std::cout<<"Adding task" << std::endl;
    taskQueue_.push(task);
}

void SchedulerWorker::process()
{
    //Free existing queue places//
    for(int i = 0; i < params_.parallelSimulations; ++i)
    {
        if(handlers[i] != nullptr)
        {
            handlerStatus_[i] = handlers[i]->pollStatus();
            // qDebug() << (int)handlerStatus_[i]<<i;
            if(handlerStatus_[i] != SimulationHandler::Running)
            {
                //std::cout<<"Task Finished, freeing spot"<<i<<"\r\n";
                //for(int j = 0; j < params_.parallelSimulations; ++j)
                //    std::cout<<handlerStatus_[j];
                delete handlers[i];
                handlers[i] = nullptr;
                handlerStatus_[i] = SimulationHandler::NotExisting;
            }
        }
    }
    //Look for new task//
    if(!taskQueue_.empty())
    {
        for(int i = 0; i < params_.parallelSimulations; ++i)
        {
            //Search for empty queue place and run if available//
            if(handlers[i] == nullptr)
            {
                //Mutex it//
                queueMutex_.lock();
                Task task = taskQueue_.front();

                handlers[i] = new SimulationHandler(*task.geometry, params_);
                handlers[i]->run();
                handlerStatus_[i] = handlers[i]->pollStatus();
                //std::cout<<"Adding task at spot"<<i<<"\r\n";
                taskQueue_.pop();
                queueMutex_.unlock();
                break;
            }
        }
    }
    //Poll/ update task states
    for(int i = 0; i < params_.parallelSimulations; ++i)
    {
        if(handlers[i] != nullptr)
        {
            handlerStatus_[i] = handlers[i]->pollStatus();
        }
    }
    /*

    */
    IsTasksFinished();
    //Q_EMIT finishedWork();
}
bool SchedulerWorker::IsTasksFinished()
{
    //Check for awaiting tasks
    if(taskQueue_.size() != 0)
    {
        emit updateIdleState(false);
        return false;
    }
    //Check also for running tasks//
    for(int i = 0; i < params_.parallelSimulations; ++i)
    {
        if(handlerStatus_[i] != SimulationHandler::NotExisting)
        {
            emit updateIdleState(false);
            return false;
        }
    }
    emit updateIdleState(true);
    //std::cout<<"Free now";
    return true;
}

SimulationScheduler::SimulationScheduler(Config::SimulationParams params, QObject *parent):
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
    QObject::connect(workerThread, SIGNAL(finished()), this, SLOT(workerFinished()), Qt::QueuedConnection);
    QObject::connect(worker_, SIGNAL(updateIdleState(bool)), this, SLOT(updateState(bool)), Qt::DirectConnection);

    worker_->moveToThread(workerThread);
    workerThread->start();
    // workerThread_ = new std::thread (&SimulationScheduler::ConsumeTask, this);

}

SimulationScheduler::~SimulationScheduler()
{
    //Terminate worker thread//
    Q_EMIT stopWorker();
    delete[] handlerStatus_;
}

void SimulationScheduler::addTask(Task task)
{
    QMutexLocker locker(&queueMutex_);
    taskQueue_.push(task);
}

void SimulationScheduler::addBatchTask(std::vector<Task> &input)
{
    QMutexLocker locker(&queueMutex_);
    for(const auto &e:input)
        taskQueue_.push(e);
}

void SimulationScheduler::waitForFinished()
{
    while(!worker_->IsTasksFinished())
    {
        QThread::msleep(10);
    }
}

bool SimulationScheduler::isTasksFinished() const
{
    return worker_->IsTasksFinished();
}

void SimulationScheduler::updateState(bool state)
{
    //std::cout<<"Updated state"<<state<<std::endl;
    if(state == true && workerIdle !=state)
        Q_EMIT simulationFinished();
    workerIdle = state;
}

void SimulationScheduler::workerFinished()
{
    std::cout<<"Finished thread\r\n";
}

void SimulationScheduler::errorString(QString str)
{
    std::cout<<str.toStdString();
}
