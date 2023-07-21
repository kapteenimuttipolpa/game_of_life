#include "customgraphicsview.h"
#include "patterns.h"
CustomGraphicsView::CustomGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    // Additional initialization code
}

void CustomGraphicsView::mousePressEvent(QMouseEvent *event)
{
    // Handle the mouse press event
    QPoint viewPos = event->pos();
    QPointF scenePos = mapToScene(viewPos);

    // Convert the scene coordinates to integer indexes
    int row = static_cast<int>(scenePos.y());
    int col = static_cast<int>(scenePos.x());

    // Store the coordinates in a data structure (e.g., vector or QList)
    // ...
    custom_patterns.push_back({row, col});

    // Call the base class implementation to handle other aspects of the event
    QGraphicsView::mousePressEvent(event);
}
