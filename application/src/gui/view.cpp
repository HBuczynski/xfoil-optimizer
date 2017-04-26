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

void View::drawChart(const std::vector<double> & dataX, const std::vector<double> & dataY)
{

}

void View::initializeGuiObjects()
{
    //TO DO : zrobić wyjątki

    initializeMainWindow();
    initializeButtons();
    initializeBaseParametersLabels();
    initializeFitnessParametersLabels();
    initializeTargetValuesFields();
    initializeChartsFrames();
    initializeBusyIndicator();
}

void View::initializeMainWindow()
{
    guiObjects_.mainWindow = componentMainWindow_->create();
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
    guiObjects_.baseParametersRoot.name = "baseParametersBox";
    guiObjects_.baseParametersRoot.object = guiObjects_.mainWindow->findChild<QObject*>(guiObjects_.baseParametersRoot.name.c_str());

    std::stringstream name;
    std::string objectName("");

    for(int i=1; i<= guiObjects_.parametersLabelCount; ++i)
    {
        name << "baseParamText" << i;
        objectName = name.str();
        guiObjects_.baseParameters.push_back(guiObjects_.baseParametersRoot.object->findChild<QObject*>(objectName.c_str()));

        name.str(std::string());
        name.clear();
    }

}

void View::initializeTargetValuesFields()
{
    guiObjects_.targetValuesRoot.name = "targetParametersBox";
    guiObjects_.targetValuesRoot.object = guiObjects_.mainWindow->findChild<QObject*>(guiObjects_.targetValuesRoot.name.c_str());

    std::stringstream name;
    std::string objectName("");

    for(int i=1; i<= guiObjects_.parametersLabelCount; ++i)
    {
        name << "targetTextField" << i;
        objectName = name.str();
        guiObjects_.targetValues.push_back(guiObjects_.targetValuesRoot.object->findChild<QObject*>(objectName.c_str()));

        name.str(std::string());
        name.clear();
    }
}

void View::initializeFitnessParametersLabels()
{
    guiObjects_.fitnessValuesRoot.name = "fitnessParameters";
    guiObjects_.fitnessValuesRoot.object = guiObjects_.mainWindow->findChild<QObject*>(guiObjects_.fitnessValuesRoot.name.c_str());

    std::stringstream name;
    std::string objectName("");

    for(int i=1; i<= guiObjects_.parametersLabelCount; ++i)
    {
        name << "fitnessText" << i;
        objectName = name.str();
        guiObjects_.fitnessValues.push_back(guiObjects_.fitnessValuesRoot.object->findChild<QObject*>(objectName.c_str()));

        name.str(std::string());
        name.clear();
    }
}

void View::initializeChartsFrames()
{
    //initialize charts frame
    guiObjects_.baseChartFrame.name = "frameBaseChart";
    guiObjects_.baseChartFrame.object = guiObjects_.mainWindow->findChild<QObject *>(guiObjects_.baseChartFrame.name.c_str());

    guiObjects_.optimizeChartFrame.name = "frameOptimizeChart";
    guiObjects_.optimizeChartFrame.object = guiObjects_.mainWindow->findChild<QObject *>(guiObjects_.optimizeChartFrame.name.c_str());
}

void View::initializeBusyIndicator()
{
    guiObjects_.busyIndicator.name = "busyIndicator";
    guiObjects_.busyIndicator.object = guiObjects_.mainWindow->findChild<QObject*>(guiObjects_.busyIndicator.name.c_str());
}

void View::initializeModelViewConnection()
{
    QObject::connect(model_, SIGNAL(updateChart(const std::vector<double> &,const std::vector<double> &)), this, SLOT(drawChart(const std::vector<double> &,const std::vector<double> &)));
}

void View::destroyGuiObjects()
{
    delete componentMainWindow_;
}
