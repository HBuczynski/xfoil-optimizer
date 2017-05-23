#include <QString>
#include <QtTest>
#include <QCoreApplication>

class QSimulationProxy_tests : public QObject
{
    Q_OBJECT

public:
    QSimulationProxy_tests();

private Q_SLOTS:
    void testCase1();
};

QSimulationProxy_tests::QSimulationProxy_tests()
{
}

void QSimulationProxy_tests::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(QSimulationProxy_tests)

#include "tst_qsimulationproxy_tests.moc"
