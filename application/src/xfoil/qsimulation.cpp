#include "qsimulation.h"
#include <qstringlist.h>
#include <QtDebug>
//For debugging
#include <iostream>

QSimulationProxy::QSimulationProxy(QObject *parent):
    status_(NotRunning)
{
    process_ = new QProcess(this);
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
void QSimulationProxy::Run()
{
    QString programPath = QString::fromStdString(exePath_);
    QString program = "\"" + programPath + "/xfoil.exe" + "\"";
    QStringList arglist;

    process_->setWorkingDirectory(programPath);
    process_->start(program, arglist,/*QIODevice::Text |*/ QIODevice::ReadWrite);
    if(process_->waitForStarted(TIMEOUT_LONG))
    {
        status_ = Running;
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
void QSimulationProxy::Terminate()
{
    if(status_ == NotRunning || status_ == Finished)
        return;
    if(!process_->waitForFinished(TIMEOUT_LONG))
    {
        qDebug() << "QSimulationProxy::Terminate() - process did not finish - forcing...\r\n";
        process_->terminate();
    }

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
    //std::cout<<"PROCESS FINSHED\r\n";
} // end_slot (SimulationProxy::finished)

void QSimulationProxy::stateChanged(QProcess::ProcessState state)
{
    //std::cout<<"STATECHANGED\r\n"<<state;
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
