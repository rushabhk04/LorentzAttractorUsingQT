#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}



void MainWindow::on_pushButton_plot_clicked()
{

    QString xvalueStr = ui->lineEdit_xvalue->text();
    QString yvalueStr = ui->lineEdit_2_yvalue->text();
    QString zvalueStr = ui->lineEdit_3_zvalue->text();

    // Convert QString values to double
    double xValue = xvalueStr.toDouble();
    double yValue = yvalueStr.toDouble();
    double zValue = zvalueStr.toDouble();


    // Create chart and series
    Qt::Charts::QChart *chart = new Qt::Charts::QChart();
    Qt::Charts::QLineSeries *series = new Qt::Charts::QLineSeries();
    Qt::Charts::QChartView *chartView = new Qt::Charts::QChartView(chart);


    // Add data points to series
    series->append(0, xValue);
    series->append(1, yValue);
    series->append(2, zValue);

    // Add series to chart
    chart->addSeries(series);

    // Set chart title
    chart->setTitle("Plot");

    // Create chart view and set chart
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Set chart view as central widget
    setCentralWidget(chartView);
}
MainWindow::~MainWindow()
{
    delete ui;
}

