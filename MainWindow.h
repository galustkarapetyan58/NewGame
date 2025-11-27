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
    const std::vector<std::vector<int>>& getCurBubbles() const { return m_current;}
    const std::vector<std::vector<int>>& getCurState() const { return m_impossibleBubbles;}
    const int& getSize() const {return m_n;}
    QLabel* getLabel() const;
    bool isAllGrey();
    int countOfWhite();
    int countOfGrey();
    void checkboxToWhite();
    void rowToGrey();
    void hardBotTime();
    void impossibleBotTime();
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
    void playImpossible();
public slots:
    void gameOverSlot();
    void mainWindowSlot(int i, int j);
    void easySlote(int i, int j);
    void mediumSlote(int i, int j);
    void hardSlote(int i, int j);
    void impossibleSlote(int i, int j);
    void animateBlueToGrey(QPushButton* button);
    void easyBotTimeSlot();
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
    int m_n, m_cnt;
    QLabel* m_label1, *m_label2;
    bool m_gameEnded;
    std::vector<std::vector<int>> m_current, m_impossibleBubbles;
};


