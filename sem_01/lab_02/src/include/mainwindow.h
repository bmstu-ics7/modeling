#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include <QMainWindow>
#include "Mathematics.h"
#include "GraphicsBuilder.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT;

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

public slots:
    void clickButtonCalculate();

private:
    Ui::MainWindow* ui;
};

#endif // __MAINWINDOW_H
