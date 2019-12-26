# ChineseWordSegmentation

for 2018-2019 fall assignment 2 --Chinese word segmentation

以最简单的方式来考虑，采用最短路径的求解算法：
Dijkstra算法，计算一个节点到其他所有节点的最短路径。
采用有向图的方式保存输入的文字，每个字视为一个节点，如果形成词语，用弧连接，构造成有向无环图，弧上的权是词频取对数。然后寻找最短路径。

词和词频等信息已给在dict文件中，使用trie树来储存。

输入的文字保存之后需要查找里面所包含的所有词和相对应的词频，以便建立节点间的弧。建立弧的时候不能出现环。（这也是分词的要求）

总结 
2018/12/12 todo:
1. 保存词典dict 
https://segmentfault.com/a/1190000008877595    trie树的基本概念原理和实现
暂定第一版本使用hash tree来实现
https://www.cnblogs.com/chinxi/p/6130791.html    有参考
2. 查找并建立有向无环图
3. 最短路径

2018/12/15 done
已完成最初版本的分词功能

