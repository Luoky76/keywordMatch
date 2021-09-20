#ifndef KEYWORDMATCH_H_
#define KEYWORDMATCH_H_

#include <bits/stdc++.h>
class KeywordMatch
{
    public:
    KeywordMatch(char *filename);
    ~KeywordMatch();
    void printAns(int mode); //根据完成等级输出答案

    private:
    std::vector <std::string> allwords_;  //储存切割后的所有单词
    std::stack <int> sta;   //栈，用于保存状态
    int totalNum_;  //文本总关键词数量
    int switchNum_; //文本swich数量
    std::vector <int> caseNum_; //每个switch下的case数量
    int if_else_num_;   //if-else数量
    int double_if_else_num_;    //if-else if-else数量

    //忽略字符串，忽略成功时 s[idx]=='"'，即字符串的结尾，同时返回true
    bool ignoreString(std::string &s,int &idx);

    //忽略多行注释，忽略成功时 s[idx]=='/'，即多行注释的结尾，同时返回true
    bool ignoreMultiAnnotation(std::string &s,int &idx);

    //忽略单行注释，忽略成功时 s[idx] 为单行注释的最后一个字符，同时返回true
    bool ignoreSingleAnnotation(std::string &s,int &idx);

    bool checkDiv(char c); //判断字符c是否为特殊字符，以此决定是否需要切割单词
    void calc(); //统计关键词个数
};

#endif //KEYWORDMATCH_H_