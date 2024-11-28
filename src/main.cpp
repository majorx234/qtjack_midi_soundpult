 #include <QApplication>

 #include "mainwindow.h"

int main(int argc, char *argv[]) {
     QApplication app(argc, argv);
     MainWindow window;
     window.show();
     window.setupSounds(&window);
     return app.exec();
 }
