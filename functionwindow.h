#ifndef FUNCTIONWINDOW_H
#define FUNCTIONWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QtCharts>

class FunctionWindow : public QChartView
{
    Q_OBJECT
public:
    FunctionWindow(QVector<QVector<qreal>> x, QVector<QVector<qreal>> y,
                   QString titleX, QString titleY, QVector<QString> legend);

protected:
    void keyReleaseEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    void change_range(qreal minX, qreal minY, qreal maxX, qreal maxY);
    bool plot_is_under_mouse(int x, int y);

    // Масштабирование
    QChart *chart = new QChart();
    QValueAxis *axisX;
    QValueAxis *axisY;    

    // Чтобы вернуть в исходное положение график
    qreal _init_min_x = 10000;
    qreal _init_max_x = -10000;
    qreal _init_min_y = 10000;
    qreal _init_max_y = -10000;
};

#endif // FUNCTIONWINDOW_H

