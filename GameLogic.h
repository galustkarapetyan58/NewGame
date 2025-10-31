#pragma once
#include <QObject>

class GameLogic : public QObject
{
    Q_OBJECT
public:
    GameLogic();
public slots:
    void buttonPressedSlot(int i, int j);

};

