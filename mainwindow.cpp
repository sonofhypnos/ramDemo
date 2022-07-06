#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QGraphicsScene>
#include <QProgressBar>
#include <QPushButton>
#include <QSlider>
#include <QTimeLine>
#include <string>


QGraphicsScene* drawLines(int start, int stop, int width, int height, int vertTickDist, QObject* parent){
//    int start = 0, stop = 300;
//    int width = 20;
//    int height = 0;
//    int vertTickDist = 20;


    QGraphicsScene *scene = new QGraphicsScene(10, 0, 100, 100, parent);
    QPen pen = QPen();
    scene->addLine(start, height, stop, height, pen);
    for (int vertTick = start; vertTick < stop; vertTick += vertTickDist) {
        scene->addLine(vertTick, height - (width / 2), vertTick, height + (width / 2), pen);
    }
    return scene;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto progressBar = new QProgressBar(this);
    progressBar->setRange(0, 1000);
    auto slider = new QSlider(this);
    slider->setRange(0, 1000);
    slider->setOrientation(Qt::Horizontal);
    auto timeline = new QTimeLine(1000, this);
    timeline->setFrameRange(0,1000);
    auto pushButton = new QPushButton(tr("Start animation"), this);
    connect(timeline, &QTimeLine::frameChanged, progressBar, &QProgressBar::setValue);
    connect(timeline, &QTimeLine::frameChanged, slider, &QSlider::setValue);
    connect(pushButton, &QPushButton::clicked, timeline, &QTimeLine::start);
    ui->vertLayout->addWidget(progressBar);
    ui->vertLayout->addWidget(pushButton);
    ui->vertLayout->addWidget(slider);

    //create Scene and add it to window:
    for (int i = 0; i < 5; ++i) {
        auto scene = drawLines(0, 200, 20, 0, 20, this);
        QGraphicsView *view = new QGraphicsView(scene, this);
        ui->vertLayout->addWidget(view);
    }

    auto scene = drawLines(0, 200, 20, 0, 20, this);
    ui->graphicsView->setScene(scene);




//    QChartView *chartView = new QChartView(this);
//	QLineSeries *series = new QLineSeries(this);
//	// ...
//	chartView->chart()->addSeries(series);

//	QValueAxis *axisX = new QValueAxis;
//	axisX->setRange(10, 20.5);
//	axisX->setTickCount(10);
//	axisX->setLabelFormat("%.2f");
//	chartView->chart()->setAxisX(axisX, series);
}

MainWindow::~MainWindow()
{
    delete ui; 
}

