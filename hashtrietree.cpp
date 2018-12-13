#include "hashtrietree.h"
#include "trienode.h"

HashTrieTree::HashTrieTree()
{
    this->_root=new TrieNode;
}

HashTrieTree::~HashTrieTree()
{
    delete _root;
}

void HashTrieTree::word_to_chs(const string & word, vector<string> & chs)
{
      int wordLen=word.size();
      int i=0;
      while(i<wordLen)
      {
          int size=1;
          if(word[i] & 0x80)
          {
             char temp = word[i];
             temp <<= 1;
             do{
                 temp <<= 1;
                 ++size;
             }while(temp & 0x80);
         }
         string subWord=word.substr(i, size);
         chs.push_back(subWord);
         i += size;
     }
 }

void HashTrieTree::insert_node(const string & word, const int &weight, const string &kind){
    //对要插入的词进行处理
    vector<string> chs;
    word_to_chs(word,chs);//把中文词语变为单个字

    vector<string>::iterator it_chs;//词语迭代器
    it_chs=chs.begin();
    TrieNode *curr=_root;//将当前指针置为根指针
    for(;it_chs!=chs.end();it_chs++){
        it_word itWord;//子节点的迭代器
        itWord=curr->_words.find(*it_chs);//在当前节点所指向的字中找到
                                      //当前输入词语的迭代器所指向的string型的字符

        if(itWord==curr->_words.end()){//如果没找到就添加到当前节点的子节点中
            pair<string,TrieNode*>temp;
            temp.first=*it_chs;//string赋值为这个字
            TrieNode *node=new TrieNode;//新建子节点

            if(it_chs==chs.end()-1){//如果要插入的是这个词的最后一个字
                node->_isWord=weight;
                node->_kind=kind;
            }

            temp.second=node;
            curr->_words.insert(temp);//插入到子节点的map中去

            curr=node;//从子节点开始继续新建
        }
        else{
            curr=itWord->second;//如果找到了那么就继续往下走
        }
    }
}

void HashTrieTree::search_node(const string &word, int &weight, string &kind){
    //对要查找的词进行处理
    vector<string> chs;
    word_to_chs(word,chs);//把中文词语变为单个字

    vector<string>::iterator it_chs;
    it_chs=chs.begin();
    TrieNode *curr=_root;//将当前指针置为根指针

    for(;it_chs!=chs.end();it_chs++){
        it_word itWord;//子节点的迭代器
        itWord=curr->_words.find(*it_chs);//在当前节点所指向的字中找到
                                      //当前输入词语的迭代器所指向的string型的字符
        if(itWord==curr->_words.end()){//没找到
            weight=INT_MAX;
            kind.clear();
        }
        else if(itWord->second->_isWord){//在根节点上
            weight=itWord->second->_isWord;
            kind=itWord->second->_kind;
            curr=itWord->second;//保证如果这个词语的前缀也是词语，那么还可以继续往后走，更新curr
        }
        else {
            curr=itWord->second;
        }
    }
}
