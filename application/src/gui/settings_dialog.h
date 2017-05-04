#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QQmlApplicationEngine>
#include <QQmlComponent>

#include "gui/gui_objects.h"

class SettingsDialog
{
public:
    SettingsDialog();
    void initialize(QQmlApplicationEngine &engine);
    void showDialog();

private:
    QQmlComponent *dialogComponent_;

    SettingsObjects guiObjects_;
};

#endif // SETTINGSDIALOG_H
