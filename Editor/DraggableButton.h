#ifndef DRAGGABLEBUTTON_H
#define DRAGGABLEBUTTON_H

#include <QPushButton>
#include <QDrag>
#include <QMouseEvent>
#include <QMimeData>

class DraggableButton: public QPushButton
{
public:
    DraggableButton();

    void mousePressEvent(QMouseEvent *event);
};

#endif // DRAGGABLEBUTTON_H
