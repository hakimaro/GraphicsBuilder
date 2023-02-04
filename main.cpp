#include "functionwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QVector<QVector<qreal>> x;
    QVector<QVector<qreal>> y;

    QVector<qreal> x1;
    QVector<qreal> y1;
    QVector<QString> legend;
    legend.append("hello");
    legend.append("world");
    for(int i = -10; i <= 10; i++) {
        x1.append(i);
        y1.append(i*i);
    }

    QVector<qreal> x2;
    QVector<qreal> y2;

    for(int i = -15; i <= 15; i++) {
        x2.append(i);
        y2.append(i+3*i);
    }

    x.append(x1);
    x.append(x2);
    y.append(y1);
    y.append(y2);

    // Запуск
    FunctionWindow w(x, y, "time", "time, t", legend);
    w.show();
    return a.exec();
}
