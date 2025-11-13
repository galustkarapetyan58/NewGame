#pragma once
class MainWindow;
class Menu;
class GameLogic;
class MenuLogic;
#include <QObject>
#include <QMainWindow>

class MainController : public QObject
{
    Q_OBJECT
public slots:

    void mainControllerSlot(int size);
public:
    MainController();
private:
    void createMembers();
    void makeConnections();


private:
    MainWindow* m_mainWindow=nullptr;
    Menu* m_menu=nullptr;
    GameLogic* m_gameLogic = nullptr;
    MenuLogic* m_menuLogic = nullptr;
    int m_n;
};
