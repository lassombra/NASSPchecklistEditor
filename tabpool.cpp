#include "tabpool.h"

TabPool::TabPool(QWidget *parent)
    : QWidget{parent}
{

}

EditorTab *TabPool::getTab()
{
    if (currentIndex == tabs.length()) {
        tabs << new EditorTab(this);
    }
    EditorTab* tab = tabs[currentIndex];
    currentIndex++;
    return tab;
}

void TabPool::releaseAllTabs()
{
    currentIndex = 0;
}
