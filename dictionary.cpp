#include "dictionary.h"
#include "hashtrietree.h"
#include <iostream>
#include <fstream>
using namespace std;

Dictionary::Dictionary()
{
    this->_dict=new HashTrieTree;
}

Dictionary::~Dictionary()
{

}

int Dictionary::load(){
    string word;
    int weight;
    string kind;
    int count=0;
    ifstream fin("dict.txt");
    while(fin){
        fin>>word>>weight>>kind;
        if(weight){
            _dict->insert_node(word,weight,kind);
            count++;
        }
        weight=0;
    }
    return count;
}
