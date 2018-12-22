#include "sentencegraph.h"
#include "hashtrietree.h"
#include <malloc.h>
#include <queue>
using namespace std;
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
    HashTrieTree::word_to_chs_GBK(Sentence,chs);//将一个句子转化为一个一个字
    this->_arc_num=0;
    this->_vex_num=chs.size()+1;
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

        node->pos=i;//初始化顶点节点的字，不更改它的弧信息,pos=1表示这个节点在第一个字之前
        ArcNode *newNode1=new ArcNode;
        newNode1->_adj_vex=i+1;
        newNode1->_weight=INT_MAX;
        newNode1->_next_arc=NULL;
        node->first_arc=newNode1;
        //接下来寻找它的弧
        for(unsigned int j=i;j<chs.size();j++){//对于chs里的每一个字，寻找它能和后续的字构成的可能词语
            possible_word+=chs[j];
            double weight=INT_MAX;
            string kind;
            T->search_node(possible_word,weight,kind);

            if(weight<INT_MAX && j==i){//如果构成词语，则更改它的弧信息
                ArcNode *newNode=new ArcNode;
                newNode->_kind=kind;
                newNode->_adj_vex=j+1;
                newNode->_weight=weight;
                newNode->_next_arc=NULL;
                newNode->_word=possible_word;
                node->first_arc=newNode;
                this->_arc_num++;
            }
            else if(weight<INT_MAX && j!=i){
                ArcNode *temp=node->first_arc;
                while(temp->_next_arc!=NULL){
                    temp=temp->_next_arc;
                }
                ArcNode *newNode=new ArcNode;
                newNode->_kind=kind;
                newNode->_adj_vex=j+1;
                newNode->_weight=weight;
                newNode->_next_arc=NULL;
                newNode->_word=possible_word;
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
    VexNode *node=new VexNode;//要插入的顶点节点

    node->pos=chs.size()+1;//初始化顶点节点的字，不更改它的弧信息,pos=0表示这个节点在第一个字之前
    node->first_arc=NULL;
    this->_vex.push_back(*node);
    delete node;
    node=NULL;
}

void SentenceGraph::shortest_cut(stack<int> &path){
    //todo直接实现n-最短路径？
    queue<int> vex_nodes;
    int pre_record[this->_vex_num]={0};
    int dist[this->_vex_num];//最大概率路径数组
    dist[0]=0;
    for(int i=1;i<this->_vex_num;i++){
        dist[i]=INT_MAX;
    }
    //第0个节点_vex[0]
    ArcNode *p=new ArcNode;
    p=this->_vex[0].first_arc;
    while(p){
        dist[p->_adj_vex]=p->_weight;
        //dist[p->_adj_vex]=1;
        vex_nodes.push(p->_adj_vex);
        p=p->_next_arc;
    }

    //处理后面的节点
    while(!vex_nodes.empty()){
        int pre_vex=vex_nodes.front();
        vex_nodes.pop();
        if(pre_vex==this->_vex_num-1)//最后一个节点的first_arc是
            continue;
        p=this->_vex[pre_vex].first_arc;
        while(p){
            if(dist[p->_adj_vex] > (dist[pre_vex] + p->_weight)){
                dist[p->_adj_vex] = dist[pre_vex] + p->_weight;
                pre_record[p->_adj_vex]=pre_vex;
                vex_nodes.push(p->_adj_vex);
            }
            p=p->_next_arc;
        }
    }

    int k=1;
    int m=this->_vex_num-1;
    while(k){
        k=pre_record[m];
        if(k)path.push(k);
        m=k;
    }
}

void SentenceGraph::shortest_cut(stack<int> &path){
    //todo直接实现n-最短路径？
    queue<int> vex_nodes;
    int pre_record[this->_vex_num]={0};
    int dist[this->_vex_num];//最大概率路径数组
    dist[0]=0;
    for(int i=1;i<this->_vex_num;i++){
        dist[i]=INT_MAX;
    }
    //第0个节点_vex[0]
    ArcNode *p=new ArcNode;
    p=this->_vex[0].first_arc;
    while(p){
        dist[p->_adj_vex]=p->_weight;
        //dist[p->_adj_vex]=1;
        vex_nodes.push(p->_adj_vex);
        p=p->_next_arc;
    }

    //处理后面的节点
    while(!vex_nodes.empty()){
        int pre_vex=vex_nodes.front();
        vex_nodes.pop();
        if(pre_vex==this->_vex_num-1)//最后一个节点的first_arc是
            continue;
        p=this->_vex[pre_vex].first_arc;
        while(p){
            if(dist[p->_adj_vex] > (dist[pre_vex] + p->_weight)){
                dist[p->_adj_vex] = dist[pre_vex] + p->_weight;
                pre_record[p->_adj_vex]=pre_vex;
                vex_nodes.push(p->_adj_vex);
            }
            p=p->_next_arc;
        }
    }

    int k=1;
    int m=this->_vex_num-1;
    while(k){
        k=pre_record[m];
        if(k)path.push(k);
        m=k;
    }
}
