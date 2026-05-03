#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

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




private:
    const int CELL_SIZE = 64;
    const int CELL_COUNT = 8;
    QGraphicsScene *scene;
    QGraphicsRectItem *quads[8][8];
    Ui::MainWindow *ui;

    void initBoard();

    void setCellColor(int r, int c);


};
#endif // MAINWINDOW_H
