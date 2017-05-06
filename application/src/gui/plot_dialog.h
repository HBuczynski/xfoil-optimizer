#ifndef PLOT_DIALOG_H
#define PLOT_DIALOG_H

#include <QQmlApplicationEngine>
#include <QQmlComponent>

#include "gui/gui_objects.h"

class PlotDialog
{
public:
    PlotDialog();

    void initialize(QQmlApplicationEngine &engine);
    void showDialog();

private:
    QQmlComponent *dialogComponent_;

    Plot guiObjects_;

};

#endif // PLOT_DIALOG_H
