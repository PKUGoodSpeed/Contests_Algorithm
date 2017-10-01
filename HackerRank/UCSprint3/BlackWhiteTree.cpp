
/*
 ***
 Question Name: Black White Tree
 ***
 Question Link: https://www.hackerrank.com/contests/university-codesprint-3/challenges/black-white-tree
 ***
 Question Description:
 There is tree with N nodes and N-1 edges, for which each node are colored with white or black. Find the subtree that has the maximum abs(# black nodes - # white nodes).
 ***
 Idea: 1, Construct the Tree by assigning the root to a random node. 2, Using dfs to traversal all the nodes, and record the subtrees having maximum abs(# black nodes - # white nodes) under each node.
 (Actually, we do not need so large space. When we get the maximum abs(# black nodes - # white nodes), we can recursively retrieve the subtree, instead of recording all the subtrees at each step.)
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

typedef long double ld;
typedef vector<int> vi;
typedef vector<long> vl;
typedef vector<bool> vb;
typedef vector<double> vd;
typedef pair<int,int> ii;
typedef pair<long, long> ll;
typedef unordered_set<int> ui;

class BlackWhiteTree{
    int N, ans;
    vi colors, ans_list;
    vector<vector<vi>> wb_list;
    vector<vi> wb_value; // Index 0 denote the white, 1 for black
    vector<vi> E;
    void init(){
        cin>>N;
        colors.resize(N);
        E.resize(N);
        wb_list = vector<vector<vi>>(N,vector<vi>(2,vi()));
        for(int i=0;i<N;++i) {
            wb_list[i][0].push_back(i);
            wb_list[i][1].push_back(i);
        }
        wb_value = vector<vi>(N,vi(2,-1));
        for(int i=0;i<N;++i) cin>>colors[i];
        for(int i=1;i<N;++i){
            int u,v;
            cin>>u>>v;
            E[u-1].push_back(v-1);
            E[v-1].push_back(u-1);
        }
    }
    // Use 0 as the root to build a tree
    void buildTree(){
        queue<int> que;
        que.push(0);
        vb used(N,true);
        used[0] = false;
        vector<vi> Chl(N,vi());
        while(!que.empty()){
            int j = que.front();
            que.pop();
            bool ok = true;
            for(auto k:E[j]) if(used[k]){
                Chl[j].push_back(k);
                que.push(k);
                used[k] = false;
                ok = false;
            }
            if(ok){//leaf
                wb_value[j][colors[j]] = 1;
                wb_value[j][1-colors[j]] = 0;
                wb_list[j][1-colors[j]].clear();
            }
        }
        E.swap(Chl);
    }
    
    void travTree(int root){
        if(wb_value[root][0] >= 0) return;
        wb_value[root][colors[root]] = 1;
        for(auto k:E[root]){
            travTree(k);
            for(int i=0;i<2;++i) if(wb_value[k][i] > 0){
                wb_value[root][i] += wb_value[k][i];
                for(int j:wb_list[k][i]) wb_list[root][i].push_back(j);
            }
        }
        for(int i=0;i<2;++i){
            if(wb_value[root][i]<=0){
                wb_value[root][i] = 0;
                wb_list[root][i].clear();
            }
            if(wb_value[root][i] > ans){
                ans = wb_value[root][i];
                ans_list = wb_list[root][i];
            }
        }
        return;
    }
public:
    void solve(){
        init();
        ans = 0;
        ans_list.push_back(0);
        buildTree();
        travTree(0);
        cout<<ans<<endl<<(int)ans_list.size()<<endl;
        for(int k:ans_list) cout<<k+1<<' ';
        cout<<endl;
    }
};

int main(){
    std::ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    BlackWhiteTree().solve();
    return 0;
}

