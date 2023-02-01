#include "functionwindow.h"
#include <QtCharts>

FunctionWindow::FunctionWindow(QVector<qreal> x, QVector<qreal> y,
                               QString titleX, QString titleY)
{
    _zoom_out = new QPushButton(tr("&-"));
    _initial_range = new QPushButton(tr("&1"));

    connect(_zoom_out, &QPushButton::clicked, this, &FunctionWindow::zoom_out_clicked);
    connect(_initial_range, &QPushButton::clicked, this, &FunctionWindow::initial_range_clicked);

    series = new QLineSeries();
    series->setName("Зависимость " + titleY + " от " + titleX);
    for(int i = 0; i < y.size(); ++i) {
        *series << QPointF(x[i], y[i]);
    }

    chart = new QChart();
    chart->addSeries(series);

    axisX = new QValueAxis();
    axisX->setTitleText(titleX);
    axisX->setLabelFormat("%g");
    axisX->setTickCount(1);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    axisY = new QValueAxis();
    axisY->setTitleText(titleY);
    axisY->setLabelFormat("%g");
    axisY->setTickCount(5);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    _init_min_x = axisX->min();
    _init_max_x = axisX->max();
    _init_min_y = axisY->min();
    _init_max_y = axisY->max();

    setChart(chart);
    QHBoxLayout *h_box = new QHBoxLayout;
    h_box->addWidget(_zoom_out);
    h_box->addWidget(_initial_range);
    h_box->setAlignment(Qt::AlignTop);
    setLayout(h_box);
    setRenderHint(QPainter::Antialiasing);

}

void FunctionWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        press_x = event->x();
        press_y = event->y();
    }
    else {
        QChartView::mousePressEvent(event);
    }
}

void FunctionWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        qreal curr_x = event->x();
        qreal curr_y = event->y();
        qDebug() << curr_x << " " << curr_y;
        qDebug() << width() << " " << height();

        // координаты, которые получились при зажатии и отпускании мыши
        qreal min_x = (curr_x < press_x) ? curr_x : press_x;
        qreal max_x = (curr_x > press_x) ? curr_x : press_x;
        qreal min_y = (curr_y < press_y) ? curr_y : press_y;
        qreal max_y = (curr_y > press_y) ? curr_y : press_y;

        // координаты начала и конца в графике (пределы)
        qreal min_axis_x = axisX->min();
        qreal max_axis_x = axisX->max();
        qreal min_axis_y = axisY->min();
        qreal max_axis_y = axisY->max();

        qreal axis_dx = (max_axis_x - min_axis_x) / width();
        qreal axis_dy = (max_axis_y - min_axis_y) / height();

        qreal min_range_x = min_axis_x + (axis_dx * min_x);
        qreal max_range_x = max_axis_x - (axis_dx * (width() - max_x));
        qreal min_range_y = min_axis_y + (axis_dy * (height() - min_y));
        qreal max_range_y = max_axis_y - (axis_dy * max_y);
        change_range(min_range_x, min_range_y, max_range_x, max_range_y);
    } else {
        QChartView::mouseReleaseEvent(event);
    }
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
    }
}

void FunctionWindow::zoom_out_clicked() {
    change_range(axisX->min()-abs(axisX->min()/1.1), axisY->min()-abs(axisY->min()/1.1),
                 axisX->max()+abs(axisX->max()/1.1), axisY->max()+abs(axisY->max()/1.1));

    qDebug() << width() << " " << height();
}

void FunctionWindow::initial_range_clicked() {
    change_range(_init_min_x, _init_min_y, _init_max_x, _init_max_y);
}

void FunctionWindow::change_range(qreal minX, qreal minY, qreal maxX, qreal maxY) {
    axisX->setRange(minX, maxX);
    axisY->setRange(minY, maxY);
}
