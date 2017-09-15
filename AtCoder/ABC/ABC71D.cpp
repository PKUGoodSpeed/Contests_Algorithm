/*
 ***
 Question Name: Coloring Dominoes
 ***
 Question Link: http://abc071.contest.atcoder.jp/tasks/arc081_b
 
 ***
 Idea: Use dp, each slot is a 2 dimensional vector storing the state: [0, 1, 2] X [0, 1, 2] to denote 3 Colors X 3 Colors. Recusively update to get the final answer.
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

class ColoringDominoes{
    const LL MOD = 1000000007;
    int N;
    string s1, s2;
    public:
    int solve(){
        cin>>N>>s1>>s2;
        vector<vector<vL>> dp(N, vector<vL>(3, vL(3, (LL)0)));
        LL ans = (LL)0;
        for(int j=0;j<3;++j) for(int k=0;k<3;++k) if((s1[0]==s2[0]) == (j == k)) dp[0][j][k] = 1;
        for(int i=1;i<N;++i) for(int j=0;j<3;++j) for(int k=0;k<3;++k){
            if((s1[i]==s2[i]) != (j == k)) continue;
            for(int r=0;r<3;++r) for(int t=0;t<3;++t){
                if((s1[i-1]==s2[i-1])!= (r==t)) continue;
                if((s1[i]==s1[i-1]) != (r==j)) continue;
                if((s2[i]==s2[i-1]) != (t==k)) continue;
                dp[i][j][k] += dp[i-1][r][t];
            }
            dp[i][j][k]%=MOD;
        }
        for(int j=0;j<3;++j) for(int k=0;k<3;++k) ans += dp[N-1][j][k];
        return (int)(ans%MOD);
    }
};



int main(){
    cout<< ColoringDominoes().solve() <<endl;
    return 0;
}
