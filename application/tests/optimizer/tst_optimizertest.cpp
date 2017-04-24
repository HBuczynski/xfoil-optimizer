#include <QString>
#include <QtTest>

class OptimizerTest : public QObject
{
    Q_OBJECT

public:
    OptimizerTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
};

OptimizerTest::OptimizerTest()
{
}

void OptimizerTest::initTestCase()
{
}

void OptimizerTest::cleanupTestCase()
{
}

void OptimizerTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(OptimizerTest)

#include "tst_optimizertest.moc"
