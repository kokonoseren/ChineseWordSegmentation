#include "sentencegraph.h"
#include "hashtrietree.h"
#include <malloc.h>

SentenceGraph::SentenceGraph()
{
    this->_vex_num=0;
    this->_arc_num=0;
}

SentenceGraph::~SentenceGraph()
{

}

SentenceGraph::SentenceGraph(const string &Sentence,HashTrieTree *T){
    vector<string> chs;
    HashTrieTree::word_to_chs(Sentence,chs);//将一个句子转化为一个一个字
    this->_arc_num=0;
    this->_vex_num=chs.size();
/*
 * 这里放弃使用迭代器进行访问，而采用数组下标来访问string和vector主要是因为
 * node->first_arc->adj_vex的类型是 int 型，直接使用数组下标来访问比较方便
    vector<string>::iterator it_chs;
    it_chs=chs.begin();

    for(;it_chs!=chs.end();it_chs++){
        string possible_word;
        vector<string>::iterator it_after_chs=it_chs;

        VexNode *node=new VexNode;//要插入的顶点节点
        for(;it_after_chs!=chs.end();it_after_chs++){//对于chs里的每一个字，寻找它能和后续的字构成的可能词语
            possible_word+=*it_after_chs;
            int weight;
            string kind;
            T.search_node(possible_word,weight,kind);

            node->ch=*it_chs;//初始化顶点节点的字，不更改它的弧信息
            node->first_arc=new ArcNode(NULL);

            if(weight<INT_MAX && node->first_arc==NULL){//如果构成词语，则更改它的弧信息
                node->first_arc->kind=kind;
                node->first_arc->_adj_vex=it_after_chs;
            }

        }
        this->_vex.push_back(*node);
        delete node;
        possible_word.clear();
        //todo 函数：从某个字到某个字的词语如果是存在的，那么就返回这个词语的信息
        //todo 函数：然后根据信息 在这两个字之间建立弧
    }

*/
    for(unsigned int i=0;i<chs.size();i++){
        string possible_word;

        VexNode *node=new VexNode;//要插入的顶点节点

        node->ch=chs[i];//初始化顶点节点的字，不更改它的弧信息
        node->first_arc=NULL;
        //接下来寻找它的弧
        for(unsigned int j=i;j<chs.size();j++){//对于chs里的每一个字，寻找它能和后续的字构成的可能词语
            possible_word+=chs[j];
            int weight=INT_MAX;
            string kind;
            T->search_node(possible_word,weight,kind);

            if(weight<INT_MAX && node->first_arc==NULL){//如果构成词语，则更改它的弧信息
                ArcNode *newNode=new ArcNode;
                newNode->kind=kind;
                newNode->_adj_vex=j;
                newNode->_weight=weight;
                newNode->_next_arc=NULL;
                node->first_arc=newNode;
                this->_arc_num++;
            }
            else if(weight<INT_MAX && node->first_arc!=NULL){//如果构成词语，并且已经有第一条弧
                ArcNode *temp=node->first_arc;
                while(temp->_next_arc!=NULL){
                    temp=temp->_next_arc;
                }
                ArcNode *newNode=new ArcNode;
                newNode->kind=kind;
                newNode->_adj_vex=j;
                newNode->_weight=weight;
                newNode->_next_arc=NULL;
                temp->_next_arc=newNode;
                this->_arc_num++;
            }
        }

        this->_vex.push_back(*node);//插入节点

        //销毁与重置工作
        delete node;
        node=NULL;
        possible_word.clear();
    }
}
