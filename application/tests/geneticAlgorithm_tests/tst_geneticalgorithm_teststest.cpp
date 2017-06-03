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
    Genome *genome = new Genome(AirfoilCoefficients());
    genome->Randomize();
    AirfoilCoefficients coeff = genome->getCoefficients();
    std::cout<<coeff.a_l<<" "<< coeff.q_u<<std::endl;
    delete genome;
}

void GeneticAlgorithm_testsTest::PerformSingleOptimizationStepOnSmallPopulation()
{
    //Config::OptimizerParams paramsOpt;
    //Config::SimulationParams paramsSim;
    //GeneticOptimizer *optimizer = new GeneticOptimizer(paramsSim,paramsOpt.fitness);
    //optimizer->initialize();
    //optimizer->runGeneticAlgorithm();
    //delete optimizer;
}

QTEST_MAIN(GeneticAlgorithm_testsTest)

#include "tst_geneticalgorithm_teststest.moc"
