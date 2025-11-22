#include "GameLogic.h"
#include "MainWindow.h"
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <bits/stdc++.h>
#include <QTimer>
GameLogic::GameLogic(MainWindow* mainWindow): m_mainWindow(mainWindow) {
    m_bubbles=m_mainWindow->getBubbles();
    m_white = m_mainWindow->countOfWhite(), m_grey = m_mainWindow->countOfGrey();
}

bool GameLogic::ok()
{
    return m_mainWindow->isAllGrey();
}
void GameLogic::buttonPressedSlot(int i, int j){
    QString l = m_bubbles[i][j]->text();
    m_state = m_mainWindow->getState();
    if(m_white+m_grey!=(m_state.size()-1)*(m_state.size()-1))
    {
    if (m_state[i][j]) {
            emit gameSignal(i, j);
      }
    }
    else{
        if(l.contains("✔")){
            emit gameOverSignal();
     }
        else{
            emit gameSignal(i, j);
      }
    }
}

void GameLogic::gameIsEasySlot(int i, int j)
{
    QString l = m_bubbles[i][j]->text();
    m_state = m_mainWindow->getState();
    if(m_white+m_grey!=(m_state.size()-1)*(m_state.size()-1))
    {
        if (m_state[i][j]) {
            emit gameIsEasySignal(i, j);
        }
    }
    else{
        emit gameOverSignal();
    }
}

void GameLogic::gameIsMediumSlot(int i, int j)
{
    QString l = m_bubbles[i][j]->styleSheet();
    m_state = m_mainWindow->getState();
    if(m_white+m_grey!=(m_state.size()-1)*(m_state.size()-1))
    {
        if (m_state[i][j]) {
            emit gameIsMediumSignal(i, j);
        }
    }
    else{
        emit gameOverSignal();
    }
}

void GameLogic::gameIsHardSlot(int i, int j)
{
    QString l = m_bubbles[i][j]->styleSheet();
    m_state = m_mainWindow->getState();
    if(m_white+m_grey!=(m_state.size()-1)*(m_state.size()-1))
    {
        if (m_state[i][j]) {
            emit gameIsHardSignal(i, j);
        }
    }
    else{
        emit gameOverSignal();
    }
}

void GameLogic::gameIsImpossibleSlot(int i, int j)
{
    emit gameIsImpossibleSignal(i, j);
}
