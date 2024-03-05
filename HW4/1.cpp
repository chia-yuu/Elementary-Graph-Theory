#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<vector<int>> adjlist;
int timer=0;
vector<int> cut_vertex, visit, has_record;
vector<int> in, low;
// `in` reocrd the first time we visit the node, `low` record the smallest visit time of the node's child
// if low[child]>=in[node], then there is a back edge -> node is a cut vertex

void remove_vertex(vector<vector<int>>& adjlist, int node, vector<int>& temp){
    temp=adjlist[node];
    for(int nd:adjlist[node]){
        auto it=find(adjlist[nd].begin(), adjlist[nd].end(), node);
        if(it!=adjlist[nd].end()){
            adjlist[nd].erase(it);
        }
        else{
            printf("in remove_vertex, can't find %d in %d\n", node, nd);
        }
    }
    adjlist[node].clear();
}
void dfs(int cur, int parent){
    int n_child=0;
    visit[cur]=true;
    in[cur]=timer;
    low[cur]=timer;
    timer++;
    for(int nd:adjlist[cur]){
        if(nd==parent){continue;}
        if(visit[nd]){
            low[cur]=min(low[cur], in[nd]);
        }
        else{
            dfs(nd, cur);
            low[cur]=min(low[cur], low[nd]);
            if(low[nd]>=in[cur] && parent!=-1){
                if(!has_record[cur]){
                    has_record[cur]=true;
                    cut_vertex.push_back(cur);
                }
            }
            n_child++;
        }
    }
    if(parent==-1 && n_child>1){
        if(!has_record[cur]){
            has_record[cur]=true;
            cut_vertex.push_back(cur);
        }
    }
}
bool disconnect(vector<int>& visit){
    int count=0;
    for(int i:visit){
        if(i==0){count++;}
        cout<<i<<" ";
    }
    cout<<endl;
    return count>1;
}
void add_vertex(vector<vector<int>>& adjlist, int node, vector<int>& temp){
    adjlist[node]=temp;
    for(int nd:temp){
        adjlist[nd].push_back(node);
    }
}

int main(){
    int n_vertex, n_edge;
    cin>>n_vertex>>n_edge;
    adjlist.resize(n_vertex);
    visit.resize(n_vertex, false);
    in.resize(n_vertex);
    low.resize(n_vertex);
    has_record.resize(n_vertex, false);
    timer=0;
    for(int i=0;i<n_edge;i++){
        int a, b;
        cin>>a>>b;
        a--, b--;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }
    /*for(int i=0;i<n_vertex-1;i++){
        visit.clear();
        visit.resize(n_vertex, false);
        int count_visit=0;
        remove_vertex(adjlist, i, temp);
        if(i+1<n_vertex){
            dfs(adjlist, visit, i+1, i, count_visit);
        }
        else{
            dfs(adjlist, visit, i-1, i, count_visit);
        }
        if(count_visit<n_vertex-1){
            cut_vertex.push_back(i);
            count++;
        }
        add_vertex(adjlist, i, temp);
    }*/
    dfs(0, -1);
    cout<<cut_vertex.size()<<"\n";
    sort(cut_vertex.begin(), cut_vertex.end());
    for(int nd:cut_vertex){
        cout<<nd+1<<" ";
    }

    return 0;
}
