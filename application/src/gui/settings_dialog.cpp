#include "settings_dialog.h"

#include "utility/utility.h"

SettingsDialog::SettingsDialog()
{

}

void SettingsDialog::initialize(QQmlApplicationEngine &engine)
{
    bool isSuccess = true;

    dialogComponent_ = new QQmlComponent(&engine,QUrl(QStringLiteral("qrc:/OptimizerSettings.qml")));
    guiObjects_.settingsWindow = dialogComponent_->create();

    if(!isSuccess)
        throw ExceptionHandler("Setting dialog didn't initialize.");

}

void SettingsDialog::showDialog()
{
    guiObjects_.settingsWindow->setProperty("visible", "true");
}
