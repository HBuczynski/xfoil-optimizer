#include <QString>
#include <QtTest>
#include "utility/config.h"
#include "utility/configuration_reader.h"

class ConfigReaderTest : public QObject
{
    Q_OBJECT

public:
    ConfigReaderTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void ObjectCreationCreatesDefaultFile();
    void DefaultObjectLoadedReturnsDefaultParameters();
    void ChangedParameterCanBeRetrievedAfterLoad();
private:
    QString configFilePath;
};

ConfigReaderTest::ConfigReaderTest()
{

}

void ConfigReaderTest::initTestCase()
{
    configFilePath = QString::fromStdString(ConfigurationReader::getParameterFilePath());
    //Delete initial config file//
    if(QFile::exists(configFilePath))
        QFile::remove(configFilePath);
    QVERIFY(!QFile::exists(configFilePath));
}

void ConfigReaderTest::cleanupTestCase()
{
    if(QFile::exists(configFilePath))
    QFile::remove(configFilePath);
    QVERIFY(!QFile::exists(configFilePath));
}

void ConfigReaderTest::ObjectCreationCreatesDefaultFile()
{
    ConfigurationReader reader;
    reader.initialize();
    QVERIFY(QFile::exists(configFilePath));
}
void ConfigReaderTest::DefaultObjectLoadedReturnsDefaultParameters()
{
    QVERIFY(QFile::exists(configFilePath));
    ConfigurationReader reader;
    reader.initialize();
    Config::SimulationParams params1;
    Config::SimulationParams params2 = reader.getSimulatorParameters();
    QVERIFY(params1.iterationLimit == params2.iterationLimit);
    QVERIFY(params1.parallelSimulations == params2.parallelSimulations);
    QVERIFY(params1.reynoldsNo == params2.reynoldsNo);
    QVERIFY(params1.viscousEnable == params2.viscousEnable);
    QVERIFY(params1.xfoilExecutablePath == params2.xfoilExecutablePath);
    QVERIFY(params1.xfoilTimeout == params2.xfoilTimeout);
}

void ConfigReaderTest::ChangedParameterCanBeRetrievedAfterLoad()
{
    QVERIFY(QFile::exists(configFilePath));
    ConfigurationReader reader;
    reader.initialize();

}

QTEST_APPLESS_MAIN(ConfigReaderTest)

#include "tst_configreadertest.moc"
