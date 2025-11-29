#include "GameLogic.h"
#include "MainWindow.h"
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <bits/stdc++.h>
#include <QTimer>

GameLogic::GameLogic(MainWindow* mainWindow): m_mainWindow(mainWindow) {
    m_bubbles=m_mainWindow->getBubbles();
    m_white = m_mainWindow->countOfWhite(), m_grey = m_mainWindow->countOfGrey();
}

bool GameLogic::ok()
{
    return m_mainWindow->isAllGrey();
}
void GameLogic::buttonPressedSlot(int i, int j)
{
    QString l = m_bubbles[i][j]->text();
    m_state = m_mainWindow->getState();

    if(!ok())
    {
        if (m_state[i][j]) {
            emit gameSignal(i, j);
        }
    }
    else
    {
        // 1. Check for Loss
        if(l.contains("✔")){
            emit gameOverSignal();
        }
        else{
            // 2. Process the move
            emit gameSignal(i, j);

            // 3. FIX: Check for Win immediately!
            // You need a function like isBoardFull() or checkWinCondition()
            if (ok())
            {
                emit gameOverSignal(); // Reuse the same signal, or create gameWonSignal()
            }
        }
    }
}

void GameLogic::gameIsEasySlot(int i, int j)
{
    QString l = m_bubbles[i][j]->text();
    m_state = m_mainWindow->getState();
    if(!ok())
    {
        if (m_state[i][j]) {
            emit gameIsEasySignal(i, j);
        }
    }
    else{
        emit gameOverSignal();
    }
}

void GameLogic::gameIsMediumSlot(int i, int j)
{
    QString l = m_bubbles[i][j]->styleSheet();
    m_state = m_mainWindow->getState();
    if(!ok())
    {
        if (m_state[i][j]) {
            emit gameIsMediumSignal(i, j);
        }
    }
    else{
        emit gameOverSignal();
    }
}

void GameLogic::gameIsHardSlot(int i, int j)
{
    QString l = m_bubbles[i][j]->styleSheet();
    m_state = m_mainWindow->getState();
    if(!ok())
    {
        if (m_state[i][j]) {
            emit gameIsHardSignal(i, j);
        }
    }
    else{
        emit gameOverSignal();
    }
}

void GameLogic::gameIsImpossibleSlot(int i, int j)
{
    QString l = m_bubbles[i][j]->styleSheet();
    m_state = m_mainWindow->getState();
    if(m_white+m_grey!=(m_state.size()-1)*(m_state.size()-1))
    {
        if (m_state[i][j]) {
            emit gameIsImpossibleSignal(i, j);
        }
    }
    else{
        emit gameOverSignal();
    }
}

void GameLogic::gameImpossibleBotTimeSlot()
{
    std::vector<std::vector<int>> cur = m_mainWindow->getCurBubbles();
    int m_n = m_mainWindow->getSize();
    bool allIsNotGreaterThanOne = true;
    int odd = 0;
    int countOfGreaterThanOne = 0;
    for(int i = 0; i < cur.size(); i++)
    {
        for(int j = 0; j < cur[i].size(); j++)
        {
            if(cur[i][j]>1)
            {
                allIsNotGreaterThanOne=false;
                countOfGreaterThanOne++;
            }
            if(cur[i][j]==1)
                odd++;
        }
    }
    if(allIsNotGreaterThanOne)
    {
        emit easyBotTime();
        return;
    }
    std::vector<std::pair<int, std::pair<int, int>>> pairs;
    for(int i = 0; i < cur.size(); i++)
    {
        for(int j = 0; j < cur[i].size(); j++)
        {
            std::pair<int, std::pair<int, int>> pai;
            pai={cur[i][j], {0, 0}};
            pairs.push_back(pai);
            for(int n = 0; n <= cur[i][j]; n++)
            {
                for(int m = n; m < cur[i][j]-n; m++)
                { std::pair<int, std::pair<int, int>> pair;
                    std::pair<int, int> p = {m, n};
                    pair = {cur[i][j], p};
                    pairs.push_back(pair);
                }
            }
        }
    }


    std::vector<std::vector<int>> current = cur;
    for(int i = 0; i < cur.size(); i++)
    {
        bool ok = false;
        for(int k = 0; k < cur[i].size(); k++)
        {
            int x = 0;
            bool p = false;
            for(int t = 0; t < pairs.size(); t++)
            {
                if(pairs[t].first==cur[i][k])
                {
                    int cnt = 0, c = 0;
                    if(pairs[t].second.first==1)
                        cnt++;
                    if(pairs[t].second.second==1)
                        cnt++;
                    if(cur[i][k]==1)
                        c++;
                    if((odd+cnt-c)%2!=0 && countOfGreaterThanOne==1 && cur[i][k]>1)
                    {
                        std::cout << "First" << std::endl;
                        cur[i][k]=pairs[t].second.first;
                        cur[i].insert(cur[i].begin()+k+1, pairs[t].second.second);
                        p=true;
                        break;
                    }
                }
            }
            if(p)
            {
                ok=true;
                break;
            }
        }
        if(ok)
            break;
    }
    std::vector<std::vector<int>> bubbles=m_mainWindow->getCurState();
    int ind = -1;
    for(int i = 0; i < cur.size(); i++)
    {

        int sum1 = 0, sum2 = 0;
        if(current[i]!=cur[i])
        {
            for(int x = 0; x < current[i].size(); x++)
            {
                sum1+=current[i][x];
            }
            for(int x = 0; x < cur[i].size(); x++)
            {
                sum2+=cur[i][x];
            }
            if(sum1!=sum2)
            {
                ind = i;
                break;
            }
        }
    }

    if(ind==-1)
    {
        for(int i = 0; i < cur.size(); i++)
        {

            bool ok = false;
            for(int k = 0; k < cur[i].size(); k++)
            {
                std::vector<int> po;
                int x = 0;
                for(int r = 0; r < cur.size(); r++)
                {
                    for(int l = 0; l < cur[r].size(); l++)
                    {
                        if(r==i)
                        {
                            if(l!=k)
                            {
                                po.push_back(cur[r][l]);
                                x^=cur[r][l];
                            }
                        }
                        else{
                            po.push_back(cur[r][l]);
                            x^=cur[r][l];
                        }
                    }
                }
                bool p = false;
                for(int t = 0; t < pairs.size(); t++)
                {
                    if(pairs[t].first==cur[i][k])
                    {
                        if((x^cur[i][k])!=0)
                        {
                            if(((x^pairs[t].second.first)^pairs[t].second.second)==0 && x!=pairs[t].second.second && x!=pairs[t].second.first)
                            {
                                std::cout << "Third" << std::endl;
                                for(int o = 0; o < po.size(); o++)
                                    std::cout << po[o] << " ";
                                std::cout << std::endl;
                                std::cout << std::endl;
                                cur[i][k]=pairs[t].second.first;
                                cur[i].insert(cur[i].begin()+k+1, pairs[t].second.second);
                                p=true;
                                break;
                            }
                        }
                        else{
                            emit easyBotTime();
                            return;
                        }
                    }
                }
                if(p)
                {
                    ok=true;
                    break;
                }
            }
            if(ok)
                break;
        }
    }
    for(int i = 0; i < cur.size(); i++)
    {
        int sum1 = 0, sum2 = 0;
        if(current[i]!=cur[i])
        {
            for(int x = 0; x < current[i].size(); x++)
            {
                sum1+=current[i][x];
            }
            for(int x = 0; x < cur[i].size(); x++)
            {
                sum2+=cur[i][x];
            }
            if(sum1!=sum2)
            {
                ind = i;
                break;
            }
        }
    }
    if(ind==-1)
    {
        for(int i = 0; i < cur.size(); i++)
        {

            bool ok = false;
            for(int k = 0; k < cur[i].size(); k++)
            {
                std::vector<int> po;
                int x = 0;
                for(int r = 0; r < cur.size(); r++)
                {
                    for(int l = 0; l < cur[r].size(); l++)
                    {
                        if(r==i)
                        {
                            if(l!=k)
                            {
                                po.push_back(cur[r][l]);
                                x^=cur[r][l];
                            }
                        }
                        else{
                            po.push_back(cur[r][l]);
                            x^=cur[r][l];
                        }
                    }
                }
                bool p = false;
                for(int t = 0; t < pairs.size(); t++)
                {
                    if(pairs[t].first==cur[i][k])
                    {
                        if((x^cur[i][k])!=0)
                        {
                            if(((x^pairs[t].second.first)^pairs[t].second.second)==0)
                            {
                                std::cout << "Third" << std::endl;
                                for(int o = 0; o < po.size(); o++)
                                    std::cout << po[o] << " ";
                                std::cout << std::endl;
                                std::cout << std::endl;
                                cur[i][k]=pairs[t].second.first;
                                cur[i].insert(cur[i].begin()+k+1, pairs[t].second.second);
                                p=true;
                                break;
                            }
                        }
                        else{
                            emit easyBotTime();
                            return;
                        }
                    }
                }
                if(p)
                {
                    ok=true;
                    break;
                }
            }
            if(ok)
                break;
        }
    }
    for(int i = 0; i < cur.size(); i++)
    {
        int sum1 = 0, sum2 = 0;
        if(current[i]!=cur[i])
        {
            for(int x = 0; x < current[i].size(); x++)
            {
                sum1+=current[i][x];
            }
            for(int x = 0; x < cur[i].size(); x++)
            {
                sum2+=cur[i][x];
            }
            if(sum1!=sum2)
            {
                ind = i;
                break;
            }
        }
    }
    if(ind==-1)
    {
        emit easyBotTime();
        return;
    }
    // Safety check for indices
    if(ind >= current.size() || ind >= cur.size()) return;

    int x = -1;
    for(int j = 0; j < std::min(cur[ind].size(), current[ind].size()); j++)
    {
        if(current[ind][j]!=cur[ind][j])
        {
            x=j;
            break;
        }
    }

    // Safety check for x
    if(x == -1 || x >= current[ind].size() || x >= cur[ind].size()) return;

    std::cout << ind+1 << std::endl;
    for(int j = 0; j < current[ind].size(); j++)
    {
        std::cout << current[ind][j] << " ";
    }
    std::cout << std::endl;
    for(int j = 0; j < cur[ind].size(); j++)
    {
        std::cout << cur[ind][j] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << x+1 << std::endl;
    std::cout << std::endl;

    int old = current[ind][x];
    int new1 = cur[ind][x];

    // Check if x+1 exists before accessing
    int new2 = 0;
    if(x+1 < cur[ind].size()) {
        new2 = cur[ind][x+1];
    }

    std::cout << new1 << " " << new2 << std::endl;
    std::cout << old << std::endl;
    std::cout << std::endl;
    int col = 0;
    int l = 0;
    int index = -1;

    // FIX: Use m_bubbles[ind].size() instead of m_n or assumption
    if(ind < m_bubbles.size()) {
        for(int j = 0; j < m_bubbles[ind].size(); j++)
        {
            QString line = m_bubbles[ind][j]->styleSheet();
            if(!line.contains("grey"))
            {
                int k = j;
                // FIX: Check range limit k < m_bubbles[ind].size()
                while(k < m_bubbles[ind].size() && !m_bubbles[ind][k]->styleSheet().contains("grey"))
                {
                    l++;
                    k++;
                }
                if(l==old)
                {
                    index=j-1;
                    break;
                }
                else{
                    l=0;
                }
            }
        }
    }
    int cnt = 0;

    while(cnt<=new1)
    {
        index++;
        cnt++;
    }
    std::cout << index+1 << std::endl;
    int length = old - new1 - new2;
    if(old==1)
        index++;

    // FIX: Check bounds for bubbles[ind]
    if(ind < bubbles.size()) {
        while(length!=0 && index < bubbles[ind].size())
        {
            if(bubbles[ind][index]!=0)
                length--;
            bubbles[ind][index]=0;
            index++;
        }
    }

    for(int i = 0; i < m_n && i < m_bubbles.size(); i++)
    {
        // FIX: Loop based on exact row size
        for(int j = 0; j < m_bubbles[i].size(); j++)
        {
            // Safety check for bubbles vector sync
            if(i < bubbles.size() && j < bubbles[i].size()) {
                if(bubbles[i][j]==0)
                {
                    emit animateToGreySignal(m_bubbles[i][j]);
                }
            }
        }
    }
}
