#include "MainWindow.h"

#include <QWidget>
#include <QPushButton>
#include <QApplication>
#include <QGridLayout>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLayout>
#include <QObject>
#include <QString>
#include <bits/stdc++.h>
#include <QPointer>
#include <QLabel>
MainWindow::MainWindow(int n, QWidget *parent)
    : QMainWindow{parent}, m_n(n)
{
    createMembers();
    setupMembers();
    makeConnections();
}

void MainWindow::createMembers() {
    m_grid = new QGridLayout();
    m_mainline = new QVBoxLayout();
    m_window = new QWidget();
}


bool MainWindow::isBlue(int x, int y)
{
    QString line = m_bubbles[x][y]->styleSheet();
    if(!line.contains("white"))
        return true;
    else
        return false;
}

bool MainWindow::isWhite(int x, int y)
{
    QString line = m_bubbles[x][y]->styleSheet();
    if(line.contains("background-color: white"))
        return true;
    else
        return false;
}

bool MainWindow::hasWhite(int row)
{
    for(int x = 0; x < m_bubbles[row].size(); x++)
    {
        QString line = m_bubbles[row][x]->styleSheet();
        if(line.contains("white"))
        {
            return true;
            break;
        }
    }
    return false;
}

void MainWindow::setWhite(int x, int y)
{
    QPushButton* btn = m_bubbles[x][y];
    btn->setStyleSheet(
        "QPushButton {"
        "   background-color: white;"
        "   font-size: 20px;"
        "   border-radius: 15px;"
        "   border: 2px solid #6ea0d6;"
        "   transition: all 0.2s ease;"
        "}"
        "QPushButton:hover {"
        "   background-color: #a3c9f1;"
        "   box-shadow: 0px 3px 8px rgba(0,0,0,0.3);"
        "}"
        "QPushButton:pressed {"
        "   background-color: #7fb1e3;"
        "}"
        );
}

void MainWindow::setBlue(int x, int y)
{
    QPushButton* btn = m_bubbles[x][y];
    btn->setStyleSheet(
        "QPushButton {"
        "background-color: #a3c9f1;"
        "font-size: 20px;"
        "border-radius: 15px;"
        "border: 2px solid #6ea0d6;"
        "}"
        "QPushButton:hover {"
        "background-color: #cde6fb;"
        "}"
        );
}
void MainWindow::animateWhiteToGrey(QPushButton* button)
{
    if (!button)
        return;
    QPointer<QPushButton> safeButton(button);


    QGraphicsColorizeEffect* effect = new QGraphicsColorizeEffect(button);
    effect->setColor(Qt::gray);
    effect->setStrength(0.0);  // start from no color
    effect->setParent(button);  // parent effect to button
    button->setGraphicsEffect(effect);


    QPropertyAnimation* anim = new QPropertyAnimation(effect, "strength", this);
    anim->setDuration(400);
    anim->setStartValue(0.0);
    anim->setEndValue(1.0);
    anim->setEasingCurve(QEasingCurve::InOutQuad);


    connect(anim, &QPropertyAnimation::finished, this, [safeButton, effect, anim]() {
        if (safeButton) {
            safeButton->setGraphicsEffect(nullptr);
            safeButton->setStyleSheet(
                "QPushButton {"
                "background-color: grey;"
                "font-size: 20px;"
                "border-radius: 15px;"
                "border: 2px solid #6ea0d6;"
                "}"
                );
        }

        anim->deleteLater();
    });

    anim->start();
}

void MainWindow::setupMembers() {
    m_grid->setSpacing(10);
    m_grid->setContentsMargins(15, 15, 15, 15);

    int row = m_n, col = m_n;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            QPushButton* btn = new QPushButton("");
            btn->setFixedSize(60, 60);
            btn->setStyleSheet(
                "QPushButton {"
                "background-color: #a3c9f1;"
                "font-size: 20px;"
                "border-radius: 15px;"
                "border: 2px solid #6ea0d6;"
                "}"
                "QPushButton:hover {"
                "background-color: #cde6fb;"
                "}"
                );
            m_grid->addWidget(btn, i, j);
            m_row.push_back(btn);
        }
        m_bubbles.push_back(m_row);
        m_row.clear();
    }


    QPushButton* btn = new QPushButton("✔");
    btn->setFixedSize(60, 60);
    btn->setStyleSheet(
        "QPushButton {"
        "background-color: #ff6b6b;"
        "color: white;"
        "font-size: 24px;"
        "border-radius: 15px;"
        "border: 2px solid #ff4c4c;"
        "}"
        "QPushButton:hover {"
        "background-color: #ff7b7b;"
        "}"

        );
    QString p1 = "Player1, it is your turn", p2 = "Player2, it is your turn";
    m_label1 = new QLabel(p1), m_label2 = new QLabel(p2);
    m_label1->setStyleSheet("font-size: 18px; color: blue;");
    m_label2->setStyleSheet("font-size: 18px; color: black;");
    m_grid->addWidget(btn, row, 0);
    m_row.push_back(btn);
    m_bubbles.push_back(m_row);
    m_row.clear();
    m_mainline->addLayout(m_grid);
    m_mainline->addWidget(m_label1);
    m_mainline->addWidget(m_label2);
    m_window->setLayout(m_mainline);
    setCentralWidget(m_window);
}



void MainWindow::makeConnections() {
    m_state.resize(m_bubbles.size());
    for (int i = 0; i < m_bubbles.size(); i++) {
        m_state[i].resize(m_bubbles[i].size(), 1);

        for (int j = 0; j < m_bubbles[i].size(); j++) {
            connect(m_bubbles[i][j], &QPushButton::clicked, this, [=]() {
                emit buttonPressedSignal(i, j);
            });
        }
    }

}

int MainWindow::countOfWhite()
{
    int cnt = 0;
    for(int x = 0; x < m_bubbles.size()-1; x++)
    {
        for(int y = 0; y < m_bubbles[x].size(); y++)
        {
            QPushButton* btn = m_bubbles[x][y];
            QString line = btn->styleSheet(), s = btn->text();
            if(line.contains("white") && !s.contains("✔"))
                cnt++;
        }
    }
    return cnt;
}

void MainWindow::mainWindowSlot(int i, int j)
{
    QPushButton* btn = m_bubbles[i][j];
    QString s = btn->text();
    QString o = btn->styleSheet();
    if (s.contains("✔"))
    {

        for (int x = 0; x < m_bubbles.size()-1; x++)
        {
            for (int y = 0; y < m_bubbles[x].size(); y++)
            {
                QPushButton* button = m_bubbles[x][y];
                if (button->styleSheet().contains("background-color: white"))
                {
                    m_state[x][y] = 0;
                    animateWhiteToGrey(button);
                }
                else
                {
                    m_state[x][y] = 1;
                }
            }
        }
        if(!o.contains("background-color: white"))
        {
            m_label1->setStyleSheet("font-size: 18px; color: black;");
            m_label2->setStyleSheet("font-size: 18px; color: red;");
            if(countOfWhite())
            btn->setStyleSheet(
                "QPushButton {"
                "   background-color: white;"
                "   color: red;"
                "   font-size: 24px;"
                "   border-radius: 15px;"
                "   border: 2px solid #ff4c4c;"
                "}"
                "QPushButton:hover {"
                "   background-color: #ff7b7b;"
                "   color: red;"
                "}"
                "QPushButton:pressed {"
                "   background-color: #ff4c4c;"
                "   color: red;"
                "}"
                );

        }
        else{
            m_label1->setStyleSheet("font-size: 18px; color: blue;");
            m_label2->setStyleSheet("font-size: 18px; color: black;");
            if(countOfWhite())
            btn->setStyleSheet(
                "QPushButton {"
                "   background-color: #ff6b6b;"
                "   color: white;"
                "   font-size: 24px;"
                "   border-radius: 15px;"
                "   border: 2px solid #ff4c4c;"
                "}"
                "QPushButton:hover {"
                "   background-color: #ff7b7b;"
                "   color: white;"
                "}"
                "QPushButton:pressed {"
                "   background-color: #ff4c4c;"
                "   color: white;"
                "}"
                );

        }
    }
    else{

    bool clickable = false;
    bool blue = isBlue(i, j);

    if (!hasWhite(i))
    {
        clickable = true;
    }
    else
    {
        if (isWhite(i, j))
        {
            clickable = true;
        }
        else if (blue)
        {
            bool leftWhite = (j > 0 && isWhite(i, j - 1));
            bool rightWhite = (j < m_bubbles[i].size() - 1 && isWhite(i, j + 1));

            if (leftWhite || rightWhite)
                clickable = true;
        }
    }

    if (!clickable)
        return;


    if (blue)
    {
        bool ok = true;
        for(int x = 0; x < m_bubbles.size()-1; x++)
        {
            if(x!=i)
            {
                if(hasWhite(x))
                {
                    ok=false;
                    break;
                }
            }
        }
        if(ok)
            setWhite(i, j);
    }
    else if (isWhite(i, j))
    {
        bool leftBlue  = (j > 0 && isBlue(i, j - 1));
        bool rightBlue = (j < m_bubbles[i].size() - 1 && isBlue(i, j + 1));

        if (leftBlue || rightBlue || j == 0 || j == m_bubbles[i].size() - 1)
            setBlue(i, j);
    }
  }
}
