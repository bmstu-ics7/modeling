#ifndef __GRAPHICS_BUILDER_H
#define __GRAPHICS_BUILDER_H

#include <QString>
#include <QtCharts>
#include <QChart>

using namespace QtCharts;

class GraphicsBuilder
{
public:
    GraphicsBuilder(QChartView *view);
    void addPoint(double x, double y);
    void editLabel(QString label);
    void editAsixLabels(QString x, QString y);
    void setChart();
private:
    QChart *_chart;
    QChartView *_view;
    QSplineSeries *_series;
    QChart::ChartTheme chartTheme = QChart::ChartThemeDark;
};

#endif // __GRAPHICS_BUILDER_H
