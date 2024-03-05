#include<iostream>
#include<vector>
#include<queue>
#include<climits>
using namespace std;

int n_vertex, n_edge;
class Edge{
public:
    int dest, rev, flow, cap;
    Edge(int _dest, int _rev, int _flow, int _cap):dest(_dest), rev(_rev), flow(_flow), cap(_cap){}
};
class Graph{
public:
    int v;
    vector<int> level;
    vector<vector<Edge>> adjlist;
    Graph(int _v){
        v=_v;
        level=vector<int>(_v);
        adjlist=vector<vector<Edge>>(_v);
    }

    void addEdge(int a, int b, int cap){
        Edge to(b, adjlist[b].size(), 0, cap);
        Edge back(a, adjlist[a].size(), 0, 0);
        adjlist[a].push_back(to);
        adjlist[b].push_back(back);
    }
    bool bfs(int s, int t){
        fill(level.begin(), level.end(), -1);
        level[s]=0;
        queue<int> q;
        q.push(s);
        while(!q.empty()){
            int cur=q.front();
            q.pop();
            for(auto &i:adjlist[cur]){
                if(level[i.dest]==-1 && i.flow<i.cap){
                    level[i.dest]=level[cur]+1;
                    q.push(i.dest);
                }
            }
        }
        return level[t]!=-1;
    }
    int sendFlow(int u, int t, int flow, vector<int>& idx){
        if(u==t){return flow;}
        for(;idx[u]<adjlist[u].size();idx[u]++){
            Edge& e=adjlist[u][idx[u]];
            if(level[e.dest]==level[u]+1 && e.flow<e.cap){
                int cur_f=min(flow, e.cap-e.flow);
                int temp_f=sendFlow(e.dest, t, cur_f, idx);
                if(temp_f>0){
                    e.flow+=temp_f;
                    adjlist[e.dest][e.rev].flow-=temp_f;
                    return temp_f;
                }
            }
        }
        return 0;
    }
    int dinic(int s, int t){
        for(int i=0;i<v;i++){
            for(Edge& e:adjlist[i]){
                e.flow=0;
            }
        }
        if(s==t){return -1;}
        int tot=0;
        while(bfs(s, t)){
            vector<int> idx(v, 0);
            
            while(int f=sendFlow(s, t, INT_MAX, idx)){
                tot+=f;
            }
        }
        return tot;
    }
};

int main(){
    cin>>n_vertex>>n_edge;
    Graph g(2*n_vertex+1);
    for(int i=0;i<n_edge;i++){
        int u, v;
        cin>>u>>v;
        g.addEdge(u, v, 1);
        g.addEdge(v, u, 1);
    }
    int k=INT_MAX;
    for(int i=1;i<=n_vertex;i++){
        for(int j=1;j<=n_vertex;j++){
            if(i!=j){
                k=min(k, g.dinic(i, j));
            }
        }
    }
    cout<<k<<endl;
    return 0;
}
