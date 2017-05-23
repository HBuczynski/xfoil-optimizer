#include <QString>
#include <QtTest>

class Geometry_Tests : public QObject
{
    Q_OBJECT

public:
    Geometry_Tests();

private Q_SLOTS:
    void SavingAGeometryObjectGeneratesAFile();
};

Geometry_Tests::Geometry_Tests()
{
}

void Geometry_Tests::SavingAGeometryObjectGeneratesAFile()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(Geometry_Tests)

#include "tst_geometry_tests.moc"
