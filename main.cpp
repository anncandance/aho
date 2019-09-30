#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std ;

map<int, string> create_wordlist(int n){
    map<int, string> wordlist;
    string word;
    for(int i=0; i<n; ++i){cin>>word; wordlist[i]=word;}
    return wordlist;
}

struct node{
    char data;
    node* parent;
    bool accepting;
    vector<node*> children; //массив ссылок на детей
    node* suff_link; //суффиксная ссылка

    int child(char s){
        for(int i=0; i<children.size(); ++i){if ((children[i])->data==s) return i;}
        return -1;
    };


    node(char data, node *parent):
    data(data),
    parent(parent),
    accepting(false),
    children(),
    suff_link(nullptr){};
};

node* create_thicket(map<int, string> wordlist){
    node* Root =  new node (' ', nullptr);
    node *v;
    Root->suff_link=Root;
    for(auto word : wordlist)
    {
        v = Root;
        for(int i=0; i<word.second.size(); ++i)
        {

            if (v->child((word.second)[i])==-1){node* chil = new node((word.second)[i], v);
                (*v).children.push_back(chil); v = chil;}
            else
            v = (v->children[v->child((word.second)[i])]);
        }
        v->accepting = true;
    }
    return Root;
}

node* get_transition(node* v, char c, node*root);

node* get_suffix_link(node* v, node* root){
    if((v->suff_link)==nullptr) {
        if (v->parent==root) v->suff_link = root; 
        else {
            v->suff_link = get_transition(get_suffix_link(v->parent, root), v->data, root);}}
    return v->suff_link;

}

node* get_transition(node* v, char c, node*root){
    if((v->child(c))==-1)  {
        if(v==root) return root;
        node* tmp =(get_transition(get_suffix_link(v, root), c, root));
        if (tmp==root) return root;
        (v->children.push_back(tmp));}
    return (v->children[v->child(c)]);
}

void Aho_search(node* root, string a){
    node* S = root;
    for(int i=0; i<a.size(); ++i){
        S = get_transition(S, a[i], root);
        if(S->accepting) cout<<i<<" "<<(*S).data;
    }
}


int main() {
    int n;
    cin>>n;
    string word;
    map<int, string> wordlist = create_wordlist(n);
    string a;
    getline(cin, a);
    node* thicket = create_thicket(wordlist);
    Aho_search(thicket, a);
    return 0;
}
