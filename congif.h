#ifndef CONGIF_H
#define CONGIF_H

#include "math.h"

#define kShapeWidth 200
#define kShapeHeight 200
#define kShapeCicrleRadius 50

#define kBtnTextMove "Переместить"
#define kBtnTextRotate "Повернуть"
#define kBtnTextScale "Масштабировать"

#define kTextTitle "Лабараторная работа 2"

#define kLabelCenter "Координаты центра"
#define kLabelNextCenter "Координаты нового центра"
#define kLabelRotation "Поворот"
#define kLabelScale "Масштабирование"

#define kPlaceHolderCoordinateX "Координата X"
#define kPlaceHolderCoordinateY "Координата Y"
#define kPlaceHolderRotationAngle "Угол поворота"
#define kPlaceHolderScaleCoef "Коэффицент масштабирования"


#define kDrawPointRadius 3
#define kDrawPenWidth 1
#define kAxisStep 100

#define kmin(a, b) ( ( a < b) ? a : b )
#define kmax(a, b) ( ( a > b) ? a : b )
#define kcalcSide(a, b) sqrt( pow( (a.x()-b.x()), 2) + pow( (a.y() - b.y()), 2) )
#define kRadianToDegree(radian) ( radian*180/M_PI )
#define kDegreeToRadian(degree) ( degree*M_PI/180 )

#endif // CONGIF_H
