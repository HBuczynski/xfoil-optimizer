#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QObject>

#include "gui/gui_objects.h"

class SettingsDialog : QObject
{
    Q_OBJECT

public:
    SettingsDialog();
    void initialize(QQmlApplicationEngine &engine);
    void showDialog();

public slots:
    void buttonsClicked(QString name);

private:
    void buttonsConnection();

    QQmlComponent *dialogComponent_;
    SettingsObjects guiObjects_;
};

#endif // SETTINGSDIALOG_H