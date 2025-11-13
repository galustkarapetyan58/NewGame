#include "GameLogic.h"
#include "MainWindow.h"
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
GameLogic::GameLogic(MainWindow* mainWindow): m_mainWindow(mainWindow) {
    m_bubbles=m_mainWindow->getBubbles();
}



void GameLogic::buttonPressedSlot(int i, int j){

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
    if(!ok){
    m_state = m_mainWindow->getState();
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
