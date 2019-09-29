#include <iostream>
#include <string>
#include <map>
using namespace std ;
//testing github on clion
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
    int n; //количество детей
    node* children; //массив детей
    node* suff_link; //суффиксная ссылка

    node& operator=(node const right){
        data=right.data;
        parent = right.parent;
        accepting = right.accepting;
        n = right.n;
        suff_link = right.suff_link;
        if (right.children==nullptr) children = nullptr;
        else{
        children = new node[n+1];
        for(int i=0; i<n; ++i){children[i] = right.children[i];}}
        return *this;
    }

    int child(char s){
        if(children==nullptr) return -1;
        for(int i=0; i<n; ++i){if (children[i].data==s) return i;}
        return -1;
    };


    node (const node& x): data(x.data),parent(x.parent), n(x.n),
                          accepting(x.accepting),
                          suff_link(x.suff_link)
    {if (x.children==nullptr) children=nullptr;
     else{
        children = new node [n+1];
        for(int i=0; i<n; ++i){children[i] = x.children[i];};}};


    void add_child(node c){
        if(children==nullptr){children = new node[n+1];}
        else {
            node* tmp = new node[n+1];
            for(int i=0; i<n; ++i){tmp[i] = children[i];}
            delete[]children;
            children = tmp;
        };
        children[n] = c;
        ++n;
        };


    node(char data=0, node* parent=nullptr):
    data(data),
    parent(parent),
    n(0),
    children(nullptr),
    accepting(false),
    suff_link(nullptr){};
};


node* create_thicket(map<int, string> wordlist){
    node* Root = new node (' ');
    Root->suff_link=Root;
    for(auto word : wordlist)
    {
        node *v = Root;
        for(int i=0; i<word.second.size(); ++i)
        {
            char c = (word.second)[i];
            if (v->child(c)==-1){node child (c, v);
            (*v).add_child(child);}
            v = &(v->children[v->child(c)]);
        }
        v->accepting = true;
    }
    //(*Root).print_child();
    return Root;
}

node* get_transition(node* v, char c, node*root);

node* get_suffix_link(node* v, node* root){
    if((v->suff_link)==nullptr) {
        if (v->parent==root) v->suff_link = root; //?
        else {
            v->suff_link = get_transition(get_suffix_link(v->parent, root), v->data, root);}}
    return v->suff_link;

}

node* get_transition(node* v, char c, node*root){
    if((v->child(c))==-1)  {
        if(v==root) return root;
        node* tmp =(get_transition(get_suffix_link(v, root), c, root));
        if (tmp==root) return root;
        (v->add_child(*tmp));}
    return &(v->children[v->child(c)]);
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
    map<int, string> wordlist = create_wordlist(n);
    string a;
    getline(cin, a);
    node *thicket = create_thicket(wordlist);
    Aho_search(thicket, a);
    return 0;
}
