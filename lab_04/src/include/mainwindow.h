#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void click_calculate();

private:
    Ui::MainWindow* ui;
};

#endif // __MAINWINDOW_H
