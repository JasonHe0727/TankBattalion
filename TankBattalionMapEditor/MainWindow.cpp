#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QGraphicsView>
#include <QPushButton>
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new BattlefieldScene();
    QGraphicsView* view = ui->graphicsView;
    view->setScene(scene);
    ui->wallsButton->setIcon(QIcon(":/images/walls.gif"));
    ui->steelsButton->setIcon(QIcon(":/images/steels.gif"));
    ui->grassButton->setIcon(QIcon(":/images/grass.png"));
    ui->waterButton->setIcon(QIcon(":/images/water.gif"));
    ui->deleteButton->setIcon(QIcon(":/images/delete.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_wallsButton_clicked()
{
    scene->AddWalls();
}

void MainWindow::on_steelsButton_clicked()
{
    scene->AddSteels();
}

void MainWindow::on_grassButton_clicked()
{
    scene->AddGrass();
}

void MainWindow::on_waterButton_clicked()
{
    scene->AddWater();
}

void MainWindow::on_deleteButton_clicked()
{
    scene->DeleteSelectedItem();
}
