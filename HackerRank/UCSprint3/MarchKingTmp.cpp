
/*
 ***
 Question Name: March of the king
 ***
 Question Link: https://www.hackerrank.com/contests/university-codesprint-3/challenges/march-of-the-king
 ***
 Question Description:
 There is a 8X8 chess board with one letter in each cell. Given a pattern (a string with length <= 11), to find the number of paths on the chess board that form the pattern. The paths should not cross itself.
 ***
 Idea: My current method passes all the test cases except 2, which runs into TLE.
 1, Use a four dimensional dp[start][end][i][j]: which records all the pathes run from start to end, that form s.substr(i,j-i+1). 3. In dp[start][end][i][j], there stores all the pathes. Each path is described by a long interger: if(1&path>>point) if point is in the path (start, end, point: 0~63; i, j: 0~10). 3. Use bisection to recusively compute those dp values. 4. Count the number of pathes that form the entire pattern.
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

int K,M;
string s;
vector<vb> E(64,vb(64,false));
vl dp[64][64][12][12];
bool isDp[64][64][12][12];
vector<string> BD(8);
int dx[8] = {0, 0, 1, -1, 1, -1, 1, -1};
int dy[8] = {1, -1, 0, 0, 1, 1, -1, -1};
vector<vi> pos(12,vi());

void init(){
    cin>>K>>s;
    M = (K-1)/2;
    for(int i=0;i<8;++i) cin>>BD[i];
    unordered_map<char,vi> cnt;
    for(int i=0;i<K;++i) cnt[s[i]].push_back(i);
    for(int i=0;i<8;++i) for(int j=0;j<8;++j) if(cnt.count(BD[i][j])){
        for(int r:cnt[BD[i][j]]) pos[r].push_back(i*8 + j);
    }
    for(int i=0;i<64;++i) for(int j=i+1;j<64;++j){
        if(max(j/8-i/8, abs(j%8-i%8)) == 1) E[i][j] = E[j][i] = true;
    }
}
vl findSeries(int start,int end,int l,int r){
    if(isDp[start][end][l][r]) return dp[start][end][l][r];
    isDp[start][end][l][r] = true;
    if(r == l+1){
        if(E[start][end] && BD[start/8][start%8]==s[l] && BD[end/8][end%8]==s[r])
            dp[start][end][l][r].push_back((1LL<<start)|(1L<<end));
        return dp[start][end][l][r];
    }
    int c = (l+r)/2;
    for(int junc: pos[c]){
        vl prev = findSeries(start, junc, l, c), post = findSeries(junc, end, c, r);
        for(long st1:prev) for(long st2:post) if((st1&st2)==(1L<<junc)) dp[start][end][l][r].push_back(st1 | st2);
    }
    return dp[start][end][l][r];
}

int main(){
    std::ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    init();
    int ans = 0;
    if(K==1){
        cout<<(int)pos[0].size()<<endl;
        return 0;
    }
    if(K==2){
        for(int i:pos[0]) for(int j:pos[1]) if(E[i][j]) ++ans;
        cout<<ans<<endl;
        return 0;
    }
    memset(isDp, 0, sizeof(isDp));
    for(int start:pos[0]) for(int end:pos[K-1]) for(int junc:pos[M]){
        vl prev = findSeries(start, junc, 0, M), post = findSeries(junc, end, M, K-1);
        for(long st1:prev) for(long st2:post) if((st1&st2)==(1L<<junc)) ++ans;
    }
    cout<<ans<<endl;
    return 0;
}
