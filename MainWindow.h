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
    QLabel* getLabel() const;
    bool isAllGrey();
     int countOfWhite();
     int countOfGrey();
private:

    bool isBlue(int x, int y);
    bool isWhite(int x, int y);
    bool hasWhite(int row);
    void animateWhiteToGrey(QPushButton *button);
    void setWhite(int x, int y);
    void setBlue(int x, int y);
    void animateBackgroundColor(QPushButton* btn, QColor start, QColor end, int duration = 200);
    void animateHighlight(QPushButton* btn);
signals:
    void buttonPressedSignal(int i, int j);
    void playersTurnSignal(int i, int j);
public slots:
    void mainWindowSlot(int i, int j);
    void easySlote(int i, int j);
    void mediumSlote(int i, int j);
    void hardSlote(int i, int j);
    void impossibleSlote(int i, int j);
private:
    void animateBlueToGrey(QPushButton* button);
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
    int m_n;
     QLabel* m_label1, *m_label2;

};


