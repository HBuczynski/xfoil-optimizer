#include "xfoil/simulation.h"
#include <qstringlist.h>
#include <QtDebug>

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
    process_->start();

}
void SimulationProxy::Run()
{
    QString program = QString::fromStdString(exePath_);
    QStringList arglist;
    process_->start(program, arglist);
    Q_EMIT feedbackLog(process_->readAllStandardOutput());
    if(process_->waitForStarted(TIMEOUT_MS))
    {
        status_ = Idle;
        started_ = true;
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
}
void SimulationProxy::error(QProcess::ProcessError error)
{
    /* just feedback some text about the error */
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
