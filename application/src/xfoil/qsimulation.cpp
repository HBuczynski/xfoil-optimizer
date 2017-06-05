#include "qsimulation.h"
#include <qstringlist.h>
#include <QtDebug>
//For debugging
#include <iostream>

QSimulationProxy::QSimulationProxy(const Config::SimulationParams &params, QObject *parent):
    params_(params),
    status_(NotRunning)
{
    process_ = new QProcess();
    connect(process_,
            SIGNAL(error(QProcess::ProcessError)),
            this,
            SLOT(error(QProcess::ProcessError)));
    connect(process_,
            SIGNAL(finished(int, QProcess::ExitStatus)),
            this,
            SLOT(finished(int, QProcess::ExitStatus)));
    connect(process_,
            SIGNAL(stateChanged(QProcess::ProcessState)),
            this,
            SLOT(stateChanged(QProcess::ProcessState)));
    connect(process_,
            SIGNAL(readyReadStandardOutput()),
            this,
            SLOT(read()));


}

QSimulationProxy::~QSimulationProxy()
{
    if(process_->state() != QProcess::NotRunning)
    {
        process_->kill();
    }
}

void QSimulationProxy::addCommand(std::string command)
{
    commands_.push_back(command);
}

void QSimulationProxy::run()
{
    QString programPath = QString::fromStdString(params_.xfoilExecutablePath);
#if defined(WIN64) || defined(_WIN64) || defined(__WIN64) && !defined(__CYGWIN__)
    QString program = "\"" + programPath + "/xfoil.exe" + "\"";
    #else
    QString program = programPath + "/xfoil";
    #endif
    QStringList arglist;

    process_->setWorkingDirectory(programPath);
    process_->start(program, arglist,/*QIODevice::Text |*/ QIODevice::ReadWrite);
    if(process_->waitForStarted(TIMEOUT_LONG))
    {
        status_ = Running;
        startTime_ = Clock::now();
        for(std::string s : commands_)
        {
            std::string command = s + "\r\n";
            process_->write(command.c_str(),command.length());
        }
        // Write commands for program termination//
        process_->write("\n\r\n\r",4);
        process_->write("QUIT\n\r",6);
        process_->waitForBytesWritten(TIMEOUT_SHORT);
        process_->closeWriteChannel();

    }
    else
    {
        status_ = Error;
        qDebug() << "QSimulationProxy::Run() start fail\r\n";
        //Error - did program did not start TODO handling approach
    }

}
void QSimulationProxy::terminate()
{
    if(status_ == NotRunning || status_ == Finished)
        return;
    if(!process_->waitForFinished(TIMEOUT_LONG))
    {
        qDebug() << "QSimulationProxy::Terminate() - process did not finish - forcing...\r\n";
        process_->terminate();
    }

}

SimulationProxy::Status QSimulationProxy::pollStatus()
{
    if(status_ == Running)
    {
        TimePoint currentTime = Clock::now();
        process_->waitForReadyRead(TIMEOUT_SHORT);
        process_->waitForBytesWritten(TIMEOUT_SHORT);

        if(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime_).count() > params_.xfoilTimeout * 1000)
        {
            status_ = Error;
            terminate();
        }
    }
    return status_;
}

const std::string QSimulationProxy::getProgramOutput()
{
    return programOutput_;
}

const std::string QSimulationProxy::getExePath()
{
    return params_.xfoilExecutablePath;
}

void QSimulationProxy::error(QProcess::ProcessError error)
{
    /* just feedback some text about the error */
    qDebug() << "SimulationProxy::error - " << error;
    status_ = Error;
} // end_slot(SimulationProxy::error)

void QSimulationProxy::finished(int exitCode, QProcess::ExitStatus status)
{
    status_ = Finished;
    /* feedback some text about finished */
    // std::cout<<"PROCESS FINSHED"<<std::endl;
} // end_slot (SimulationProxy::finished)

void QSimulationProxy::stateChanged(QProcess::ProcessState state)
{
    //std::cout<<"STATECHANGED\r\n"<<state<<std::endl;
    switch(state)
    {
     case QProcess::NotRunning:
        status_ = Finished;
        break;
     case QProcess::Running:
        status_ = Running;
        break;
     default:
        break;
    }

    //qDebug() << "SimulationProxy::stateChanged" << state;
}
void QSimulationProxy::read()
{
    programOutput_ += std::string(process_->readAllStandardOutput().data());
}
