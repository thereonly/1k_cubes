#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "player.h"
#include "rule.h"

#include <QMainWindow>
#include <QLabel>
#include <QDebug>
#include <QtCore>
#include <QString>
#include <QLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QAction>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();   // Кнопка кинуть кубики
    void on_giveStep_clicked();     // Кнопка передать ход
    void setPlayers();
    void startNewGame();
    void showRules();
    void exit();
private:
    Ui::MainWindow *ui;
    QTableWidget *scoreTable;
    QVBoxLayout *l;
    int step, count;        //  step - определяет кто ходит, count - общее кол-во игроков
    void updScoreTable();
    bool canStep;
    int resBros;
    Player *player;

};

#endif // MAINWINDOW_H
