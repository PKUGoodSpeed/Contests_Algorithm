
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


const LD error = 1.E-11;
LL T, N, M, W, X, Y, Z;

bool ableToAdjust(LD v, vL &height, vL &updiff, vL &downdiff){
    if(v < 0) return false;
    LD lower = height[0] - v, upper = height[0] + v;
    for(int i=1; i<N; ++i){
        lower = max(lower - downdiff[i-1], height[i] - v);
        upper = min(upper + updiff[i-1], height[i] + v);
        if(upper < lower) return false;
    }
    return true;
}



void solve(LL t){
    cin >> N >> M;
    vL h(N), u(N-1, 1E8), d(N-1, 1E8);
    cin >> h[0] >> h[1] >> W >> X >> Y >> Z;
    for(int i=2; i<N; ++i) h[i] = (W*h[i-2] + X*h[i-1] + Y)%Z;
    for(int i=0; i<M; ++i){
        LL A, B, U, D;
        cin >> A >> B >> U >> D;
        if(B < A){
            swap(A, B);
            swap(U, D);
        }
        for(int i=A-1; i<B-1; ++i){
            u[i] = min(u[i], U);
            d[i] = min(d[i], D);
        }
    }
    LD l = -1, r = 1000001;
    while(l+error < r){
        LD c = 0.5 * (l + r);
        if(ableToAdjust(c, h, u, d)) r = c;
        else l = c;
    }
    if(ableToAdjust(0, h, u, d)) r = 0.0;
    cout<<"Case #" << t << ": " << setprecision(12) << r << endl;
    cerr<<"Case #" << t << ": " << setprecision(12) << r << endl;
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
