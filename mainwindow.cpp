#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtWidgets>
#include <QtCharts>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    chartView(nullptr),
    chart(nullptr)
{
    ui->setupUi(this);

    // Connect signals and slots
    connect(ui->horizontalSlider_sigma, &QSlider::valueChanged, this, &MainWindow::on_horizontalSlider_sigma_valueChanged);
    connect(ui->horizontal_slider_rho, &QSlider::valueChanged, this, &MainWindow::on_horizontal_slider_rho_valueChanged);
    connect(ui->horizontalSlider_beta_value, &QSlider::valueChanged, this, &MainWindow::on_horizontalSlider_beta_value_valueChanged);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete chartView; // Release chartView memory
    delete chart; // Release chart memory
}

void MainWindow::on_horizontalSlider_sigma_valueChanged(int value)
{
    ui->label_sigma_value->setText(QString::number(value));
}

void MainWindow::on_horizontal_slider_rho_valueChanged(int value)
{
    ui->label_rrho_slider_value->setText(QString::number(value));
}

void MainWindow::on_horizontalSlider_beta_value_valueChanged(int value)
{
    ui->label_beta_value->setText(QString::number(value));
}

void MainWindow::on_pushButton_clicked()
{
    // Retrieve values from sliders
    double sigma = ui->horizontalSlider_sigma->value();
    double rho = ui->horizontal_slider_rho->value();
    double beta = ui->horizontalSlider_beta_value->value();

    // Compute Lorenz equations and form a vector of points
    QVector<QPointF> points;
    double x = -1.8; // Adjusted initial condition for x
    double y = 2.5; // Example initial condition
    double z = 9.6; // Example initial condition
    double dt = 0.01; // Example time step
    int steps = 10000; // Number of steps

    for (int i = 0; i < steps; ++i) {
        double dx = sigma * (y - x);
        double dy = x * (rho - z) - y;
        double dz = x * y - beta * z;

        x += dx * dt;
        y += dy * dt;
        z += dz * dt;

        points.append(QPointF(x, y));
    }

    // Create a series for x, y, z points
    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < points.size(); ++i) {
        series->append(points[i]);
    }

    // Check if a chart view already exists, if so, delete it
    if(chartView) {
        delete chartView;
    }

    // Create a chart
    chart = new QChart();
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Add series to the chart
    chart->addSeries(series);

    // Set chart title
    chart->setTitle("Lorentz Curve");

    // Set axes titles
    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("X");
    chart->setAxisX(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Y");
    chart->setAxisY(axisY);

    // Add chart view to layout
    ui->verticalLayout->addWidget(chartView);
}
