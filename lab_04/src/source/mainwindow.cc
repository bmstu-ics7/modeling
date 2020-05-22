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
    double a1 = ui->lineEdit_a1->text().toDouble();
    double b1 = ui->lineEdit_b1->text().toDouble();
    double c1 = ui->lineEdit_c1->text().toDouble();
    double m1 = ui->lineEdit_m1->text().toDouble();

    double a2 = ui->lineEdit_a2->text().toDouble();
    double b2 = ui->lineEdit_b2->text().toDouble();
    double c2 = ui->lineEdit_c2->text().toDouble();
    double m2 = ui->lineEdit_m2->text().toDouble();

    double alpha0 = ui->lineEdit_alpha0->text().toDouble();
    double alphaN = ui->lineEdit_alphaN->text().toDouble();
    double l = ui->lineEdit_l->text().toDouble();
    double T0 = ui->lineEdit_T0->text().toDouble();
    double R = ui->lineEdit_R->text().toDouble();
    double Ft = ui->lineEdit_Ft->text().toDouble();

    Mathematics math(a1, b1, c1, m1, a2, b2, c2, m2, alpha0, alphaN, l, T0, R, Ft);
    GraphicsBuilder builder(ui->chart_Xn);

    for (int i = 0; i < math.temp.count(); i += 100) {
        builder.addGraph();
        for (int j = 0, x = 0; j < math.temp[i].count(); ++j, x += math._h) {
            builder.addPoint(x, math.temp[i][j]);
        }
        builder.editLabel(QString(i));
    }

    builder.editAsixLabels("Длина, см", "Температура, K");
    builder.setChart();
}
