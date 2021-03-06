#include <QString>
#include <QtTest>
#include "xfoil/qsimulation.h"
#include "xfoil/simulation_proxy.h"
#include "xfoil/simulation.h"
#include "optimizer/geometry.h"
#include "utility/config.h"

class Geometry_Tests : public QObject
{
    Q_OBJECT

public:
    Geometry_Tests();
private:
    QString profilePath;
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void LoadingGeometryFromFileCreatesPoints();
    void SavingGeometryObjectsToFileIsReversible();
    void SavingAGeometryObjectGeneratesAFile();
    void SavingCoefficientsObjectsToFile();
    void CreateVectorX();
    void CheckIfBasicProfileIsNotCrossed();
    void CheckBasicAirfoilSimResultsMethodAccess();
};

Geometry_Tests::Geometry_Tests()
{
}
void Geometry_Tests::initTestCase()
{
    //This is old direct proxy method of recieving airfoil file but omits geometry object//
    Config::SimulationParams params;
    QSimulationProxy proxy(params);
    proxy.addCommand("NACA 0012");
    proxy.addCommand("SAVE NACA0012.dat");
    proxy.addCommand("\r\n");
    proxy.run();
    proxy.terminate();
    profilePath = QString::fromStdString(proxy.getExePath() + "/NACA0012.dat");
    QVERIFY(QFile::exists(profilePath));
}
void Geometry_Tests::cleanupTestCase()
{
    QVERIFY(QFile::exists(profilePath));
    QFile::remove(profilePath);
    QVERIFY(!QFile::exists(profilePath));
}
void Geometry_Tests::CreateVectorX()
{
    Geometry geom1(profilePath.toStdString());
    QVERIFY((*(--geom1.getPoints().end())).x == 1);
    QVERIFY(geom1.getPoints().size() == 2*geom1.getPointsCount());
}
void Geometry_Tests::LoadingGeometryFromFileCreatesPoints()
{
    Geometry geom(profilePath.toStdString());
    QVERIFY(geom.getPoints().size() > 0);
}
void Geometry_Tests::SavingAGeometryObjectGeneratesAFile()
{
    Geometry geom1(profilePath.toStdString());
    geom1.save("tmpgeom.dat");
    QVERIFY(QFile::exists(QString::fromStdString("tmpgeom.dat")));
    QFile::remove(QString::fromStdString("tmpgeom.dat"));
    QVERIFY(!QFile::exists(QString::fromStdString("tmpgeom.dat")));
}
void Geometry_Tests::SavingGeometryObjectsToFileIsReversible()
{
    Geometry geom1(profilePath.toStdString());
    geom1.save("tmpgeom.dat");
    QVERIFY(QFile::exists(QString::fromStdString("tmpgeom.dat")));
    Geometry geom2("tmpgeom.dat");
    QVERIFY(geom1.getPoints().size() == geom2.getPoints().size());
    //Compare both vectors//
    //QVERIFY(equal(geom1.GetPoints().begin(), geom1.GetPoints().end(), geom2.GetPoints().begin()));
    QFile::remove(QString::fromStdString("tmpgeom.dat"));
    QVERIFY(!QFile::exists(QString::fromStdString("tmpgeom.dat")));
}

void Geometry_Tests::SavingCoefficientsObjectsToFile()
{
    Geometry geom1(profilePath.toStdString());
    geom1.saveCoefficients("coefTest.dat");
    geom1.loadFromCoefficients("coefTest.dat");

    AirfoilCoefficients coefficients = geom1.getAifroilCoefficients();

    QVERIFY(coefficients.a_l != -100);
    QVERIFY(coefficients.b_l != -100);
    QVERIFY(coefficients.c_l != -100);
    QVERIFY(coefficients.d_l != -100);
    QVERIFY(coefficients.q_l != -100);
    QVERIFY(coefficients.p_l != -100);
    QVERIFY(coefficients.a_u != -100);
    QVERIFY(coefficients.b_u != -100);
    QVERIFY(coefficients.c_u != -100);
    QVERIFY(coefficients.d_u != -100);
    QVERIFY(coefficients.p_u != -100);
    QVERIFY(coefficients.q_u != -100);

    QFile::remove(QString::fromStdString("tmpgeom.dat"));
    QVERIFY(!QFile::exists(QString::fromStdString("tmpgeom.dat")));
}

void Geometry_Tests::CheckIfBasicProfileIsNotCrossed()
{
    Geometry geom1;
    QVERIFY(geom1.isProfileCrossed() == false);
}
void Geometry_Tests::CheckBasicAirfoilSimResultsMethodAccess()
{
    Config::SimulationParams params;
    params.viscousEnable = false;
    Geometry testGeom(profilePath.toStdString());
    SimulationHandler sim(testGeom,params);
    sim.run();
    while(sim.pollStatus() == SimulationHandler::Running);
    QVERIFY(testGeom.getResults().isCalculated());
}

QTEST_MAIN(Geometry_Tests)

#include "tst_geometry_tests.moc"
