#include<iostream>
#include<vector>
using namespace std;

int main(){
    int n_vertex, n_edge;
    cin>>n_vertex>>n_edge;
    // construct mtx
    vector<vector<int>> mtx(n_vertex, vector<int>(n_vertex, 0));
    for(int i=0;i<n_edge;i++){
        int u, v, w;
        cin>>u>>v>>w;
        u--, v--;   // vertex start from 1
        mtx[u][v]=w;
    }
        
    // print mtx
    for(auto v:mtx){
        for(int n:v){
            cout<<n<<' ';
        }
        cout<<'\n';
    }

    // print in/out degree
    int in=0, out=0;
    for(int i=0;i<n_vertex;i++){
        out=0, in=0;
        for(int j=0;j<n_vertex;j++){
            if(mtx[i][j]!=0){out++;}
            if(mtx[j][i]!=0){in++;}
        }
        cout<<in<<' '<<out<<'\n';
    }
    return 0;
}
