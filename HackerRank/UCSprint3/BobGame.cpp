/*
 ***
 Question Name: Bob's Game
 ***
 Question Link: https://www.hackerrank.com/contests/university-codesprint-3/challenges/bobs-game
 ***
 Initially on a nxn chess board, there are m kings: 'K'. At every step, each player can move one of the kings towards up, left, upper-left by one cell. On the board there are obstacles: 'X', where the kings cannot move towards. Given a initial configuration, Bob is going to play first. Asking how many ways Bob has to move the first step in order to guarantee winning.
 ***
 Idea: Generate the states function g(i,j) for each king:
         g(i,j) = argmin k s.t. k is in {0, 1, 2, 3, ...} but k != g(i',j')
 where (i',j') is the state can be arrived from (i, j) by a single move.
 Which player is gonna win is determined by the XOR sum of g(i,j) for all the kings.
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

class BGame{
    int N;
    vector<string> chess;
    int dx[3] = {-1, 0, -1};
    int dy[3] = {0, -1, -1};
public:
    void solve(){
        cin>>N;
        chess.resize(N);
        for(int i=0;i<N;++i) cin>>chess[i];
        int xo_sum = 0, ans = 0;
        vector<vi> dp(N, vi(N,0));
        vector<vi> king_status;
        for(int i=0;i<N;++i) for(int j=0;j<N;++j) if(chess[i][j]!='X'){
            vi tmp(4,0);
            for(int k=0;k<3;++k){
                int x = i+dx[k], y = j+dy[k];
                if(x>=0 && y>=0 && chess[x][y]!='X') tmp[dp[x][y]]++;
            }
            for(dp[i][j]=0;tmp[dp[i][j]];dp[i][j]++);
            if(chess[i][j] == 'K'){
                tmp.push_back(dp[i][j]);
                king_status.push_back(tmp);
                xo_sum ^= dp[i][j];
            }
        }
        if(!xo_sum) cout<<"LOSE"<<endl;
        else{
            cout<<"WIN ";
            for(auto vec:king_status) ans += vec[xo_sum^vec[4]];
            cout<<ans<<endl;
        }
    }
};

int main(){
    std::ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    int Q;
    cin>>Q;
    for(int q=0;q<Q;++q) BGame().solve();
    return 0;
}

