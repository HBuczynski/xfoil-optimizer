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
    process_->start(program, arglist,QIODevice::Text | QIODevice::ReadWrite);
    if(process_->waitForStarted(TIMEOUT_MS))
    {
        status_ = Running;
        //We want to wait for the prompt//
        process_->waitForReadyRead(100);
        if(process_->canReadLine())
            std::cout<<"LOLHOW";
        qDebug() << "SimulationProxy::PROCESSSTARTED";
    }
    else
    {
        status_ = Error;
        //Error - did program did not start TODO handling approach
    }

}
void QSimulationProxy::Terminate()
{
    //TODO - exit from any menu - enter exits submenu//
    std::cout<<"Program returned:\r\n";
    int no_written = process_->write("\n\r\n\rQUIT\n\r",10);
    process_->waitForBytesWritten();
    process_->closeWriteChannel();
    if(!process_->waitForFinished(100))
    {
        std::cout<< "Process did not finish, force closing, written "<<no_written<<"\r\n";
        process_->terminate();
        if(!process_->waitForFinished(100))
        {
            std::cout<< "Process did not finish, force closing 2\r\n";
            process_->terminate();
            process_->waitForFinished(100);
        }
    }
    //Here we must navigate backwards and exit the program safely or just kill it
}
void QSimulationProxy::error(QProcess::ProcessError error)
{
    /* just feedback some text about the error */
    qDebug() << "SimulationProxy::error - " << error;
} // end_slot(SimulationProxy::error)

void QSimulationProxy::finished(int exitCode, QProcess::ExitStatus status)
{
    status_ = NotRunning;
    /* feedback some text about finished */
       std::cout<<"PROCESS FINSEHD\r\n";
} // end_slot (SimulationProxy::finished)

void QSimulationProxy::stateChanged(QProcess::ProcessState state)
{
    //std::cout<<"STATECHANGED\r\n"<<state.t;
    qDebug() << "SimulationProxy::stateChanged" << state;
}
void QSimulationProxy::read()
{
    std::cout<<"READ()r\n";
    qDebug() << process_->readAllStandardOutput();
}
