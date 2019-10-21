#include <iostream>
#include <string>
#include <map>

#include "aho_corasic_search_funk.h"
#include "node.h"

using namespace std ;


int main() {
    int n;
    cout<<"enter a number of words:"<<endl;
    cin>>n;
    string word;
    map<int, string> wordlist = create_wordlist(n);
    string a;
    char c;
    cout<<"enter text and press 0: "<<endl;
    cin>>noskipws>>c;
    getline(cin, a, '0');
    node* thicket = create_thicket(wordlist);
    Aho_search(thicket, a);
    return 0;
}

// test
// 4
// wood chuck woodchuck would
// How much wood would a woodchuck chuck if a woodchuck could chuck wood?
//He would chuck, he would, as much as he could, and chuck as much wood
//As a woodchuck would if a woodchuck could chuck wood

