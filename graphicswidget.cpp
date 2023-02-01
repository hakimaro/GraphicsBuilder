#include "graphicswidget.h"

#include <QtCharts>

#include <math.h>

using namespace QtCharts;

GraphicsWidget::GraphicsWidget(QVector<qreal> x, QVector<qreal> y1, QVector<qreal> y2,
                               QString titleX, QString titleY1, QString titleY2)
    : QWidget(nullptr)
{ 
    QHBoxLayout *box = new QHBoxLayout;
    FunctionWindow *w1 = new FunctionWindow(x, y1, titleX, titleY1);
    FunctionWindow *w2 = new FunctionWindow(x, y2, titleX, titleY2);
    box->addWidget(w1);
    box->addWidget(w2);
    setLayout(box);
    resize(800, 400);
}
