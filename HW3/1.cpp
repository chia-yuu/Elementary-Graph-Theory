// AC, long long sum, include<climits>
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;

int findp(int x, vector<int>& parent){
    return x==parent[x]? x : (parent[x]=findp(parent[x], parent));
}
void joint(int x, int y, vector<int>& parent){
    parent[findp(x, parent)]=findp(y, parent);
}
static bool cmp(vector<int> &a, vector<int> &b){
    if(a[2]!=b[2]){return a[2]<b[2];}
    else{return a[0]<b[0];}
}

int main(){
    int n_testcase;
    cin>>n_testcase;
    while(n_testcase--){
        // read input
        int n, m, mincost=INT_MAX, minidx=-1;
        long long sum=0;
        cin>>n>>m;
        vector<int> node_cost(n, 0), parent(n);
        vector<vector<int>> edge;
        // read cost of each node
        for(int i=0;i<n;i++){
            parent[i]=i;    // init
            cin>>node_cost[i];
            if(node_cost[i]<mincost){
                mincost=node_cost[i];
                minidx=i;
            }
        }
        // read special offer, if it is better then push it into edge
        for(int i=0;i<m;i++){
            int u, v, w;
            cin>>u>>v>>w;
            u--, v--;
            if(w>node_cost[u]+node_cost[v]){continue;}
            edge.push_back({u, v, w});
        }
        // all the nodes will connect to the min cost edge, so add them to edge
        for(int i=0;i<n;i++){
            if(i==minidx){continue;}
            edge.push_back({i, minidx, node_cost[i]+node_cost[minidx]});
        }
        // connect the graph from the smallest edge
        sort(edge.begin(), edge.end(), cmp);
        for(int n_edge=0, i=0; i<edge.size() && n_edge<n-1;i++){
            if(findp(edge[i][0], parent)==findp(edge[i][1], parent)){/*cout<<edge[i][0]<<"-"<<edge[i][1]<<endl;*/continue;} // has been in the same set (has been connected)
            joint(edge[i][0], edge[i][1], parent);  // connect two nodes and union them in the same set
            sum+=edge[i][2];
            n_edge++;
        }
        cout<<sum<<endl;
        /*for(auto v:edge){
            cout<<v[0]<<' '<<v[1]<<' '<<v[2]<<endl;
        }*/
    }
    return 0;
}
