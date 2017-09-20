/*
 ***
 Question Name: Prime Flip
 ***
 Question Link: http://arc080.contest.atcoder.jp/tasks/arc080_d
 
 ***
 Idea: 1, Convert the flip problem into a problem of annihlating jogs, where a jog at i is defined that the ith card and the i-1th card are not on the same face. 2, Flipping card starting from a jog is equivalant of moving the jog. 3, When two jogs meets together, both will disappear: then the original problem becomes to compute the minimum number of moves to annihlate all the jogs.
 Since we can only move a jog by prime number of steps per time, so:
    ***** d[i][j] : odd prime : 1 step
    ***** d[i][j] : odd but not prime : 3 steps
    ***** d[i][j] : even : 2 steps
 if(number of 1's == k) the final answer = k + ((n_even-k)/2 + (n_odd-k)/2)*2 + (n_even-k)%2*3 (The total number must be even.) When is a monotonically increasing function.
 Maximizing k's is a maximum biparticle matching problem.
 Biparticle matching:
 1, Fix v and find a u that can match it.
 2, If u has not been paired, then assign u to v.
 3, If u has been assigned to w, using dfs to check whether w can be assigned another vertex. If yes, make updates, otherwise go to 1 and find a another u' to match it with v.
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

class PrimeFlip{
    int N = 1E7, n, m;
    vi mapping;
    vb vist;
    vector<vb> E;
    void init(){
        int K;
        cin>>K;
        unordered_set<int> cnt;
        vi odds,evens;
        for(int i=0;i<K;++i){
            int x;
            cin>>x;
            if(cnt.count(x)) cnt.erase(x);
            else cnt.insert(x);
            cnt.insert(x+1);
        }
        for(auto k:cnt){
            if(k%2) odds.push_back(k);
            else evens.push_back(k);
        }
        cnt.clear();
        n = (int)odds.size();
        m = (int)evens.size();
        mapping = vi(m,-1);
        E = vector<vb>(n,vb(m, false));
        vb prime(N+1,true);
        prime[0] = prime[1] = false;
        for(int i=2;i<=N;++i) if(prime[i]){
            for(int j=2;j*i<=N;++j) prime[i*j] = false;
        }
        prime[2] = false;
        for(int i=0;i<n;++i) for(int j=0;j<m;++j) E[i][j] =prime[abs(odds[i]-evens[j])];
        prime.clear();
    }
    bool arange(int i){
        for(int j=0;j<m;++j) if(E[i][j] && !vist[j]){
            vist[j] = true;
            if(mapping[j]==-1 || arange(mapping[j])){
                mapping[j] = i;
                return true;
            }
        }
        return false;
    }
public:
    void solve(){
        init();
        int cnt = 0;
        for(int i=0;i<n;++i) {
            vist.assign(m, false);
            cnt += arange(i);
        }
        int ans = cnt + ((n-cnt)/2 + (m-cnt)/2)*2 + ((m-cnt)%2)*3;
        cout<<ans<<endl;
    }
};



int main(){
    PrimeFlip().solve();
    return 0;
}




