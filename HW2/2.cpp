#include<iostream>
#include<vector>
using namespace std;

int x;  // farthest node = leaf
void dfs_util(vector<vector<int>>& adjlist, vector<bool>& visit, int node, int len, int& mx){
    visit[node]=true;
    len++;
    for(int nd:adjlist[node]){
        if(!visit[nd]){
            if(len>mx){
                mx=len;
                x=nd;
            }
            dfs_util(adjlist, visit, nd, len, mx);
        }
    }
}
void dfs(vector<vector<int>>& adjlist, int n, int node, int& mx){
    vector<bool> visit(n,0);
    int len=0;
    dfs_util(adjlist, visit, node, len, mx);
}
int diameter(vector<vector<int>>& adjlist, int n){
    int mx=0;
    dfs(adjlist, n, 0, mx);     // dfs from a random node to find the longest path (the random node to leaf x)
    dfs(adjlist, n, x, mx);     // dfs from leaf x to find the longest path
    return mx;
}

int main(){
    int n_node;
    cin>>n_node;
    vector<vector<int>> adjlist(n_node);
    int dia=0;    // diameter

    // construct graph (adjancy list)
    for(int i=0;i<n_node-1;i++){
        int a, b;
        cin>>a>>b;
        a--, b--;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }

    // find diameter
    dia=diameter(adjlist, n_node);
    cout<<dia<<"\n";

    return 0;
}
