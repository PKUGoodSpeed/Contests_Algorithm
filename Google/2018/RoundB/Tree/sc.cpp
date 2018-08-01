
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


LL T, N, M, K;
vector<string> B;
vector<map<int, int>> R;

bool oK(map<int, int> &range, int level, int center){
    auto it = --range.upper_bound(center);
    return (it->first <= center - level) && (it->second >= center + level);
}


void solve(LL t){
    cin >> N >> M >> K;
    assert(K == 1);
    B.resize(N);
    R.clear();
    R.resize(N);
    for(int i=0; i<N; ++i){
        cin >> B[i];
        R[i][-5] = -5;
        R[i][200] = 200;
        auto j = B[i].find('#');
        while(j!=string::npos && j<M){
            auto k = B[i].find('.', j);
            if(k == string::npos) k = M;
            R[i][int(j)] = int(k) - 1;
            j = B[i].find('#', k);
        }
    }
    int ans = 0;
    for(int i=0; i<N; ++i) for(int j=0; j<M; ++j) if(B[i][j] == '#') {
        int cnt = 1;
        for(int level=1; i+level<N && oK(R[i+level], level, j); ++level) cnt += 2*level + 1;
        ans = max(cnt, ans);
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
