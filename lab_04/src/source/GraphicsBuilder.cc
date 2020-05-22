#include "GraphicsBuilder.h"

GraphicsBuilder::GraphicsBuilder(QChartView *view)
    : _view(view)
{
    _chart = new QChart();
    _chart->setTheme(chartTheme);
}

void GraphicsBuilder::addGraph()
{
    _series.append(new QSplineSeries());
}

void GraphicsBuilder::addPoint(double x, double y)
{
    if (_series.count() == 0) {
        _series.append(new QSplineSeries());
    }

    _series.last()->append(x, y);
}

void GraphicsBuilder::editLabel(QString label)
{
    _chart->setTitle(label);
}

void GraphicsBuilder::editAsixLabels(QString x, QString y)
{
    _chart->addSeries(_series.last());

    QValueAxis *axisX = new QValueAxis();
    axisX->setLabelFormat("%.3f");
    axisX->setTitleText(x);
    _chart->addAxis(axisX, Qt::AlignBottom);
    _series.last()->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%.3f");
    axisY->setTitleText(y);
    _chart->addAxis(axisY, Qt::AlignLeft);
    _series.last()->attachAxis(axisY);
}

void GraphicsBuilder::setChart()
{
    _view->setChart(_chart);
}
