#pragma once
class MainWindow;
class Menu;
class GameLogic;

#include <QObject>


class MainController : public QObject
{
    Q_OBJECT
public:
    MainController();
    // void run();
private:
    void createMembers();
    void setupMembers();
    void makeConnections();


private:
    MainWindow* m_mainWindow = nullptr;
    Menu* m_menu = nullptr;
    GameLogic* m_gameLogic = nullptr;

};
