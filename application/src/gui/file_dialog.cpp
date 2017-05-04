#include "file_dialog.h"

FileDialog::FileDialog()
{

}

void FileDialog::initialize(QQmlApplicationEngine &engine)
{
    dialogComponent_ = new QQmlComponent(&engine,QUrl(QStringLiteral("qrc:/FileDialog.qml")));
    fileWindow_ = dialogComponent_->create();
}

void FileDialog::showDialog()
{
    fileWindow_->setProperty("visible", "true");
}
