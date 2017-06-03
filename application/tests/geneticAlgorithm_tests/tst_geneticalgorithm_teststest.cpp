#include <QString>
#include <QtTest>
#include "optimizer/airfoil_optimizer.h"
#include "optimizer/genetic/genetic.h"
#include "utility/config.h"
#include "optimizer/genetic/genome.h"
class GeneticAlgorithm_testsTest : public QObject
{
    Q_OBJECT

public:
    GeneticAlgorithm_testsTest();

private Q_SLOTS:
    void GenomObjectRandomizesAfterCreation();
    void PerformSingleOptimizationStepOnSmallPopulation();
};

GeneticAlgorithm_testsTest::GeneticAlgorithm_testsTest()
{


}
void GeneticAlgorithm_testsTest::GenomObjectRandomizesAfterCreation()
{
    Genome genomeRand;
    Genome genomeConst;
    genomeConst.Set(BinaryAirfoilCoefficients());
    uint8_t *array1 = genomeConst.getCoefficientsArray();
    uint8_t *array2 = genomeRand.getCoefficientsArray();
    for(int i = 0; i < sizeof(BinaryAirfoilCoefficients); ++i)
    {
        QVERIFY(array1[i] == 0);
    }
}

void GeneticAlgorithm_testsTest::PerformSingleOptimizationStepOnSmallPopulation()
{
    Config::OptimizerParams paramsOpt;
    Config::SimulationParams paramsSim;
    paramsSim.viscousEnable = false;
    GeneticOptimizer *optimizer = new GeneticOptimizer(paramsSim,paramsOpt.fitness);
    optimizer->initialize();
    optimizer->runGeneticAlgorithm();
    while(optimizer->isRunning())
    {
        QThread::msleep(10);
    }
    delete optimizer;
}

QTEST_MAIN(GeneticAlgorithm_testsTest)

#include "tst_geneticalgorithm_teststest.moc"
