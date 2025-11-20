#include "GameLogic.h"
#include "MainWindow.h"
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
GameLogic::GameLogic(MainWindow* mainWindow): m_mainWindow(mainWindow) {
    m_bubbles=m_mainWindow->getBubbles();
}

bool GameLogic::ok()
{
    return m_mainWindow->isAllGrey();
}
void GameLogic::buttonPressedSlot(int i, int j){
    QString l = m_bubbles[i][j]->text();
    int white = m_mainWindow->countOfWhite(), grey = m_mainWindow->countOfGrey();
    m_state = m_mainWindow->getState();
    if(!ok() && white+grey!=(m_state.size()-1)*(m_state.size()-1))
    {
    if (m_state[i][j]) {
            emit gameSignal(i, j);
      }
    }
    else{
        if(l.contains("✔")){
        m_mainWindow->close();
        QVBoxLayout* layout = new QVBoxLayout();
        QLabel* label;
        QLabel* label1 = m_mainWindow->getLabel();
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
        else{
            emit gameSignal(i, j);
    }
    }
}

void GameLogic::gameIsEasySlot(int i, int j)
{
    int white = m_mainWindow->countOfWhite(), grey = m_mainWindow->countOfGrey();
    m_state = m_mainWindow->getState();
    if(!ok() && white+grey!=(m_state.size()-1)*(m_state.size()-1))
    {
        if (m_state[i][j]) {
            emit gameIsEasySignal(i, j);
        }
    }
    else{
        m_mainWindow->close();
        QVBoxLayout* layout = new QVBoxLayout();
        QLabel* label;
        QLabel* label1 = m_mainWindow->getLabel();
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
}

void GameLogic::gameIsMediumSlot(int i, int j)
{
    int white = m_mainWindow->countOfWhite(), grey = m_mainWindow->countOfGrey();
    m_state = m_mainWindow->getState();
    if(!ok() && white+grey!=(m_state.size()-1)*(m_state.size()-1))
    {
        if (m_state[i][j]) {
            emit gameIsMediumSignal(i, j);
        }
    }
    else{
        m_mainWindow->close();
        QVBoxLayout* layout = new QVBoxLayout();
        QLabel* label;
        QLabel* label1 = m_mainWindow->getLabel();
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
}

void GameLogic::gameIsHardSlot(int i, int j)
{
    emit gameIsHardSignal(i, j);
}

void GameLogic::gameIsImpossibleSlot(int i, int j)
{
    emit gameIsImpossibleSignal(i, j);
}
