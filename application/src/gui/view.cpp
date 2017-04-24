#include "view.h"

View::View()
{
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
}

View::~View()
{

}
