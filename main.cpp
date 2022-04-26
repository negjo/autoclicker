#include "mainwindow.h"
#include "mythread.h"
#include <QApplication>
#include <QWidget>
#include "windows.h"
#include <QWindow>
#include <QSettings>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QCoreApplication::setApplicationName( QString("My Application") );
    //setWindowTitle( QCoreApplication::applicationName() );
    w.show();
    return a.exec();
}
