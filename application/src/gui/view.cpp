#include "view.h"

#include <QDebug>
#include <QFileDialog>

#include <sstream>

#include "utility/utility.h"

View::View(Model *model): model_(model),
                          componentMainWindow_(new QQmlComponent(&engine_,QUrl(QStringLiteral("qrc:/main.qml"))))
{
    initializeGuiObjects();
    initializeModelViewConnection();

//    //only for tests
//    std::vector<double> dataX;
//    dataX.push_back(0.15);
//    dataX.push_back(0.3);
//    dataX.push_back(0.74);
//    dataX.push_back(0.3);
//    dataX.push_back(0.15);

//    //only for tests
//    std::vector<double> dataY;
//    dataY.push_back(0.45);
//    dataY.push_back(0.6);
//    dataY.push_back(0.24);
//    dataY.push_back(0.3);
//    dataY.push_back(0.45);

//    //only for tests
//    model_->updateBaseChart(dataX, dataY);
//    model_->updateOptimizedChart(dataX, dataY);
//    model_->updateGeneticChart(dataX, dataY);
}

void View::enableProgressBar()
{
    guiObjects_.busyIndicator.object->setProperty("indeterminate", "true");
}

void View::disableProgressBar()
{
    guiObjects_.busyIndicator.object->setProperty("indeterminate", "false");
}

View::~View()
{

}

void View::drawBaseChart(const std::vector<double> & dataX, const std::vector<double> & dataY)
{
    QVariantList x, y;

    for(int i=0; i<dataX.size(); ++i)
    {
        x << dataX[i];
        y << dataY[i];
    }

    QMetaObject::invokeMethod(guiObjects_.basePlot, "addData", Q_ARG(QVariant, x), Q_ARG(QVariant, y));
}

void View::drawOptimizedChart(const std::vector<double> &dataX, const std::vector<double> &dataY)
{
    QVariantList x, y;

    for(int i=0; i<dataX.size(); ++i)
    {
        x << dataX[i];
        y << dataY[i];
    }

    QMetaObject::invokeMethod(guiObjects_.optimizedPlot, "addData", Q_ARG(QVariant, x), Q_ARG(QVariant, y));
}

void View::drawGeneticPlot(const std::vector<double> &dataX, const std::vector<double> &dataY)
{
    plotDialog_.drawChart(dataX, dataY);
}

void View::buttonsClicked(QString name)
{
    //only for test
    qDebug() << name;

    if(name == "button1")
    {
        setFilePath();
    }
    else if(name == "button2")
    {
        settingDialog_.showDialog();
    }
    else if(name == "button3")
    {
        plotDialog_.showDialog();
    }
    else if(name == "runButton")
    {
        //TO DO
        // check target values
        // zabezpieczenie przed ponownym kliknięciem przycisku RUN ??

        if(guiObjects_.SET_BASE && checkIfTargetIsSet())
        {
            emit setTargetProfileValues(targetParameters_);

            enableProgressBar();


            //TO DO
            //run optimization
        }
    }
}

void View::getFitnessParametersLabel(AviationProfileParameters data)
{
   guiObjects_.fitnessValues.at(0)->setProperty("text", data.alfa);
   guiObjects_.fitnessValues.at(1)->setProperty("text", data.clMax);
   guiObjects_.fitnessValues.at(2)->setProperty("text", data.cdMax);
}

void View::getBaseProfileValues(AviationProfileParameters data)
{
    guiObjects_.baseParameters.at(0)->setProperty("text", data.alfa);
    guiObjects_.baseParameters.at(1)->setProperty("text", data.clMax);
    guiObjects_.baseParameters.at(2)->setProperty("text", data.cdMax);

    guiObjects_.SET_BASE = true;
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
        initializeOptimizerSettings();
        initializePlotDialog();
    }
    catch(const ExceptionHandler &ex)
    {
        //TO DO: save information to logger and end program
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

    //initialize run button
    guiObjects_.runButton = guiObjects_.mainWindow->findChild<QObject*>("runButton");
    isSuccess = isSuccess && guiObjects_.runButton;

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

    guiObjects_.basePlot = guiObjects_.baseChartFrame.object->findChild<QObject *>("basePlot");
    if(!guiObjects_.basePlot)
        throw ExceptionHandler("Gui object - basePlot didn't initialize.");


    guiObjects_.optimizeChartFrame.name = "frameOptimizeChart";
    guiObjects_.optimizeChartFrame.object = guiObjects_.mainWindow->findChild<QObject *>(guiObjects_.optimizeChartFrame.name.c_str());
    if(!guiObjects_.baseChartFrame.object)
        throw ExceptionHandler("Gui object - " + guiObjects_.baseChartFrame.name + " didn't initialize.");

    guiObjects_.optimizedPlot = guiObjects_.optimizeChartFrame.object->findChild<QObject *>("optimizedPlot");
    if(!guiObjects_.optimizedPlot)
        throw ExceptionHandler("Gui object - optimizedPlot didn't initialize.");
}

void View::initializeBusyIndicator()
{
    guiObjects_.busyIndicator.name = "busyIndicator";
    guiObjects_.busyIndicator.object = guiObjects_.mainWindow->findChild<QObject*>(guiObjects_.busyIndicator.name.c_str());
    if(!guiObjects_.busyIndicator.object)
        throw ExceptionHandler("Gui object - " + guiObjects_.busyIndicator.name + " didn't initialize.");
}

void View::initializeOptimizerSettings()
{
    settingDialog_.initialize(engine_);
}

void View::initializePlotDialog()
{
    plotDialog_.initialize(engine_);
}

void View::setFilePath()
{
    std::string baseFilePath("");
    baseFilePath = (QFileDialog::getOpenFileName(Q_NULLPTR,QString(),QString(),"*.dat")).toStdString();

    if(baseFilePath != "")
        emit redirectPathToBaseProfile(baseFilePath);
}

bool View::checkIfTargetIsSet()
{
    bool flag = true;

//    QString lol = guiObjects_.targetValues[0]->getPlaceHolderText();
//    flag = flag && (guiObjects_.targetValues[0]->getText() != " ");
//    flag = flag && (guiObjects_.targetValues.at(1)->getText() != " ");
//    flag = flag && (guiObjects_.targetValues.at(2)->getText() != " ");

    return flag;
}

void View::initializeModelViewConnection()
{
    //connect model with view
    QObject::connect(model_, SIGNAL(updateBaseChart(const std::vector<double> &,const std::vector<double> &)),
                     this, SLOT(drawBaseChart(const std::vector<double> &,const std::vector<double> &)));
    QObject::connect(model_, SIGNAL(updateOptimizedChart(const std::vector<double> &,const std::vector<double> &)),
                     this, SLOT(drawOptimizedChart(const std::vector<double> &,const std::vector<double> &)));
    QObject::connect(model_, SIGNAL(updateGeneticChart(const std::vector<double> &,const std::vector<double> &)),
                     this, SLOT(drawGeneticPlot(std::vector<double>,std::vector<double>)));
    QObject::connect(model_, SIGNAL(setFitnessParameters(AviationProfileParameters)), this, SLOT(getFitnessParametersLabel(AviationProfileParameters)));
    QObject::connect(model_, SIGNAL(setBasicProfileParameters(AviationProfileParameters)), this, SLOT(getBaseProfileValues(AviationProfileParameters)));
    QObject::connect(this, SIGNAL(setTargetProfileValues(AviationProfileParameters)), model_, SLOT(getTargetProfileValues(AviationProfileParameters)));
    QObject::connect(this, SIGNAL(redirectPathToBaseProfile(std::string)), model_, SLOT(calculateBaseProfileParameters(std::string)));
    //initialize connection with buttons
    for(int i=0; i<guiObjects_.buttonsCount; ++i)
        QObject::connect(guiObjects_.settingsButtons.at(i), SIGNAL(buttonClick(QString)), this,  SLOT(buttonsClicked(QString)));

    QObject::connect(guiObjects_.runButton, SIGNAL(buttonClick(QString)), this,  SLOT(buttonsClicked(QString)));
}
