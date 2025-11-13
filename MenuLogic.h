#pragma once
#include <QObject>
class QString;
class Menu;
class QWidget;
class QPushButton;
class MenuLogic:public QObject
{
    Q_OBJECT
signals:
    void menuLogicSignal(int i, int j);
 public slots:
    void buttonIsPressedSlot(int i, int j);
public:
    explicit MenuLogic(Menu* menu);
private:
    Menu* m_menu;
     QVector<QVector<QPushButton*>> m_buttons;
    std::vector<std::vector<bool>> m_state;
};
