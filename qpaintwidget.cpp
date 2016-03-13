#include "qpaintwidget.h"
#include "congif.h"

#include <QDebug>
#include <QPainter>

QPaintWidget::QPaintWidget(QWidget * parent) : QWidget(parent)
{
  // Initialization

}

void QPaintWidget::paintEvent(QPaintEvent *) {

    QPainter ppainter(this);
    ppainter.save();
    ppainter.setPen(QPen(Qt::black, kDrawPenWidth));
    ppainter.setBrush(QBrush(Qt::transparent));

    ppainter.drawPoints(circle());

    ppainter.restore();
}


// Generation Points for Shapes Functions

QVector <QPointF> QPaintWidget::circle()
{
    QVector <QPointF> circleArray;
    double x0, y0, x, y;


    x0 = paintStates.last().center.x() - kShapeWidth/2;
    y0 = paintStates.last().center.y() - kShapeHeight/2;

    for (int i = 0; i < 2*M_PI*kShapeCicrleRadius; i++)
    {
        x = x0 + kShapeCicrleRadius * cos(i) + kShapeCicrleRadius*2 ;
        y = y0 + kShapeCicrleRadius * sin(i) + kShapeCicrleRadius*2;
        circleArray.append( transform( QPointF(x,y) ) );

    }

    return circleArray;

}

QPointF QPaintWidget::transform(QPointF point)
{
    QPaintState *paintState = &paintStates.last();
    QPointF *scaleCenter = &(paintState->scaleCenter);
    double scale =  paintState->scaleCoef;
    QPointF *rotateCenter =  &(paintState->rotateCenter);
    double angle = paintState->rotateAngle;

    return QPointF(scale * (rotateCenter->x()+ (point.x() - rotateCenter->x()) * cos(angle) - (point.y()- rotateCenter->y()) * sin(angle)) + scaleCenter->x() * (1 - scale),
                   scale * (rotateCenter->y()+ (point.y() - rotateCenter->y()) * cos(angle) - (point.x() - rotateCenter->x()) * sin(angle)) + scaleCenter->y() * (1 - scale));
}
