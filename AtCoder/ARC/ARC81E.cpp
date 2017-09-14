/*
 ***
 Question Name: Don't Be a Subsequence
 ***
 Question Link: http://arc081.contest.atcoder.jp/tasks/arc081_c
 
 ***
 Idea: Using dp: (let the input string be S)
    dp[i] = the minLength of the string that is not a subsequence of S.substr(i)
    define a vector<vector<int>> next: next[c - 'a'][i] is the first position that a char (c) appears couning from i;
    Then if( there is a c s.t. next[c-'a][i] == S.size()) dp[i] = 1, the corresponding string is string(c)
    The derivation is : dp[i] = min_j in [0,25](1 + dp[next[j][i]+1]).
    Every time, we need to record the optimal choice: which char we would choose
    One corner case is when i == S.size(), dp[i] = 1, the corresponding choice is "a".
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


class NotSubsequence{
    vi dp;
    vector<char> to;
    vector<vi> next;
    string S;
    int N;
    void init(string &s){
        S = s;
        N = (int)s.size();
        dp = vi(N+1,-1);
        dp[N] = 1;
        to = vector<char>(N+1,'a');
        next = vector<vi>(26,vi(N,N));
        for(int i=N-1;i>=0;--i) for(int j=0;j<26;++j){
            if(S[i] == char((int)'a' + j)) next[j][i] = i;
            else next[j][i] = (i<N-1? next[j][i+1]:N);
        }
        return;
    }
    
    int minLength(int i){
        if(i>N) return 0;
        if(dp[i] >= 0) return dp[i];
        dp[i] = N+1;
        to[i] = 'z';
        for(int j=0;j<26;++j){
            int tmpl = 1 + minLength(next[j][i]+1);
            if(tmpl < dp[i]){
                dp[i] = tmpl;
                to[i] = (char)((int)'a' + j);
            }
        }
        return dp[i];
    }
    public:
    string solution(string s){
        if(s.empty()) return "a";
        init(s);
        int L = minLength(0), j = 0;
        assert(L > 0);
        string ans;
        while(true){
            ans += to[j];
            j = next[(int)(to[j]-'a')][j]+1;
            if(j>=N) break;
        }
        return ans;
    }
};

int main(){
    string s;
    cin>>s;
    cout<<NotSubsequence().solution(s)<<endl;
    return 0;
}
