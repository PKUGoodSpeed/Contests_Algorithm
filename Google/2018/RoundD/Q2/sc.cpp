
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
LL A, B, C, M;

bool comp(const vL& v1, const vL& v2){
    if(v1[0] - v1[1] == v2[0] - v2[1]) return v1[1] > v2[1];
    return v1[0] - v1[1] < v2[0] - v2[1];
}


void solve(LL t){
    cin>>N>>K;
    vector<vL> tow(N, vL(2, 0L));
    vector<vL> bal(K, vL(2, 0L));
    cin >> tow[0][0] >> tow[1][0] >> A >> B >> C >> M;
    for(int i=2; i<N; ++i){
        tow[i][0] = (A * tow[i-1][0] + B * tow[i-2][0] + C) % M + 1;
    }
    cin >> tow[0][1] >> tow[1][1] >> A >> B >> C >> M;
    for(int i=2; i<N; ++i){
        tow[i][1] = (A * tow[i-1][1] + B * tow[i-2][1] + C) % M + 1;
    }
    
    cin >> bal[0][0] >> bal[1][0] >> A >> B >> C >> M;
    for(int i=2; i<K; ++i){
        bal[i][0] = (A * bal[i-1][0] + B * bal[i-2][0] + C) % M + 1;
    }
    cin >> bal[0][1] >> bal[1][1] >> A >> B >> C >> M;
    for(int i=2; i<K; ++i){
        bal[i][1] = (A * bal[i-1][1] + B * bal[i-2][1] + C) % M + 1;
    }

    sort(tow.begin(), tow.end(), comp);
    vector<vL> er;
    er.push_back(vL{LL(-1E9-1L), 0L});
    for(int i=0; i<N; ++i){
        LL x0 = er.back()[0], y0 = er.back()[1];
        if(tow[i][0] + tow[i][1] > x0 + y0) er.push_back(tow[i]);
    }
    er.push_back(vL{LL(1E9) + 1L, 0L});

    sort(bal.begin(), bal.end());
    int i=0, j=0, ans = 0;
    for(int k=0; k<er.size()-1; ++k){
        while(j < K && bal[j][0]<= er[k+1][0]) ++j;
        for(int q=i; q<j; ++q){
            if((bal[q][0] - er[k][0] + bal[q][1] <= er[k][1]) || (er[k+1][0] - bal[q][0] + bal[q][1] <= er[k+1][1])){
                ++ans;
            }
        }
        i = j;
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
