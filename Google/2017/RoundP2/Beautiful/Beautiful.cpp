
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


LL T, N;

LL getCnt(LL N, LL k, LL c){
    LL i = 0, cnt = 0;
    for(i=0; i<k&&cnt<=(N/c); ++i){
        cnt = cnt*c + 1;
    }
    if(i < k) cnt = N+1;
    return cnt;
}

void solve(LL t){
    cin >> N;
    LL k = LL(log(double(N))/log(2.)) + 3;
    LL ans = -1;
    while(k > 1){
        LL l = max(2, (int)pow(double(N), 1./k)), r = (int)pow(double(N), 1./(k-1)) + 1;
        //cerr << l <<' '<< r << ' ' << k << endl;
        while(l < r - 1 && ans < 0){
            LL c = (l+r)/2;
            LL cnt = getCnt(N, k, c);
            if(cnt <= N) l = c;
            else r = c;
        }
        if(getCnt(N, k, l) == N){
            ans = l;
        }
        --k;
    }
    if(ans < 0) ans = N-1;
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
