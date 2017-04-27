#include "view.h"

#include <QDebug>
#include <sstream>

#include "utility/utility.h"

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

void View::buttonsClicked(QString name)
{
    //only for test
    qDebug() << name;
}

void View::initializeGuiObjects()
{
    try
    {
        initializeMainWindow();
        initializeButtons();
        initializeBaseParametersLabels();
        initializeFitnessParametersLabels();
        initializeTargetValuesFields();
        initializeChartsFrames();
        initializeBusyIndicator();
    }
    catch(const ExceptionHandler &ex)
    {
        //TO DO: save information and end program to logger
        qDebug() << ex.e.c_str();   //only for tests
    }
}

void View::initializeMainWindow()
{
    guiObjects_.mainWindow = componentMainWindow_->create();

    if(guiObjects_.mainWindow == nullptr)
        throw ExceptionHandler("Main window object didn't initialize.");
}

void View::initializeButtons()
{
    guiObjects_.settingsButtonsRoot.name = "buttonFrame";
    guiObjects_.settingsButtonsRoot.object = guiObjects_.mainWindow->findChild<QObject*>(guiObjects_.settingsButtonsRoot.name.c_str());

    if(!guiObjects_.settingsButtonsRoot.object)
        throw ExceptionHandler("Gui object - " + guiObjects_.settingsButtonsRoot.name + " didn't initialize.");

    std::stringstream name;
    std::string objectName("");
    bool isSuccess = true;

    for(int i=1; i<= guiObjects_.buttonsCount; ++i)
    {
        name << "button" << i;
        objectName = name.str();
        guiObjects_.settingsButtons.push_back(guiObjects_.settingsButtonsRoot.object->findChild<QObject*>(objectName.c_str()));
        isSuccess = isSuccess && guiObjects_.settingsButtons.front();
        name.str(std::string());
        name.clear();
    }

    if(!isSuccess)
        throw ExceptionHandler("Gui buttons object didn't initialize.");
}

void View::initializeBaseParametersLabels()
{
    guiObjects_.baseParametersRoot.name = "baseParametersBox";
    guiObjects_.baseParametersRoot.object = guiObjects_.mainWindow->findChild<QObject*>(guiObjects_.baseParametersRoot.name.c_str());

    if(! guiObjects_.baseParametersRoot.object)
        throw ExceptionHandler("Gui object - " +  guiObjects_.baseParametersRoot.name + " didn't initialize.");

    std::stringstream name;
    std::string objectName("");
    bool isSuccess = true;

    for(int i=1; i<= guiObjects_.parametersLabelCount; ++i)
    {
        name << "baseParamText" << i;
        objectName = name.str();
        guiObjects_.baseParameters.push_back(guiObjects_.baseParametersRoot.object->findChild<QObject*>(objectName.c_str()));
        isSuccess = isSuccess && guiObjects_.baseParameters.front();
        name.str(std::string());
        name.clear();
    }

    if(!isSuccess)
        throw ExceptionHandler("Gui baseParameters object didn't initialize.");
}

void View::initializeTargetValuesFields()
{
    guiObjects_.targetValuesRoot.name = "targetParametersBox";
    guiObjects_.targetValuesRoot.object = guiObjects_.mainWindow->findChild<QObject*>(guiObjects_.targetValuesRoot.name.c_str());

    if(!guiObjects_.targetValuesRoot.object)
        throw ExceptionHandler("Gui object - " + guiObjects_.targetValuesRoot.name + " didn't initialize.");

    std::stringstream name;
    std::string objectName("");
    bool isSuccess = true;

    for(int i=1; i<= guiObjects_.parametersLabelCount; ++i)
    {
        name << "targetTextField" << i;
        objectName = name.str();
        guiObjects_.targetValues.push_back(guiObjects_.targetValuesRoot.object->findChild<QObject*>(objectName.c_str()));
        isSuccess = isSuccess && guiObjects_.targetValues.front();
        name.str(std::string());
        name.clear();
    }

    if(!isSuccess)
        throw ExceptionHandler("Gui targetParameters object didn't initialize.");
}

void View::initializeFitnessParametersLabels()
{
    guiObjects_.fitnessValuesRoot.name = "fitnessParameters";
    guiObjects_.fitnessValuesRoot.object = guiObjects_.mainWindow->findChild<QObject*>(guiObjects_.fitnessValuesRoot.name.c_str());

    if(!guiObjects_.fitnessValuesRoot.object)
        throw ExceptionHandler("Gui object - " + guiObjects_.fitnessValuesRoot.name + " didn't initialize.");

    std::stringstream name;
    std::string objectName("");
    bool isSuccess = true;

    for(int i=1; i<= guiObjects_.parametersLabelCount; ++i)
    {
        name << "fitnessText" << i;
        objectName = name.str();
        guiObjects_.fitnessValues.push_back(guiObjects_.fitnessValuesRoot.object->findChild<QObject*>(objectName.c_str()));
        isSuccess = isSuccess && guiObjects_.fitnessValues.front();
        name.str(std::string());
        name.clear();
    }
    if(!isSuccess)
        throw ExceptionHandler("Gui fitnessParameters object didn't initialize.");
}

void View::initializeChartsFrames()
{
    //initialize charts frame
    guiObjects_.baseChartFrame.name = "frameBaseChart";
    guiObjects_.baseChartFrame.object = guiObjects_.mainWindow->findChild<QObject *>(guiObjects_.baseChartFrame.name.c_str());
    if(!guiObjects_.baseChartFrame.object)
        throw ExceptionHandler("Gui object - " + guiObjects_.baseChartFrame.name + " didn't initialize.");

    guiObjects_.optimizeChartFrame.name = "frameOptimizeChart";
    guiObjects_.optimizeChartFrame.object = guiObjects_.mainWindow->findChild<QObject *>(guiObjects_.optimizeChartFrame.name.c_str());
    if(!guiObjects_.baseChartFrame.object)
        throw ExceptionHandler("Gui object - " + guiObjects_.baseChartFrame.name + " didn't initialize.");
}

void View::initializeBusyIndicator()
{
    guiObjects_.busyIndicator.name = "busyIndicator";
    guiObjects_.busyIndicator.object = guiObjects_.mainWindow->findChild<QObject*>(guiObjects_.busyIndicator.name.c_str());
    if(!guiObjects_.busyIndicator.object)
        throw ExceptionHandler("Gui object - " + guiObjects_.busyIndicator.name + " didn't initialize.");
}

void View::initializeModelViewConnection()
{
    //connect model with view
    QObject::connect(model_, SIGNAL(updateChart(const std::vector<double> &,const std::vector<double> &)), this, SLOT(drawChart(const std::vector<double> &,const std::vector<double> &)));

    //initialize connection with buttons
    for(int i=0; i<guiObjects_.buttonsCount; ++i)
        QObject::connect(guiObjects_.settingsButtons.at(i), SIGNAL(buttonClick(QString)), this,  SLOT(buttonsClicked(QString)));
}

void View::destroyGuiObjects()
{
    delete componentMainWindow_;
}
