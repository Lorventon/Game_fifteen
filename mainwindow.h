#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QTimer>
#include <QSettings>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void startGame();
    void tileClicked();
    void updateTimer();
    void checkVictory();

private:
    // Главное окно
    QWidget *centralWidget;
    QLabel *welcomeLabel;
    QLabel *bestResultLabel;
    QPushButton *startButton;

    // Игровое поле
    QWidget *gameWidget;
    QGridLayout *gridLayout;
    QPushButton *tiles[4][4];
    int gameBoard[4][4];
    int emptyRow, emptyCol;

    // Таймер
    QLabel *timerLabel;
    QTimer *timer;
    int elapsedTime;


    QSettings *settings;
    int bestTime;

    void setupMainMenu();
    void setupGameField();
    void shuffleBoard();
    void updateBoard();
    void loadBestResult();
    void saveBestResult();
};
#endif // MAINWINDOW_H
