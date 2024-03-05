#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;

#define INF 99999999

int overLap(string a, string b){
    for(int i=1;i<a.size();i++){
        if(b.find(a.substr(i))==0){
            return b.size()-a.size()+i;
        }
    }
    return b.size();
}
string shortestString(vector<string>& v){
    int n=v.size();
    // construct graph (adj mtx)
    vector<vector<int>> graph(n, vector<int>(n, 0));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            graph[i][j]=overLap(v[i], v[j]);
            graph[j][i]=overLap(v[j], v[i]);
        }
    }

    // create dp and path arr
    vector<vector<int>> dp(1<<n, vector<int>(n));
    vector<vector<int>> path(1<<n, vector<int>(n));
    int last=-1, minval=INF;

    // TSP DP
    for(int i=1;i<(1<<n);i++){
        fill(dp[i].begin(), dp[i].end(), INF);      // init
        for(int j=0;j<n;j++){
            // if visit[j]==true
            if((i & (1<<j))>0){
                int pre=i-(1<<j);
                // if this is the first visit
                if(pre==0){
                    dp[i][j]=v[j].size();
                }
                // otherwise
                else{
                    for(int k=0;k<n;k++){
                        if(dp[pre][k]<INF && dp[pre][k]+graph[k][j]<dp[i][j]){
                            dp[i][j]=dp[pre][k]+graph[k][j];
                            path[i][j]=k;
                        }
                    }
                }
            }
            // all visited, check the last dp[i][j]
            if(i==(1<<n)-1 && dp[i][j]<minval){
                minval=dp[i][j];
                last=j;
            }
        }
    }

    // build path
    string res;
    int cur=(1<<n)-1;
    stack<int> st;
    while(cur>0){
        st.push(last);
        int temp=cur;
        cur-=(1<<last);
        last=path[temp][last];
    }
    
    // get result
    int i=st.top();
    st.pop();
    res+=v[i];
    while(!st.empty()){
        int j=st.top();
        st.pop();
        res+=v[j].substr(v[j].size()-graph[i][j]);
        i=j;
    }
    return res;
}

int main(){
    // read input
    int n;
    cin>>n;
    vector<string> s(n);
    string ans="";
    for(int i=0;i<n;i++){
        cin>>s[i];
        for(int j=0;j<i;j++){
            if(s[j].size()>s[i].size() && s[j].find(s[i])!=string::npos){
                s[i]="";
            }
            else if(s[i].find(s[j])!=string::npos){
                s[j]="";
            }
        }
    }
    // sort and erase duplicate
    sort(s.rbegin(), s.rend());
    // solove
    ans=shortestString(s);
    // output
    cout<<ans<<"\n";
    return 0;
}
