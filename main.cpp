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
    cout<<"enter text and press 0 at the end: "<<endl;
    cin>>noskipws>>c;
    getline(cin, a, '0');
    node* thicket = create_thicket(wordlist);
    Aho_search(thicket, a);
    return 0;
}
