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
bool checkDiv(std::string& s,int& i)   //用部分符号切割单词
{
	if (s[i]=='"')   //忽略字符串
	{
		for (i=i+1;i<s.size();i++)
		{
			if (s[i]=='"') return true;
		}
		while (getline(std::cin,s))
		{
			for (i=0;i<s.size();i++)
			{ 
				if (s[i]=='"') return true;
			}		
		}
	}
	if (s[i]=='/' && i+1<s.size() && s[++i]=='*')  //忽略注释
	{
		for (i=i+1;i<s.size();i++)
		{
			if (s[i]=='*' && s[++i]=='/') return true;
		}
		while (getline(std::cin,s))
		{
			for (i=0;i<s.size();i++)
			{ 
				if (s[i]=='*' && i+1<s.size() && s[++i]=='/') return true;
			}		
		}
	}
    return s[i]==' ' || s[i]=='\n' || s[i]==';' || s[i]=='(' || s[i]==')' || s[i]=='{' || s[i]=='}' || s[i]=='<' || s[i]=='>' || s[i]==',' || s[i]==':';
}
void calc()
{
    KeyWord keyWord;
    bool hasPreSwitch=false; //防止出现一个switch都没有的情况而误统计
    int curCaseNum=0;
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
int main(int mode,char* filename[])
{
    std::ios::sync_with_stdio(false);

    freopen("in.cpp","r",stdin);
    freopen("out.txt","w",stdout);

    std::cout<<mode<<std::endl;
    for (int i=0;i<strlen(filename[0]);++i) std::cout<<filename[0][i];
    std::cout<<std::endl;

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
                        if (!hasPreIf)  //上个if-else段不以if作结尾
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
    std::cout<<"total num: "<<totalNum<<std::endl;
    std::cout<<"swich num: "<<switchNum<<std::endl;
    std::cout<<"case num:";
    for (int i:caseNum) std::cout<<" "<<i;
    std::cout<<std::endl;
    std::cout<<"if-else num: "<<if_else_num<<std::endl;
    std::cout<<"if-else if-else num: "<<double_if_else_num<<std::endl;
    fclose(stdin);
    fclose(stdout);
}