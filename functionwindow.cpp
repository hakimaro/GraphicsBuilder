#include "functionwindow.h"
#include <QtCharts>

FunctionWindow::FunctionWindow(QVector<QVector<qreal>> x, QVector<QVector<qreal>> y,
                               QString titleX, QString titleY, QVector<QString> legend)
{
    QFile *file = new QFile("style.css");
    file->open(QFile::ReadOnly);
    QString strCSS = QLatin1String(file->readAll());
    setStyleSheet(strCSS);
    setFixedSize(800, 600);

    chart = new QChart();
    axisX = new QValueAxis();
    axisX->setTitleText(titleX);
    chart->addAxis(axisX, Qt::AlignBottom);

    axisY = new QValueAxis();
    axisY->setTitleText(titleY);
    chart->addAxis(axisY, Qt::AlignLeft);
    // ! Добавление графика функций
    for(int i = 0; i < x.size(); i++) {
        QLineSeries *series = new QLineSeries();
        series->setName(legend[i]);
        for(int j = 0; j < x[i].size(); ++j) {
            *series << QPointF(x[i][j], y[i][j]);
            if (x[i][j] < _init_min_x) _init_min_x = x[i][j];
            if (x[i][j] > _init_max_x) _init_max_x = x[i][j];
            if (y[i][j] < _init_min_y) _init_min_y = y[i][j];
            if (y[i][j] > _init_max_y) _init_max_y = y[i][j];
        }
        chart->addSeries(series);
        series->attachAxis(axisX);
        series->attachAxis(axisY);
    }

    axisX->setRange(_init_min_x, _init_max_x);
    axisY->setRange(_init_min_y, _init_max_y);

    chart->setBackgroundVisible(false);
    setChart(chart);
    QHBoxLayout *h_box = new QHBoxLayout;
    h_box->setAlignment(Qt::AlignTop);
    setLayout(h_box);
    setRenderHint(QPainter::Antialiasing);
}
void FunctionWindow::keyReleaseEvent(QKeyEvent *event) {
    qreal dx = (axisX->max() - axisX->min()) / 10;
    qreal dy = (axisY->max() - axisY->min()) / 10;

    if (event->key() == Qt::Key_Left) {
        change_range(axisX->min()-dx, axisY->min(), axisX->max()-dx, axisY->max());
    } else if (event->key() == Qt::Key_Up) {
        change_range(axisX->min(), axisY->min() + dy, axisX->max(), axisY->max() + dy);
    } else if (event->key() == Qt::Key_Right) {
        change_range(axisX->min()+dx, axisY->min(), axisX->max()+dx, axisY->max());
    } else if (event->key() == Qt::Key_Down) {
        change_range(axisX->min(), axisY->min() - dy, axisX->max(), axisY->max() - dy);
    } else if (event->key() == Qt::Key_Space) {
        change_range(_init_min_x, _init_min_y, _init_max_x, _init_max_y);
    }
}

void FunctionWindow::wheelEvent(QWheelEvent *event) {
    qreal x = event->x();
    qreal y = event->y();
    if (event->delta() > 0 && plot_is_under_mouse(x, y)) {
        qreal min_axis_x = axisX->min();
        qreal max_axis_x = axisX->max();
        qreal min_axis_y = axisY->min();
        qreal max_axis_y = axisY->max();

        qreal x_at_plot = x - chart->plotArea().x();
        qreal y_at_plot = y - chart->plotArea().y();

        qreal axis_dx = (max_axis_x - min_axis_x) / chart->plotArea().width();
        qreal axis_dy = (max_axis_y - min_axis_y) / chart->plotArea().height();

        qreal min_range_x = min_axis_x + (axis_dx * (abs(x_at_plot)))/10;
        qreal min_range_y = min_axis_y + (axis_dy * (abs(y_at_plot - chart->plotArea().height())))/10;
        qreal max_range_x = max_axis_x - (axis_dx * (abs(x_at_plot - chart->plotArea().width())))/10;
        qreal max_range_y = max_axis_y - (axis_dy * (abs(y_at_plot)))/10;

        change_range(min_range_x, min_range_y, max_range_x, max_range_y);
    }
    else if (event->delta() < 0 && plot_is_under_mouse(x, y)) {
        change_range(axisX->min()-abs(axisX->min()/10), axisY->min()-abs(axisY->min()/10),
                     axisX->max()+abs(axisX->max()/10), axisY->max()+abs(axisY->max()/10));
    }
}

void FunctionWindow::change_range(qreal minX, qreal minY, qreal maxX, qreal maxY) {
    axisX->setRange(minX, maxX);
    axisY->setRange(minY, maxY);
}

bool FunctionWindow::plot_is_under_mouse(int x, int y) {
    return (x >= chart->plotArea().x() && x <= chart->plotArea().x() + chart->plotArea().width() &&
            y >= chart->plotArea().y() && y <= chart->plotArea().y() + chart->plotArea().height());

}
