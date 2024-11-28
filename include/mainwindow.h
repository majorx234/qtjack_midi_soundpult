#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPixmap>
#include <QMainWindow>
#include "ui_mainwindow.h"
#include "soundpult_widget.h"
#include "instruments_list.h"
#include <sound_dispatcher.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

 public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setupSounds(QWidget *parent = 0);
 public slots:
    void setupSoundpult();

 private slots:

 private:
    void setupMenus();
    void setupWidgets();

    QPixmap SoundpultImage;
    Instruments_List *instruments_list;
    Soundpult_Widget *soundpult;
    Sound_Dispatcher *dispatcher_test;
};

 #endif
