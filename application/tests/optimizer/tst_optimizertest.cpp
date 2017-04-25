#include <QString>
#include <QtTest>

#include "optimizer/airfoil_optimizer.h"
#include "optimizer/geometry.h"
class OptimizerTest : public QObject
{
    Q_OBJECT

public:
    OptimizerTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void GivenDudOptimizerProgressChanges();
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

void OptimizerTest::GivenDudOptimizerProgressChanges()
{
    DudOptimizer optimizer = DudOptimizer(Geometry());
    double savedProgress = optimizer.GetProgress();
    optimizer.OptimizeStep();
    QVERIFY(optimizer.GetProgress() > savedProgress);
}

QTEST_APPLESS_MAIN(OptimizerTest)

#include "tst_optimizertest.moc"
