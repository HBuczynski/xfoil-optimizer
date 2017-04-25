#include "gui/view.h"

//Test area for me
#include "optimizer/airfoil_optimizer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Model *model = new Model;
    View *view = new View(model);

    return app.exec();
}
