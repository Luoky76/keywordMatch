#ifndef IFELSEMATCH_H_
#define IFELSEMATCH_H_

#include <bits/stdc++.h>
class IfElseMatch
{
    public:
    IfElseMatch();
    ~IfElseMatch();
    int get_if_else_num();
    int get_double_if_else_num();
    void clear(); //清除所有数据

    //插入一个可能是if或else的新单词
    void newWord(std::string word);

    //插入一个符号，可能影响if else的连接，或是需要状态压栈
    void newPunctuation(char punctuation);

    private:
    std::stack <int> statestack_;   //栈，用于保存状态
    void pushAllState();    //把所有状态入栈
    void popAllState();     //把所有状态出栈
    int if_else_num_;           //if-else数量
    int double_if_else_num_;    //if-else if-else数量
    bool hasPreElse;  //记录上一个单词是否为else且与现单词之间均为空字符
    bool hasPreIf;    //记录上一个if/else单词是否是if
    int cnt;              //记录有几个连续的if-else if-else
};

#endif //IFELSEMATCH_H_