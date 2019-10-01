#include "aho_corasic_search_funk.h"
#include "node.h"
#include <iostream>

std::map<int, std::string> create_wordlist(int n) {
    std::map<int, std::string> wordlist;
    std::string word;
    std::cout << "enter words and press Enter: " << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cin >> word;
        wordlist[i] = word;
    }
    return wordlist;
}


node* create_thicket(std::map<int, std::string> wordlist){
    node* Root =  new node (' ', nullptr);
    node* v;
    Root->suff_link=Root;
    for(auto word : wordlist){
        v = Root;
        for(int i=0; i<word.second.size(); ++i){
            if (v->child((word.second)[i])==-1){
                node* chil = new node((word.second)[i], v);
                (*v).children.push_back(chil); v = chil;}
            else
                v = (v->children[v->child((word.second)[i])]);}
        v->accepting = true;}
    return Root;
}

node* get_suffix_link(node* v, node* root) {
    if ((v->suff_link) == nullptr) {
        if (v->parent == root)
            v->suff_link = root;
        else {
            v->suff_link = get_transition(get_suffix_link(v->parent, root), v->data, root);
        }
    }
    return v->suff_link;
}

node* get_transition(node* v, char c, node*root){
    if(((v->child(c))==-1)&&(v->link(c)==-1))  {
        if(v==root) return root;
        node* tmp =(get_transition(get_suffix_link(v, root), c, root));
        v->links.push_back(tmp);
        return tmp;};
    if(v->child(c)!=-1) return v->children[v->child(c)];
    return (v->links[v->link(c)]);
}

void Aho_search(node* root, std::string a){
    node* S = root;
    for(int i=0; i<a.size(); ++i){
        S = get_transition(S, a[i], root);
        if (S->accepting) {std::cout<<i<<": "; print(S, root); std::cout<<std::endl;}
    }}

void print(node *S, node*root){
    node *v=S;
    if(v!=root){print(v->parent, root); std::cout<<v->data;}
}


