#ifndef FUNCTIONWINDOW_H
#define FUNCTIONWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QtCharts>

class FunctionWindow : public QChartView
{
    Q_OBJECT
public:
    FunctionWindow(QVector<qreal> x, QVector<qreal> y,
                   QString titleX, QString titleY);

public slots:
    void zoom_out_clicked();
    void initial_range_clicked();

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    void change_range(qreal minX, qreal minY, qreal maxX, qreal maxY);

    // Масштабирование
    QChart *chart = new QChart();
    QLineSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;    
    QPushButton *_zoom_out; // отдаление

    // Все связанное с приближением
    qreal press_x;
    qreal press_y;
    // Чтобы вернуть в исходное положение график
    QPushButton *_initial_range;
    qreal _init_min_x;
    qreal _init_max_x;
    qreal _init_min_y;
    qreal _init_max_y;
};

#endif // FUNCTIONWINDOW_H
