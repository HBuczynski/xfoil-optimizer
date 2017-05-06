#include "settings_dialog.h"

#include "utility/utility.h"
#include <QDebug>

SettingsDialog::SettingsDialog()
{

}

void SettingsDialog::initialize(QQmlApplicationEngine &engine)
{
    bool isSuccess = true;

    dialogComponent_ = new QQmlComponent(&engine,QUrl(QStringLiteral("qrc:/OptimizerSettings.qml")));
    guiObjects_.settingsWindow = dialogComponent_->create();
    isSuccess = isSuccess && guiObjects_.settingsWindow;

    guiObjects_.windowFrame = guiObjects_.settingsWindow->findChild<QObject*>("frame");
    isSuccess = isSuccess && guiObjects_.windowFrame;

    guiObjects_.cancelButton = guiObjects_.windowFrame->findChild<QObject*>("cancelButton");
    isSuccess = isSuccess && guiObjects_.cancelButton;

    guiObjects_.applyButton = guiObjects_.windowFrame->findChild<QObject*>("applyButton");
    isSuccess = isSuccess && guiObjects_.applyButton;

    if(!isSuccess)
        throw ExceptionHandler("Setting dialog didn't initialize.");

    buttonsConnection();

}

void SettingsDialog::showDialog()
{
    guiObjects_.settingsWindow->setProperty("visible", "true");
}

void SettingsDialog::buttonsClicked(QString name)
{
    qDebug() << name;

    if(name == "applyButton")
    {

    }
    else if (name == "cancelButton")
    {
        guiObjects_.settingsWindow->setProperty("visible", "false");
    }
}

void SettingsDialog::buttonsConnection()
{
    QObject::connect(guiObjects_.applyButton, SIGNAL(buttonClick(QString)), this,  SLOT(buttonsClicked(QString)));
    QObject::connect(guiObjects_.cancelButton, SIGNAL(buttonClick(QString)), this,  SLOT(buttonsClicked(QString)));
}
