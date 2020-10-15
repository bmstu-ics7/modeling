#include "GraphicsBuilder.h"

GraphicsBuilder::GraphicsBuilder(QChartView *view)
    : _view(view)
{
    _chart = new QChart();
    _chart->setTheme(chartTheme);
    _series = nullptr;
}

void GraphicsBuilder::addPoint(double x, double y)
{
    if (_series == nullptr) {
        _series = new QLineSeries();
    }

    _series->append(x, y);
}

void GraphicsBuilder::editLabel(QString label)
{
    _chart->setTitle(label);
}

void GraphicsBuilder::editAsixLabels(QString x, QString y)
{
    _chart->addSeries(_series);

    QValueAxis *axisX = new QValueAxis();
    axisX->setLabelFormat("%.5f");
    axisX->setTitleText(x);
    _chart->addAxis(axisX, Qt::AlignBottom);
    _series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%.5f");
    axisY->setTitleText(y);
    _chart->addAxis(axisY, Qt::AlignLeft);
    _series->attachAxis(axisY);
}

void GraphicsBuilder::setChart()
{
    _view->setChart(_chart);
}
