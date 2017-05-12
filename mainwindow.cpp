#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QAction *newGame = ui->startNewGame;
    connect(newGame, SIGNAL(triggered()), this, SLOT(startNewGame()));

    QAction *rules = ui->rules;
    connect(rules, SIGNAL(triggered()), this, SLOT(showRules()));

    QAction *exit = ui->exit;
    connect(exit, SIGNAL(triggered()), this, SLOT(exit()));

    scoreTable = ui->tableWidget;
    startNewGame();

    ui->good->setStyleSheet("color: green");
    ui->bad->setStyleSheet("color: red");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showRules(){
    Rule *rules = new Rule();
    connect(rules, &Rule::returnToMainWindow, this, &MainWindow::show);
    this->setVisible(false);
    rules->show();
}

void MainWindow::exit(){
    qApp->quit();
}

void MainWindow::startNewGame(){
    setPlayers();
}

// Вводим кол-во игроков, их имена, заполняем таблицу рекордов
void MainWindow::setPlayers(){
    bool ok;
    count = QInputDialog::getInt(this,
                                 QString::fromUtf8("Игроки"),
                                 QString::fromUtf8("Введите кол-во игроков:"),
                                 2,2,4,1,&ok);
    player = new Player[count];
    for(int i = 0; i < count; i++){
        bool ok;
        QString str = "Представьтесь, игрок номер " + QString::number(i + 1);
        QString text;
        do{
            text = QInputDialog::getText(this,
                                     QString::fromUtf8("Выбор имени"),
                                     str,
                                     QLineEdit::Normal,
                                     "", &ok);

        } while(text == NULL);
        player[i].setName(text);
    }
    step = 0;
    ui->step->setText(player[step].getName());
    scoreTable->setRowCount(count);

    for(int i = 0; i < scoreTable->rowCount(); i++){
        QTableWidgetItem *name = new QTableWidgetItem(player[i].getName());
        QTableWidgetItem *score = new QTableWidgetItem(QString::number(player[i].getScore()));
        QTableWidgetItem *bolt = new QTableWidgetItem(QString::number(player[i].getBolt()));
        scoreTable->setItem(i,0,name);
        scoreTable->setItem(i,1,score);
        scoreTable->setItem(i,2,bolt);
    }
    scoreTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeMode(1));
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << QString("Кубики кинуты, господа");
    resBros = player[step].step();

    switch (resBros) {
    case -1:
        // Болт (не на бочке)
        ui->pushButton->setEnabled(false);
        player[step].setBolt(); 
        QMessageBox::about(this,"Уведомление", "Увы, у вас болт. Передайте ход.");
        break;
    case 0:
        // Игрок ничего не набросал и он на бочке
        qDebug() << QString("Игрок на бочке и результат его броска нулевой");
        ui->pushButton->setEnabled(false);
        break;
    case 1:
        // Можем записать, ничего не делаем
        break;
    case 2:
        // Самосвал
        player[step].samosval();
        ui->pushButton->setEnabled(false);
        QMessageBox::about(this,"Уведомление", "Самосвал подъехал, очки на ноль");
        break;
    case 3:
        // Игрок что-то накидал, но недостаточно, чтобы выйти из бочки, ничего не делаем
        qDebug() << QString("Нужно больше очков, чтобы выйти с бочки");
        break;
    case 4:
        QMessageBox::about(this,"Победа", "Поздравляем, Вы победили!");
        player[step].setScore(player[step].getRes());
        updScoreTable();
        ui->pushButton->setEnabled(false);
        ui->giveStep->setEnabled(false);
        break;
    default:
        break;
    }

    qDebug() << QString("Ситуация: ");
    qDebug() << int(resBros);

    QString usedCubes = player[step].getUsedCubes();
    QString availableCubes = player[step].getNonUsedCubes();

    ui->good->setText(usedCubes);
    ui->bad->setText(availableCubes);
    if (availableCubes == ""){        // Вот это костыль, если строка с незачетными кубиками пуста, значит все кубики зачетные, а значит их можно перекидать
        qDebug() << QString("Оп, кажется все кубики зачетные!");
        player[step].freeCubes();
    }
    /* Изначально кубики освобождались после в ф-ии Cubes::haveNonUsedCubes() (там закомментированы те строчки, что это делали)
     * но так как в таком случае я сначала их обнуляю (что не обязательно, но на всякий случай), а только в этой фунции вывожу
     * (см выше строки 126-130), то они записывались в bad, и были равны нулям, однако все работало как и должно,
     * мы могли кинуть их или записать и там дальше все шло нормально. Но это не красиво.
     * И тут мне в голову взбрело это безумное решение, я его реализовал и оно работает.
     * Да, костыль, да, так не надо делать в реальном проекте. Но решил оставить так, на память.
     * TODO: а может все таки переделать?
     */

    ui->brosRes->setText(QString::number(player[step].getRes()));
    ui->score->setText(QString::number(player[step].getScore()));

}

void MainWindow::on_giveStep_clicked()
{
    qDebug() << QString("Игрок передал ход");
    qDebug() << QString("Ситуация: ");
    qDebug() << int(resBros);
    qDebug() << QString("Может игрок ходить: ");
    qDebug() << bool(canStep);
    if ( resBros == 1 ){
        player[step].setScore(player[step].getRes());
        player[step].clearBolt();       /* Есть два варианта, либо после записи очков болты сбрасываются (как тут),
                                         * либо нет. Когда хочется посложнее - можно просто закомментить эту строчку
                                         */
    }


    ui->score->setText("");
    ui->good->setText("");
    ui->bad->setText("");
    ui->brosRes->setText("");
    ui->pushButton->setEnabled(true);

    player[step].setRes(0);
    updScoreTable();
    player[step].setCubesRes();        // Обнуляем кубики. Вроде и не нужно, но на всякий случай оставим
    player[step].freeCubes();          // Ход сменился, новый игрок, новые, неиспользованные, кубики!

    if ((step + 1) >= count)
        step = 0;
    else
        step++;

    ui->step->setText(player[step].getName());
}

void MainWindow::updScoreTable(){
    for (int i = 0; i < scoreTable->rowCount(); i++){
        scoreTable->item(i,1)->setText(QString::number(player[i].getScore()));
        scoreTable->item(i,2)->setText(QString::number(player[i].getBolt()));
    }

}
