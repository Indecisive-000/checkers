#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    scene -> setSceneRect(0,0, CELL_SIZE *CELL_COUNT, CELL_SIZE*CELL_COUNT);

    ui -> graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(CELL_SIZE * CELL_COUNT, CELL_SIZE * CELL_COUNT);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFrameStyle(QFrame::NoFrame);
    ui->graphicsView->setInteractive(false);

    initBoard();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initBoard(){
    QPen borderPen(Qt::black, 1);
    for (int r =0; r < CELL_COUNT; r++){
        for (int c = 0; c < CELL_COUNT; c++){
            quads[r][c] = scene->addRect(c* CELL_SIZE, r * CELL_SIZE, CELL_SIZE, CELL_SIZE);
            setCellColor(r, c);

            // LATER add initialisation
        }
    }
}



void MainWindow::setCellColor(int r, int c){
    QColor light("#fdb"), dark("#b86");
    quads[r][c]->setBrush(QBrush(((r+c)% 2 == 0)? light : dark));

}
