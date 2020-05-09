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

    GraphicsBuilder(ui->chart).setChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::click_calculate()
{
    double k0 = ui->lineEdit_k0->text().toDouble();
    double kn = ui->lineEdit_kn->text().toDouble();
    double a0 = ui->lineEdit_a0->text().toDouble();
    double an = ui->lineEdit_an->text().toDouble();
    double F0 = ui->lineEdit_F0->text().toDouble();
    bool ax3  = ui->checkBox_Alpha->isChecked();

    Mathematics math(k0, kn, a0, an, F0, ax3);
    GraphicsBuilder builder(ui->chart);

    for (int i = 0; i < math.X.length(); ++i) {
        builder.addPoint(math.X[i], math.Y[i]);
    }

    builder.editLabel("Температура стержня");
    builder.editAsixLabels("Длина, см", "Температура, K");
    builder.setChart();
}
