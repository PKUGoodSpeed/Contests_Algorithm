
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


LL T, N, K;
vL A;

int findIdx(LD v){
    int l = -1, r = N;
    while(l < r-1){
        int c = (l+r)/2;
        if(A[c] >= v) r = c;
        else l = c;
    }
    return r;
}

void solve(LL t){
    cin >> N >> K;
    A.resize(N);
    vL P(N+1, 0L);
    for(int i=0; i<N; ++i) cin>>A[i];
    sort(A.begin(), A.end());
    for(int i=1; i<=N; ++i) P[i] = P[i-1] + A[i-1];
    LD ans = LD(P[N])/N;
    for(int j=1; j<=K; ++j){
        int r = findIdx(ans);
        ans = LD(P[N]-P[r])/LD(N) + LD(r)/N * ans;
    }
    cout<<"Case #" << t << ": " << setprecision(12)<< ans << endl;
    cerr<<"Case #" << t << ": " << setprecision(12)<< ans << endl;
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
