
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


LL T, N, A, B, C1, C2, M;
vector<pLL> I;

void solve(LL t){
    cin >> N;
    I.resize(N);
    cin >> I[0].first >> I[0].second >> A >> B >> C1 >> C2 >> M;
    for(int i=1; i<N; ++i){
        I[i].first = (I[i-1].first * A + I[i-1].second * B + C1) % M;
        I[i].second = (I[i-1].second * A + I[i-1].first * B + C2) % M;
    }
    for(int i=0; i<N; ++i) if(I[i].first > I[i].second) I[i] = pLL(I[i].second, I[i].first);
    sort(I.begin(), I.end());
    map<LL, LL> R1, R2, R3;
    R1[-10L] = R2[-10L] = R3[-10L] = -10L;
    R1[LL(2E9)] = R2[LL(2E9)] = R3[LL(2E9)] = LL(2E9);
    LL s1 = -10L, e1 = -10L, s2 = -10L, e2 = -10L, total = -2L, ans = 0L;
    for(auto p: I){
        if(p.first > e1){
            R1[s1] = e1;
            s1 = p.first;
            e1 = p.second;
        }
        else{
            LL l = p.first, r = min(p.second, e1);
            e1 = max(p.second, e1);
            if(l > e2){
                R2[s2] = e2;
                s2 = l;
                e2 = r;
            }
            else{
                e2 = max(e2, r);
            }
        }
    }
    R1[s1] = e1;
    R2[s2] = e2;
    for(auto p: R1){
        total += p.second - p.first + 1L;
    }
    auto i1 = R1.begin(), i2 = R2.begin();
    while(i1 != R1.end()){
        int l = i1->first, r = i1->first;
        while(i2!=R2.end() && i2->second <= i1->second){
            r = i2->first - 1;
            if(l<=r) R3[l] = r;
            l = i2->second + 1;
            ++i2;
        }
        r = i1->second;
        if(l <= r) R3[l] = r;
        ++i1;
    }
    for(auto p: I){
        LL tmp = 0L;
        auto it = --R3.upper_bound(p.first);
        while(it!=R3.end() && it->first <= p.second){
            LL l = max(it->first, p.first);
            LL r = min(it->second, p.second);
            if(l <= r) tmp += (r-l+1L);
            ++it;
        }
        ans = max(ans, tmp);
    }
    ans = total - ans;
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
