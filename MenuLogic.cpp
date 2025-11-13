#include "MenuLogic.h"
#include "Menu.h"


MenuLogic::MenuLogic(Menu* menu): m_menu(menu){
    m_buttons = m_menu->getButtons();
    m_state.resize(m_buttons.size());
    for (int i = 0; i < m_buttons.size(); ++i)
        m_state[i].resize(m_buttons[i].size(), 0);
}
void MenuLogic::buttonIsPressedSlot(int i, int j)
{
    emit menuLogicSignal(i, j);
}
