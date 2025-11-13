#pragma once

#include <QMainWindow>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QVector>
#include <QLineEdit>
#include <QGraphicsColorizeEffect>
#include <QPropertyAnimation>
#include <QLabel>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int n, QWidget *parent = nullptr);
    const QVector<QVector<QPushButton*>>& getBubbles() const { return m_bubbles; }
     const QVector<QVector<bool>>& getState() const { return m_state; }
    bool isAllGrey();
private:

    bool isBlue(int x, int y);
    bool isWhite(int x, int y);
    bool hasWhite(int row);
    void animateWhiteToGrey(QPushButton *button);
    void setWhite(int x, int y);
    void setBlue(int x, int y);
    void animateBackgroundColor(QPushButton* btn, QColor start, QColor end, int duration = 200);
    void animateHighlight(QPushButton* btn);
    int countOfWhite();
signals:
    void buttonPressedSignal(int i, int j);
public slots:
    void mainWindowSlot(int i, int j);
private:
    void createMembers();
    void setupMembers();
    void makeConnections();
    QWidget* m_window;
    QLineEdit* m_display;
    QVBoxLayout* m_mainline;
    QGridLayout* m_grid;
    QVector<QVector<QPushButton*>> m_bubbles;
    QVector<QPushButton*> m_row;
    QVector<QVector<bool>> m_state;
    QLabel* m_label1, *m_label2;
    int m_n;

};


