/*
 ***
 Question Name: Transit Tree Path
 ***
 Question Link: http://abc070.contest.atcoder.jp/tasks/abc070_d
 
 ***
 Idea:  Construct Tree with root equals K,
 Then the shortest path mast be dis[from root to x] + dis[from root to y]
 */

#include <memory.h>
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

class TransitTreePath{
    int N,K,Q;
    vector<vector<ii>> E;
    vL ans;
    void init(){
        cin>>N;
        E.resize(N);
        ans = vL(N,-1);
        for(int i=0;i<N-1;++i){
            int a,b,c;
            cin>>a>>b>>c;
            E[a-1].push_back(ii(b-1, c));
            E[b-1].push_back(ii(a-1, c));
        }
    }
    void constructTree(){
        --K;
        assert(K>=0 && K<N);
        queue<int> que;
        que.push(K);
        ans[K] = (LL)0;
        while (!que.empty()) {
            int i = que.front();
            que.pop();
            for(auto p:E[i]) if(ans[p.first]==-1){
                ans[p.first] = ans[i] + (LL)p.second;
                que.push(p.first);
            }
        }
        return ;
    }
    public:
    void solve(){
        init();
        cin>>Q>>K;
        constructTree();
        for(int q=0;q<Q;++q){
            int x, y;
            cin>>x>>y;
            cout<< ans[x-1] + ans[y-1] <<endl;
        }
        return ;
    }
};



int main(){
    TransitTreePath().solve();
    return 0;
}
