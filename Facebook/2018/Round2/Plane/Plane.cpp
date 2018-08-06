
//
//  Created by Zebo Li on 7/7/18.
//  Copyright © 2017 Zebo Li. All rights reserved.
//

#include<cassert>
#include<string>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<memory.h>
#include<math.h>
#include<vector>
#include<algorithm>
#include<map>
#include<numeric>
#include<deque>
#include<set>
#include<functional>
#include<queue>
#include<stack>
#include<unordered_set>
#include<unordered_map>


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

//const LL M = 1000000007;
LL T, N, S, E;
vector<pLL> C;
unordered_map<LL, int> Xm, Ym;
LL dp[55][55][55][55];
/*
void solve(LL t){
    cin >> N >> S >> E;
    Xm.clear();
    Ym.clear();
    C.resize(N)
    for(int i=0; i<N; ++i){
        cin>> C[i].first >> C[i].second;
    }
    sort(C.begin(), C.end());
    set<LL> tmp1, tmp2;
    for(auto p: C){
        tmp1.insert(p.first);
        tmp2.insert(p.second);
    }
    int i;
    i = 1;
    for(auto k: tmp1){
        Xm[k] = i;
        ++i;
    }
    i = 1;
    for(auto k: tmp2){
        Ym[k] = i;
        ++i;
    }
    for(auto &p: C){
        p.first = Xm[p.first];
        p.second = Ym[p.second];
    }
    memset(dp, 0, sizeof(dp));
    dp[0][55][0][55] = 1;
    
    
    for(int i=0; i<N; ++i) getline(cin, names[i]);
    string ans = names[0];
    for(string s: names){
        if(cmp(s, ans)) ans = s;
    }
    cout<<"Case #" << t << ": " << ans << endl;
    cerr<<"Case #" << t << ": " << ans << endl;
}
*/

class Solution {
    typedef vector<int> vi;
    typedef pair<string, vi> svi;
    const int inf = 1E8;
    string reduce(string s, int i){
        assert(i<s.size());
        int j = i, k = i;
        while(j>=0 && s[j]==s[i]) --j;
        while(k<s.size() && s[k]==s[i]) ++k;
        while(j>=0 && k<s.size() && s[j]==s[k] && ((j && s[j]==s[j-1]) || (k<s.size()-1 && s[k]==s[k+1]))){
            char c = s[j];
            while(j>=0 && s[j]==c) --j;
            while(k<s.size() && s[k]==c) ++k;
        }
        assert(j<i && k>i);
        cout<<j<<' '<<k<<endl;
        if(k< s.size()) return s.substr(0, j+1) + s.substr(k);
        return s.substr(0, j+1);
    }
    int getIdx(char c){
        switch(c){
            case 'R': return 0;
            case 'Y': return 1;
            case 'B': return 2;
            case 'G': return 3;
            case 'W': return 4;
        }
        return -1;
    }
    map<svi, int> dp;
    int dfs(string s, vi &v){
        cout << s << endl;
        for(auto k: v) cout << k <<' ';
        cout << endl;
        if(s.empty()) return 0;
        //if(dp.count(svi(s, v))) return dp[svi(s, v)];
        //dp[svi(s, v)] = inf;
        int ans = inf;
        int cnt = 1, n = s.size();
        for(int i=1; i<n; ++i){
            if(s[i]==s[i-1]) ++cnt;
            else {
                if(cnt + v[getIdx(s[i-1])] >= 3){
                    v[getIdx(s[i-1])] += cnt - 3;
                    //dp[svi(s, v)] = min(dp[svi(s, v)], 3 - cnt + dfs(reduce(s, i-1), v));
                    cout<<s << ' '<< i-1<<' '<<reduce(s, i-1)<<endl;
                    assert(s.size() >= reduce(s, i-1).size());
                    ans = min(ans, 3-cnt + dfs(reduce(s, i-1), v));
                    v[getIdx(s[i-1])] += 3 - cnt;
                }
                cnt = 1;
            }
        }
        if(cnt + v[getIdx(s[n-1])] >= 3){
            v[getIdx(s[n-1])] += cnt - 3;
            //dp[svi(s, v)] = min(dp[svi(s, v)], 3 - cnt + dfs(reduce(s, n-1), v));
            ans = min(ans, 3-cnt + dfs(reduce(s, n-1), v));
            v[getIdx(s[n-1])] += 3 - cnt;
        }
        //return dp[svi(s, v)];
        return ans;
    }
public:
    int findMinStep(string board, string hand) {
        vi init(5, 0);
        for(char c: hand) init[getIdx(c)]++;
        int ans = dfs(board, init);
        if(ans == inf) return -1;
        return ans;
    }
};

int main(int argc, char *argv[]) {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    //assert(argc > 1);
    //std::ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    //freopen(argv[1],"r",stdin);
    //freopen("output.txt","w",stdout);
    //cin>>T;
    //cerr<<T<<endl;
    //for(LL t=1; t<=T; ++t) solve(t);
    string board = "WWRRBBWW", hand="WRBRW";
    int ans = Solution().findMinStep(board, hand);
    cout << ans << endl;
    return 0;
}
