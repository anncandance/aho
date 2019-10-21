#ifndef ALGOSY_NODE_H
#define ALGOSY_NODE_H

#include<vector>

struct node{
    char data;
    node* parent;
    bool accepting;         //конец ли слова
    std::vector<node*> children; // вектор ссылок на детей
    node* suff_link;        // суффиксная ссылка
    std::vector<node*> links;    // переходы

    // есть ли слово в боре, продолжающееся на s
    int child(char s);

    // проверка существования перехода по символу
    int link(char s);

    // конструктор узла
    node(char data, node *parent);
};


#endif //ALGOSY_NODE_H
