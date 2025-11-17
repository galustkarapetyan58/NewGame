#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QObject>
#include <QPushButton>
#include "MainController.h"
class Menu : public QObject
{
Q_OBJECT
signals:
    void buttonIsPressedSignal(int i, int j);
    void startSignal(int size);
    void onePlayerSignal(int size);
    void easySignal(int size);
    void mediumSignal(int size);
    void hardSignal(int size);
    void impossibleSignal(int size);
public slots:
    void menuSlot(int i, int j);
    void selectSlote(int size);
public:
    const QVector<QVector<QPushButton*>>& getButtons() const { return m_allButtons; }
    Menu();
private:
    QVector<int> m_members;
    QVector<QPushButton*> m_buttons, m_newButtons;
    QVector<QVector<QPushButton*>> m_allButtons, m_selectButtons;
    QWidget* m_window, *m_newWindow;
    int m_n=2, m_count = 7;
    void open_menu();
    void makeConnections();
};
