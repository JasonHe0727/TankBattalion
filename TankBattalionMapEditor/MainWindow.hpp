#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "BattlefieldScene.hpp"
#include <QMainWindow>
#include <QVector>
enum class BattlefieldKind
{
    Steel = 0,
    Wall = 1,
    Grass = 2,
    Water = 3
};

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QVector<BattlefieldKind> mapInfo;
    BattlefieldScene* scene;
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void on_wallsButton_clicked();

    void on_steelsButton_clicked();

    void on_grassButton_clicked();

    void on_waterButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_HPP
