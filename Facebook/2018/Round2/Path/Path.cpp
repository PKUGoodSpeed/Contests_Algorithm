
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


void solve(LL t){
    cin >> N >> K;
    vector<vL> E;
    LL ans = 0, Lo = 0, Sh = 0;
    E.push_back(vL{1, N, K});
    if(N==2 || K<3){
        ans = 0;
    }
    else{
        Lo = K;
        LL cur = K-1, i = 1;
        while(cur>1 && i<N){
            E.push_back(vL{i, i+1, cur});
            Sh += cur;
            ++i;
            --cur;
        }
        if(i<N && cur==1) {
            E.push_back(vL{i, N, 1});
            Sh += 1;
        }
        ans = Sh - Lo;
        if(ans < 0) ans = 0;
    }
    cout<<"Case #" << t << ": " << ans << endl;
    cout<<(int)E.size() << endl;
    for(auto vec: E) cout << vec[0] <<" "<<vec[1]<<" "<<vec[2]<<endl;
    cerr<<"Case #" << t << ": " << ans << endl;
    cerr<<(int)E.size() << endl;
    for(auto vec: E) cerr << vec[0] <<" "<<vec[1]<<" "<<vec[2]<<endl;
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
