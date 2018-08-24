
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


LL T, N, Q;

int getNOne(int n){
    int cnt = 0;
    while(n){
        n &= (n-1);
        ++cnt;
    }
    return cnt;
}

void solve(LL t){
    cin >> N >> Q;
    vector<int> P(N), S(N+1, 0);
    for(int i=0; i<=N; ++i) {
        string s;
        cin>>s;
        for(int j=0; j<Q; ++j) if(s[j]=='T') S[i] |= (1<<j);
    }
    for(int i=0; i<N; ++i) cin>> P[i];
    int ans = 0;
    for(int k=0; k<(1<<Q); ++k){
        bool ok = true;
        for(int i=0; i<N&&ok; ++i){
            int score = Q - getNOne(S[i] ^ k);
            if(score != P[i]) ok = false;
        }
        if(ok){
            int score = Q - getNOne(S[N] ^ k);
            ans = max(ans, score);
        }
    }
    

    cout<<"Case #" << t << ": " << setprecision(16)<< ans << endl;
    cerr<<"Case #" << t << ": " << setprecision(16) << ans << endl;
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
