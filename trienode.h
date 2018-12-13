#ifndef TRIENODE_H
#define TRIENODE_H
#include <iostream>
#include <string>
#include <tr1/unordered_map>
namespace std {
    using std::tr1::unordered_map;
}

using namespace std;

class TrieNode
{
public:
    TrieNode(){
        this->_num=0;
        this->_isWord=0;
        this->_kind=' ';
    }
    ~TrieNode(){}//销毁节点todo

    int _num;              //经过该节点的词数；如果是根节点，则填总词数
    int _isWord;          //标记该结点处是否构成单词,如果构成，那么写成词频
    string _kind;          //如果构成单词，标记该节点的词性
    std::unordered_map < string, TrieNode* > _words;
    //存储若干个子节点，可以通过下一个自直接查找到下一个节点
    //string类型中存储下一个自，下一个字每个都不一样，所以可以采用unordered_map来进行储存
    //TrieNode中存储下一个节点
};

typedef unordered_map<string,TrieNode*>::iterator it_word;
//这个迭代器用来遍历当前节点的所有子节点

#endif // TRIENODE_H
