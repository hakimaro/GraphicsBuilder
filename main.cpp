#include "functionwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QVector<qreal> x1;
    QVector<qreal> y1;
    QVector<qreal> x2;
    QVector<qreal> y2;
    QVector<qreal> x3;
    QVector<qreal> y3;

    QVector<QString> legend;
    legend.append("sin(x)");
    legend.append("cos(x)");
    legend.append("sin(x)+cos(x)");

    for(qreal i = -5; i <= 5; i+=0.1) {
        x1.append(i);
        y1.append(sin(i));
        x2.append(i);
        y2.append(cos(i));
        x3.append(i);
        y3.append(sin(i)+cos(i));
    }

    QVector<QVector<qreal>> x;
    QVector<QVector<qreal>> y;

    x.append(x1);
    x.append(x2);
    x.append(x3);
    y.append(y1);
    y.append(y2);
    y.append(y3);

    // Запуск
    FunctionWindow w(x, y, "y", "x", legend);
    w.show();
    return a.exec();
}
