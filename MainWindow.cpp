#include "MainWindow.h"

#include <QWidget>
#include <QPushButton>
#include <QApplication>
#include <QGridLayout>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLayout>
#include <QObject>
#include <QString>
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{

    createMembers();
    setupMembers();

}


void MainWindow::createMembers(){
    // m_window = new QWidget();
    m_grid = new QGridLayout();
    m_mainline = new QVBoxLayout();
}

void MainWindow::setupMembers(){
    m_grid->setSpacing(8);
    m_grid->setContentsMargins(10, 10, 10, 10);
    int row = m_n, col = m_n;
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            QPushButton* btn = new QPushButton(".");
            btn->setFixedSize(60, 60);
            btn->setStyleSheet("background-color: lightblue; font-size: 20px; border-radius: 30px;");
            m_grid->addWidget(btn, i, j);
            m_row.push_back(btn);
        }
        m_bubbles.push_back(m_row);
        m_row.clear();
    }
    QPushButton* btn = new QPushButton("✔");
    btn->setStyleSheet("background-color: red; font-size: 20px; border-radius: 30px;");
    m_grid->addWidget(btn, row, col);
    m_row.push_back(btn);
    m_bubbles.push_back(m_row);
    m_row.clear();
    m_mainline->addLayout(m_grid);
    this->setLayout(m_mainline);
}

void MainWindow::makeConnections(){

        // for(int i = 0; i < m_bubbles.size(); ++i)
        // {
        //     for(int j = 0; j < m_bubbles[i].size(); ++j)
        //     {
        //         QPushButton* btn = m_bubbles[i][j];
        //         connect(btn, &QPushButton::pressed, this, &GameLogic::receiveSignal);
        //     }
        // }

}
