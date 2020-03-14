#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    math.process();

    GraphicsBuilder builderI(ui->chartI);
    GraphicsBuilder builderR(ui->chartR);
    GraphicsBuilder builderU(ui->chartU);
    GraphicsBuilder builderT(ui->chartT);
    GraphicsBuilder builderIR(ui->chartIR);

    for (int i = 0; i < math.timevec.size(); ++i) {
        builderI.addPoint(math.timevec[i], math.Ivec[i]);
        builderR.addPoint(math.timevec[i], math.Rvec[i]);
        builderU.addPoint(math.timevec[i], math.Uvec[i]);
        builderT.addPoint(math.timevec[i], math.Tvec[i]);
        builderIR.addPoint(math.timevec[i], math.Ivec[i] * math.Rvec[i]);
    }

    builderI.editLabel("Сила тока в цепи");
    builderR.editLabel("Сопротивление лампы");
    builderU.editLabel("Напряжение на конденсаторе");
    builderT.editLabel("Температура");
    builderIR.editLabel("Напряжение на лампе");

    builderI.editAsixLabels("time", "I");
    builderR.editAsixLabels("time", "Rp");
    builderU.editAsixLabels("time", "Uc");
    builderT.editAsixLabels("time", "T0");
    builderIR.editAsixLabels("time", "I * Rp");

    builderI.setChart();
    builderR.setChart();
    builderU.setChart();
    builderT.setChart();
    builderIR.setChart();
}
