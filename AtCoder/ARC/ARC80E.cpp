/*
 ***
 Question Name: Young Maids
 ***
 Question Link: http://arc080.contest.atcoder.jp/tasks/arc080_c
 
 ***
 Idea: 1, Divided the indexes into odd and even, and we need to process the data for even and odd indices separately; 2, Use segment Tree to quickly search for the minimum element in an interval of the original permulation. 3, Create tree edges, which is the priority relationship between intervals. 4, Build the final permulation.
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

/*Here is a stupid solution using dfs, which will lead to TLE
class YoungMaids{
    int N;
    vi P,I;
    vector<vi> E;
    void init(){
        cin>>N;
        P.resize(N);
        I.resize(N+1);
        E.resize(N+1);
        for(int i=0;i<N;++i) cin>>P[i];
    }
    int dfs(int l,int r){
        assert((l+r)%2 == 0);
        if(r==l+2){
            I[P[l]] = P[r-1];
            return P[l];
        }
        int ie = l, io = l+1;
        for(int i=2;i<r-l;++i){
            if(i%2==0 && P[l+i]<P[ie]){
                ie = l+i;
                io = l+i+1;
            }
            else if(i%2 && P[l+i]<P[io]) io = l+i;
        }
        I[P[ie]] = P[io];
        if(ie>l) E[P[ie]].push_back(dfs(l, ie));
        if(io>ie+1) E[P[ie]].push_back(dfs(ie+1, io));
        if(r>io+1) E[P[ie]].push_back(dfs(io+1, r));
        return P[ie];
    }
    
    
public:
    void solve(){
        init();
        int beg = dfs(0, N);
        priority_queue<int, vector<int>, greater<int>> que;
        que.push(beg);
        while(!que.empty()){
            int k = que.top();
            que.pop();
            cout<<k<<' '<<I[k]<<' ';
            for(auto j:E[k]) que.push(j);
        }
        cout<<endl;
    }
};
*/

class YoungMaids{
    vector<vector<ii>> seg;
    vi P,C;
    vector<vi> E;
    int N,n;
    void init(){
        cin>>n;
        P.resize(n);
        E.resize(n+1);
        C.resize(n+1);
        for(int i=0;i<n;++i) cin>>P[i];
        N = 1;
        while(N<n/2) N*=2;
        seg = vector<vector<ii>>(2,vector<ii>(2*N-1,ii(n+1,-1)));
        int j = N-1;
        for(int i=0;i<n;++i) seg[i%2][j+i/2] = ii(P[i],i);
        while(j){
            for(int i=j/2;i<j;++i) for(int k=0;k<2;++k) seg[k][i] = min(seg[k][2*i+1], seg[k][2*i+2]);
            j /= 2;
        }
    }
    ii findMin(int l,int r,int a,int b,int k,int t){ //Using Segment Tree to quickly find the minimum element with in an interval.
        if(r<=a || b<=l) return ii(n+1,-1);
        if(a<=l && b>=r) return seg[t][k];
        ii vl = findMin(l, (l+r)/2, a, b, 2*k+1, t);
        ii vr = findMin((l+r)/2, r, a, b, 2*k+2, t);
        return min(vl, vr);
    }
    int findPair(int l,int r){
        if(l==r-2){
            C[P[l]] = P[l+1];
            return P[l];
        }
        auto x1 = findMin(0, N, l/2, r/2, 0, l%2);
        int ie = x1.second;
        auto x2 = findMin(0, N, (ie+1)/2, (r+1)/2, 0, (l+1)%2);
        int io = x2.second;
        C[x1.first] = x2.first;
        if(ie > l) E[x1.first].push_back(findPair(l, ie));
        if(io>ie+1) E[x1.first].push_back(findPair(ie+1, io));
        if(r>io+1) E[x1.first].push_back(findPair(io+1, r));
        return x1.first;
    }
public:
    void solve(){
        init();
        priority_queue<int,vector<int>,greater<int>> que;
        que.push(findPair(0, n));
        while(!que.empty()){
            int k = que.top();
            cout<<k<<' '<<C[k]<<' ';
            que.pop();
            for(int j:E[k]) que.push(j);
        }
    }
};

int main(){
    YoungMaids().solve();
    return 0;
}
