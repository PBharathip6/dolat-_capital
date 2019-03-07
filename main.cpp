#include "mainwindow.h"
#include <QApplication>
#include <QLineEdit>
#include <QRegExpValidator>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QLineEdit volume;
    volume.setValidator(new QRegExpValidator(QRegExp("[0-9]*"),&volume));
    w.show();

    return a.exec();
}
