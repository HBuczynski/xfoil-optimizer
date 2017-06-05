#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QQmlApplicationEngine>
#include <QQmlComponent>

#include "gui/gui_objects.h"


/**
*	@file settings_dialog.h
*	@brief This header file consists settings dialog class.
*	@author Jakub Polaczek & Hubert Buczyński
*	@date 05/06/2017
*/

//!  The class takes care of genetic algorithm's settings obtain from user
class SettingsDialog : public QObject
{
    Q_OBJECT

public:
    SettingsDialog();
    void initialize(QQmlApplicationEngine &engine);
    void setInitialValues();
    void showDialog();

signals:
    void redirectOptimizerParameters();

public slots:
    void buttonsClicked(QString name);

private:
    void buttonsConnection();

    QQmlComponent *dialogComponent_;
    SettingsObjects guiObjects_;
};

#endif // SETTINGSDIALOG_H
