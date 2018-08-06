
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


LL T, N, M, A, B;
vL P, D;

LL findCandy(LL j, LL &g){
    if(D[j]>0){
        g = 1;
        D[j]--;
        return j;
    }
    if(j==0) return 0;
    return P[j] = findCandy(P[j], g);
}


void solve(LL t){
    cin >> N >> M >> A >> B;
    P = vL(N, 0);
    D = vL(N, 0);
    for(LL i=1; i<N; ++i) cin>>P[i];
    for(LL i=0; i<M; ++i){
        LL C = (A * i + B) % N;
        ++D[C];
    }
    LL ans = 0;
    for(LL j=N-1; j>=0; --j){
        LL g = 0L;
        findCandy(j, g);
        ans += g * j;
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
