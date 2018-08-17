
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
vector<vL> R;
vector<string> B;

void solve(LL t){
    cin >> N;
    B.resize(N);
    for(int i=0; i<N; ++i) cin>>B[i];
    vector<vi> R(N, vi()), C(N, vi());
    string ans = "POSSIBLE";
    for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) if(B[i][j]=='X'){
        R[i].push_back(j);
        C[j].push_back(i);
    }
    for(auto vec: R){
        bool ok = true;
        if(vec.empty() || vec.size()>2) ok = false;
        else if(vec.size()==1){
            if(C[vec[0]].size()!=1) ok = false;
        }
        else{
            if(C[vec[0]].size()!=2 || C[vec[1]].size()!=2 || C[vec[0]]!=C[vec[1]]) ok=false;
        }
        if(!ok){
            ans = "IMPOSSIBLE";
            break;
        }
    }
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
