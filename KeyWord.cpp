#include "keyword.h"
KeyWord::KeyWord()
{
    dict.clear();
    dict["auto"]=1; dict["break"]=1; dict["case"]=1; dict["char"]=1; dict["const"]=1; dict["continue"]=1; dict["default"]=1; dict["do"]=1;
    dict["double"]=1; dict["else"]=1; dict["enum"]=1; dict["extern"]=1; dict["float"]=1; dict["for"]=1; dict["goto"]=1; dict["if"]=1;
    dict["int"]=1; dict["long"]=1; dict["register"]=1; dict["return"]=1; dict["short"]=1; dict["signed"]=1; dict["sizeof"]=1; dict["static"]=1;
    dict["struct"]=1; dict["switch"]=1; dict["typedef"]=1; dict["union"]=1; dict["unsigned"]=1; dict["void"]=1; dict["volatile"]=1; dict["while"]=1;
}
bool KeyWord::isKeyword(std::string word)
{
    return dict.find(word)!=dict.end();
}
void KeyWord::addKeyword(std::string word)
{
    dict[word]=1;
}