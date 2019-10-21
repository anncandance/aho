#ifndef ALGOSY_AHO_CORASIC_SEARCH_H
#define ALGOSY_AHO_CORASIC_SEARCH_H

#include <string>
#include <map>
#include <vector>
#include "node.h"



// штука для хранения набора слов
std::map<int, std::string> create_wordlist(int n);


// как бы бор
node* create_thicket(std::map<int, std::string> wordlist);

//далее все по рецепту:
node* get_transition(node* v, char c, node*root);

node* get_suffix_link(node* v, node* root);

void Aho_search(node* root, std::string a);

// и вывод
void print(node *S, node*root);


#endif