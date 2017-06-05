#include "gui/view.h"

#include <QDebug>
//Test area for me
#include "optimizer/airfoil_optimizer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Model *model = new Model;
    View *view = new View(model);

    if(app.exec() == 0)
    {
        delete model;
        delete view;
    }

    return 0;
}
