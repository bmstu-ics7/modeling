#include "GraphicsBuilder.h"

GraphicsBuilder::GraphicsBuilder(QChartView *view)
    : _view(view)
{
    _chart = new QChart();
    _chart->setTheme(chartTheme);
    _chart->legend()->setVisible(false);
}

void GraphicsBuilder::addGraph()
{
    _series.append(new QLineSeries());
}

void GraphicsBuilder::addPoint(double x, double y)
{
    if (_series.count() == 0) {
        _series.append(new QLineSeries());
    }

    _series.last()->append(x, y);
}

void GraphicsBuilder::editLabel(QString label)
{
    _series.last()->setName(label);
}

void GraphicsBuilder::editAsixLabels(QString x, QString y)
{
    QValueAxis *axisX = new QValueAxis();
    axisX->setLabelFormat("%.3f");
    axisX->setTitleText(x);
    _chart->addAxis(axisX, Qt::AlignBottom);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%.3f");
    axisY->setTitleText(y);
    _chart->addAxis(axisY, Qt::AlignLeft);

    for (int i = 0; i < _series.count(); ++i) {
        _chart->addSeries(_series[i]);
        _series[i]->attachAxis(axisY);
        _series[i]->attachAxis(axisX);
    }
}

void GraphicsBuilder::setChart()
{
    _view->setChart(_chart);
}
