#include <QString>
#include <QtTest>
#include "xfoil/qsimulation.h"
#include "xfoil/simulation_proxy.h"
#include "optimizer/geometry.h"

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

};

Geometry_Tests::Geometry_Tests()
{
}
void Geometry_Tests::initTestCase()
{
    QSimulationProxy proxy;
    proxy.AddCommand("NACA 0012");
    proxy.AddCommand("SAVE NACA0012.dat");
    proxy.AddCommand("\r\n");
    proxy.Run();
    proxy.Terminate();
    profilePath = QString::fromStdString(proxy.GetExePath() + "/NACA0012.dat");
    QVERIFY(QFile::exists(profilePath));
}
void Geometry_Tests::cleanupTestCase()
{
    QVERIFY(QFile::exists(profilePath));
    QFile::remove(profilePath);
    QVERIFY(!QFile::exists(profilePath));
}
void Geometry_Tests::LoadingGeometryFromFileCreatesPoints()
{
    Geometry geom(profilePath.toStdString());
    QVERIFY(geom.GetPoints().size() > 0);
}
void Geometry_Tests::SavingAGeometryObjectGeneratesAFile()
{
    Geometry geom1(profilePath.toStdString());
    geom1.Save("tmpgeom.dat");
    QVERIFY(QFile::exists(QString::fromStdString("tmpgeom.dat")));
    QFile::remove(QString::fromStdString("tmpgeom.dat"));
    QVERIFY(!QFile::exists(QString::fromStdString("tmpgeom.dat")));
}
void Geometry_Tests::SavingGeometryObjectsToFileIsReversible()
{
    Geometry geom1(profilePath.toStdString());
    geom1.Save("tmpgeom.dat");
    QVERIFY(QFile::exists(QString::fromStdString("tmpgeom.dat")));
    Geometry geom2("tmpgeom.dat");
    QVERIFY(geom1.GetPoints().size() == geom2.GetPoints().size());
    //Compare both vectors//
    QVERIFY(equal(geom1.GetPoints().begin(), geom1.GetPoints().end(), geom2.GetPoints().begin()));
    QFile::remove(QString::fromStdString("tmpgeom.dat"));
    QVERIFY(!QFile::exists(QString::fromStdString("tmpgeom.dat")));
}



QTEST_MAIN(Geometry_Tests)

#include "tst_geometry_tests.moc"
