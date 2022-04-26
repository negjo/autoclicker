#ifndef MYTHREAD_H
#define MYTHREAD_H

//#include "mainwindow.h"
#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QRandomGenerator>
#include <QMouseEvent>
#include <Windows.h>
#include <QMainWindow>

extern qint32 minDelay;
extern qint32 maxDelay;
extern qint32 button;
extern qint32 mode;
extern UINT hotkey;
class myThread: public QThread
{
    QMutex sync;
    QWaitCondition pauseCond;

private:

public:
    bool pause = true;
    myThread() : pause(false){}
    void resumeAC();
    void pauseAC();
protected:
    void run();
};

#endif // MYTHREAD_H
