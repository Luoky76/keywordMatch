#include <bits/stdc++.h>//这是多行注释
using namespace std;
priority_queue <int,vector<int>,greater<int> > minp;
/*this is
int
hhhh
*/
int main()
{
    int n,k;
    while(scanf("%d %d",&n,&k)!=EOF){
        while(!minp.empty()){
            minp.pop();
        }
        char c;
        int x;
        for(int i=0;i<n;i++){
            getchar();
            scanf("%c",&c);
            if(c=='\n') c=getchar();
            if(c=='I'){
                scanf("%d",&x);
                if(minp.size()<k) minp.push(x);
                else if(minp.top()<x){
                    minp.push(x);
                    minp.pop();
                }
            }else if(c=='Q'){
                printf("/*%d\n",minp.top());
            }
        }
    }
    switch ()
    {}
    return 0;
}