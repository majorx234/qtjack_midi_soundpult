#include <QtGui>
#include <QListWidget>
#include "soundpult_widget.h"

Soundpult_Widget::Soundpult_Widget(QWidget *parent)
    : QWidget(parent)
{
    setAcceptDrops(true);
    setMinimumSize(320, 320);
    setMaximumSize(320, 320);

    for (int i = 0;i<4;i++)
        for(int j =0;j<4;j++)
            matrix[i][j] = 0;
}

Soundpult_Widget::~Soundpult_Widget() {
}

void Soundpult_Widget::clear() {
    pieceLocations.clear();
    piecePixmaps.clear();
    pieceRects.clear();
    highlightedRect = QRect();
    inPlace = 0;
    update();
}

void Soundpult_Widget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece"))
        event->accept();
    else
        event->ignore();
}

void Soundpult_Widget::dragLeaveEvent(QDragLeaveEvent *event) {
    QRect updateRect = highlightedRect;
    highlightedRect = QRect();
    update(updateRect);
    event->accept();
}

void Soundpult_Widget::dragMoveEvent(QDragMoveEvent *event) {
    QRect updateRect = highlightedRect.united(targetSquare(event->pos()));
    if (event->mimeData()->hasFormat("image/x-puzzle-piece")
        && find_instrument(targetSquare(event->pos())) == -1) {

        highlightedRect = targetSquare(event->pos());
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        highlightedRect = QRect();
        event->ignore();
    }

    update(updateRect);
}

void Soundpult_Widget::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasFormat("image/x-puzzle-piece")
        && find_instrument(targetSquare(event->pos())) == -1) {
        QByteArray pieceData = event->mimeData()->data("image/x-puzzle-piece");
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        QRect square = targetSquare(event->pos());
        QPixmap pixmap;
        QPoint location;
        dataStream >> pixmap >> location;

        pieceLocations.append(location);
        piecePixmaps.append(pixmap);
        pieceRects.append(square);

        highlightedRect = QRect();
        update(square);

        event->setDropAction(Qt::MoveAction);
        event->accept();
        /*
        if (location == QPoint(square.x()/80, square.y()/80)) {
            inPlace++;
            if (inPlace == 25)
                emit puzzleCompleted();
        }*/
    } else{
        highlightedRect = QRect();
        event->ignore();
    }
}

int Soundpult_Widget::find_instrument(const QRect &pieceRect) const {
    for (int i = 0; i < pieceRects.size(); ++i) {
        if (pieceRect == pieceRects[i]) {
            return i;
        }
    }
    return -1;
}

void Soundpult_Widget::mousePressEvent(QMouseEvent *event) {
     QRect square = targetSquare(event->pos());
     int found = find_instrument(square);

     if (found == -1)
         return;

     QPoint location = pieceLocations[found];
     QPixmap pixmap = piecePixmaps[found];
     pieceLocations.removeAt(found);
     piecePixmaps.removeAt(found);
     pieceRects.removeAt(found);

     if (location == QPoint(square.x()/80, square.y()/80))
         inPlace--;

     update(square);

     QByteArray itemData;
     QDataStream dataStream(&itemData, QIODevice::WriteOnly);

     dataStream << pixmap << location;

     QMimeData *mimeData = new QMimeData;
     mimeData->setData("image/x-puzzle-piece", itemData);

     QDrag *drag = new QDrag(this);
     drag->setMimeData(mimeData);
     drag->setHotSpot(event->pos() - square.topLeft());
     drag->setPixmap(pixmap);

     if (!(drag->exec(Qt::MoveAction) == Qt::MoveAction)) {
         pieceLocations.insert(found, location);
         piecePixmaps.insert(found, pixmap);
         pieceRects.insert(found, square);
         update(targetSquare(event->pos()));

         if (location == QPoint(square.x()/80, square.y()/80))
             inPlace++;
     }
}

void Soundpult_Widget::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(this);
    painter.fillRect(event->rect(), Qt::white);

    if (highlightedRect.isValid()) {
        painter.setBrush(QColor("#ffcccc"));
        painter.setPen(Qt::NoPen);
        painter.drawRect(highlightedRect.adjusted(0, 0, -1, -1));
    }

    for (int i = 0; i < pieceRects.size(); ++i) {
        painter.drawPixmap(pieceRects[i], piecePixmaps[i]);
    }
    painter.end();
}

const QRect Soundpult_Widget::targetSquare(const QPoint &position) const {
    return QRect(position.x()/80 * 80, position.y()/80 * 80, 80, 80);
}
