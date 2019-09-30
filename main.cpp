#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std ;


// штука для хранения набора слов
map<int, string> create_wordlist(int n){
    map<int, string> wordlist;
    string word;
    cout<<"enter words and press Enter: "<<endl;
    for(int i=0; i<n; ++i){cin>>word; wordlist[i]=word;}
    return wordlist;
}

struct node{

    char data;
    node* parent;
    bool accepting;
    vector<node*> children; // вектор ссылок на детей
    node* suff_link;        // суффиксная ссылка
    vector<node*> links;    // переходы

    // есть ли слово в боре, продолжающееся на s
    int child(char s){
        for(int i=0; i<children.size(); ++i){if ((children[i])->data==s) return i;}
        return -1;};


    // проверка существования перехода по символу
    int link(char s){
        for(int i=0; i<links.size(); ++i) if(links[i]->data==s) return i;
        return -1;}

    // конструктор узла
    node(char data, node *parent):
    data(data),
    parent(parent),
    accepting(false),
    children(0),
    suff_link(nullptr),
    links(0){};
};


    // как бы роща
node* create_thicket(map<int, string> wordlist){
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


    // далее  все по рецепту
node* get_transition(node* v, char c, node*root);

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

void print(node *S, node*root){
    node *v=S;
    if(v!=root){print(v->parent, root); cout<<v->data;}

    }

void Aho_search(node* root, string a){
    node* S = root;
    for(int i=0; i<a.size(); ++i){
        S = get_transition(S, a[i], root);
        if (S->accepting) {cout<<i<<": "; print(S, root); cout<<endl;}
}}


int main() {
    int n;
    cout<<"enter a number of words:"<<endl;
    cin>>n;
    string word;
    map<int, string> wordlist = create_wordlist(n);
    string a;
    char c;
    cout<<"enter text and press 0 at the end: "<<endl;
    cin>>noskipws>>c;
    getline(cin, a, '0');
    node* thicket = create_thicket(wordlist);
    Aho_search(thicket, a);
    return 0;
}
