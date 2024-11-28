#include <QtGui>
#include <stdlib.h>
#include <QListWidgetItem>
#include <QHBoxLayout>

#include "mainwindow.h"
#include "instruments_list.h"
#include "soundpult_widget.h"


MainWindow::MainWindow(QWidget *parent)
 : QMainWindow(parent)
{
    setupMenus();
    setupWidgets();

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setWindowTitle(tr("Soundpult"));
    setupSoundpult();
}

MainWindow::~MainWindow() {
}

void MainWindow::setupSoundpult() {
    instruments_list->clear();

//load list of instrumenst here
     /*
     //map_view = QPixmap::fromImage(map_image);

     start_point_image.load(QString("icons/green_point.png"));
     for (int y = 0; y < 5; ++y) {
        QPixmap pieceImage = puzzleImage.copy(x*80, y*80, 80, 80);
        piecesList->addPiece(pieceImage, QPoint(x, y));
     }*/
    QImage guitar_image;
    guitar_image.load(QString("../icons/guitar.png"));
    QImage  bass_drum_image;
    bass_drum_image.load(QString("../icons/bass_drum.png"));

    QPixmap guitar_map = QPixmap::fromImage(guitar_image);
    QPixmap bass_drum_map = QPixmap::fromImage(bass_drum_image);

    instruments_list->addPiece(bass_drum_map,QPoint(1,1));
    instruments_list->addPiece(guitar_map,QPoint(2,1));

    soundpult->clear();
}


void MainWindow::setupMenus() {
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *openAction = fileMenu->addAction(tr("&Open..."));
    openAction->setShortcuts(QKeySequence::Open);

    QAction *exitAction = fileMenu->addAction(tr("E&xit"));
    exitAction->setShortcuts(QKeySequence::Quit);

    QMenu *gameMenu = menuBar()->addMenu(tr("&Game"));

    QAction *restartAction = gameMenu->addAction(tr("&Restart"));

    //connect(openAction, SIGNAL(triggered()), this, SLOT(openImage()));
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(restartAction, SIGNAL(triggered()), this, SLOT(setupSoundpult()));
}

void MainWindow::setupWidgets() {
    QFrame *frame = new QFrame;
    QHBoxLayout *frameLayout = new QHBoxLayout(frame);

    instruments_list = new Instruments_List;
    soundpult = new Soundpult_Widget;

    frameLayout->addWidget(instruments_list);
    frameLayout->addWidget(soundpult);
    setCentralWidget(frame);
}

void MainWindow::setupSounds(QWidget *parent) {
    dispatcher_test    =   new Sound_Dispatcher(parent);
    //dispatcher_test->add_instrument(std::string("guitar"),QString("../sounds/guitar.wav"));
    dispatcher_test->add_instrument(std::string("bass_drum"),QString("../sounds/bass_drum.wav"));
}
