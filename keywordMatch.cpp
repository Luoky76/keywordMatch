#include "keywordmatch.h"
#include "keyword.cpp"
KeywordMatch::KeywordMatch(char *filename)
{
    freopen(filename,"r",stdin);
    bool hasPreElse=false;  //记录上一个单词是否为else且与现单词之间均为空字符
    bool hasPreIf=false;    //记录上一个if/else单词是否是if
    int cnt=0;              //记录有几个连续的if-else if-else
    std::string subs;       //用于暂存单个单词
    std::string s;          //用于读入一整行字符串

    totalNum_=0;
    switchNum_=0;
    if_else_num_=0;
    double_if_else_num_=0;

    while (getline(std::cin,s))
    {
        for (int i=0;i<s.size();++i)
        {
            //若出现了字符串或注释则应切割，出现特殊字符也应切割
            if (ignoreString(s,i) || ignoreMultiAnnotation(s,i) || ignoreSingleAnnotation(s,i) || checkDiv(s[i]))
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
                            if (cnt>1) ++double_if_else_num_;
                            else if (cnt==1) ++if_else_num_;     
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
                    allwords_.push_back(subs);
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
                        if (cnt>1) ++double_if_else_num_;
                        else if (cnt==1) ++if_else_num_;     
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
    fclose(stdin);
}
KeywordMatch::~KeywordMatch() {}
bool KeywordMatch::ignoreString(std::string &s,int &idx)
{
    if (s[idx]=='"')
	{
		for (idx=idx+1;idx<s.size();++idx)
		{
			if (s[idx]=='"') return true;
		}
		getline(std::cin,s);
        for (idx=0;idx<s.size();++idx)
		{
			if (s[idx]=='"') return true;
		}
	}
    return false;
}
bool KeywordMatch::ignoreMultiAnnotation(std::string &s,int &idx)
{
    if (s[idx]=='/' && idx+1<s.size() && s[++idx]=='*')
	{
		for (idx=idx+1;idx+1<s.size();++idx)
		{
			if (s[idx]=='*' && s[++idx]=='/') return true;
		}
		getline(std::cin,s);
		for (idx=0;idx+1<s.size();++idx)
		{ 
			if (s[idx]=='*' && s[++idx]=='/') return true;
		}
	}
    return false;
}
bool KeywordMatch::ignoreSingleAnnotation(std::string &s,int &idx)
{
    if (s[idx]=='/' && idx+1<s.size() && s[++idx]=='/')
	{
		idx=s.size();
        return true;
	}
    return false;
}
bool KeywordMatch::checkDiv(char c)
{
    //逐个判断字符c是否为切割单词的符号
    bool flag;
    flag=c==' ' || c=='\n' || c==';' || c=='(' || c==')';
    flag|=c=='{' || c=='}' || c=='<' || c=='>' || c==',' || c==':';
    flag|=c=='*' || c=='/';
    return flag;
}
void KeywordMatch::calc()
{
    KeyWord keyWord;
    bool hasPreSwitch=false; //记录是否已经找到了某个switch，防止出现一个switch都没有的情况而误统计
    int curCaseNum=0;   //记录某个switch下的case个数
    for (std::string it:allwords_)
    {
        if (keyWord.isKeyword(it)) ++totalNum_;
        if (it=="case") ++curCaseNum;
        else if (it=="switch")
        {
            ++switchNum_;
            if (hasPreSwitch) caseNum_.push_back(curCaseNum);
            curCaseNum=0;
            hasPreSwitch=true;
        }
    }
    if (hasPreSwitch) caseNum_.push_back(curCaseNum);
}
void KeywordMatch::printAns(int mode)
{
    if (mode>=1) std::cout<<"total num: "<<totalNum_<<std::endl;
    if (mode>=2)
    {
        std::cout<<"swich num: "<<switchNum_<<std::endl;
        std::cout<<"case num:";
        for (int i:caseNum_) std::cout<<" "<<i;
        std::cout<<std::endl;
    }
    if (mode>=3) std::cout<<"if-else num: "<<if_else_num_<<std::endl;
    if (mode>=4) std::cout<<"if-else if-else num: "<<double_if_else_num_<<std::endl;
}
int main(int x,char* arg[])
{
    std::ios::sync_with_stdio(false);
    char s[10];
    strcpy(s,"in.cpp");
    KeywordMatch keywordMatch(s);
    keywordMatch.printAns(4);
    return 0;
}