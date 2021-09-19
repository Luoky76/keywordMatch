#include <bits/stdc++.h>
#include "keyword.cpp"
std::vector <std::string> vec;
std::string s,subs;
std::stack <int> sta;
int totalNum;
int switchNum;
std::vector <int> caseNum;
int if_else_num;
int double_if_else_num;
bool ignoreString(std::string &s,int &idx)   //忽略字符串
{
    if (s[idx]=='"')
	{
		for (idx=idx+1;idx<s.size();++idx)
		{
			if (s[idx]=='"') return true;
		}
		while (getline(std::cin,s))
		{
			for (idx=0;idx<s.size();++idx)
			{
				if (s[idx]=='"') return true;
			}
		}
	}
    return false;
}
bool ignoreAnnotation(std::string &s,int &idx)    //忽略注释
{
    if (s[idx]=='/' && idx+1<s.size() && s[++idx]=='*')
	{
		for (idx=idx+1;idx<s.size();++idx)
		{
			if (s[idx]=='*' && s[++idx]=='/') return true;
		}
		while (getline(std::cin,s))
		{
			for (idx=0;idx<s.size();++idx)
			{ 
				if (s[idx]=='*' && idx+1<s.size() && s[++idx]=='/') return true;
			}		
		}
	}
    return false;
}
bool checkDiv(std::string &s,int &idx)   //用部分符号切割单词，同时忽略注释和字符串
{
    //忽略字符串和注释
	if (ignoreString(s,idx)) return true;
	if (ignoreAnnotation(s,idx)) return true;

    //用特殊字符切割单词
    bool flag;
    flag=s[idx]==' ' || s[idx]=='\n' || s[idx]==';' || s[idx]=='(' || s[idx]==')';
    flag|=s[idx]=='{' || s[idx]=='}' || s[idx]=='<' || s[idx]=='>' || s[idx]==',' || s[idx]==':';
    return flag;
}
void calc()
{
    KeyWord keyWord;
    bool hasPreSwitch=false; //记录是否已经找到了某个switch，防止出现一个switch都没有的情况而误统计
    int curCaseNum=0;   //记录某个switch下的case个数
    for (std::string it:vec)
    {
        if (keyWord.isKeyword(it)) ++totalNum;
        if (it=="case") ++curCaseNum;
        else if (it=="switch")
        {
            ++switchNum;
            if (hasPreSwitch) caseNum.push_back(curCaseNum);
            curCaseNum=0;
            hasPreSwitch=true;
        }
    }
    if (hasPreSwitch) caseNum.push_back(curCaseNum);
}
void printAns(int mode) //根据完成等级输出答案
{
    if (mode>=1) std::cout<<"total num: "<<totalNum<<std::endl;
    if (mode>=2)
    {
        std::cout<<"swich num: "<<switchNum<<std::endl;
        std::cout<<"case num:";
        for (int i:caseNum) std::cout<<" "<<i;
        std::cout<<std::endl;
    }
    if (mode>=3) std::cout<<"if-else num: "<<if_else_num<<std::endl;
    if (mode>=4) std::cout<<"if-else if-else num: "<<double_if_else_num<<std::endl;
}
int main(int x,char* arg[])
{
    std::ios::sync_with_stdio(false);
    freopen(arg[1],"r",stdin);

    bool hasPreElse=false;  //记录上一个单词是否为else且与现单词之间均为空字符
    bool hasPreIf=false;    //记录上一个if/else单词是否是if
    int cnt=0;  //记录有几个连续的if-else if-else
    while (getline(std::cin,s))
    {
        s=' '+s+' ';
        subs.clear();
        for (int i=1;i<s.size();++i)
        {
            if (checkDiv(s,i))
            { 
                if (subs=="if")
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
                            if (cnt>1) ++double_if_else_num;
                            else if (cnt==1) ++if_else_num;     
                        }
                        cnt=0;
                    }
                    hasPreIf=true;
                }
                else if (subs=="else")
                {
                    ++cnt;
                    hasPreIf=false;
                    hasPreElse=true;
                }

                if (s[i]!=' ' && s[i]!='\n') hasPreElse=false;

                if (subs.size()>0)
                {
                    vec.push_back(subs);
                    subs.clear();
                }

                if (s[i]=='{')
                {
                    sta.push(hasPreElse);
                    sta.push(hasPreIf);
                    sta.push(cnt);
                    hasPreElse=false;
                    hasPreIf=false;
                    cnt=0;
                }
                else if (s[i]=='}')
                {
                    if (!hasPreIf)  //遇到右括号时直接先统计当前的if-else if-else段
                    {
                        if (cnt>1) ++double_if_else_num;
                        else if (cnt==1) ++if_else_num;     
                    }
                    cnt=sta.top(); sta.pop();
                    hasPreIf=sta.top(); sta.pop();
                    hasPreElse=sta.top(); sta.pop();
                }
            }
            else subs+=s[i];
        }
    }
    calc();
    printAns(atoi(arg[2]));
    fclose(stdin);
}