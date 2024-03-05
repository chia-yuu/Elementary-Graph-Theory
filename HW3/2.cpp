// 用adj list，不要用 adj mtx，不然會有sparse matrix，memory太大會RE/WA
#include<iostream>
#include<vector>
#include<queue>
#include<climits>
using namespace std;

void dijk(vector<vector<pair<long long, long long> > >& adjlist, vector<long long>& dist, long long src){
    // pq.first=distance, second=node
    priority_queue<pair<long long, long long>, vector<pair<long long, long long> >, greater<pair<long long, long long> > > pq;
    pq.push({0, src});
    dist[src]=0;
    while(!pq.empty()){
        long long cur=pq.top().second;
        pq.pop();
        for(long long i=0;i<adjlist[cur].size();i++){
            long long v=adjlist[cur][i].first, d=adjlist[cur][i].second;
            if(d+dist[cur]<dist[v]){
                dist[v]=d+dist[cur];
                pq.push({dist[v], v});
            }
        }
        /*for(long long i=0;i<adjlist[cur].size();i++){
            if(adjlist[cur][i]==-1){continue;}      // no edge
            if(adjlist[cur][i]+dist[cur]<dist[i]){
                dist[i]=adjlist[cur][i]+dist[cur];
                pq.push({dist[i], i});
            }
        }*/
    }
}

int main(){
    long long n_testcase, sub;
    cin>>n_testcase>>sub;
    while(n_testcase--){
        long long n_node, n_edge, k;
        cin>>n_node>>n_edge>>k;
        vector<vector<pair<long long, long long> > > adjlist(n_node+5);     // adjlist[src]={dest, weight};
        vector<long long> dist_from1(n_node+5, LLONG_MAX), dist_fromn(n_node+5, LLONG_MAX), dist_fromN(n_node+5, LLONG_MAX);
        // construct graph (u->v 變成 v->u, 題目變成找1或n到每個點的距離)
        for(long long i=0;i<n_edge;i++){
            long long u, v, w;
            cin>>u>>v>>w;
            adjlist[v].push_back({u, w});
        }
        dijk(adjlist, dist_from1, 1);       // distance from 1 to all node
        dijk(adjlist, dist_fromn, n_node);  // distance from n to all node
        // debug : print dist_from1 and dist_fromn
        /*for(auto d:dist_from1){
            if(d>=LLONG_MAX){cout<<"-1 ";}
            else{cout<<d<<' ';}
        }cout<<endl;
        for(auto d:dist_fromn){
            if(d>=LLONG_MAX){cout<<"-1 ";}
            else{cout<<d<<' ';}
        }cout<<endl;*/
        for(long long i=1;i<=n_node;i++){
            if(dist_from1[i]>=LLONG_MAX || dist_fromn[i]>=LLONG_MAX){continue;}
            adjlist[n_node+1].push_back({i, dist_from1[i]+dist_fromn[i]});
        }
        dijk(adjlist, dist_fromN, n_node+1);
        // debug : print graph adjlist
        /*for(auto v:adjlist){
            for(auto nd:v){
                if(nd>=LLONG_MAX){cout<<"-1 ";}
                else{cout<<nd<<' ';}
            }
            cout<<endl;
        }*/
        // anya win, output distance from i to 1 
        if(k==1){
            for(long long i=1;i<=n_node;i++){
                if(dist_from1[i]>=LLONG_MAX){cout<<"-1 ";}  // no road
                else{cout<<dist_from1[i]<<" ";}
            }
            cout<<endl;
        }
        // damian win, output distance from i to 1 and n
        else{
            for(long long i=1;i<=n_node;i++){
                if(dist_from1[i]==LLONG_MAX || dist_fromn[i]==LLONG_MAX || dist_fromN[i]>=LLONG_MAX){cout<<"-1 ";}  //no road
                else{cout<<dist_fromN[i]<<" ";}
            }
            cout<<endl;
        }

    }
    return 0;
}
