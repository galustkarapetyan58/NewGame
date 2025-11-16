#pragma once
#include <QMainWindow>

class QPushButton;
class QWidget;

class Select : public QMainWindow
{
    Q_OBJECT

public:
    explicit Select(QWidget *parent = nullptr);

signals:
    void selectModeSignal(int size);

public slots:
    void selectModeSlot(int size);
};
