#ifndef MAINWINDOW_H
#define MAINWINDOW_H

constexpr int CELL_SIZE = 64;
constexpr int CELL_COUNT = 8;


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

    QGraphicsScene *scene;
    QGraphicsRectItem *quads[8][8];
    Ui::MainWindow *ui;

    void initBoard();

    void setCellColor(int r, int c);
};

#endif // MAINWINDOW_H
