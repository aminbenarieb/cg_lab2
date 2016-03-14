#ifndef QPAINTWIDGET_H
#define QPAINTWIDGET_H

#include <QWidget>
#include <QVarLengthArray>

class QPaintEvent;
struct QPaintState
{
    double scaleCoef;
    double rotateAngle;
    QPointF center;
    QPointF rotateCenter;
    QPointF scaleCenter;
};

class QPaintWidget : public QWidget
{
    Q_OBJECT
public:
    QPaintWidget(QWidget * parent = 0);
    QVector <QPaintState> paintStates;
    int paintStatesIndex;
    bool showShapeCenter;

protected:
    void paintEvent(QPaintEvent *);
    QVector <QPointF> circle();
    QVector <QPointF> arcRect();
    QVector <QPointF> twoRects();
    QPointF transform(QPointF );
};

#endif // QPAINTWIDGET_H
