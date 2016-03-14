#include "qpaintwidget.h"
#include "congif.h"

#include <QDebug>
#include <QPainter>

QPaintWidget::QPaintWidget(QWidget * parent) : QWidget(parent)
{
  // Initialization
    showShapeCenter = false;

}

void QPaintWidget::paintEvent(QPaintEvent *) {

    QPainter ppainter(this);
    ppainter.setPen(QPen(Qt::blue, kDrawPenWidth));
    ppainter.setBrush(QBrush(Qt::transparent));

    if (showShapeCenter)
    {
        ppainter.save();
        ppainter.setPen(QPen(Qt::blue, kDrawPenWidth));
        ppainter.drawEllipse(QPointF(paintStates.last().center.x(), paintStates.last().center.y()), 3, 3);

        ppainter.restore();
    }

    if (showShapeCenter && paintStates.last().center != paintStates.last().rotateCenter)
    {
        ppainter.save();
        ppainter.setPen(QPen(Qt::darkCyan, kDrawPenWidth));
        ppainter.drawEllipse(QPointF(paintStates.last().rotateCenter.x(), paintStates.last().rotateCenter.y()), 3, 3);

        ppainter.restore();
    }
    if (showShapeCenter && paintStates.last().center != paintStates.last().scaleCenter)
    {
        ppainter.save();
        ppainter.setPen(QPen(Qt::darkYellow, kDrawPenWidth));
        ppainter.drawEllipse(QPointF(paintStates.last().scaleCenter.x(), paintStates.last().scaleCenter.y()), 3, 3);

        ppainter.restore();
    }

    ppainter.setPen(QPen(Qt::black, kDrawPenWidth));

    ppainter.drawPoints( circle() );
    ppainter.drawPoints( arcRect() );
    ppainter.drawPoints( twoRects() );

}


// Generation Points for Shapes

QVector <QPointF> QPaintWidget::circle()
{

    QVector <QPointF > circleArray;
    double x0, y0, x, y;

    x0 = paintStates.last().center.x();
    y0 = paintStates.last().center.y() + kShapeHeight/10;

    for (int i = 0; i <= 360; i++)
    {
        x = x0 + kShapeCicrleRadius * cos(kDegreeToRadian(i));
        y = y0 + kShapeCicrleRadius * sin(kDegreeToRadian(i));
        circleArray.append( transform( QPointF(x,y) ) );
    }

    return circleArray;

}
QVector <QPointF> QPaintWidget::twoRects()
{

    QVector <QPointF > twoRectsArray;
    double x0, y0, x, y;

    // ** Правый прямоугольник **

    // Верхяя сторона
    x0 = paintStates.last().center.x();
    y0 = paintStates.last().center.y() - 3*kShapeHeight/10;

    for (int i = 0; i <= 2*kShapeWidth/8; i++)
    {
        x = x0 + i;
        y = y0 - i*0.5;
        twoRectsArray.append( transform( QPointF(x,y) ) );
    }

    // Левая
    for (int i = 0; i <= 4*kShapeHeight/10; i++)
    {
        x = x0 + i;
        y = y0 + i * 1.5;
        twoRectsArray.append( transform( QPointF(x,y) ) );
    }

    // Нижняя
    x0 = paintStates.last().center.x() + 2*kShapeWidth/8;
    y0 = paintStates.last().center.y() + 3*kShapeHeight/10;

    for (int i = 0; i <= 2*kShapeWidth/8; i++)
    {
        x = x0 + i;
        y = y0 - i*0.5;
        twoRectsArray.append( transform( QPointF(x,y) ) );
    }

    // Правая
    x0 = x;
    y0 = y;
    for (int i = 0; i <= 4*kShapeHeight/10; i++)
    {
        x = x0 - i;
        y = y0 - i * 1.5;
        twoRectsArray.append( transform( QPointF(x,y) ) );
    }


    // ** Левый прямоугольник **

    // Верхяя сторона
    x0 = paintStates.last().center.x();
    y0 = paintStates.last().center.y() - 3*kShapeHeight/10;

    for (int i = 0; i <= 2*kShapeWidth/8; i++)
    {
        x = x0 - i;
        y = y0 - i*0.5;
        twoRectsArray.append( transform( QPointF(x,y) ) );
    }

    // Левая
    for (int i = 0; i <= 4*kShapeHeight/10; i++)
    {
        x = x0 - i;
        y = y0 + i * 1.5;
        twoRectsArray.append( transform( QPointF(x,y) ) );
    }

    // Нижняя
    x0 = paintStates.last().center.x() - 2*kShapeWidth/8;
    y0 = paintStates.last().center.y() + 3*kShapeHeight/10;

    for (int i = 0; i <= 2*kShapeWidth/8; i++)
    {
        x = x0 - i;
        y = y0 - i*0.5;
        twoRectsArray.append( transform( QPointF(x,y) ) );
    }

    // Правая
    x0 = x;
    y0 = y;
    for (int i = 0; i <= 4*kShapeHeight/10; i++)
    {
        x = x0 + i;
        y = y0 - i * 1.5;
        twoRectsArray.append( transform( QPointF(x,y) ) );
    }



    return twoRectsArray;

}
QVector <QPointF> QPaintWidget::arcRect()
{
    QVector <QPointF> arcRect;
    double x0, y0, x, y;



    x0 = paintStates.last().center.x();
    y0 = paintStates.last().center.y() + 3*kShapeHeight/10;;

    for (int i = 0; i <= 180; i++)
    {
        x = x0 + kShapeWidth/4 * cos(kDegreeToRadian(i));
        y = y0 + kShapeWidth/10 * sin(kDegreeToRadian(i));
        arcRect.append( transform( QPointF(x,y) ) );
    }


    x0 = paintStates.last().center.x() -  kShapeWidth/4;
    for (int i = 0; i <= kShapeWidth/2; i++)
    {
        x = x0 + i;
        y = y0;
        arcRect.append( transform( QPointF(x,y) ) );
    }

    return arcRect;

}


// General Point Transformation algorithm

QPointF QPaintWidget::transform(QPointF point)
{
    QPaintState *paintState = &paintStates.last();
    QPointF *scaleCenter = &(paintState->scaleCenter);
    double scale =  paintState->scaleCoef;
    QPointF *rotateCenter =  &(paintState->rotateCenter);
    double angle = kDegreeToRadian(paintState->rotateAngle);

    return QPointF(scale * (rotateCenter->x()+ (point.x() - rotateCenter->x()) * cos(angle) - (point.y()- rotateCenter->y()) * sin(angle)) + scaleCenter->x() * (1 - scale),
                   scale * (rotateCenter->y()+ (point.y() - rotateCenter->y()) * cos(angle) + (point.x() - rotateCenter->x()) * sin(angle)) + scaleCenter->y() * (1 - scale));
}
