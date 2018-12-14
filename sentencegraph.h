#ifndef SENTENCEGRAPH_H
#define SENTENCEGRAPH_H
#include <vector>
#include <string>
#include <iostream>
#include <stack>
using namespace std;

class HashTrieTree;

//采用邻接表来储存有向无环图DAG
typedef struct arc_node{//弧节点储存词语的信息，
    int _adj_vex;
    struct arc_node *_next_arc;
    string _word;
    double _weight;
    string _kind;
}ArcNode;

typedef struct {
    int pos;//pos的范围0~n
    ArcNode *first_arc;
}VexNode;

class SentenceGraph//以有向无环图DAG的结构来存储
{
public:
    SentenceGraph();//建立一个空图
    SentenceGraph(const string &Sentence, HashTrieTree *T);//根据一个
    ~SentenceGraph();//销毁一个图

    void shortest_cut(stack<int> &path);
private:
    vector<VexNode> _vex;//储存图的顶点,寻找每个
    int _vex_num;//整个句子中的顶点数
    int _arc_num;//整个句子中的可能的划分的词语数
};

#endif // SENTENCEGRAPH_H
