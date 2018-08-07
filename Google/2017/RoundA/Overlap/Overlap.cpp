
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


LL T;

string A;
string B;

bool matCh(string C, string D){
    int n = C.size(), m = D.size();
    vector<vb> dp(n+1, vb(m+1, false));
    dp[n][m] = true;
    for(int i=n-1; i>=0 && C[i]=='*'; --i) dp[i][m] = true;
    for(int j=m-1; j>=0 && D[j]=='*'; --j) dp[n][j] = true;
    for(int i=n-1; i>=0; --i) for(int j=m-1; j>=0; --j){
        if(C[i]=='*' && D[j]=='*') dp[i][j] = dp[i][j+1] || dp[i+1][j] || dp[i+1][j+1];
        else if(C[i]=='*' && D[j]!='*') dp[i][j] = dp[i+1][j] || dp[i+1][j+1];
        else if(C[i]!='*' && D[j]=='*') dp[i][j] = dp[i][j+1] || dp[i+1][j+1];
        else dp[i][j] = (C[i] == D[j]) && dp[i+1][j+1];
    }
    return dp[0][0];
}

void solve(LL t){
    cin >> A >> B;
    string C, D;
    for(char c: A) {
        if(c == '*') for(int i=0; i<4; ++i) C += c;
        else C += c;
    }
    for(char d: B){
        if(d == '*') for(int i=0; i<4; ++i) D += d;
        else D += d;
    }
    cerr<<C<<endl<<D<<endl;
    string ans = (matCh(C, D)? "TRUE":"FALSE");
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
