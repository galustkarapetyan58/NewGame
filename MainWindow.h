#pragma once

class QPushButton;
class QWidget;
class QGridLayout;
class QLineEdit;
class QVBoxLayout;
class QString;

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:
    void buttonPressedSignal(int i, int j);

private:
    void createMembers();
    void setupMembers();
    void makeConnections();
private:
    QWidget* m_window;
    QLineEdit* m_display;
    QVBoxLayout* m_mainline = nullptr;
    QPushButton* m_matrix[5][4];
    QGridLayout* m_grid;
    QVector<QVector<QPushButton*>> m_bubbles;
    QVector<QPushButton*> m_row;
    int m_n, m_index=-1;

};


