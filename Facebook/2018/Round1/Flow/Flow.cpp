
//
//  Created by Zebo Li on 7/7/18.
//  Copyright © 2017 Zebo Li. All rights reserved.
//

#include<cassert>
#include<string>
#include<iostream>
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



void solve(LL t){
    vector<string> A(3);
    cin >> N;
    for(int i=0; i<3; ++i) cin >> A[i];
    vector<vL> dp(N+1, vL(3, 0L));
    dp[0][0] = 1L;
    bool imp = false;
    for(int i=1; i<=N && !imp; ++i){
        imp = true;
        if(A[0][i-1] == '.' && A[1][i-1] == '.') {
            dp[i][0] = dp[i-1][1];
            dp[i][1] += dp[i-1][0];
            imp = false;
        }
        if(A[2][i-1] == '.' && A[1][i-1] == '.'){
            dp[i][1] += dp[i-1][2];
            dp[i][2] = dp[i-1][1];
            imp = false;
        }
        for(int j=0; j<3; ++j) dp[i][j]%=MOD;
    }
    cout<<"Case #" << t << ": " << dp[N][2] << endl;
    cerr<<"Case #" << t << ": " << dp[N][2] << endl;
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
