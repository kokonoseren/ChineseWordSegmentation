void WordSegmentation::show(){
    string sentence;
    cout<<"请输入待划分语句:"<<endl;
    cin>>sentence;

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

