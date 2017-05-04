#include "settings_dialog.h"

SettingsDialog::SettingsDialog()
{

}

void SettingsDialog::initialize(QQmlApplicationEngine &engine)
{
    dialogComponent_ = new QQmlComponent(&engine,QUrl(QStringLiteral("qrc:/OptimizerSettings.qml")));
    guiObjects_.settingsWindow = dialogComponent_->create();
}

void SettingsDialog::showDialog()
{
    guiObjects_.settingsWindow->setProperty("visible", "true");
}
