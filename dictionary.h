#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class HashTrieTree;

class Dictionary
{
public:
    Dictionary();
    ~Dictionary();
    int load();
    HashTrieTree *get_dict();
private:
    HashTrieTree *_dict;
};

#endif // DICTIONARY_H
