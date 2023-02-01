#ifndef GRAPHICSWIDGET_H
#define GRAPHICSWIDGET_H

#include <QWidget>
#include <functionwindow.h>

class GraphicsWidget : public QWidget
{
    Q_OBJECT

public:
    GraphicsWidget(QVector<qreal> x, QVector<qreal> y1, QVector<qreal> y2,
                   QString titleX, QString titleY1, QString titleY2);
};
#endif // GRAPHICSWIDGET_H
