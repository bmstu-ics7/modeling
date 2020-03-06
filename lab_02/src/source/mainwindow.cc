#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(
        ui->buttonCalculate, &QPushButton::clicked,
        this, &MainWindow::clickButtonCalculate
    );

    GraphicsBuilder(ui->chartI).setChart();
    GraphicsBuilder(ui->chartR).setChart();
    GraphicsBuilder(ui->chartU).setChart();
    GraphicsBuilder(ui->chartT).setChart();
    GraphicsBuilder(ui->chartIR).setChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clickButtonCalculate()
{
    double L = ui->lineL->text().toDouble();
    double R = ui->lineR->text().toDouble();
    double U = ui->lineU->text().toDouble();
    double I = ui->lineI->text().toDouble();
    double tau = ui->lineTau->text().toDouble();
    double t = ui->lineT->text().toDouble();

    Mathematics math = Mathematics(L, R, U, I, tau, t);

    GraphicsBuilder build = GraphicsBuilder(ui->chartI);
    for (int i = 0; i < 100; ++i)
        build.addPoint(i, sqrt(i));
    build.editLabel("kekas");
    build.editAsixLabels("x axis", "y axis");
    build.setChart();

    qDebug() << Interpolation::getT(I);
    qDebug() << Interpolation::getM(I);
    qDebug() << Interpolation::getSig(t);
}
