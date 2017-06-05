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

    guiObjects_.generationCount = guiObjects_.windowFrame->findChild<QObject*>("generationCount");
    isSuccess = isSuccess && guiObjects_.generationCount;

    guiObjects_.populationSize = guiObjects_.windowFrame->findChild<QObject*>("populationSize");
    isSuccess = isSuccess && guiObjects_.populationSize;

    guiObjects_.muatationRate = guiObjects_.windowFrame->findChild<QObject*>("mutationRate");
    isSuccess = isSuccess && guiObjects_.muatationRate;

    if(!isSuccess)
        throw ExceptionHandler("Setting dialog didn't initialize.");

    buttonsConnection();
    setInitialValues();

}

void SettingsDialog::setInitialValues()
{
    guiObjects_.populationSize->setProperty("text", 20);
    guiObjects_.generationCount->setProperty("text", 100);
    guiObjects_.muatationRate->setProperty("text", 0.05);
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
        //TO DO: zapisac do struktury parametry
        // przekazac ta strukture w sygnale;
        emit redirectOptimizerParameters();
    }
    else if (name == "cancelButton")
    {
        guiObjects_.settingsWindow->setProperty("visible", "false");
        setInitialValues();
    }
}

void SettingsDialog::buttonsConnection()
{
    QObject::connect(guiObjects_.applyButton, SIGNAL(buttonClick(QString)), this,  SLOT(buttonsClicked(QString)));
    QObject::connect(guiObjects_.cancelButton, SIGNAL(buttonClick(QString)), this,  SLOT(buttonsClicked(QString)));
}
