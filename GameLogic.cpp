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

    int white = m_mainWindow->countOfWhite(), grey = m_mainWindow->countOfGrey();
    m_state = m_mainWindow->getState();
    if(!ok() && white+grey!=(m_state.size()-1)*(m_state.size()-1))
    {
    if (m_state[i][j]) {
        emit gameSignal(i, j);

      }
    }
    else{
        m_mainWindow->close();
        QVBoxLayout* layout = new QVBoxLayout();
        QString line = m_bubbles[m_bubbles.size()-1][0]->styleSheet();
        QLabel* label;
        QString edit = "";
        if(line.contains("background-color: white"))
        {
            edit = "Congratulations, Player1, You Have Won";
            label = new QLabel(edit);
            label->setAlignment(Qt::AlignCenter);
            label->setStyleSheet("font-size: 18px; color: blue;");
        }
        else{
            edit = "Congratulations, Player2, You Have Won";
            label = new QLabel(edit);
            label->setAlignment(Qt::AlignCenter);
            label->setStyleSheet("font-size: 18px; color: red;");
        }
        QWidget* window = new QWidget;
        layout->addWidget(label);
        window->setLayout(layout);
        window->show();
    }
}
