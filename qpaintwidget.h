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

protected:
    void paintEvent(QPaintEvent *);
    QVector <QPointF> circle();
    QPointF transform(QPointF );
};

#endif // QPAINTWIDGET_H
