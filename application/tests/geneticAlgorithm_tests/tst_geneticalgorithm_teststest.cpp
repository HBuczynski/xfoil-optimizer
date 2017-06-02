#include <QString>
#include <QtTest>

class GeneticAlgorithm_testsTest : public QObject
{
    Q_OBJECT

public:
    GeneticAlgorithm_testsTest();

private Q_SLOTS:
    void testCase1();
};

GeneticAlgorithm_testsTest::GeneticAlgorithm_testsTest()
{
}

void GeneticAlgorithm_testsTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(GeneticAlgorithm_testsTest)

#include "tst_geneticalgorithm_teststest.moc"
