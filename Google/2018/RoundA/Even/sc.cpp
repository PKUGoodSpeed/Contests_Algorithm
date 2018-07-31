
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


void solve(LL t){
    cin >> N;
    LL ans = N, a = 0, b = 0;
    vi D;
    while(ans){
        D.push_back(ans%10);
        ans /= 10;
    }
    reverse(D.begin(), D.end());
    vi A(D.size(), 0), B(D.size(), 8);
    int i = 0;
    while(i<D.size() && D[i]%2 == 0){
        A[i] = B[i] = D[i];
        ++i;
    }
    if(i<D.size()){
        if(D[i]<=7) {
            A[i] = D[i] + 1;
            B[i] = D[i] - 1;
            for(int i=0; i<D.size(); ++i){
                a = a*10 + A[i];
                b = b*10 + B[i];
            }
            ans = min(a-N, N-b);
        }
        else{
            B[i] = D[i] - 1;
            for(int i=0; i<D.size(); ++i){
                b = b*10 + B[i];
            }
            ans = N - b;
        }
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
