/*
 ***
 Question Name: Root Change
 ***
 Question Link: https://csacademy.com/contest/algorithms-2017-09-24-23/task/root-change/
 ***
 Question Description:
 You are given a tree with N nodes. You should analyze N scenarios, in each scenario i consider node i to be the root of the tree.
 In a rooted tree, you are allowed to cut exactly one edge. When you do this, all nodes that are connected to the root through this edge disappear. Count how many of the N−1 edges can be cut without changing the height of the tree.
 
 ***
 Idea:
 1, Find the longest path of the Tree: (1) Randomly choose a node u and use dfs or bfs to find the most faraway node v from the chosen node. (2) Start from v and use dfs or bfs to find the longest path, which is the longest path of the who tree.
 2, Fine the Centroid of the Tree, which is the center node of the longest path. Set the Centroid to be the root and construct the tree.
 3, Compute the answer for the root. And track the lowest merge points of the farthest leaves for each subtree.
 4, Compute the answers for the nodes in each subtree.
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
    int N,tr_root,length;
    vector<vi> E;
    vi depth;
    vector<unordered_set<int>> chl;
    vi longPath(int root){
        /*
         This function is used to find and output the longest path with in a tree.
         */
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
        /*
         Find the Centroid of the tree and set it into root;
         */
        int k = longPath(0)[0];
        vi path = longPath(k);
        int l = (int)path.size();
        length = l-1;
        return path[(l-1)/2];
    }
    unordered_map<int,ii> preProcess(){
        tr_root = centRoot();
        unordered_map<int,ii> ans;
        queue<int> que;
        vi par(N, tr_root);
        int cnt = 0;
        for(auto j:E[tr_root]){
            int L = 0;
            depth[j] = 1;
            que.push(j);
            unordered_set<int> S;
            chl[j].insert(j);
            while(!que.empty()){
                int k = que.front();
                que.pop();
                for(int i:E[k]) if(i!=par[k]){
                    par[i] = k;
                    depth[i] = depth[k] + 1;
                    que.push(i);
                    chl[j].insert(i);
                }
                if(que.empty()) L = depth[k];
            }
            ans[j] = ii(L, 1);
            if(L<length/2 || cnt > 2) continue;
            ++cnt;
            for(auto k:chl[j]) if(depth[k]==L) S.insert(k);
            while ((int)S.size()>1) {
                unordered_set<int> tmp;
                for(auto k:S) tmp.insert(par[k]);
                S.swap(tmp);
            }
            ans[j].second += depth[*S.begin()] - depth[j];
        }
        /*
         ans[j] = ii(L,v);
         L is the length of the subtree j;
         v is the answer for the root, if the root only has this one subtree. (The distance between root and the lowest merge point.)
         */
        return ans;
    }
    void buildAns(vi &ans){
        unordered_map<int, ii> pre_ans = preProcess();
        if(pre_ans.empty()) return;
        set<vi> sc;
        for(auto p:pre_ans) sc.insert(vi{-p.second.first,p.first,p.second.second});
        /*
         Compute answer for the root.
         */
        if((*sc.begin())[0] == (*(++sc.begin()))[0]) ans[tr_root] = 0;
        else ans[tr_root] = (*sc.begin())[2];
        /*
         compute answers for the nodes on each subtrees.
         */
        for(auto j:E[tr_root]){
            vi tmp = {-pre_ans[j].first, j, pre_ans[j].second},par(N,tr_root);
            sc.erase(tmp);
            if((int)sc.size()>1 && (*sc.begin())[0] == (*(++sc.begin()))[0]) ans[j] = 1;
            else ans[j] = (*sc.begin())[2] + 1;
            for(auto k:chl[j]) if(k!=j) ans[k] = ans[j]-1+depth[k];
            sc.insert(tmp);
        }
    }
public:
    void solve(){
        cin>>N;
        E.resize(N);
        depth.assign(N, 0);
        chl.resize(N);
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

/*
 There is one case that the code cannot pass.
 */


