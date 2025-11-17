#include "MainController.h"
#include "MainWindow.h"
#include "Menu.h"
#include "GameLogic.h"
#include "MenuLogic.h"

MainController::MainController() {

    createMembers();
    makeConnections();

}

void MainController::createMembers()
{

    m_menu = new Menu();
    m_menuLogic = new MenuLogic(m_menu);
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

void MainController::easySlote(int size)
{
    m_mainWindow=new MainWindow(size);
    m_gameLogic = new GameLogic(m_mainWindow);
    m_mainWindow->show();
}

void MainController::mediumSlote(int size)
{
    m_mainWindow=new MainWindow(size);
    m_gameLogic = new GameLogic(m_mainWindow);
    m_mainWindow->show();
}
void MainController::hardSlote(int size)
{
    m_mainWindow=new MainWindow(size);
    m_gameLogic = new GameLogic(m_mainWindow);
    m_mainWindow->show();
}
void MainController::impossibleSlote(int size)
{
    m_mainWindow=new MainWindow(size);
    m_gameLogic = new GameLogic(m_mainWindow);
    m_mainWindow->show();
}
void MainController::makeConnections(){
    connect(m_menu, &Menu::startSignal, this, &MainController::mainControllerSlot);
    connect(m_menu, &Menu::buttonIsPressedSignal, m_menuLogic, &MenuLogic::buttonIsPressedSlot);
    connect(m_menuLogic, &MenuLogic::menuLogicSignal, m_menu, &Menu::menuSlot);
    connect(m_menu, &Menu::easySignal, this, &MainController::easySlote);
    connect(m_menu, &Menu::mediumSignal, this, &MainController::mediumSlote);
    connect(m_menu, &Menu::hardSignal, this, &MainController::hardSlote);
    connect(m_menu, &Menu::impossibleSignal, this, &MainController::impossibleSlote);
}
