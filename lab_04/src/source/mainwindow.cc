#include "mainwindow.h"
#include "Mathematics.h"
#include "ui_mainwindow.h"
#include "GraphicsBuilder.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(
        ui->button_Calculate, &QPushButton::clicked,
        this, &MainWindow::click_calculate
    );

    GraphicsBuilder(ui->chart_Tm).setChart();
    GraphicsBuilder(ui->chart_Xn).setChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::click_calculate()
{
    double alpha0 = ui->lineEdit_alpha0->text().toDouble();
    double alphaN = ui->lineEdit_alphaN->text().toDouble();
    double l = ui->lineEdit_l->text().toDouble();
    double T0 = ui->lineEdit_T0->text().toDouble();
    double R = ui->lineEdit_R->text().toDouble();
    double Ft = ui->lineEdit_Ft->text().toDouble();
    bool again = ui->checkBox_AgainWithFt->isChecked();
    bool anotherStart = ui->checkBox_AnotherStart->isChecked();

    Mathematics math(alpha0, alphaN, l, T0, R, Ft, again, anotherStart);

    GraphicsBuilder builderXn(ui->chart_Xn);

    for (int i = 0; i < math.temp.count(); i += math.temp.count() < 10 ? 1 : math.temp.count() / 10) {
        builderXn.addGraph();
        double x = 0;
        for (int j = 0; j < math.temp[i].count(); ++j, x += math._h) {
            builderXn.addPoint(x, math.temp[i][j]);
        }
        builderXn.editLabel(QString::number(i + 1));
    }

    builderXn.editAsixLabels("Длина, см", "Температура, K");
    builderXn.setChart();

    GraphicsBuilder builderTm(ui->chart_Tm);

    double x = 0;
    for (int i = 0; i < math.temp[0].count() - 1; i += 10, x += 10 * math._h) {
        builderTm.addGraph();
        for (int j = 0; j < math.temp.count(); ++j) {
            builderTm.addPoint(j, math.temp[j][i]);
        }
        builderTm.editLabel(QString::number(x));
    }

    builderTm.editAsixLabels("Время, сек", "Температура, K");
    builderTm.setChart();
}
