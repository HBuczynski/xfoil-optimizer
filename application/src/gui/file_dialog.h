#ifndef FILE_DIALOG_H
#define FILE_DIALOG_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

class FileDialog
{
public:
    FileDialog();

    void initialize(QQmlApplicationEngine &engine);
    void showDialog();
private:

    QQmlComponent *dialogComponent_;

    QObject* fileWindow_;
};

#endif // FILE_DIALOG_H
