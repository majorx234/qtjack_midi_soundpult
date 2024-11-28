#ifndef INSTRUMENTS_LIST_H
#define INSTRUMENTS_LIST_H

#include <QListWidget>

class Instruments_List : public QListWidget {
    Q_OBJECT

  public:
    Instruments_List(QWidget *parent = 0);
    ~Instruments_List();
    void addPiece(QPixmap pixmap, QPoint location);
    //piecesList->takeItem(i);
    //piecesList->insertItem(0, item);
    //piecesList->count()
 protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void startDrag(Qt::DropActions supportedActions);
};


#endif //INSTRUMENTS_LIST_H
