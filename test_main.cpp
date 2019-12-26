#include "wordsegmentation.h"
//#include "hashtrietree.h"
#include "dictionary.h"
#include "sentencegraph.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    /*
    QApplication a(argc, argv);
    WordSegmentation w;
    w.show();
    */
    //return a.exec();
    Dictionary dict;
    dict.load();
    string a("我的梦想是成为你爸爸");
    SentenceGraph g(a,dict.get_dict());
    return 0;
}

//dict一共有109750个词条
