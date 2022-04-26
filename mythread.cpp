#include "mythread.h"
#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QRandomGenerator>
#include <QMouseEvent>
#include <Windows.h>
#include <QMainWindow>
#include <QDebug>

bool pause = true;

void myThread::resumeAC(){
    sync.lock();
    qDebug() << "yey";
    pause = false;
    sync.unlock();
    pauseCond.wakeAll();
}

void myThread::pauseAC(){
    sync.lock();
    qDebug() << "nah";
    pause = true;
    sync.unlock();
}


void myThread::run(){
    while(true){

        if(mode == 1){
            if(!GetAsyncKeyState(hotkey)){
                pauseAC();
            }
        }
        sync.lock();
        if(pause){
            pauseCond.wait(&sync);
        }

        sync.unlock();
        quint32 waitDealay = QRandomGenerator::global()->bounded(minDelay, maxDelay);
        msleep(waitDealay);
        if(button == 0){
            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        }
        else if(button == 1){
            mouse_event(MOUSEEVENTF_MIDDLEDOWN | MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
        }
        else{
            mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
        }
    }
}
