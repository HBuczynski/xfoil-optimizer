#include <QString>
#include <QtTest>

#include "optimizer/airfoil_optimizer.h"
#include "optimizer/genetic/genetic.h"
#include "optimizer/geometry.h"
#include "xfoil/simulation.h"
class OptimizerTest : public QObject
{
    Q_OBJECT

public:
    OptimizerTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void GivenDudOptimizerProgressChanges();
    void OptimizerIsNotInitializedAtConstruction();
    void OptimizerIsInitializedAfterInitialize();
    void FitnessFunctionObjectCreation();
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
    Geometry geom = SimulationHandler::getNACAAirfoil("0012");
    DudOptimizer optimizer(geom);
    double savedProgress = optimizer.getProgress();
    optimizer.optimizeStep();
    QVERIFY(optimizer.getProgress() > savedProgress);
}
void OptimizerTest::OptimizerIsNotInitializedAtConstruction()
{
     //GeneticOptimizer optimizer;
     //QVERIFY(optimizer.GetState() == GeneticOptimizer::NotInitialized);
}
void OptimizerTest::OptimizerIsInitializedAfterInitialize()
{
     //GeneticOptimizer optimizer;
     //QVERIFY(optimizer.GetState() != GeneticOptimizer::GenerationComplete);
}
void OptimizerTest::FitnessFunctionObjectCreation()
{

}

QTEST_APPLESS_MAIN(OptimizerTest)

#include "tst_optimizertest.moc"
