#include "keyword.h"
KeyWord::KeyWord()
{
    //设置关键词字典的初始关键词
    dict_.clear();
    dict_["auto"]=1; dict_["break"]=1; dict_["case"]=1; dict_["char"]=1;
    dict_["const"]=1; dict_["continue"]=1; dict_["default"]=1; dict_["do"]=1;
    dict_["double"]=1; dict_["else"]=1; dict_["enum"]=1; dict_["extern"]=1;
    dict_["float"]=1; dict_["for"]=1; dict_["goto"]=1; dict_["if"]=1;
    dict_["int"]=1; dict_["long"]=1; dict_["register"]=1; dict_["return"]=1;
    dict_["short"]=1; dict_["signed"]=1; dict_["sizeof"]=1; dict_["static"]=1;
    dict_["struct"]=1; dict_["switch"]=1; dict_["typedef"]=1; dict_["union"]=1;
    dict_["unsigned"]=1; dict_["void"]=1; dict_["volatile"]=1; dict_["while"]=1;
}
bool KeyWord::isKeyword(std::string word)
{
    return dict_.find(word)!=dict_.end();
}
void KeyWord::addKeyword(std::string word)
{
    dict_[word]=1;
}