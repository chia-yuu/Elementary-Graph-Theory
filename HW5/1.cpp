#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

bool is_k5(vector<vector<long long>>& adjlist, vector<long long>& vertex){
    if(vertex.size()!=5){return false;}
    for(long long i=0;i<vertex.size();i++){
        for(long long j=i+1;j<vertex.size();j++){
            if(adjlist[vertex[i]][vertex[j]]==0){return false;}
        }
    }
    return true;
}
bool is_k33(vector<vector<long long>>& adjlist, vector<long long>& vertex){
    if(vertex.size()!=6){return false;}
    /*vector<long long> X, Y;
    // find vertex in X
    X.push_back(vertex[0]);
    // cout<<"X= "<<X[0]<<' ';
    for(long long i=0;i<adjlist.size();i++){
        if(adjlist[vertex[0]][i]==1){X.push_back(i); /*cout<<i<<' ';}
    }
    // find vertex in Y
    // cout<<"\nY= ";
    for(long long nd:vertex){
        if(find(vertex.begin(), vertex.end(), nd)!=X.end()){Y.push_back(nd); /*cout<<nd<<' ';}
    }/*cout<<endl;
    for(int i=0;i<3;i++){
        for(int j=i+1;j<3;j++){
            if(adjlist[X[i]][X[j]]==1 || adjlist[Y[i]][Y[j]==1]){return false;}
        }
    }
    // X and Y all connect
    for(long long x:X){
        for(long long y:Y){
            if(adjlist[x][y]==0){return false;}
        }
    }
    return true;*/
    sort(vertex.begin(), vertex.end());
    do{
        bool k33=true;
        // no edge in the same subset (X or Y) is connected
        for(int i=0;i<3;i++){
            for(int j=i+1;j<3;j++){
                if(adjlist[vertex[i]][vertex[j]]==1 || adjlist[vertex[5-i]][vertex[5-j]]==1){
                    k33=false;
                    break;
                }
            }
            if(!k33){break;}
        }
        if(!k33){continue;}
        // all edge in X connect to Y
        for(int i=0;i<3;i++){
            for(int j=3;j<6;j++){
                if(adjlist[vertex[i]][vertex[j]]==0){
                    k33=false;
                    break;
                }
            }
            if(!k33){break;}
        }
        if(k33){return true;}
    }while(next_permutation(vertex.begin(), vertex.end()));
    return false;
}

int main(){
    long long n_testcase;
    cin>>n_testcase;
    while(n_testcase--){
        long long n_vertex, n_edge;
        bool is_planar=true;
        cin>>n_vertex>>n_edge;
        vector<pair<long long, long long>> edges(n_edge);
        for(long long i=0;i<n_edge;i++){
            long long u, v;
            cin>>u>>v;
            u--, v--;
            edges[i]={u, v};
        }

        // debug : print edge
        /*for(int i=0;i<n_edge;i++){
            cout<<edges[i].first<<' '<<edges[i].second<<endl;
        }*/
        
        if(n_edge>3*n_vertex-6){
            // cout<<"e>3v-6\n";
            cout<<"No\n";
            continue;
        }
        // try all possible edge combination to find k5 or k3,3
        for(long long mask=0;mask<(1<<n_edge);mask++){
        // long long mask=0;
            vector<vector<long long>> adjlist(n_vertex, vector<long long>(n_vertex, 0));
            vector<long long> deg(n_vertex,0);

            // construct graph (adj mtx) with selected vertex
            long long temp=mask;
            for(long long i=0;i<n_edge;i++){
                if(temp&1){
                    adjlist[edges[i].first][edges[i].second]=1;
                    adjlist[edges[i].second][edges[i].first]=1;
                }
                temp>>=1;
            }

            // debug : print graph
            /*cout<<"\n\nmask= "<<mask<<endl;
            for(auto v:adjlist){
                for(auto nd:v){cout<<nd<<' ';}cout<<endl;
            }*/

            // count degree
            for(long long i=0;i<n_vertex;i++){
                for(long long j=0;j<n_vertex;j++){
                    if(adjlist[i][j]==1){deg[i]++;}
                }
            }

            // simplify graph, if there is a subdivision, merge two vertex as one vertex
            bool is_simplify;
            while(true){
                is_simplify=true;
                for(long long i=0;i<n_vertex;i++){
                    if(deg[i]==2){
                        deg[i]=0;
                        long long u=-1, v=-1;
                        for(long long j=0;j<n_vertex;j++){
                            if(adjlist[i][j]==1){
                                if(u==-1){u=j;}
                                else{v=j;}
                            }
                        }
                        // uv has edge
                        if(adjlist[u][v]==1){
                            deg[u]--, deg[v]--;
                        }
                        // merge ui and vi as uv
                        adjlist[u][v]=1, adjlist[v][u]=1;
                        adjlist[u][i]=0, adjlist[i][u]=0;
                        adjlist[v][i]=0, adjlist[i][v]=0;
                        is_simplify=false;
                        break;
                    }
                }
                if(is_simplify){break;}
            }

            // debug : print graph
            /*cout<<endl;
            for(auto v:adjlist){
                for(auto nd:v){cout<<nd<<' ';}cout<<endl;
            }*/

            // check k5
            vector<long long> vertex;
            for(long long i=0;i<n_vertex;i++){
                if(deg[i]==4){vertex.push_back(i);}
            }
            if(is_k5(adjlist, vertex)){
                is_planar=false;
                // cout<<"is_k5\n";
                cout<<"No\n";
                break;
            }
            // check k3,3
            vertex.clear();
            for(long long i=0;i<n_vertex;i++){
                if(deg[i]==3){vertex.push_back(i);}
            }
            if(is_k33(adjlist, vertex)){
                is_planar=false;
                // cout<<"is_k33\n";
                cout<<"No\n";
                break;
            }
        }
        if(is_planar){
            cout<<"Yes\n";
        }
        
    }
    return 0;
}
