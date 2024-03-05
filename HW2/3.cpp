#include<iostream>
#include<vector>
using namespace std;

// find_key util, dfs to make the key, -1==leaf
void key_dfs(int from, int node, int len, vector<vector<int>>& adjlist, vector<bool>& visit, vector<vector<pair<int,int>>>& key){
    visit[node]=true;
    len++;
    // printf("node= %d, len= %d ,  ", node, len);
    // is leaf
    if(adjlist[node].size()==1){
        if(key[from][2].second==-1){
            key[from][2]={-1, len};     // -1 means this is a leaf
        }
        else{
            key[from][1]={-1, len};
        }
    }
    // is joint
    if(adjlist[node].size()==3 && node!=from){
        // update from-node length
        if(key[from][0].second==-1){
            key[from][0]={node, len};
        }
        else{
            key[from][1]={node, len};
        }
        // update node-from length
        if(key[node][0].second==-1){
            key[node][0]={from, len};
        }
        else{
            key[node][1]={from, len};
        }
        visit[node]=false;
        return;
    }
    // recursive dfs
    for(int nd:adjlist[node]){
        if(!visit[nd]){
            key_dfs(from, nd, len, adjlist, visit, key);
        }
    }
}
// construct key
void find_key(vector<vector<int>>& adjlist, vector<int>& joint, vector<vector<pair<int,int>>>& key){
    int n=adjlist.size();
    int m=joint.size();
    vector<bool> visit(n, 0);
    // dfs from every joint (from) and count length, the three connected vertex may be leaf or another joint
    // if it is a joint (nd), record the joint in key[from][0]={nd, len}; if [0] has been used, then record it in [1]
    // if it is a leaf, record it in key[from][2]={-1, len}; if [2] has been used, then record it in [1]. len==vertical length
    for(int i=0;i<m;i++){
        key_dfs(joint[i], joint[i], -1, adjlist, visit, key);
    }
}
// vertical_len util, dfs through every joint and record the vertical length
void ver_dfs(vector<vector<pair<int,int>>>& key, int node, vector<vector<int>>& ver_len, vector<bool>& visit){
    visit[node]=true;
    // printf("visit node %d\n", node);     // debug
    // push back the vertical len
    vector<int> temp;
    for(int i=1;i<3;i++){
        pair<int, int> nd=key[node][i];
        if(nd.first==-1){temp.push_back(nd.second);}
    }
    ver_len.push_back(temp);
    // recursive dfs
    for(int i=0;i<2;i++){
        int nd=key[node][i].first;
        if(nd!=-1 && !visit[nd]){
            ver_dfs(key, nd,ver_len, visit);
        }
    }
}
// construct ver_len, record the vertical length of each joint in ver_len
void vertical_len(vector<vector<pair<int,int>>>& key, vector<vector<int>>& ver_len){
    // find leaf and start dfs from leaf
    int leaf;
    vector<bool> visit(key.size(),0);
    // find leaf
    for(int i=0;i<key.size();i++){
        // if(key[i][2].first==-1 && key[i][2].second!=-1){leaf=i; break;}        //////??key[i][1]??
        if(key[i][1].first==-1 && key[i][1].second!=-1){leaf=i;}        //////??key[i][1]??
    }
    // printf("leaf= %d\n", leaf);  // debug
    ver_dfs(key, leaf, ver_len, visit);  // start from leaf and construct the key
}
// check if cind and driz have the same key
bool share_same(vector<vector<int>>& driz, vector<int>& cind){
    if(cind.size()!=driz.size()){/*printf("different size, cind= %d, driz= %d\n", cind.size(), driz.size());*/return false;}
    bool from_head=false, from_end=false;
    int n=cind.size()-1;
    // 正著從頭比
    if(cind[0]==driz[0][0] || cind[0]==driz[0][1]){
        from_head=true;
        // printf("from head is true\n");
        for(int i=1;i<cind.size()-1;i++){	// 因為最後一個有兩種可能，所以不要比到最後一個
            // printf("cind=%d, driz=%d\n", cind[i], driz[i][0]);
            if(cind[i]!=driz[i][0]){
                // printf("from head, cind %d != driz %d\n", cind[i], driz[i][0]);
                from_head=false;
            }
        }
        // 如果前面都一樣(from==true)，繼續比最後一個(可能有兩種長度)
        if(from_head==true){
            if(cind[n]!=driz[n][0] && cind[n]!=driz[n][1]){from_head=false;}
        }
    }
    if(from_head==true){return true;}
    // 反著從後面比
    if(cind[n]==driz[0][0] || cind[n]==driz[0][1]){
        from_end=true;
        // printf("from end is true\n");
        for(int i=cind.size()-2, j=1;i>=1;i--, j++){
            // printf("cind=%d, driz=%d\n", cind[i], driz[j][0]);
            if(cind[i]!=driz[j][0]){
                // printf("from end, cind %d != driz %d\n", cind[i], driz[j][0]);
                from_end=false;    
            }
        }
        // 比第一個
        if(from_end==true){
            if(cind[0]!=driz[n][0] && cind[0]!=driz[n][1]){from_end=false;}
        }
    }
    return from_head || from_end;
}

int main(){
    // construct drizella's key (adjancy list)
    int n, m;
    cin>>n;
    vector<vector<int>> driz(n);    // driz's key (adjlist)
    vector<int> joint;              // vector to record joint
    for(int i=0;i<n-1;i++){
        int a, b;
        cin>>a>>b;
        driz[a].push_back(b);
        driz[b].push_back(a);
        if(driz[a].size()==3){joint.push_back(a);}  // deg[a]==3 -> a is a joint
        if(driz[b].size()==3){joint.push_back(b);}  // deg[b]==3 -> b is a joint
    }

    // construct cinderella's key (vector)
    cin>>m;
    vector<int> cind(m);
    for(int i=0;i<m;i++){cin>>cind[i];}

    // solve
    vector<vector<pair<int,int>>> key(n, vector<pair<int, int>>(3, {-1, -1}));
    vector<vector<int>> ver_len;    // vector to record the vertical length
    bool is_same;
    find_key(driz, joint, key);    // find the path that contains all the joint (the horizontal bar)
    vertical_len(key, ver_len); // find vertical length
    is_same=share_same(ver_len, cind);   // check if it's possible that Cinderella and Drizella share the same key
    
    // output
    is_same? cout<<"YES\n" : cout<<"NO\n";
    // debug
    // print ver_len
    /*for(int i=0;i<ver_len.size();i++){
        cout<<ver_len[i][0]<<' ';
        if(i==0 || i==ver_len.size()-1){
            cout<<", "<<ver_len[i][1]<<' ';
        }
        cout<<endl;
    }*/
    // print key
    /*for(auto v:key){
        for(pair<int, int> p:v){
            cout<<p.first<<" "<<p.second<<",  ";
        }
        cout<<endl;
    }*/
    return 0;
}
