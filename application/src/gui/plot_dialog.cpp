#include "plot_dialog.h"
#include <QVariant>
#include <QDebug>

#include "utility/utility.h"

PlotDialog::PlotDialog()
{

}

void PlotDialog::initialize(QQmlApplicationEngine &engine)
{
    bool isSuccess = true;

    dialogComponent_ = new QQmlComponent(&engine,QUrl(QStringLiteral("qrc:/GeneticPlot.qml")));
    guiObjects_.plotWindow = dialogComponent_->create();
    isSuccess = isSuccess && guiObjects_.plotWindow;

    guiObjects_.plotFrame = guiObjects_.plotWindow->findChild<QObject*>("frame");
    isSuccess = isSuccess && guiObjects_.plotFrame;

    guiObjects_.plot = guiObjects_.plotFrame->findChild<QObject*>("geneticPlot");
    isSuccess = isSuccess && guiObjects_.plot;

    if(!isSuccess)
        throw ExceptionHandler("Plot dialog didn't initialize.");

}

void PlotDialog::showDialog()
{
    guiObjects_.plotWindow->setProperty("visible", "true");
}

void PlotDialog::drawChart(const std::vector<double> &dataX, const std::vector<double> &dataY)
{
    QVariantList x, y;

    for(int i=0; i<dataX.size(); ++i)
    {
        x << dataX[i];
        y << dataY[i];
    }

    QMetaObject::invokeMethod(guiObjects_.plot, "addData", Q_ARG(QVariant, x), Q_ARG(QVariant, y));
}

void PlotDialog::clear()
{
    QMetaObject::invokeMethod(guiObjects_.plot,"clear");
}
