#include "functionwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QVector<qreal> x;
    QVector<qreal> y1;
    QVector<qreal> y2;

    for(int i = -10; i < 10; i++) {
        x.append(i);
        y1.append(i+1);
        y2.append(i*i);
    }

    // Запуск
    FunctionWindow w(x, y1, "время", "что-то");
    w.show();
    return a.exec();
}
