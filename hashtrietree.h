#ifndef HASHTRIETREE_H
#define HASHTRIETREE_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TrieNode;

class HashTrieTree
{
public:
    HashTrieTree();//构造一个空树
    ~HashTrieTree();//销毁一个数
    static void word_to_chs_UTF8(const string & word, vector<string> & chs);//把中文词语分成一个一个字
    static void word_to_chs_GBK(const string & word, vector<string> & chs);//把中文词语分成一个一个字
    void search_node(const string & word, double &weight, string &kind);//查找一个单词是否存在
    void insert_node(const string & word, const double &weight, const string &kind);//插入节点

private:
    TrieNode *_root;//根节点的指针
};

#endif // HASHTRIETREE_H
