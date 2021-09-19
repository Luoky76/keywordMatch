#ifndef KEYWORD_H_
#define KEYWORD_H_

#include <bits/stdc++.h>
class KeyWord
{
    public:
    KeyWord();
    bool isKeyword(std::string word);
    void addKeyword(std::string word);

    private:
    std::unordered_map <std::string,int> dict;
};

#endif //KEYWORD_H_