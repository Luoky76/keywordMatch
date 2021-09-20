#include "ifelsematch.h"
IfElseMatch::IfElseMatch()
{
    if_else_num_=0;
    double_if_else_num_=0;
    hasPreElse=false;
    hasPreIf=false;
    cnt=0;
}
IfElseMatch::~IfElseMatch() {}
void IfElseMatch::newWord(std::string word)
{
    if (word=="if")
    {
        if (hasPreElse)
        {
            hasPreElse=false;
        }
        else
        {
            //出现if且前面没有紧跟着的else，说明已经进入新的if-else段中
            if (!hasPreIf)  //上个if-else段以else作结尾
            {
                if (cnt>1) ++double_if_else_num_;
                else if (cnt==1) ++if_else_num_;     
            }
            cnt=0;
        }
        hasPreIf=true;
    }
    else if (word=="else")
    {
        ++cnt;
        hasPreIf=false;
        hasPreElse=true;
    }
}
void IfElseMatch::newPunctuation(char punctuation)
{
    if (punctuation!=' ' && punctuation!='\n') hasPreElse=false;
    if (punctuation=='{')
    {
        pushAllState();
    }
    else if (punctuation=='}')
    {
        if (!hasPreIf)  //遇到右括号时直接先统计当前的if-else if-else段
        {
            if (cnt>1) ++double_if_else_num_;
            else if (cnt==1) ++if_else_num_;     
        }
        popAllState();
    }
}
void IfElseMatch::pushAllState()
{
    statestack_.push(hasPreElse);
    statestack_.push(hasPreIf);
    statestack_.push(cnt);
    hasPreElse=false;
    hasPreIf=false;
    cnt=0;
}
void IfElseMatch::popAllState()
{
    cnt=statestack_.top(); statestack_.pop();
    hasPreIf=statestack_.top(); statestack_.pop();
    hasPreElse=statestack_.top(); statestack_.pop();
}
int IfElseMatch::get_if_else_num()
{
    return if_else_num_;
}
int IfElseMatch::get_double_if_else_num()
{
    return double_if_else_num_;
}
void IfElseMatch::clear()
{
    if_else_num_=0;
    double_if_else_num_=0;
    hasPreElse=false;
    hasPreIf=false;
    cnt=0;
}