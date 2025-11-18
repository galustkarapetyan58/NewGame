#pragma once
class MainWindow;
class Menu;
class GameLogic;
class MenuLogic;
class Select;
#include <QObject>
#include <QMainWindow>

class MainController : public QObject
{
    Q_OBJECT
public slots:

    void mainControllerSlot(int size);
    void mainEasySlote(int size);
    void mainMediumSlote(int size);
    void mainHardSlote(int size);
    void mainImpossibleSlote(int size);
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
    Select* m_select = nullptr;
    int m_n;
};
