#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QtWidgets>
#include <QtDataVisualization>
#include <QtCharts>
#include <QtGui>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::on_pushButton_plot_clicked()
{
    // Convert QString values to double
    double xFrom = ui->x_from_value->text().toDouble();
    double xStep = ui->x_stepsize_value->text().toDouble();
    double xTo = ui->x_to_value->text().toDouble();

    double yFrom = ui->y_from_value->text().toDouble();
    double yStep = ui->y_stepsize_value->text().toDouble();
    double yTo = ui->y_to_value->text().toDouble();

    double zFrom = ui->z_from_value->text().toDouble();
    double zStep = ui->z_stepsize_value->text().toDouble();
    double zTo = ui->z_to_value->text().toDouble();

    // Create 3D surface graph
    Q3DSurface *graph = new Q3DSurface();

    QSurfaceDataArray *data = new QSurfaceDataArray();

    // Generate data points
    for (double x = xFrom; x <= xTo; x += xStep) {
        QSurfaceDataRow *rowData = new QSurfaceDataRow();
        for (double y = yFrom; y <= yTo; y += yStep) {
            QList<QSurfaceDataItem> points;
            for (double z = zFrom; z <= zTo; z += zStep) {
                points.append(QSurfaceDataItem(QVector3D(x, y, z)));
            }
            *rowData << points;
        }
        *data << rowData;
    }

    // Create series and add data
    QSurface3DSeries *series = new QSurface3DSeries();
    series->dataProxy()->resetArray(data);

    // Add series to graph
    graph->addSeries(series);

    // Customize graph properties if needed
    graph->setTitle("3D Graph");
    graph->activeTheme()->setType(Q3DTheme::ThemeEbony);

    // Create chart view and set graph
    QWidget *container = QWidget::createWindowContainer(graph);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Set chart view as central widget
    setCentralWidget(container);
}

MainWindow::~MainWindow()
{
    delete ui;
}
