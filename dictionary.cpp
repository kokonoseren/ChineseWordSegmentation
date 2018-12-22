#include "dictionary.h"
#include "hashtrietree.h"
#include <iostream>
#include <fstream>
#include <cmath>
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
    double weight;
    string kind;
    int count=0;
    ifstream fin("dict.txt");
    while(fin){
        fin>>word>>weight>>kind;

        //weight=log(weight);

        if(weight){
            _dict->insert_node(word,weight,kind);
            count++;
        }

        weight=0;
    }
    return count;
}

HashTrieTree * Dictionary::get_dict(){
    return this->_dict;
}
