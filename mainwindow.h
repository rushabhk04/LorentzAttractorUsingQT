#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_horizontalSlider_sigma_valueChanged(int value);
    void on_horizontal_slider_rho_valueChanged(int value);
    void on_horizontalSlider_beta_value_valueChanged(int value);
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QChartView *chartView; // Declare chartView as a member variable
    QChart *chart; // Declare chart as a member variable
};

#endif // MAINWINDOW_H
