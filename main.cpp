#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<queue>
#include<cmath>
#include<map>
#include<unordered_map>
#include<unordered_set>
#include<set>
#include<regex>
#define FOR(i,a,b) for( int i=(a);i<(b);++i)
#define MEMSET(arr,value,type,length) memset(arr,value,sizeof(type)*length)
#define MEMSET_0(arr,type,length) MEMSET(arr,0,type,length)
#define MEMSET_MIN(arr,type,length) MEMSET(arr,-0x3f,type,length)
#define MEMSET_MAX(arr,type,length) MEMSET(arr,0x3f,type,length)
#define READ_INT(i) int i;cin>>i
using namespace std;
int _count;

struct family{
    set<int,less<int> > member;
    double estate=0;
    double area=0;
    double avg_estate=0;
    double avg_area=0;
};
vector<family> li;

struct person{
    unordered_set<int> related;
    double estate=0;
    double area=0;
    bool vis=false;
};

unordered_map<int,person> id_map;
unordered_map<int,bool> vis_map;

bool cmp(family&a,family&b){
    if(a.avg_area==b.avg_area){
        return (*a.member.begin())<(*b.member.begin());
    }
    return a.avg_area>b.avg_area;
}


void dfs(int node,family&f){
    if(node==0)return;

    person &p=id_map[node];
    f.estate+=p.estate;
    f.area+=p.area;
    f.member.insert(node);

    vis_map[node]=true;

    for(auto &it:p.related){
        if(!vis_map[it])
         dfs(it,f);
    }
}


int main()
{
    freopen("data.txt","r",stdin);
    cin>>_count;

    FOR(i,1,_count+1){
        READ_INT(id);

        id++;
        person& p=id_map[id];
        READ_INT(a);
        READ_INT(b);
        if(a!=-1){
            a++;
            p.related.insert(a);
            id_map[a].related.insert(id);
        }
        if(b!=-1){
            b++;
            p.related.insert(b);
            id_map[b].related.insert(id);
        }

        READ_INT(c);
        FOR(j,0,c){
            READ_INT(tmp);
            tmp++;
            p.related.insert(tmp);
            id_map[tmp].related.insert(id);
        }
        cin>>p.estate>>p.area;
    }


    for(auto &it:id_map){
        if(vis_map[it.first])continue;
        family f;
        dfs(it.first,f);
        f.avg_area=f.area/f.member.size();
        f.avg_estate=f.estate/f.member.size();
        li.push_back(f);

    }


    sort(li.begin(),li.end(),cmp);

    printf("%d\n",li.size());
    for(auto &it:li){
        int len=it.member.size();
        printf("%04d %d %0.3f %.3f\n",
               (*it.member.begin())-1,len,
               it.avg_estate,it.avg_area);
    }
	return 0;
}




