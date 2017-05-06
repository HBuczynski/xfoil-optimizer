#include "plot_dialog.h"

PlotDialog::PlotDialog()
{

}

void PlotDialog::initialize(QQmlApplicationEngine &engine)
{
    dialogComponent_ = new QQmlComponent(&engine,QUrl(QStringLiteral("qrc:/GeneticPlot.qml")));
    guiObjects_.plotWindow = dialogComponent_->create();
}

void PlotDialog::showDialog()
{
    guiObjects_.plotWindow->setProperty("visible", "true");
}
