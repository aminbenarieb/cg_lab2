#include <QApplication>

#include "mainwindow.h"
//#include "KeyFilter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Главное окно
    MainWindow w;
    w.windowTitle() = kTextTitle;
    w.show();

    // Обработчик событий
//    KeyFilter* pFilter = new KeyFilter(&w);
//    w.installEventFilter(pFilter);

    return a.exec();
}
