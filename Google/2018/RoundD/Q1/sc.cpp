
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


LL T, N, O, D, X1, X2, A, B, C, M, L;


void solve(LL t){
    cin >> N >> O >> D;
    vector<LL> S(N, 0);
    
    cin >> S[0] >> S[1] >> A >> B >> C >> M >> L;
    bool impossible = true;
    for(LL i=2; i<N; ++i) {
        S[i] = (A * S[i-1] + B * S[i-2] + C)%M;
    }
    for(LL i=0; i<N; ++i) {
        S[i] += L;
    }
    vL P(N+1, 0L);
    map<LL, int> cnt;
    for(int i=1; i<=N; ++i){
        P[i] = P[i-1] + S[i-1];
    }
    int i = 0, j = 0, odd = 0;
    LL ans = LL(-3E18);
    while(i<N && j<=N){
        while(j<=N && odd <= O){
            auto it = cnt.lower_bound(P[j] - D);
            if(it != cnt.end()){
                impossible = false;
                ans = max(ans, P[j] - it->first);
            }
            cnt[P[j]]++;
            if(j==N) break;
            if(S[j]%2) odd++;
            j++;
        }
        if(j==N && odd<=O) break;
        while(i<j && odd>O){
            if(S[i]%2) odd--;
            cnt[P[i]]--;
            if(!cnt[P[i]]) cnt.erase(P[i]);
            ++i;
        }
    }
    if(impossible){
        cout<<"Case #" << t << ": " << "IMPOSSIBLE" << endl;
        cerr<<"Case #" << t << ": " << "IMPOSSIBLE" << endl;
    }
    else{
        cout<<"Case #" << t << ": " << ans << endl;
        cerr<<"Case #" << t << ": " << ans << endl;
    }
}


int main(int argc, char *argv[]) {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    assert(argc > 1);
    std::ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    freopen(argv[1],"r",stdin);
    freopen("output.txt","w",stdout);
    cin>>T;
    cerr<<T<<endl;
    for(LL t=1; t<=T; ++t) solve(t);
    return 0;
}
