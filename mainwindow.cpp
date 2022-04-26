#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"
#include <QDebug>
#include <QWidget>
#include <QKeyEvent>
#include <QSettings>

qint32 minDelay = 70;
qint32 maxDelay = 120;
bool catchHotkey = false;
qint32 button = 0;
qint32 mode = 0;
QSettings settings("negjo", "autoclicker by negjo");
UINT hotkey = 0x47;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->minDelayInput->setRange(0,1000000000);
    ui->maxDelayInput->setRange(0,1000000000);

    ui->minDelayInput->setValue(settings.value("minDelay", 70).toUInt());
    ui->maxDelayInput->setValue(settings.value("maxDelay", 120).toUInt());
    ui->minDelayInput->setSingleStep(5);
    ui->maxDelayInput->setSingleStep(5);
    ui->currentMinDelay->setText(settings.value("minDelay", 70).toString());
    ui->currentMaxDelay->setText(settings.value("maxDelay", 120).toString());
    ui->currentState->setText("OFF");
    button = settings.value("button", 0).toInt();
    if(button == 0){
        ui->buttonLeft->toggle();
    }
    else if(button == 1){
        ui->buttonMiddle->toggle();
    }
    else{
        ui->buttonRight->toggle();
    }
    mode = settings.value("mode", 0).toInt();
    if(mode == 0){
        ui->toggle->toggle();
    }
    else{
        ui->hold->toggle();
    }
    hotkey = settings.value("hotkey", 71).toUInt();

    if (!RegisterHotKey(HWND(winId()), 0, 0x4000, hotkey))
    {
        QMessageBox::warning(this, "Warning", "Něco se dojebalo");
    }
    ui->currentKey->setText(QKeySequence(hotkey).toString());
    thread123.start();
    thread123.pauseAC();
}

MainWindow::~MainWindow()
{
    thread123.terminate();
    delete ui;
}


void MainWindow::on_saveSettings_clicked()
{
    minDelay = ui->minDelayInput->value();
    maxDelay = ui->maxDelayInput->value();
    if(maxDelay < minDelay){
        QMessageBox::warning(this, tr("Ani píču"), tr("Ti mrdá? Maximální delay musí být větší než minimální delay."));
        return;
    }
    settings.setValue("minDelay", minDelay);
    settings.setValue("maxDelay", maxDelay);
    ui->currentMinDelay->setText(QString::number(minDelay));
    ui->currentMaxDelay->setText(QString::number(maxDelay));
}

void MainWindow::on_runStop_clicked()
{
    if(thread123.pause){
        thread123.resumeAC();
        ui->currentState->setText("ON");
    }
    else{
        thread123.pauseAC();
        ui->currentState->setText("OFF");

    }
}

bool MainWindow::nativeEvent(const QByteArray& eventType, void* message, long long* result)
{
    Q_UNUSED(eventType);
    Q_UNUSED(result);
    MSG* msg = static_cast<MSG*>(message);
    if (msg->message == WM_HOTKEY)
    {
        if(mode == 0){
            if(thread123.pause){
                thread123.resumeAC();
                ui->currentState->setText("ON");
            }
            else{
                thread123.pauseAC();
                ui->currentState->setText("OFF");

            }
        }
        else{
            thread123.resumeAC();
            //ui->currentState->setText("ON");
        }
        return true;
    }
    return false;
}

void MainWindow::on_setHotkey_clicked()
{
    ui->setHotkey->setText("Press any key");
    catchHotkey = true;
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(catchHotkey){
       hotkey = event->key();
       qDebug() << hotkey;
       UnregisterHotKey(HWND(winId()), 0);
       RegisterHotKey(HWND(winId()), 0, 0x4000, hotkey);
       ui->currentKey->setText(QKeySequence(hotkey).toString());
       ui->setHotkey->setText("Set hotkey");
       settings.setValue("hotkey", hotkey);
       catchHotkey = false;
    }
}

void MainWindow::on_buttonLeft_clicked()
{
    button = 0;
    settings.setValue("button", 0);
}

void MainWindow::on_buttonMiddle_clicked()
{
    button = 1;
    settings.setValue("button", 1);
}

void MainWindow::on_buttonRight_clicked()
{
    button = 2;
    settings.setValue("button", 2);
}

void MainWindow::on_toggle_clicked()
{
    mode = 0;
    settings.setValue("mode", 0);
}


void MainWindow::on_hold_clicked()
{
    mode = 1;
    settings.setValue("mode", 1);
}

