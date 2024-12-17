#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <cstdlib>
#include <ctime>
#include <random>

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

void MainWindow::startGame() {
    // Удаляем старое окно
    centralWidget->deleteLater();

    // Создаём игровое поле
    gameWidget = new QWidget(this);
    setCentralWidget(gameWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(gameWidget);
    timerLabel = new QLabel("Время: 0 сек", this);
    mainLayout->addWidget(timerLabel);

    gridLayout = new QGridLayout();
    mainLayout->addLayout(gridLayout);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);
    timer->start(1000);

    setupGameField();
    shuffleBoard();
    updateBoard();
}

void MainWindow::setupGameField() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            tiles[i][j] = new QPushButton("", this);
            tiles[i][j]->setFixedSize(80, 80);
            connect(tiles[i][j], &QPushButton::clicked, this, &MainWindow::tileClicked);
            gridLayout->addWidget(tiles[i][j], i, j);
        }
    }
}

void MainWindow::shuffleBoard() {
    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned int>(time(nullptr)));
    std::vector<int> numbers(16);

    // Заполнение массива числами от 1 до 15 и 0
    for (int i = 0; i < 15; ++i) {
        numbers[i] = i + 1;
    }
    numbers[15] = 0;

    // Создаем генератор случайных чисел
    std::random_device rd;
    std::mt19937 g(rd());    // Инициализация генератора

    // Перемешиваем числа с использованием shuffle
    std::shuffle(numbers.begin(), numbers.end(), g);

    // Заполняем игровую доску
    int index = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            gameBoard[i][j] = numbers[index++];
            if (gameBoard[i][j] == 0) {
                emptyRow = i;
                emptyCol = j;
            }
        }
    }
}

void MainWindow::updateBoard() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (gameBoard[i][j] == 0) {
                tiles[i][j]->setText("");
            } else {
                tiles[i][j]->setText(QString::number(gameBoard[i][j]));
            }
        }
    }
}

void MainWindow::tileClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    int row, col;

    // Найдём нажатую кнопку
    for (row = 0; row < 4; ++row)
        for (col = 0; col < 4; ++col)
            if (tiles[row][col] == clickedButton)
                goto found;

found:
    if ((abs(row - emptyRow) == 1 && col == emptyCol) || (abs(col - emptyCol) == 1 && row == emptyRow)) {
        std::swap(gameBoard[row][col], gameBoard[emptyRow][emptyCol]);
        emptyRow = row;
        emptyCol = col;
        updateBoard();
        checkVictory();
    }
}


