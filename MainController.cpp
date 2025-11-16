#include "MainController.h"
#include "MainWindow.h"
#include "Menu.h"
#include "GameLogic.h"
#include "MenuLogic.h"
#include "Select.h"

MainController::MainController() {

    createMembers();
    makeConnections();

}

void MainController::createMembers()
{

    m_menu = new Menu();
    m_menuLogic = new MenuLogic(m_menu);
    m_select = new Select();
}

void MainController::mainControllerSlot(int size)
{
    m_mainWindow=new MainWindow(size);
    m_gameLogic = new GameLogic(m_mainWindow);
    connect(m_gameLogic, &GameLogic::gameSignal,
            m_mainWindow, &MainWindow::mainWindowSlot);
    connect(m_mainWindow, &MainWindow::buttonPressedSignal,
            m_gameLogic, &GameLogic::buttonPressedSlot);
    m_mainWindow->show();
}

void MainController::onePlayerSlot(int size)
{

}

void MainController::makeConnections(){
    connect(m_menu, &Menu::startSignal, this, &MainController::mainControllerSlot);

    connect(m_menu, &Menu::buttonIsPressedSignal, m_menuLogic, &MenuLogic::buttonIsPressedSlot);
    connect(m_menuLogic, &MenuLogic::menuLogicSignal, m_menu, &Menu::menuSlot);
    connect(m_select, &Select::selectModeSignal, this, &MainController::onePlayerSlot);
    connect(m_menu, &Menu::onePlayerSignal, m_select, &Select::selectModeSlot);
}
