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

void MainController::mainEasySlote(int size)
{
    m_mainWindow=new MainWindow(size);
    m_gameLogic = new GameLogic(m_mainWindow);
    connect(m_mainWindow, &MainWindow::buttonPressedSignal,
            m_gameLogic, &GameLogic::gameIsEasySlot);
    connect(m_gameLogic, &GameLogic::gameIsEasySignal, m_mainWindow, &MainWindow::easySlote);
    m_mainWindow->show();
}

void MainController::mainMediumSlote(int size)
{
    m_mainWindow=new MainWindow(size);
    m_gameLogic = new GameLogic(m_mainWindow);
    connect(m_mainWindow, &MainWindow::buttonPressedSignal,
            m_gameLogic, &GameLogic::gameIsMediumSlot);
    connect(m_gameLogic, &GameLogic::gameIsMediumSignal, m_mainWindow, &MainWindow::mediumSlote);
    m_mainWindow->show();
}
void MainController::mainHardSlote(int size)
{
    m_mainWindow=new MainWindow(size);
    m_gameLogic = new GameLogic(m_mainWindow);
    connect(m_mainWindow, &MainWindow::buttonPressedSignal,
            m_gameLogic, &GameLogic::gameIsHardSlot);
    connect(m_gameLogic, &GameLogic::gameIsHardSignal, m_mainWindow, &MainWindow::hardSlote);
    m_mainWindow->show();
}
void MainController::mainImpossibleSlote(int size)
{
    m_mainWindow=new MainWindow(size);
    m_gameLogic = new GameLogic(m_mainWindow);
    connect(m_mainWindow, &MainWindow::buttonPressedSignal,
            m_gameLogic, &GameLogic::gameIsImpossibleSlot);
    connect(m_gameLogic, &GameLogic::gameIsImpossibleSignal, m_mainWindow, &MainWindow::impossibleSlote);
    m_mainWindow->show();
}

void MainController::makeConnections(){
    connect(m_menu, &Menu::startSignal, this, &MainController::mainControllerSlot);
    connect(m_menu, &Menu::buttonIsPressedSignal, m_menuLogic, &MenuLogic::buttonIsPressedSlot);
    connect(m_menuLogic, &MenuLogic::menuLogicSignal, m_menu, &Menu::menuSlot);
    connect(m_menu, &Menu::easySignal, this, &MainController::mainEasySlote);
    connect(m_menu, &Menu::mediumSignal, this, &MainController::mainMediumSlote);
    connect(m_menu, &Menu::hardSignal, this, &MainController::mainHardSlote);
    connect(m_menu, &Menu::impossibleSignal, this, &MainController::mainImpossibleSlote);
    connect(m_gameLogic, &GameLogic::gameOverSignal, m_mainWindow, &MainWindow::gameOverSlot);
}
