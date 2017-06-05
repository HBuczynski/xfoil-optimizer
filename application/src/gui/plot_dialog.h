#ifndef PLOT_DIALOG_H
#define PLOT_DIALOG_H

#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <vector>
#include <QObject>

#include "gui/gui_objects.h"

/**
*	@file plot_dialog.h
*	@brief This header file contains all required functions to draw progress plot of genethic algorithm.
*	@author Jakub Polaczek & Hubert Buczyński
*	@date 05/06/2017
*/

//!  Class provides drawing chart in external dialog
class PlotDialog :QObject
{
    Q_OBJECT

public:
    PlotDialog();

    void initialize(QQmlApplicationEngine &engine);
    void showDialog();

    void drawChart(const std::vector<double> &dataX_, const std::vector<double> &dataY_);

private:
    QQmlComponent *dialogComponent_;

    Plot guiObjects_;
};

#endif // PLOT_DIALOG_H
