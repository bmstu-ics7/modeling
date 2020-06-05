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

    GraphicsBuilder(ui->chart_AB).setChart();
    GraphicsBuilder(ui->chart_Impulse).setChart();
    GraphicsBuilder(ui->chart_Xn).setChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::click_calculate()
{
    double alpha0     = ui->lineEdit_alpha0->text().toDouble();
    double alphaN     = ui->lineEdit_alphaN->text().toDouble();
    double l          = ui->lineEdit_l->text().toDouble();
    double T0         = ui->lineEdit_T0->text().toDouble();
    double R          = ui->lineEdit_R->text().toDouble();
    double Fmax       = ui->lineEdit_Fmax->text().toDouble();
    double Tmax       = ui->lineEdit_Tmax->text().toDouble();
    double nu         = ui->lineEdit_nu->text().toDouble();
    bool needX        = ui->checkBox_X->isChecked();
    bool needTau      = ui->checkBox_Tau->isChecked();
    bool needXn       = ui->checkBox_Xn->isChecked();
    bool needC        = ui->checkBox_C->isChecked();
    bool needImpulse  = ui->checkBox_Impulse->isChecked();

    Mathematics math(
        alpha0, alphaN,
        l, T0, R, Fmax, Tmax, nu,
        needX, needTau, needXn, needC, needImpulse
    );

    if (needC) {
        GraphicsBuilder builderAB(ui->chart_AB);

        for (auto graph : math.testAB) {
            builderAB.addGraph();
            double t = 0;
            for (auto el : graph) {
                builderAB.addPoint(t, el);
                t += math._tau;
            }
            builderAB.editLabel("empty");
        }

        builderAB.editAsixLabels("Время, сек", "Температура, K");
        builderAB.setChart();
    }

    if (needImpulse) {
        GraphicsBuilder builderImpulse(ui->chart_Impulse);
        builderImpulse.addGraph();

        double t = 0;
        for (auto el : math.testImpulse) {
            builderImpulse.addPoint(t, el);
            t += math._tau;
        }

        builderImpulse.editLabel("empty");
        builderImpulse.editAsixLabels("Время, сек", "Температура, K");
        builderImpulse.setChart();
    }

    if (needXn) {
        GraphicsBuilder builderXn(ui->chart_Xn);

        double x = 0;
        for (int i = 0; i < math.temp[0].count() - 1; i += 10, x += 10 * math._h) {
            builderXn.addGraph();
            double t = 0;
            for (int j = 0; j < math.temp.count(); ++j, t += math._tau) {
                builderXn.addPoint(t, math.temp[j][i]);
            }
            builderXn.editLabel(QString::number(x));
        }

        builderXn.editAsixLabels("Время, сек", "Температура, K");
        builderXn.setChart();
    }

    if (needX) {
        QStandardItemModel *model = new QStandardItemModel;
        QStandardItem *item;

        QStringList horizontalHeader;
        horizontalHeader.append("1");
        horizontalHeader.append("0.1");
        horizontalHeader.append("0.01");
        horizontalHeader.append("0.001");

        QStringList verticalHeader;
        for (int i = 0; i < math.testH[0].count(); ++i) {
            verticalHeader.append(QString::number(i));

            item = new QStandardItem(QString::number(math.testH[0][i]));
            model->setItem(i, 0, item);

            item = new QStandardItem(QString::number(math.testH[1][i]));
            model->setItem(i, 1, item);

            item = new QStandardItem(QString::number(math.testH[2][i]));
            model->setItem(i, 2, item);

            item = new QStandardItem(QString::number(math.testH[3][i]));
            model->setItem(i, 3, item);
        }

        model->setHorizontalHeaderLabels(horizontalHeader);
        model->setVerticalHeaderLabels(verticalHeader);

        ui->tableView_x->setModel(model);

        ui->tableView_x->resizeRowsToContents();
        ui->tableView_x->resizeColumnsToContents();
    }

    if (needTau) {
        QStandardItemModel *model = new QStandardItemModel;
        QStandardItem *item;

        QStringList horizontalHeader;
        horizontalHeader = QStringList();
        horizontalHeader.append("1");
        horizontalHeader.append("0.1");
        horizontalHeader.append("0.01");
        horizontalHeader.append("0.001");

        QStringList verticalHeader;
        verticalHeader = QStringList();
        for (int i = 0; i < math.testTau[0].count(); ++i) {
            verticalHeader.append(QString::number(i));

            item = new QStandardItem(QString::number(math.testTau[0][i]));
            model->setItem(i, 0, item);

            item = new QStandardItem(QString::number(math.testTau[1][i]));
            model->setItem(i, 1, item);

            item = new QStandardItem(QString::number(math.testTau[2][i]));
            model->setItem(i, 2, item);

            item = new QStandardItem(QString::number(math.testTau[3][i]));
            model->setItem(i, 3, item);
        }

        model->setHorizontalHeaderLabels(horizontalHeader);
        model->setVerticalHeaderLabels(verticalHeader);

        ui->tableView_t->setModel(model);

        ui->tableView_t->resizeRowsToContents();
        ui->tableView_t->resizeColumnsToContents();
    }
}
