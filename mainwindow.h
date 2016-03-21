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
        btnNewCenter->setText(kBtnTextApply);
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

        lineEditDeltaX->setPlaceholderText(kPlaceHolderDeltaX);
        lineEditDeltaY->setPlaceholderText(kPlaceHolderDeltaY);

        lineEditRotationCenterX->setPlaceholderText(kPlaceHolderCoordinateX);
        lineEditRotationCenterY->setPlaceholderText(kPlaceHolderCoordinateY);
        lineEditRotationAngle->setPlaceholderText(kPlaceHolderRotationAngle);

        lineEditScaleCenterX->setPlaceholderText(kPlaceHolderCoordinateX);
        lineEditScaleCenterY->setPlaceholderText(kPlaceHolderCoordinateY);
        lineEditScaleCoefX->setPlaceholderText(kPlaceHolderScaleCoefX);
        lineEditScaleCoefY->setPlaceholderText(kPlaceHolderScaleCoefY);



        //*******************************

        QObject::connect(btnNewCenter, SIGNAL(clicked()), this, SLOT(actionNewCenter()) );
        QObject::connect(btnMove, SIGNAL(clicked()), this, SLOT(actionMove()) );
        QObject::connect(btnRotate, SIGNAL(clicked()), this, SLOT(actionRotate()));
        QObject::connect(btnScale, SIGNAL(clicked()), this, SLOT(actionScale()));

        //*******************************

        QMenuBar mnuBar;

        QMenu* pmnu = new QMenu("Меню");

        pmnu->addAction("Отменить", this,
                        SLOT(actionUndo()),
                        Qt::CTRL + Qt::Key_U );

        QAction* pCheckableAction = pmnu->addAction("Показать границы фигуры", this,
                                                    SLOT(actionToggleShowShapeCenter()),
                                                    Qt::CTRL + Qt::Key_D );
        pCheckableAction->setCheckable(true);
        pCheckableAction->setChecked(wgt->showShapeCenter);
        pmnu->addSeparator();

        pmnu->addAction("&Выйти", this, SLOT(actionQuit()));


        mnuBar.addMenu(pmnu);
        mnuBar.show();

        this->setMenuBar(&mnuBar);
    }

public slots:
    void actionSetUp()
    {
        QPointF centerPoint = QPointF(wgt->width()/2, wgt->height()/2);
        QPaintState paintState = { 1, 1, 0, 0, 0, centerPoint, centerPoint, centerPoint };
        wgt->paintStatesIndex = 0;
        wgt->paintStates.append( paintState );
        updateScreen();
    }
    void actionToggleShowShapeCenter()
    {
        wgt->showShapeCenter = !wgt->showShapeCenter;
        updateScreen();
    }

    void actionQuit(){
        QApplication::quit();
    }
    void actionUndo(){

        if (wgt->paintStatesIndex > 0)
        {
            wgt->paintStates.removeLast();
            wgt->paintStatesIndex--;
            updateScreen();
        }
    }

    void actionNewCenter(){

        QPaintState paintState = wgt->paintStates.last();

        bool xValid = false;
        bool yValid = false;

        double x = lineEditCenterX->text().toDouble(&xValid);
        double y = lineEditCenterY->text().toDouble(&yValid);

        if (!lineEditCenterX->text().isEmpty() && !lineEditCenterY->text().isEmpty())
        {
            if (xValid && yValid)
            {

                QPaintState nextPaintState = {
                    paintState.scaleCoefX,
                    paintState.scaleCoefY,
                    paintState.rotateAngle,
                    paintState.deltaX,
                    paintState.deltaY,
                    QPointF(x,y),
                    QPointF(x,y),
                    QPointF(x,y)
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
            showMsg("Введите данные для нового центра.");
        }



    }

    void actionMove(){

        QPaintState paintState = wgt->paintStates.last();

        bool deltaXValid = false;
        bool deltaYValid = false;

        double deltaX = lineEditDeltaX->text().toDouble(&deltaXValid);
        double deltaY = lineEditDeltaY->text().toDouble(&deltaYValid);

        if (!lineEditDeltaX->text().isEmpty() && !lineEditDeltaY->text().isEmpty())
        {
            if (deltaXValid && deltaYValid)
            {

                QPaintState nextPaintState = {
                    paintState.scaleCoefX,
                    paintState.scaleCoefY,
                    paintState.rotateAngle,
                    deltaX,
                    deltaY,
                    paintState.center,
                    paintState.rotateCenter,
                    paintState.scaleCenter
                };
                wgt->paintStatesIndex++;
                wgt->paintStates.append( nextPaintState );

                updateScreen();
            }
            else
            {
                showMsg("Неверный ввод для задания переноса.");
            }
        }
        else
        {
            showMsg("Введите данные для переноса.");
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
                paintState.scaleCoefX,
                paintState.scaleCoefY,
                paintState.rotateAngle + rotationAngle,
                paintState.deltaX,
                paintState.deltaY,
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

        bool scaleCoefValidX = false;
        bool scaleCoefValidY = false;
        bool scaleXValid = false;
        bool scaleYValid = false;

        double scaleCoefX = lineEditScaleCoefX->text().toDouble(&scaleCoefValidX);
        double scaleCoefY = lineEditScaleCoefY->text().toDouble(&scaleCoefValidY);
        double scaleX = lineEditScaleCenterX->text().toDouble(&scaleXValid);
        double scaleY = lineEditScaleCenterY->text().toDouble(&scaleYValid);

        if (scaleCoefValidX && scaleCoefValidY)
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
                paintState.scaleCoefX*scaleCoefX,
                paintState.scaleCoefY*scaleCoefY,
                paintState.rotateAngle,
                paintState.deltaX,
                paintState.deltaY,
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
             showMsg("Введите верные коэффиценты масштабирования. (действительное число)");
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

