#include "keyword.h"
KeyWord::KeyWord()
{
    //设置关键词字典的初始关键词
    dict_.clear();
    dict_.insert("auto"); dict_.insert("break"); dict_.insert("case"); dict_.insert("char");
    dict_.insert("const"); dict_.insert("continue"); dict_.insert("default"); dict_.insert("do");
    dict_.insert("double"); dict_.insert("else"); dict_.insert("enum"); dict_.insert("extern");
    dict_.insert("float"); dict_.insert("for"); dict_.insert("goto"); dict_.insert("if");
    dict_.insert("int"); dict_.insert("long"); dict_.insert("register"); dict_.insert("return");
    dict_.insert("short"); dict_.insert("signed"); dict_.insert("sizeof"); dict_.insert("static");
    dict_.insert("struct"); dict_.insert("switch"); dict_.insert("typedef"); dict_.insert("union");
    dict_.insert("unsigned"); dict_.insert("void"); dict_.insert("volatile"); dict_.insert("while");
}
bool KeyWord::isKeyword(std::string word)
{
    return dict_.find(word)!=dict_.end();
}
void KeyWord::addKeyword(std::string word)
{
    if (dict_.find(word)==dict_.end()) dict_.insert(word);
}
void KeyWord::deleteKeyword(std::string word)
{
    if (dict_.find(word)!=dict_.end()) dict_.erase(word);
}