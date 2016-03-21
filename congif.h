#ifndef CONGIF_H
#define CONGIF_H

#include "math.h"

#define kShapeWidth (320)
#define kShapeHeight (200)
#define kShapeCicrleRadius (kShapeWidth/8)

#define kBtnTextApply "Применить"
#define kBtnTextMove "Переместить"
#define kBtnTextRotate "Повернуть"
#define kBtnTextScale "Масштабировать"

#define kTextTitle "Лабараторная работа 2"

#define kLabelCenter "Координаты центра"
#define kLabelNextCenter "Смещение"
#define kLabelRotation "Поворот"
#define kLabelScale "Масштабирование"

#define kPlaceHolderCoordinateX "Координата X"
#define kPlaceHolderCoordinateY "Координата Y"
#define kPlaceHolderDeltaX "По оси X"
#define kPlaceHolderDeltaY "По оси Y"
#define kPlaceHolderRotationAngle "Угол поворота"
#define kPlaceHolderScaleCoefX "Коэффицент масштабирования по X"
#define kPlaceHolderScaleCoefY "Коэффицент масштабирования по Y"


#define kDrawPointRadius 3
#define kDrawPenWidth 1
#define kAxisStep 100

#define kmin(a, b) ( ( a < b) ? a : b )
#define kmax(a, b) ( ( a > b) ? a : b )
#define kcalcSide(a, b) sqrt( pow( (a.x()-b.x()), 2) + pow( (a.y() - b.y()), 2) )
#define kRadianToDegree(radian) ( radian*180/M_PI )
#define kDegreeToRadian(degree) ( degree*M_PI/180 )

#endif // CONGIF_H
