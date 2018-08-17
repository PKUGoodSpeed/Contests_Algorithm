
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

bool cmp(const vL&A, const vL&B){
    if(A[0]+A[3] != B[0]+B[3]) return A[0] + A[3] < B[0] + B[3];
    return A[0] - A[3] < B[0] - B[3];
}

void solve(LL t){
    cin >> N;
    R = vector<vL>(N, vL(4, 0L));
    for(int i=0; i<N; ++i) cin >> R[i][0] >> R[i][1] >> R[i][2] >> R[i][3];
    vi idx = {0, 1, 2};
    LL ans = LL(5E9);
    do{
        vector<vL> S(N, vL(4, 0L));
        for(int i=0; i<N; ++i) {
            for(int j=0; j<3; ++j) S[i][j] = R[i][idx[j]];
            S[i][3] = R[i][3];
        }
        sort(S.begin(), S.end(), cmp);
        vector<map<LL, int>> LEFT(3), RIGHT(3);
        for(vL vec: S) for(int i=0; i<3; ++i) {
            ++RIGHT[i][vec[i] + vec[3]];
            ++RIGHT[i][vec[i] - vec[3]];
        }
        for(vL vec: S){
            LL l = 0L, r = 0L;
            for(int i=0; i<3; ++i){
                ++LEFT[i][vec[i] + vec[3]];
                ++LEFT[i][vec[i] - vec[3]];
                --RIGHT[i][vec[i] + vec[3]];
                --RIGHT[i][vec[i] - vec[3]];
                if(!RIGHT[i][vec[i]-vec[3]]) RIGHT[i].erase(vec[i]-vec[3]);
                if(!RIGHT[i][vec[i]+vec[3]]) RIGHT[i].erase(vec[i]+vec[3]);
                if(!RIGHT[i].empty()){
                    r = max(r, (--RIGHT[i].end())->first - RIGHT[i].begin()->first);
                }
                l = max(l, (--LEFT[i].end())->first - LEFT[i].begin()->first);
            }
            ans = min(ans, max(l, r));
        }
    }while(next_permutation(idx.begin(), idx.end()));
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
