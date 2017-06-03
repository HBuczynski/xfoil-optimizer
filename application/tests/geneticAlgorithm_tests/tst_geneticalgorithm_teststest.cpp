#include <QString>
#include <QtTest>
#include "optimizer/airfoil_optimizer.h"
#include "optimizer/genetic/genetic.h"
#include "utility/config.h"
class GeneticAlgorithm_testsTest : public QObject
{
    Q_OBJECT

public:
    GeneticAlgorithm_testsTest();

private Q_SLOTS:
    void PerformSingleOptimizationStepOnSmallPopulation();
};

GeneticAlgorithm_testsTest::GeneticAlgorithm_testsTest()
{
}

void GeneticAlgorithm_testsTest::PerformSingleOptimizationStepOnSmallPopulation()
{
    Config::OptimizerParams paramsOpt;
    Config::SimulationParams paramsSim;
    GeneticOptimizer *optimizer = new GeneticOptimizer(paramsSim,paramsOpt.fitness);
    delete optimizer;
}

QTEST_MAIN(GeneticAlgorithm_testsTest)

#include "tst_geneticalgorithm_teststest.moc"
