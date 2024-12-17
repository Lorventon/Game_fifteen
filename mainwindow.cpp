#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <cstdlib>
#include <ctime>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), elapsedTime(0), bestTime(INT_MAX) {
    settings = new QSettings("MyCompany", "FifteenPuzzle", this);
    loadBestResult();

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    setupMainMenu();
}

void MainWindow::setupMainMenu() {
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    welcomeLabel = new QLabel("Добро пожаловать в игру \"Пятнашки\"!\nЦель: расположить числа от 1 до 15.", this);
    bestResultLabel = new QLabel("Лучший результат: Не установлено", this);
    startButton = new QPushButton("Начать игру", this);

    layout->addWidget(welcomeLabel);
    layout->addWidget(bestResultLabel);
    layout->addWidget(startButton);

    connect(startButton, &QPushButton::clicked, this, &MainWindow::startGame);

    if (bestTime != INT_MAX)
        bestResultLabel->setText(QString("Лучший результат: %1 сек").arg(bestTime));
}


