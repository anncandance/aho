#include"node.h"

// есть ли слово в боре, продолжающееся на s
int node::child(char s){
        for(int i = 0; i < children.size(); ++i){
            if ((children[i]) -> data == s) return i;
        }
        return -1;
};

// проверка существования перехода по символу
int node::link(char s){
    for(int i = 0; i < links.size(); ++i)
        if(links[i] -> data == s) return i;
    return -1;
};

// конструктор узла
node::node(char data, node *parent):
data(data),
parent(parent),
accepting(false),
children(0),
suff_link(nullptr),
links(0){};
