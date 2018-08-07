
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

const LL M = 1000000007;
LL T, R, C;
LL ad(LL x, LL y){
    return (x + y) % M;
}
LL mu(LL x, LL y){
    return (x * y) % M;
}
LL pwr(LL x, LL n){
    LL ans = 1;
    while(n){
        if(n%2) ans = mu(ans, x);
        x = mu(x, x);
        n /= 2;
    }
    return ans;
}
LL di(LL x){
    return pwr(x, M-2);
}

void solve(LL t){
    cin >> R >> C;
    if(C > R) swap(C, R);
    --C;
    --R;
    LL A = mu(2, mu(R, C));
    A += mu(4, R);
    A += M - mu(C, C);
    A += M - C;
    A += 2;
    A %= M;
    A = mu(A, C);
    A = mu(A, C+1);
    A = mu(A, di(12));
    LL ans = A%M;
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
