#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QApplication>
#include <QDebug>

#include "ui_mainwindow.h"
#include "qpaintwidget.h"
#include "congif.h"

class MainWindow : public  QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    //explicit MainWindow(QMainWindow *parent = 0);
    ~MainWindow();

    MainWindow(QMainWindow* pwgt = 0) : QMainWindow(pwgt) {

        setupUi(this);

        this->setWindowTitle(kTextTitle);

        //***** QPaintWidget Settings ******

        wgt->setMouseTracking(true);
        wgt->installEventFilter(this);
        wgt->setAutoFillBackground(true);
        QPalette Pal = palette();
        Pal.setColor(QPalette::Background, Qt::white);
        wgt->setPalette(Pal);

        //*******************************

        //***** Buttons Settings ******
        btnMove->setText(kBtnTextMove);
        btnRotate->setText(kBtnTextRotate);
        btnScale->setText(kBtnTextScale);
        //*******************************


        //***** Labels Settings ******
        labelCenter->setText(kLabelCenter);
        labelNextCenter->setText(kLabelNextCenter);
        labelRotate->setText(kLabelRotation);
        labelScale->setText(kLabelScale);
        //*******************************

        //***** LineEdit Settings ******
        lineEditCenterX->setPlaceholderText(kPlaceHolderCoordinateX);
        lineEditCenterY->setPlaceholderText(kPlaceHolderCoordinateY);

        lineEditNextCenterX->setPlaceholderText(kPlaceHolderCoordinateX);
        lineEditNextCenterY->setPlaceholderText(kPlaceHolderCoordinateY);

        lineEditRotationCenterX->setPlaceholderText(kPlaceHolderCoordinateX);
        lineEditRotationCenterY->setPlaceholderText(kPlaceHolderCoordinateY);
        lineEditRotationAngle->setPlaceholderText(kPlaceHolderRotationAngle);

        lineEditScaleCenterX->setPlaceholderText(kPlaceHolderCoordinateX);
        lineEditScaleCenterY->setPlaceholderText(kPlaceHolderCoordinateY);
        lineEditScaleCoef->setPlaceholderText(kPlaceHolderScaleCoef);
        //*******************************

        QObject::connect(btnMove, SIGNAL(clicked()), this, SLOT(actionMove()) );
        QObject::connect(btnRotate, SIGNAL(clicked()), this, SLOT(actionRotate()));
        QObject::connect(btnScale, SIGNAL(clicked()), this, SLOT(actionScale()));

        //*******************************
    }

public slots:
    void actionSetUp()
    {
        QPointF centerPoint = QPointF(wgt->width()/2, wgt->height()/2);
        QPaintState paintState = { 1, 0, centerPoint, centerPoint, centerPoint };
        wgt->paintStatesIndex = 0;
        wgt->paintStates.append( paintState );
        updateScreen();
    }

    void actionQuit(){
        QApplication::quit();
    }
    void actionUndo(){

        if (wgt->paintStatesIndex > 0)
        {
            wgt->paintStates.removeFirst();
            wgt->paintStatesIndex--;
            updateScreen();
        }
    }

    void actionMove(){

        QPaintState paintState = wgt->paintStates.last();

        bool moveXValid = false;
        bool moveYValid = false;

        double moveX = lineEditNextCenterX->text().toDouble(&moveXValid);
        double moveY = lineEditNextCenterY->text().toDouble(&moveYValid);

        if (!lineEditNextCenterX->text().isEmpty() && !lineEditNextCenterY->text().isEmpty())
        {
            if (moveXValid && moveYValid)
            {
                QPaintState nextPaintState = {
                    paintState.scaleCoef,
                    paintState.rotateAngle,
                    QPointF(moveX, moveY),
                    paintState.rotateCenter,
                    paintState.scaleCenter
                };
                wgt->paintStatesIndex++;
                wgt->paintStates.append( nextPaintState );

                updateScreen();
            }
            else
            {
                showMsg("Координаты нового центра должны быть дейстительными числами.");
            }
        }
        else
        {
            showMsg("Введите координаты нового центра.");
        }



    }
    void actionRotate(){

        QPaintState paintState = wgt->paintStates.last();

        bool rotateCoefValid = false;
        bool rotateXValid = false;
        bool rotateYValid = false;

        double rotationAngle = lineEditRotationAngle->text().toDouble(&rotateCoefValid);
        double rotateX = lineEditRotationCenterX->text().toDouble(&rotateXValid);
        double rotateY = lineEditRotationCenterY->text().toDouble(&rotateYValid);

        if (rotateCoefValid)
        {

            QPointF rotationCenter;

            if (!lineEditRotationCenterX->text().isEmpty() && !lineEditRotationCenterY->text().isEmpty())
            {
                if (rotateXValid && rotateYValid)
                {
                    rotationCenter = QPointF(rotateX, rotateY);
                }
                else
                {
                    showMsg("Координаты центра врашения должны быть действительными числами");
                }
            }
            else
            {
                rotationCenter = paintState.rotateCenter;
            }

            QPaintState nextPaintState = {
                paintState.scaleCoef,
                rotationAngle,
                paintState.center,
                rotationCenter,
                paintState.scaleCenter
            };
            wgt->paintStatesIndex++;
            wgt->paintStates.append( nextPaintState );

            updateScreen();
        }
        else
        {
            showMsg("Введите угол вращения (градусы).");
        }
    }
    void actionScale(){

        QPaintState paintState = wgt->paintStates.last();

        bool scaleCoefValid = false;
        bool scaleXValid = false;
        bool scaleYValid = false;

        double scaleCoef = lineEditScaleCoef->text().toDouble(&scaleCoefValid);
        double scaleX = lineEditScaleCenterX->text().toDouble(&scaleXValid);
        double scaleY = lineEditScaleCenterY->text().toDouble(&scaleYValid);

        if (scaleCoefValid)
        {

            QPointF scaleCenter;

            if (!lineEditScaleCenterX->text().isEmpty() && !lineEditScaleCenterY->text().isEmpty())
            {
                if (scaleXValid && scaleYValid)
                {
                    scaleCenter = QPointF(scaleX, scaleY);
                }
                else
                {
                    showMsg("Координаты центра масштабирования должны быть действительными числами");
                }
            }
            else
            {
                scaleCenter = paintState.scaleCenter;
            }

            QPaintState nextPaintState = {
                paintState.scaleCoef*scaleCoef,
                paintState.rotateAngle,
                paintState.center,
                paintState.rotateCenter,
                scaleCenter
            };
            wgt->paintStatesIndex++;
            wgt->paintStates.append( nextPaintState );

            updateScreen();
        }
        else
        {
             showMsg("Введите коэффицент масштабирования. (положительное действительное число)");
        }

    }

private:
    bool eventFilter(QObject *, QEvent *);
    void updateScreen()
    {
        QPointF centerPoint = wgt->paintStates.last().center;
        lineEditCenterX->setText( QString::number(centerPoint.x()) );
        lineEditCenterY->setText( QString::number(centerPoint.y()) );

        wgt->update();
    }
    void showMsg(QString );

protected:
    void showEvent(QShowEvent *e){
        QWidget::showEvent(e);
        QCoreApplication::processEvents();

        actionSetUp();
    }


};

#endif // MAINWINDOW_H

