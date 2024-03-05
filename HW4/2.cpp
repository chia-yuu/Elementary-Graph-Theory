#include<iostream>
#include<vector>
using namespace std;

int n_potion;
bool can_match(vector<vector<int>>& adjlist, int monster, vector<bool>& visit, vector<vector<int>>& match){
    for(int h:adjlist[monster]){
        if(!visit[h]){
            visit[h]=true;
            // printf("match[%d].size()=%d\n", h, match[h].size());
            if(match[h].size()==0){
                match[h].push_back(monster);
                return true;
            }
            if(match[h].size()==1 && n_potion>0){
                match[h].push_back(monster);
                n_potion--;
                return true;
            }
            else if(can_match(adjlist, match[h][0], visit, match)){
                match[h][0]=monster;
                return true;
            }
            else if(can_match(adjlist, match[h][1], visit, match)){
                match[h][1]=monster;
                return true;
            }
        }
    }
    return false;
}
int maxkill(vector<vector<int>>& adjlist, int n_hero, int n_monster){
    vector<vector<int>> match(n_hero);
    int ret=0;
    for(int i=0;i<n_monster;i++){
        vector<bool> visit(n_hero, false);
        if(can_match(adjlist, i, visit, match)){
            ret++;
        }
    }
    /*for(int i=0;i<n_hero;i++){
        cout<<i<<": ";
        for(int m:match[i]){
            cout<<m<<' ';
        }cout<<endl;
    }*/
    return ret;
}

int main(){
    int n_hero, n_monster;
    cin>>n_hero>>n_monster>>n_potion;
    vector<vector<int>> adjlist(n_monster);
    // construct graph
    for(int i=0;i<n_hero;i++){
        int t;
        cin>>t;
        for(int j=0;j<t;j++){
            int m;
            cin>>m;
            m--;
            adjlist[m].push_back(i);
        }
    }
    int ans=0;
    ans=maxkill(adjlist, n_hero, n_monster);
    cout<<ans<<endl;
    return 0;
}
