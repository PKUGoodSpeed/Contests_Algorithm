/*
 ***
 Question Name: Bichrome Tree
 ***
 Question Link: http://arc083.contest.atcoder.jp/tasks/arc083_c
 
 ***
 Idea: 
    1, Tracking X[i] and the weight sum of the other color, which we call S[i]
    2, Indeed, we assume now considering the ith node, which value is V[i], its children are {kj}, j = 1, 2,...,
Black B[kj] or Wight W[kj] colors are assigned to X[kj] or S[kj] respectively, ans we want to:
            minimize sum_j W[kj] meanwhile maintain sum_j B[kj] <= X[i].
So at every step, we want to maximize sum_j B[kj] <===> minimize X[i] - sum_j B[kj] since sum_j B[kj] + sum_j W[kj] is fixed. So actually we want to minimize S[i] for every i, which is consistant with the above minimization, since S[i] = X[i] - sum_j B[kj].
    3, If at some point, X[i] < sum_j B[kj] for any assignment, which means this tree is impossible. Otherwise, it is possible.
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

class BichromeTree{
    int N;
    vi P,X,S;
    vector<vi> E;
    vector<unordered_set<int>> T;
    int dfs(vi &A, vi &B, int tar){
        int n = (int)A.size();
        vector<vb> dp(n+1,vb(tar+1,false));
        dp[0][tar] = true;
        bool ok = true;
        for(int i=1;i<=n && ok;++i){
            ok = false;
            for(int j=0;j<=tar;++j){
                dp[i][j] = (j+A[i-1]<=tar && dp[i-1][j+A[i-1]])||(j+B[i-1]<=tar && dp[i-1][j+B[i-1]]);
                if(dp[i][j]) ok = true;
            }
        }
        if(!ok) return -1;
        for(int j=0;j<=tar;++j) if(dp[n][j]) return j;
        return -1;
    }
    int init(){
        T.push_back(unordered_set<int>());
        T[0].insert(0);
        queue<ii> que;
        que.push(ii(1,0));
        while (!que.empty()) {
            int l = que.front().first, i = que.front().second;
            que.pop();
            if(!E[i].empty() && l>=(int)T.size()) T.push_back(unordered_set<int>());
            for(auto j:E[i]){
                T[l].insert(j);
                que.push(ii(l+1,j));
            }
        }
        return (int)T.size();
    }
    public:
    bool solve(){
        cin>>N;
        P = X = S = vi(N, -1);
        E.resize(N);
        for(int i=1;i<N;++i){
            cin>>P[i];
            --P[i];
            E[P[i]].push_back(i);
        }
        for(int i=0;i<N;++i){
            cin>>X[i];
            if(E[i].empty()){ //
                S[i] = 0;
            }
        }
        int L = init();
        cout<<endl;
        for (int l=L-1; l>0; --l) {
            while (!T[l].empty()) {
                int j = P[*T[l].begin()],sum = 0;
                vi A,B;
                for(auto k:E[j]){
                    assert(T[l].count(k));
                    T[l].erase(k);
                    A.push_back(X[k]);
                    B.push_back(S[k]);
                    assert(X[k]>=0 && S[k]>=0);
                    sum += S[k] + X[k];
                }
                S[j] = dfs(A, B, X[j]);
                if(S[j]==-1) return false;
                S[j] += sum - X[j];
            }
        }
        return true;
    }
};


int main(){
    if(BichromeTree().solve()) cout<<"POSSIBLE"<<endl;
    else cout<<"IMPOSSIBLE"<<endl;
    return 0;
}
