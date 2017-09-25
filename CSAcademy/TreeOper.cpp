
/*
 ***
 Question Name: Centroid algorithm
 ***
 Question Link:
 
 ***
 Idea: Failed Question
 */

#include <memory.h>
#include <ctime>
#include <random>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <functional>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>

#define REP(i,s,n) for(int (i)=s; (i)<(int)(n);(i)++)
#define RIT(it,c) for(__typeof(c.begin()) it = c.begin();it!=c.end();it++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (int)(x).size()
#define MSET(m,v) memset(m,v,sizeof(m))

using namespace std;

typedef long long LL;
typedef long double LD;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<LL> vL;
typedef vector<bool> vb;
typedef unordered_set<int> ui;
typedef pair<LL,LL> pLL;

class RootChange{
    int N,tr_root;
    vector<vi> E;
    vi depth;
    vi longPath(int root){
        vi par(N,-1), ans;
        queue<int> que;
        que.push(root);
        while(!que.empty()){
            int k = que.front();
            que.pop();
            for(auto j:E[k]) if(j!=par[k]){
                par[j] = k;
                que.push(j);
            }
            if(que.empty()) ans.push_back(k);
        }
        for(int i=par[ans[0]];i>=0;i=par[i]) ans.push_back(i);
        return ans;
    }
    int centRoot(){
        int k = longPath(0)[0];
        vi path = longPath(k);
        int l = (int)path.size();
        return path[l/2];
    }
    map<int,ii> preProcess(){
        tr_root = centRoot();
        vi par(N, tr_root);
        map<int,ii> ans;
        queue<int> que;
        for(auto j:E[tr_root]){
            int L = 0;
            depth[j] = 1;
            que.push(j);
            unordered_set<int> S;
            S.insert(j);
            while(!que.empty()){
                int k = que.front();
                que.pop();
                for(int i:E[k]) if(i!=par[k]){
                    par[i] = k;
                    depth[i] = depth[k] + 1;
                    que.push(i);
                    S.insert(i);
                }
                if(que.empty()) L = depth[k];
            }
            ans[j] = ii(L, 1);
            for(auto k:S) if(depth[k]<L) S.erase(k);
            while ((int)S.size()>1) {
                unordered_set<int> tmp;
                for(auto k:S) tmp.insert(par[k]);
                S.swap(tmp);
            }
            for(int k=*S.begin();k!=j;k=par[k]) ans[j].second++;
        }
        return ans;
    }
    void buildAns(vi &ans){
        map<int, ii> pre_ans = preProcess();
        set<vi> sc;
        for(auto p:pre_ans) sc.insert(vi{-p.second.first,p.first,p.second.second});
        if((*sc.begin())[0] == (*(++sc.begin()))[0]) ans[tr_root] = 0;
        else ans[tr_root] = (*sc.begin())[2];
        for(auto j:E[tr_root]){
            vi tmp = {-pre_ans[j].first, j, pre_ans[j].second},par(N,tr_root);
            sc.erase(tmp);
            if((int)sc.size()>1 && (*sc.begin())[0] == (*(++sc.begin()))[0]) ans[j] = 1;
            else ans[j] = (*sc.begin())[2] + 1;
            queue<int> que;
            que.push(j);
            while(!que.empty()){
                int k = que.front();
                que.pop();
                for(int i:E[k]) if(i!=par[k]){
                    par[i] = k;
                    ans[i] = ans[k] + 1;
                    que.push(i);
                }
            }
            sc.insert(tmp);
        }
    }
public:
    void solve(){
        cin>>N;
        E.resize(N);
        depth.assign(N, 0);
        for(int i=1;i<N;++i){
            int u,v;
            cin>>u>>v;
            E[u-1].push_back(v-1);
            E[v-1].push_back(u-1);
        }
        vi ans(N,0);
        buildAns(ans);
        for(int k:ans) cout<<N-1-k<<endl;
    }
};

int main(){
    RootChange().solve();
    return 0;
}
