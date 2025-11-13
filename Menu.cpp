#include "Menu.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QAbstractButton>
#include "MainWindow.h"

int size = 0;
        Menu::Menu() {
            open_menu();
    }

    void Menu::open_menu()
    {
        m_window = new QWidget();
        m_newWindow = new QWidget();
        QGridLayout* layout = new QGridLayout();
        layout->setSpacing(10);
        layout->setContentsMargins(20,20,20,20);


        for(int i = 1; i <= m_n; i++) {
            m_members.push_back(i);
        }



        for(int i = 0; i < m_members.size(); i++) {
            QString s = QString::number(m_members[i]) + "P";
            QPushButton* btn = new QPushButton(s);


            btn->setFixedSize(80, 80);


            btn->setStyleSheet(
                "QPushButton {"
                "   background-color: #3498db;"
                "   color: white;"
                "   border-radius: 15px;"
                "   font-size: 18px;"
                "   font-weight: bold;"
                "}"
                "QPushButton:hover {"
                "   background-color: #2980b9;"
                "}"
                "QPushButton:pressed {"
                "   background-color: #1c5980;"
                "}"
                );

            m_buttons.push_back(btn);
        }
        m_allButtons.push_back(m_buttons);
        for(int i = 1; i <= m_count; i++)
        {
            QString s = QString::number(i);
            s+="x";
            s+=QString::number(i);
            QPushButton* btn = new QPushButton(s);
            btn->setFixedSize(80, 80);


            btn->setStyleSheet(
                "QPushButton {"
                "   background-color: #3498db;"
                "   color: white;"
                "   border-radius: 15px;"
                "   font-size: 18px;"
                "   font-weight: bold;"
                "}"
                "QPushButton:hover {"
                "   background-color: #2980b9;"
                "}"
                "QPushButton:pressed {"
                "   background-color: #1c5980;"
                "}"
                );

            m_newButtons.push_back(btn);
        }
        m_allButtons.push_back(m_newButtons);
        m_newButtons.clear();
        QPushButton* btn = new QPushButton("Start");
        btn->setFixedSize(80, 80);


        btn->setStyleSheet(
            "QPushButton {"
            "   background-color: red;"
            "   color: white;"
            "   border-radius: 15px;"
            "   font-size: 18px;"
            "   font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "   background-color: #ff6b6b;"
            "}"
            "QPushButton:pressed {"
            "   background-color: #e55a5a;"
            "}"
            );

        m_newButtons.push_back(btn);
        m_allButtons.push_back(m_newButtons);
        for(int i = 0; i < m_allButtons.size(); i++)
        {
            for(int j = 0; j < m_allButtons[i].size(); j++)
            {
                layout->addWidget(m_allButtons[i][j], i, j);
                connect(m_allButtons[i][j], &QPushButton::clicked, this, [=]()
                {
                  emit buttonIsPressedSignal(i, j);
                });
            }
        }
        m_window->setLayout(layout);
        m_window->setWindowTitle("Menu");
        m_window->show();
}

 void Menu::menuSlot(int i, int j)
    {
        if (m_allButtons[i][j] != nullptr)
        {
            QPushButton* btn = m_allButtons[i][j];
            QString s = btn->styleSheet();
            QString a = btn->text();

            if (s.contains("background-color: #3498db") || s.contains("background-color: red"))
            {
                if (s.contains("#3498db"))
                {
                    for(int x = 0; x <= 2; x++)
                    {
                        for(int y = 0; y < m_allButtons[x].size(); y++)
                        {
                            QString line = m_allButtons[x][y]->styleSheet();
                            if(m_allButtons[x][y]!=btn)
                            if(line.contains("background-color: white") && x==i)
                                {
                                    m_allButtons[x][y]->setStyleSheet(
                                        "QPushButton {"
                                        "   background-color: #3498db;"
                                        "   color: white;"
                                        "   border-radius: 15px;"
                                        "   font-size: 18px;"
                                        "   font-weight: bold;"
                                        "   border: 2px solid #3498db;"
                                        "   transition: all 0.2s ease;"
                                        "}"
                                        "QPushButton:hover {"
                                        "   background-color: #5dade2;"
                                        "   color: white;"
                                        "   box-shadow: 0px 0px 8px #5dade2;"
                                        "}"
                                        "QPushButton:pressed {"
                                        "   background-color: #1c5980;"
                                        "   color: white;"
                                        "}"
                                        );
                            }
                        }
                    }
                    btn->setStyleSheet(
                        "QPushButton {"
                        "   background-color: white;"
                        "   color: black;"
                        "   border-radius: 15px;"
                        "   font-size: 18px;"
                        "   font-weight: bold;"
                        "   border: 2px solid #3498db;"
                        "   transition: all 0.2s ease;"
                        "}"
                        "QPushButton:hover {"
                        "   background-color: #5dade2;"
                        "   color: white;"
                        "   box-shadow: 0px 0px 8px #5dade2;"
                        "}"
                        "QPushButton:pressed {"
                        "   background-color: #1c5980;"
                        "   color: white;"
                        "}"
                        );
                }
                else if (s.contains("red"))
                {
                    bool ok = false;
                    int cnt = 0;
                    for(int x = 0; x <= 1; x++)
                    {
                        bool good = false;
                        for(int y = 0; y < m_allButtons[x].size(); y++)
                        {
                          QString line = m_allButtons[x][y]->styleSheet();
                          if(line.contains("background-color: white"))
                          {
                              good = true;
                              break;
                          }
                        }
                        if(good)
                        {
                            cnt++;
                        }
                    }
                    if(cnt==2)
                        ok=true;
                    if(ok)
                    {
                    btn->setStyleSheet(
                        "QPushButton {"
                        "   background-color: white;"
                        "   color: black;"
                        "   border-radius: 15px;"
                        "   font-size: 18px;"
                        "   font-weight: bold;"
                        "   border: 2px solid #ff6b6b;"
                        "   transition: all 0.2s ease;"
                        "}"
                        "QPushButton:hover {"
                        "   background-color: #ff7f7f;"
                        "   color: white;"
                        "   box-shadow: 0px 0px 8px #ff7f7f;"
                        "}"
                        "QPushButton:pressed {"
                        "   background-color: #e55a5a;"
                        "   color: white;"
                        "}"
                      );
                    }
                }

                if (a.contains("x"))
                {
                    std::string c = a.toStdString();
                    size = c[0] - '0';
                }

                if (a.contains("Start"))
                {                    bool ok = false;
                    int cnt = 0;
                    for(int x = 0; x <= 1; x++)
                    {
                        bool good = false;
                        for(int y = 0; y < m_allButtons[x].size(); y++)
                        {
                            QString line = m_allButtons[x][y]->styleSheet();
                            if(line.contains("background-color: white"))
                            {
                                good = true;
                                break;
                            }
                        }
                        if(good)
                        {
                            cnt++;
                        }
                    }
                    if(cnt==2)
                        ok=true;
                    if(ok)
                    {
                    m_window->close();
                    emit startSignal(size);
                    }
                }
            }
            else{
                btn->setStyleSheet(
                    "QPushButton {"
                    "   background-color: #3498db;"
                    "   color: white;"
                    "   border-radius: 15px;"
                    "   font-size: 18px;"
                    "   font-weight: bold;"
                    "   border: 2px solid #3498db;"
                    "   transition: all 0.2s ease;"
                    "}"
                    "QPushButton:hover {"
                    "   background-color: #5dade2;"
                    "   color: white;"
                    "   box-shadow: 0px 0px 8px #5dade2;"
                    "}"
                    "QPushButton:pressed {"
                    "   background-color: #1c5980;"
                    "   color: white;"
                    "}"
                    );
            }
        }
    }

