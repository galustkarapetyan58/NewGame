#include "MainController.h"
#include "MainWindow.h"
#include "Menu.h"
#include "GameLogic.h"

#include <iostream>

MainController::MainController() {

    createMembers();
    setupMembers();
    makeConnections();

}

void MainController::createMembers()
{
    m_mainWindow = new MainWindow;
    m_menu = new Menu;
    m_gameLogic = new GameLogic;


}

void MainController::setupMembers()
{
    m_mainWindow->show();


}

void MainController::makeConnections(){
    connect(m_mainWindow,&MainWindow::buttonPressedSignal,
            m_gameLogic,&GameLogic::buttonPressedSlot);

}



    // QPushButton* btn = qobject_cast<QPushButton*>(sender());
    // if(btn!=nullptr)
    // {
    //     QString s = btn->text();
    //     if(s==".")
    //     {
    //         QString style = btn->styleSheet();
    //         QString state = m_bubbles[m_n][0]->styleSheet();
    //         if(m_index==-1)
    //         {
    //             for(int i = 0; i < m_bubbles.size(); ++i)
    //             {
    //                 for(int j = 0; j < m_bubbles[i].size(); ++j)
    //                 {
    //                     if(m_bubbles[i][j]==btn)

    //                     {
    //                         m_index=i;
    //                         break;
    //                     }
    //                 }
    //             }
    //         }
    //         bool ok = true, good = false;
    //         for(int i = 0; i < m_bubbles.size(); ++i)
    //         {
    //             for(int j = 0; j < m_bubbles[i].size(); ++j)
    //             {
    //                 QString o = m_bubbles[i][j]->styleSheet();
    //                 if(o.contains("white"))
    //                 {
    //                     good=true;
    //                     break;
    //                 }
    //             }
    //         }
    //         for(int i = 0; i < m_bubbles.size(); ++i)
    //         {
    //             for(int j = 0; j < m_bubbles[i].size(); ++j)
    //             {
    //                 QString o = m_bubbles[i][j]->styleSheet(), p = btn->styleSheet();
    //                 if(m_bubbles[i][j]==btn && m_index==i)
    //                 {
    //                     ok=false;
    //                     break;
    //                 }
    //             }
    //         }
    //         if(!ok)
    //         {
    //             if(style.contains("white"))
    //                 btn->setStyleSheet("background-color: lightblue; font-size: 20px; border-radius: 30px;");
    //             else{
    //                 btn->setStyleSheet("background-color: white; font-size: 20px; border-radius: 30px;");
    //             }
    //         }
    //     }
    //     else{
    //         m_index=-1;
    //         QString style = btn->styleSheet();
    //         if(style.contains("white"))
    //             btn->setStyleSheet("background-color: red; font-size: 20px; border-radius: 30px;");
    //         else{
    //             btn->setStyleSheet("background-color: white; font-size: 20px; border-radius: 30px;");
    //         }
    //     }
    // }


// void MainController::run() {
//     m_window->show();
// }
