#include "xfoil/simulation.h"
#include <qstringlist.h>
#include <QtDebug>

#include <iostream>

SimulationProxy::SimulationProxy(QObject *parent):
    results_(nullptr),
    status_(NotRunning),
    started_(false)
{
    process_ = new QProcess(this);
    connect(process_,
            SIGNAL(error(QProcess::ProcessError)),
            SLOT(error(QProcess::ProcessError)));
    connect(process_,
            SIGNAL(finished(int, QProcess::ExitStatus)),
            SLOT(finished(int, QProcess::ExitStatus)));
    connect(process_,
            SIGNAL(stateChanged(QProcess::ProcessState)),
            SLOT(stateChanged(QProcess::ProcessState)));
    //Fork the process//
    //process_->start();

}
void SimulationProxy::Run()
{
    QString programPath = QString::fromStdString(exePath_);
    QString program = "\"" + programPath + "/xfoil.exe" + "\"";
    QStringList arglist;


    //QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    process_->setWorkingDirectory(programPath);
    //QString fullPath = programPath + ";" + env.value("Path");
    //env.insert("PATH", fullPath);
    //process_->setProcessEnvironment(env);



    process_->start(program, arglist, QIODevice::ReadWrite);
    Q_EMIT feedbackLog(process_->readAllStandardOutput());
    if(process_->waitForStarted(TIMEOUT_MS))
    {
        status_ = Idle;
        started_ = true;
        qDebug() << "SimulationProxy::PROCESSSTARTED";
    }
    else
    {
        status_ = Error;
        started_ = false;
        //Error - did program did not start TODO handling approach
    }


    //qDebug() << "SimulationProxy::Run";
}
void SimulationProxy::Terminate()
{
    //TODO - exit from any menu//
    //std::cout<<"Program returned:\r\n";
    //while(process_->waitForReadyRead());
    //qDebug() << process_->readAllStandardOutput();
    int no_written = process_->write("QUIT\n\r",6);
    program_.closeWriteChannel();
    //QByteArray result = process_->readAllStandardOutput();
    //std::string retval = result.toStdString();
    //std::cout<< retval;
    //Here we must navigate backwards and exit the program safely or just kill it
}
void SimulationProxy::error(QProcess::ProcessError error)
{
    /* just feedback some text about the error */
    qDebug() << "SimulationProxy::error - " << error;
} // end_slot(SimulationProxy::error)

void SimulationProxy::finished(int exitCode, QProcess::ExitStatus status)
{
    started_ = false;
    status_ = Finished;
    /* feedback some text about finished */
} // end_slot (SimulationProxy::finished)

void SimulationProxy::stateChanged(QProcess::ProcessState state)
{
    //qDebug() << "SimulationProxy::stateChanged" << state;
}
void feedbackLog(QString log)
{

}
