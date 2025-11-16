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
public slots:
    void menuSlot(int i, int j);
public:
    const QVector<QVector<QPushButton*>>& getButtons() const { return m_allButtons; }
    Menu();
private:
    QVector<int> m_members;
    QVector<QPushButton*> m_buttons, m_newButtons;
    QVector<QVector<QPushButton*>> m_allButtons;
    QWidget* m_window, *m_newWindow;
    int m_n=2, m_count = 7;
    void open_menu();
};
