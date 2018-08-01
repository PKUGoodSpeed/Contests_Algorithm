
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

const LL MOD = 1000000007;
LL T, N;
vL K;

LL mu(LL x, LL y){ return (x * y) % MOD; }
LL ad(LL x, LL y){ return (x + y) % MOD; }
LL pwr(LL x, LL n){
    LL ans = 1;
    while(n){
        if(n%2) ans = mu(ans, x);
        x = mu(x, x);
        n /= 2;
    }
    return ans;
}


void solve(LL t){
    cin >> N;
    K.resize(N);
    for(LL i=0; i<N; ++i) cin >> K[i];
    vL P(N+1, 0L);
    for(int i=1; i<=N; ++i) P[i] = P[i-1] + K[i-1];
    LL ans = 0;
    for(LL i=0; i<N-1; ++i){
        LL tmp = (P[N] - P[N-i-1] - P[i+1] + P[0]) % MOD;
        ans = ad(ans, mu(pwr(2L, i), tmp));
    }
    cout<<"Case #" << t << ": " << ans << endl;
    cerr<<"Case #" << t << ": " << ans << endl;
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
