#include "MainWindow.h"
#include <QTimer>
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
#include <QColor>
MainWindow::MainWindow(int n, QWidget *parent)
    : QMainWindow{parent}, m_n(n)
{
    m_gameEnded=false;
    createMembers();
    setupMembers();
    makeConnections();
    std::vector<int> a = {m_n};
    for(int i = 0; i < m_n; i++)
        m_current.push_back(a);
    a.clear();
    m_cnt=1;
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

    m_grid->addWidget(btn, row, 0);
    m_row.push_back(btn);
    m_bubbles.push_back(m_row);
    m_row.clear();

    m_label1->setStyleSheet("font-size: 18px; color: blue;");
    m_label2->setStyleSheet("font-size: 18px; color: black;");
    m_mainline->addLayout(m_grid);
    m_mainline->addWidget(m_label1);
    m_mainline->addWidget(m_label2);
    m_window->setLayout(m_mainline);
    setCentralWidget(m_window);
}

bool MainWindow::isAllGrey()
{
    bool ok = true;
    for(int x = 0; x < m_bubbles.size()-1; x++)
    {
        for(int y = 0; y < m_bubbles[x].size(); y++)
        {
            QString line = m_bubbles[x][y]->styleSheet();
            if(!line.contains("grey"))
            {
                ok=false;
                break;
            }
        }
    }
    return ok;
}

void MainWindow::makeConnections() {
    connect(this, &MainWindow::playersTurnSignal, this, &MainWindow::mainWindowSlot);
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

int MainWindow::countOfGrey()
{
    int cnt = 0;
    for(int x = 0; x < m_bubbles.size(); x++)
    {
        for(int y = 0; y < m_bubbles[x].size(); y++)
        {
            QString line = m_bubbles[x][y]->styleSheet();
            if(line.contains("grey"))
                cnt++;
        }
    }
    return cnt;
}
void MainWindow::mainWindowSlot(int i, int j)
{
    int cnt = countOfGrey();
    QPushButton* btn = m_bubbles[i][j];
    QString s = btn->text();
    QString o = btn->styleSheet();
    QString _o = o;

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
                    cnt++;
                }
                else
                {
                    m_state[x][y] = 1;
                }
            }
        }
        if(cnt==(m_bubbles.size()-1)*(m_bubbles.size()-1))
        {
            gameOverSlot();
            m_gameEnded=true;
        }
        else{
        if(!o.contains("background-color: white"))
        {
            if(countOfWhite()){
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
                o = btn->styleSheet();
            }
            if(_o!=o)
            {
                m_label1->setStyleSheet("font-size: 18px; color: black;");
                m_label2->setStyleSheet("font-size: 18px; color: red;");
            }
        }
        else{
            m_label1->setStyleSheet("font-size: 18px; color: black;");
            m_label2->setStyleSheet("font-size: 18px; color: red;");
            if(countOfWhite()){
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
                o=btn->styleSheet();
            }
            if(_o!=o)
            {
                m_label1->setStyleSheet("font-size: 18px; color: blue;");
                m_label2->setStyleSheet("font-size: 18px; color: black;");
            }
         }
        }
    }
    else{

    bool clickable = false;
    bool blue = isBlue(i, j);
    QString line = m_bubbles[i][j]->styleSheet();
    if(!line.contains("grey"))
    {
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
}

QLabel* MainWindow::getLabel() const
{
    return m_label1;
}
void MainWindow::gameOverSlot()
{
    if(m_gameEnded)
        return;
    this->close();
    QVBoxLayout* layout = new QVBoxLayout();
    QLabel* label;
    QLabel* label1 = this->getLabel();
    QString line = label1->styleSheet();
    QString edit = "";
    if(line.contains("blue"))
    {
        edit = "Congratulations, Player2, You Have Won";
        label = new QLabel(edit);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("font-size: 18px; color: red;");
    }
    else{
        edit = "Congratulations, Player1, You Have Won";
        label = new QLabel(edit);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("font-size: 18px; color: blue;");
    }
    QWidget* window = new QWidget;
    layout->addWidget(label);
    window->setLayout(layout);
    window->show();
}

void MainWindow::animateBlueToGrey(QPushButton* button)
{
    if (!button) {
        return;
    }

    QColor startColor("#a3c9f1");
    QColor endColor("grey");
    int duration = 500;


    QPropertyAnimation* animation = new QPropertyAnimation(button, "animatedColor", this);

    button->setProperty("animatedColor", startColor);
    animation->setDuration(duration);
    animation->setStartValue(startColor);
    animation->setEndValue(endColor);



    QObject::connect(animation, &QPropertyAnimation::finished, this, [=]() {
        button->setStyleSheet(
            "QPushButton {"
            "background-color: grey;"
            "font-size: 20px;"
            "border-radius: 15px;"
            "border: 2px solid #6ea0d6;"
            "}"
            "QPushButton:hover {"
            "background-color: grey;"
            "}"
            );


        if(isAllGrey())
        {
            this->hide();
            QLabel* label = new QLabel("Congratulations, Player1, You Have Won");
            label->setAlignment(Qt::AlignCenter);
            label->setStyleSheet("font-size: 18px; color: blue;");
            QVBoxLayout* layout = new QVBoxLayout();
            layout->addWidget(label);
            QWidget* window = new QWidget;
            window->setLayout(layout);
            window->show();
            return;
        }

        m_label1->setStyleSheet("font-size: 18px; color: blue;");
        m_label2->setStyleSheet("font-size: 18px; color: black;");
    });
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}


void MainWindow::easySlote(int i, int j)
{
    QPushButton* checkBtn = m_bubbles[m_n][0];
    QString l = checkBtn->styleSheet();
    if (!l.contains("background-color: white"))
    {
        emit playersTurnSignal(i, j);
        if(i==m_n)
        QTimer::singleShot(500, this, [this]() {
            easySlote(m_n, 0);
        });
    }
    else
    {
        bool found_blue = false;
        for(int x = 0; x < m_bubbles.size()-1; x++)
        {
            for(int y = 0; y < m_bubbles[x].size(); y++)
            {
                QPushButton* button = m_bubbles[x][y];
                QString line = button->styleSheet();
                if(!line.contains("grey"))
                {
                    animateBlueToGrey(button);
                    m_state[x][y] = 0;
                    found_blue = true;
                    break;
                }
            }
            if(found_blue)
                break;
        }
        QTimer::singleShot(1000, this, [this]()
        {
            checkboxToWhite();
        });
    }
}

void MainWindow::checkboxToWhite()
{
    m_bubbles[m_n][0]->setStyleSheet(
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

void MainWindow::mediumSlote(int i, int j)
{
    QPushButton* checkBtn = m_bubbles[m_n][0];
    QString l = checkBtn->styleSheet();
    if (!l.contains("background-color: white"))
    {
        emit playersTurnSignal(i, j);
        if(i==m_n)
            QTimer::singleShot(500, this, [this]() {
                mediumSlote(m_n, 0);
            });
    }
    else
    {
        QTimer::singleShot(500, this, [this](){
            rowToGrey();
        });
        QTimer::singleShot(1500, this, [this](){
            checkboxToWhite();
        });
    }
}

void MainWindow::rowToGrey()
{
    int i = -1;
    bool ok = true;
    int cnt = 0;
    for(int x = 0; x < m_bubbles.size()-1; x++)
    {
        for(int y = 0; y < m_bubbles[x].size(); y++)
        {
            QString line = m_bubbles[x][y]->styleSheet();
            if(!line.contains("grey"))
            {
                cnt++;
            }
        }
    }
    for(int x = 0; x < m_bubbles.size()-1; x++)
    {
        for(int y = 0; y < m_bubbles[x].size(); y++)
        {
            QString line = m_bubbles[x][y]->styleSheet();
            if(line.contains("grey"))
            {
                ok=false;
                break;
            }
        }
        if(ok)
        {
            i=x;
            break;
        }
        else{
            ok=true;
        }
    }
    if(i!=-1)
    {
        for(int x = 0; x < m_bubbles[i].size(); x++)
        {
            animateBlueToGrey(m_bubbles[i][x]);
        }
    }
    else{
        if(cnt==3)
        {
            bool ok = false;
            int l = -1, r = -1, row = -1;
            for(int x = 0; x < m_bubbles.size()-1; x++)
            {
                for(int y = 1; y < m_bubbles[x].size(); y++)
                {
                    QString line1 = m_bubbles[x][y]->styleSheet(), line2 = m_bubbles[x][y-1]->styleSheet();
                    if(!line1.contains("grey") && !line2.contains("grey"))
                    {
                        ok=true;
                        row = x;
                        l=y-1, r = y;
                        break;
                    }
                }
            }
            if(ok)
            {
                animateBlueToGrey(m_bubbles[row][l]);
                animateBlueToGrey(m_bubbles[row][r]);
                return;
            }
        }
        else{
            bool found_blue = false;
            for(int x = 0; x < m_bubbles.size()-1; x++)
            {
                for(int y = 0; y < m_bubbles[x].size(); y++)
                {
                    QPushButton* button = m_bubbles[x][y];
                    QString line = button->styleSheet();
                    if(!line.contains("grey"))
                    {
                        animateBlueToGrey(button);
                        m_state[x][y] = 0;
                        found_blue = true;
                        break;
                    }
                }
                if(found_blue)
                    break;
            }
        }
    }
}


void MainWindow::hardSlote(int i, int j)
{
    m_cnt++;
    QPushButton* checkBtn = m_bubbles[m_n][0];
    QString l = checkBtn->styleSheet();
    if (!l.contains("background-color: white"))
    {
        emit playersTurnSignal(i, j);
        if(i==m_n)
            QTimer::singleShot(500, this, [this]() {
                hardSlote(m_n, 0);
            });
    }
    else
    {
        QTimer::singleShot(500, this, [this](){
            hardBotTime();
        });
        QTimer::singleShot(3000, this, [this](){
            checkboxToWhite();
        });
    }
}

void MainWindow::hardBotTime()
{
    if(m_cnt)
    {
     std::vector<std::vector<int>> cur;
     for(int i = 0; i < m_n; i++)
     {
         std::vector<int> c;
         int cnt = 0;
         QString line1="", line2="", line3 = "", line4 = "";
         int m = 1;
         for(int j = 1; j < m_n; j++)
         {
            line1=m_bubbles[i][j]->styleSheet(), line2 = m_bubbles[i][j-1]->styleSheet();
            if(line1==line2 && line1.contains("#a3c9f1"))
            {
                m++;
                cnt=m;
            }
            else if(j<m_n-1 && line1.contains("#a3c9f1") && line2!=line1)
            {
                cnt=m;
            }
            else{
                if(cnt)
                {
                 c.push_back(cnt);
                }
                cnt=0;
                m=1;
            }
         }
         line1=m_bubbles[i][m_n-1]->styleSheet(), line2 = m_bubbles[i][m_n-2]->styleSheet(), line3 = m_bubbles[i][0]->styleSheet(), line4 = m_bubbles[i][1]->styleSheet();
         if(line1.contains("#a3c9f1") && line1!=line2)
         cnt=1;
         c.push_back(cnt);
         if(line3.contains("#a3c9f1") && line3!=line4)
         {
          c.insert(c.begin(), 1);
         }
         cur.push_back(c);
     }
     for(int i = 0; i < m_current.size(); i++)
     {
         for(int j = 0; j < m_current[i].size(); j++)
         {
             std::cout << m_current[i][j] << " ";
         }
         std::cout << std::endl;
     }
     std::cout << std::endl;
     for(int i = 0; i < cur.size(); i++)
     {
         for(int j = 0; j < cur[i].size(); j++)
         {
             std::cout << cur[i][j] << " ";
         }
         std::cout << std::endl;
     }
     std::vector<std::vector<int>> p;
     int Xor = 0;
     for(int i = 0; i < m_current.size(); i++)
     {
         for(int j = 0; j < m_current[i].size(); j++)
         {
             Xor^=m_current[i][j];
         }
     }
     if(Xor!=0)
     {
         std::map<std::vector<int>, int> count;
         for(int i = 0; i < cur.size(); i++)
         {
            std::vector<int> c(m_n, 1);
            if(m_current[i]!=cur[i])
            {
                 for(int j = 0; j < cur[i].size(); j++)
                 {
                    QString line = m_bubbles[i][j]->styleSheet();
                    if(line.contains("grey") || line.contains("white"))
                    {
                        c[j]=0;
                    }
                 }
            }
            count[c]++;
            p.push_back(c);
         }
         for(int i = 0; i < cur.size(); i++)
         {
             if(count[p[i]]%2!=0)
             {
                 bool c = false;
                 for(int j = 0; j < cur.size(); j++)
                 {
                     if(p[i]!=p[j])
                     {
                         int cnt1 = 0, cnt2 = 0;
                         for(int k = 0; k < cur.size(); k++)
                         {
                             if(p[i][k]==1)
                             {
                                 cnt1++;
                             }
                             if(p[j][k]==1)
                             {
                                 cnt2++;
                             }
                         }
                         if(cnt1>cnt2)
                         {
                             p[i]=p[j];
                             c=true;
                             break;
                         }
                         else{
                             p[j]=p[i];
                             c=true;
                             break;
                         }
                     }
                 }
                 if(c)
                     break;
             }
         }
         for(int i = 0; i < m_bubbles.size()-1; i++)
         {
             for(int j = 0; j < m_bubbles[i].size(); j++)
             {
                 QString line = m_bubbles[i][j]->styleSheet();
                 if(p[i][j]==0 && !line.contains("white") && !line.contains("grey"))
                 {
                     animateBlueToGrey(m_bubbles[i][j]);
                     m_state[i][j]=0;
                 }
             }
         }
         m_current=cur;
     }
     else{
         easySlote(m_n, 0);
     }
    }
    else{

        easySlote(m_n, 0);
    }
}

void MainWindow::impossibleSlote(int i, int j)
{

}
