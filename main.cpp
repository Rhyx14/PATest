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
#define READ_INT(i) int i;scanf("%d",&i)
using namespace std;
int query_count,node_count;

struct node{
    int content;
    int lchild=-1;
    int rchild=-1;
}*tree;
int _index=-1;
unordered_set<int> _set;
void _insert(int key,int root){
    if(tree[root].content>tree[key].content){
        if(tree[root].lchild==-1)tree[root].lchild=key;
        else _insert(key,tree[root].lchild);
    }
    else{
        if(tree[root].rchild==-1)tree[root].rchild=key;
        else _insert(key,tree[root].rchild);
    }
}


void LCA(int a,int b){
    if(_set.find(a)==_set.end()&&_set.find(b)==_set.end()){
        printf("ERROR: %d and %d are not found.\n",a,b);
    }
    else if(_set.find(a)==_set.end()){
        printf("ERROR: %d is not found.\n",a);
    }
    else if(_set.find(b)==_set.end()){
        printf("ERROR: %d is not found.\n",b);
    }
    else{
        int d=0;
        int lca;
        while(1){
            if(a==tree[d].content ||b==tree[d].content){
                lca=tree[d].content;
                break;
            }
            if((a>tree[d].content && b<tree[d].content)||(a<tree[d].content && b>tree[d].content )){
                lca=tree[d].content;
                break;
            }

            if(a>tree[d].content&&b>tree[d].content){
                d=tree[d].rchild;
            }else{
                d=tree[d].lchild;
            }
        }
        if(lca==a){
            printf("%d is an ancestor of %d.\n",a,b);
        }
        else if(lca==b){
            printf("%d is an ancestor of %d.\n",b,a);
        }
        else{
            printf("LCA of %d and %d is %d.\n",a,b,lca);
        }
    }
}


int main()
{
   // freopen("data.txt","r",stdin);
    cin>>query_count>>node_count;
    tree=new node[node_count];

    int root=0;
    scanf("%d",&tree[0].content);
    _set.insert(tree[0].content);
    FOR(i,1,node_count){
        scanf("%d",&tree[i].content);
        _insert(i,root);
        _set.insert(tree[i].content);
    }

    FOR(i,0,query_count){
        READ_INT(a);
        READ_INT(b);
        LCA(a,b);
    }
	return 0;
}
