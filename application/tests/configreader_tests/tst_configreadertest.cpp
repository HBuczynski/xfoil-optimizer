#include <QString>
#include <QtTest>

class ConfigReaderTest : public QObject
{
    Q_OBJECT

public:
    ConfigReaderTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void ObjectCreationCreatesDefaultFile();
};

ConfigReaderTest::ConfigReaderTest()
{
}

void ConfigReaderTest::initTestCase()
{
}

void ConfigReaderTest::cleanupTestCase()
{
}

void ConfigReaderTest::ObjectCreationCreatesDefaultFile()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(ConfigReaderTest)

#include "tst_configreadertest.moc"
