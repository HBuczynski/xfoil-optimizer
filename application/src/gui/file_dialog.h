#ifndef FILE_DIALOG_H
#define FILE_DIALOG_H

#include <QObject>
#include <QFileDialog>
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
    QQmlApplicationEngine engine_;
};

#endif // FILE_DIALOG_H
