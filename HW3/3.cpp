#include<iostream>
#include<vector>
using namespace std;

void root_dfs(vector<vector<int>>& adjlist, vector<int>& visit, vector<int>& leaf, vector<int>& parent, vector<int>& height, int cur, int h){
    visit[cur]=true;
    if(h>height[0]){height[0]=h;}
    if(adjlist[cur].size()==1){leaf.push_back(cur);}
    for(int nd : adjlist[cur]){
        if(!visit[nd]){
            parent[nd]=cur;
            root_dfs(adjlist, visit, leaf, parent, height, nd, h+1);
        }
    }
}
void leaf_dfs(vector<int>& parent, vector<int>& visit, vector<int>& height, int cur, int h){
    height[cur]=max(height[cur], h);
    visit[cur]=true;
    if(cur==0){return;} // root
    leaf_dfs(parent, visit, height, parent[cur], h+1);
}
void get_height(vector<int>& parent, vector<int>& leaf, vector<int>& height){
    vector<int> visit(height.size(), 0);
    for(int nd:leaf){
        leaf_dfs(parent, visit, height, nd, 0);
    }
}

int main(){
    int n;
    cin>>n;
    vector<vector<int>> adjlist(n);
    vector<int> leaf, parent(n, -2), height(n, 0), visit(n, false);
    for(int i=0;i<n-1;i++){
        int a, b;
        cin>>a>>b;
        a--, b--;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }
    root_dfs(adjlist, visit, leaf, parent, height, 0, 0);
    get_height(parent, leaf, height);
    for(int i=0;i<n;i++){
        cout<<height[i]<<" "<<parent[i]+1<<endl;
    }

    return 0;
}

/*
dfs from root : find parent and root height and leaves
dfs from leaves : find height
*/
