#pragma once
#include <QObject>
#include "MainWindow.h"
#include <QMainWindow>

class GameLogic : public QObject
{
    Q_OBJECT
signals:
    void gameSignal(int i, int j);
    void gameIsEasySignal(int i, int j);
    void gameIsMediumSignal(int i, int j);
    void gameIsHardSignal(int i, int j);
    void gameIsImpossibleSignal(int i, int j);
public:
   explicit GameLogic(MainWindow* mainwindow);
    bool ok();
public slots:
    void buttonPressedSlot(int i, int j);
    void gameIsEasySlot(int i, int j);
    void gameIsMediumSlot(int i, int j);
    void gameIsHardSlot(int i, int j);
    void gameIsImpossibleSlot(int i, int j);
private:
    MainWindow* m_mainWindow;
    QVector<QVector<bool>> m_state;
    QVector<QVector<QPushButton*>> m_bubbles;

};

