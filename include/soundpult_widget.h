#ifndef SOUNDPULT_WIDGET_H
#define SOUNDPULT_WIDGET_H

#include <QList>
#include <QPoint>
#include <QPixmap>
#include <QWidget>
#include <QDragEnterEvent> 
#include <QDropEvent>
#include <QMouseEvent>

 class Soundpult_Widget : public QWidget
 {
 	Q_OBJECT

 	public:
     Soundpult_Widget(QWidget *parent = 0);
     ~Soundpult_Widget();
     void clear();

 signals:

 protected:
     void dragEnterEvent(QDragEnterEvent *event);
     void dragLeaveEvent(QDragLeaveEvent *event);
     void dragMoveEvent(QDragMoveEvent *event);
     void dropEvent(QDropEvent *event);
     int  find_instrument(const QRect &pieceRect) const;
     void mousePressEvent(QMouseEvent *event);
     void paintEvent(QPaintEvent *event);

 private:
     int findPiece(const QRect &pieceRect) const;
     const QRect targetSquare(const QPoint &position) const;

     QList<QPixmap> piecePixmaps;
     QList<QRect> pieceRects;
     QList<QPoint> pieceLocations;
     QRect highlightedRect;
     int inPlace;
     int matrix[4][4];
 };

 
 #endif