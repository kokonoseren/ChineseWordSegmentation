#include "wordsegmentation.h"
#include "ui_wordsegmentation.h"
#include "hashtrietree.h"
#include <stack>

using namespace std;

/*
WordSegmentation::WordSegmentation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WordSegmentation)
{
    ui->setupUi(this);
}

WordSegmentation::~WordSegmentation()
{
    delete ui;
}
*/
WordSegmentation::WordSegmentation(){
    this->_dict=new Dictionary;
    this->_dict->load();
}

WordSegmentation::~WordSegmentation(){
    delete _dict;
}

void WordSegmentation::show(){
    string sentence;
    cout<<"请输入待划分语句:"<<endl;
    cin>>sentence;

    double weight;
    string kind;
    /*
    this->_dict->get_dict()->search_node("应",weight,kind);
    cout<<"应"<<weight<<kind;
    this->_dict->get_dict()->search_node("该",weight,kind);
    cout<<"该"<<weight<<kind;
    this->_dict->get_dict()->search_node("应该",weight,kind);
    cout<<"应该"<<weight<<kind;
    */

    vector<string> chs;
    HashTrieTree::word_to_chs_GBK(sentence,chs);//将一个句子转化为一个一个字

    SentenceGraph graph(sentence,this->_dict->get_dict());
    //this->shortest_path(graph);
    stack<int> path;
    graph.shortest_cut(path);
    string sen_aft_cut;
    for(int i=0;i<chs.size();i++){
        if(path.size() && i==path.top()){
            sen_aft_cut=sen_aft_cut + '/' + chs[i];
            path.pop();
        }
        else {
            sen_aft_cut=sen_aft_cut + chs[i];
        }
    }
    cout<<sen_aft_cut<<endl;
}
