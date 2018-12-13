#include "wordsegmentation.h"
#include "hashtrietree.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    /*
    QApplication a(argc, argv);
    WordSegmentation w;
    w.show();
    */
    HashTrieTree HTT;
    string a="我",b="是",c="你",d="爸爸";
    HTT.insert_node(a,1,"wo");
    HTT.insert_node(b,2,"shi");
    HTT.insert_node(c,3,"ni");
    HTT.insert_node(d,4,"baba");
    int weight;
    string kind;
    HTT.search_node("爸爸",weight,kind);
    cout<<weight<<" "<<kind<<endl;
    //return a.exec();
    return 0;
}
