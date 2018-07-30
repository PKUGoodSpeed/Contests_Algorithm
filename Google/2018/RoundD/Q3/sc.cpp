
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


LL T, R, C, W;
vector<string> dic;

int gcd(int x, int y){
    if(x < y) swap(x, y);
    if(!y) return x;
    return gcd(y, x%y);
}


void solve(LL t){
    cin>>R>>C>>W;
    vector<string> B(R);
    for(int i=0; i<R; ++i) cin>>B[i];
    vector<vi> S(R+1, vi(C+1, 0)), J(R, vi(C, 0));
    dic.resize(W);
    for(int i=0; i<W; ++i) cin>>dic[i];
    unordered_set<char> pool;
    for(string s: dic) pool.insert(s[0]);
    for(int i=0; i<R; ++i) for(int j=0; j<C; ++j){
        J[i][j] = pool.count(B[i][j]);
    }
    for(int i=1; i<=R; ++i) for(int j=1; j<=C;++j){
        S[i][j] = S[i][j-1] + S[i-1][j] + J[i-1][j-1] - S[i-1][j-1];
    }
    ii ans = ii(0, 1);
    int cnt = 0;
    for(int i=0;i<R;++i) for(int j=i+1;j<=R;++j) for(int k=0; k<C;++k) for(int l=k+1; l<=C; ++l){
        int d = 4 * (S[j][l] - S[j][k] - S[i][l] + S[i][k]), n = l + j - i - k;
        if(d * ans.second > n * ans.first){
            int m = gcd(d, n);
            ans = ii(d/m, n/m);
            cnt = 1;
        }
        else if(d * ans.second == n * ans.first){
            ++cnt;
        }
    }
    
    cout<<"Case #" << t << ": " << ans.first <<"/" << ans.second<<" "<<cnt << endl;
    cerr<<"Case #" << t << ": " << ans.first <<"/" << ans.second<<" "<<cnt << endl;
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
