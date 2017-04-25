#include "view.h"

#include <QDebug>
#include <sstream>

View::View(Model *model): model_(model),
                          componentMainWindow_(new QQmlComponent(&engine_,QUrl(QStringLiteral("qrc:/main.qml"))))
{
    initializeGuiObjects();
    initializeModelViewConnection();
}

View::~View()
{
    destroyGuiObjects();
}

const AviationProfileParameters& View::getInitialProfileParameters()
{
    return profileParameters_;
}

void View::initializeGuiObjects()
{
    //initialize main window
    guiObjects_.mainWindow = componentMainWindow_->create();

    //initialize components inside window
    initializeButtons();
    initializeBaseParametersLabels();
    initializeFitnessParametersLabels();
    initializeTargetValuesFields();
    initializeBusyIndicator();
}

void View::initializeButtons()
{
    guiObjects_.settingsButtonsRoot.name = "buttonFrame";
    guiObjects_.settingsButtonsRoot.object = guiObjects_.mainWindow->findChild<QObject*>(guiObjects_.settingsButtonsRoot.name.c_str());

    std::stringstream name;
    std::string objectName("");

    for(int i=1; i<= guiObjects_.buttonsCount; ++i)
    {
        name << "button" << i;
        objectName = name.str();
        guiObjects_.settingsButtons.push_back(guiObjects_.settingsButtonsRoot.object->findChild<QObject*>(objectName.c_str()));
        name.str(std::string());
        name.clear();
    }
}

void View::initializeBaseParametersLabels()
{

}

void View::initializeTargetValuesFields()
{

}

void View::initializeFitnessParametersLabels()
{

}

void View::initializeChartsFrames()
{
    //initialize charts frame
    guiObjects_.baseChartFrame.name = "baseChartFrame";
    guiObjects_.baseChartFrame.object = guiObjects_.mainWindow->findChild<QObject *>(guiObjects_.baseChartFrame.name.c_str());

    guiObjects_.optimizeChartFrame.name = "optimizeChartFrame";
    guiObjects_.optimizeChartFrame.object = guiObjects_.mainWindow->findChild<QObject *>(guiObjects_.optimizeChartFrame.name.c_str());
}

void View::initializeBusyIndicator()
{
    guiObjects_.busyIndicator.name = "busyIndicator";
    guiObjects_.busyIndicator.object = guiObjects_.mainWindow->findChild<QObject*>(guiObjects_.busyIndicator.name.c_str());
}

void View::initializeModelViewConnection()
{

}

void View::destroyGuiObjects()
{
    delete componentMainWindow_;
}
