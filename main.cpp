#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<algorithm>
#include<math.h>
#include<regex>
#include<set>
#include<map>
#include<queue>
using namespace std;
struct book{
    int id;
    string title;
    string author;
    vector<string> keyword;
    string publisher;
    int year;
}*lis;

map<string,vector<int>> map_title;
map<string,vector<int>> map_author;
map<string,vector<int>> map_publisher;
map<string,vector<int>> map_keyword;
map<int,vector<int>> map_year;

void parser(int i,string &s){
    string tmp;
    int length=s.length();
    for(int j=0;j<length;j++){
        if(s[j]==' '){
            lis[i].keyword.push_back(tmp);
            map_keyword[tmp].push_back(lis[i].id);
            tmp.clear();
        }
        else{
            tmp+=s[j];
        }
    }
    if(tmp.length()!=0) map_keyword[tmp].push_back(lis[i].id);
    return;
}
int capacity;
void display(vector<int>& v){
    if(v.size()==0){
        printf("Not Found\n");
        return;
    }
    sort(v.begin(),v.end());
    for(auto &it:v){
        printf("%07d\n",it);
    }
}
int main()
{
    freopen("data.txt","r",stdin);
    cin>>capacity;
    getchar();
    lis=new book[capacity+1];
    for(int i=0;i<capacity;i++){
        cin>>lis[i].id;
        getchar();
        getline(cin,lis[i].title);
        map_title[lis[i].title].push_back(lis[i].id);

        getline(cin,lis[i].author);
        map_author[lis[i].author].push_back(lis[i].id);

        string s;
        getline(cin,s);
        parser(i,s);

        getline(cin,lis[i].publisher);
        map_publisher[lis[i].publisher].push_back(lis[i].id);


        cin>>lis[i].year;
        map_year[lis[i].year].push_back(lis[i].id);
    }

    int query_count;
    cin>>query_count;
    getchar();
    for(int i=0;i<query_count;i++){
        int _case;
        string s;
        getline(cin,s);
        _case=s[0]-'0';
        string s2=s.substr(3,100);
        switch(_case){
        case 1:
            printf("%s\n",s.c_str());
            display(map_title[s2]);
            break;
        case 2:
            printf("%s\n",s.c_str());
            display(map_author[s2]);
            break;
        case 3:
            printf("%s\n",s.c_str());
            display(map_keyword[s2]);
            break;
        case 4:
            printf("%s\n",s.c_str());
            display(map_publisher[s2]);
            break;
        case 5:
            printf("%s\n",s.c_str());
            display(map_year[atoi(s2.c_str())]);
            break;
        }
    }
    return 0;
}
