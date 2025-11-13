#pragma once
#include <QObject>
#include "MainWindow.h"
#include <QMainWindow>

class GameLogic : public QObject
{
    Q_OBJECT
signals:
    void gameSignal(int i, int j);
public:
   explicit GameLogic(MainWindow* mainwindow);

public slots:
    void buttonPressedSlot(int i, int j);
private:
    MainWindow* m_mainWindow;
    QVector<QVector<bool>> m_state;
    QVector<QVector<QPushButton*>> m_bubbles;

};

