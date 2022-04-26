#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QThread>
#include <QKeyEvent>
#include <QShortcut>
#include "mythread.h"
#include "windows.h"
#include <QSettings>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    myThread thread123;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    bool nativeEvent(const QByteArray &eventType, void *message, long long *result);
    void on_saveSettings_clicked();
    void on_runStop_clicked();

    void on_setHotkey_clicked();
    void keyPressEvent(QKeyEvent *event);

    void on_buttonLeft_clicked();

    void on_buttonMiddle_clicked();

    void on_buttonRight_clicked();

    void on_toggle_clicked();

    void on_hold_clicked();

private:

    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
