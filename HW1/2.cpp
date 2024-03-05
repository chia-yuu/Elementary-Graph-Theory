#include<iostream>
#include<vector>
#include<fstream>
#include<queue>
#include<stack>
using namespace std;


int main(){
        int n_node, n_edge;
        cin>>n_node>>n_edge;
        vector<vector<int>> adjlist(n_node);
        vector<int> color(n_node, 0);
        bool valid=true;

        // construct adjacent list
        for(int i=0;i<n_edge;i++){
            int n1, n2;
            cin>>n1>>n2;
            n1--, n2--;
            adjlist[n1].push_back(n2);
            adjlist[n2].push_back(n1);
        }

        // dfs color each node
        int cur_color;
        stack<int> st;
        st.push(0);
        color[0]=1;
        while(!st.empty()){
            int cur_node=st.top();
            st.pop();
            cur_color=color[cur_node];
            for(int node:adjlist[cur_node]){
                if(color[node]==cur_color){
                    valid=false;
                    break;
                }
                if(color[node]==0){
                    color[node]=cur_color*(-1);
                    st.push(node);
                }
            }
        }

        // print result
        valid? cout<<"Yes\n" : cout<<"No\n";
    return 0;
}
