#include "mygraphicsview.h"
#include <QWheelEvent>
#include <QScrollBar>
/***
 * Code snippet from stackoverflow
 * Adds functionality to zoom in the view
 * and move around using right-click
 * ***/

MyGraphicsView::MyGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{

}

void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        // Zoom with Ctrl + scroll
        const ViewportAnchor anchor = transformationAnchor();
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        int angle = event->angleDelta().y();
        qreal factor;
        if (angle > 0) {
            factor = 1.1;
        } else {
            factor = 0.9;
        }
        scale(factor, factor);
        setTransformationAnchor(anchor);
    } else {
        // If Ctrl key is not pressed, handle the event normally
        QGraphicsView::wheelEvent(event);
    }
}
void MyGraphicsView::mousePressEvent(QMouseEvent* event){
    if(event->button() == Qt::RightButton){
        pan = true;
        pan_start_x = event->x();
        pan_start_y = event->y();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
        return;
    }
    event->ignore();
}
void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton){
        pan = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
        return;
    }
    event->ignore();

}
void MyGraphicsView::mouseMoveEvent(QMouseEvent *event){
    if(pan){
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() -(event->x() - pan_start_x));
        verticalScrollBar()->setValue(verticalScrollBar()->value() -(event->y() - pan_start_y));
        pan_start_x = event->x();
        pan_start_y = event->y();
        event->accept();
        return;
    }
    event->ignore();
}
