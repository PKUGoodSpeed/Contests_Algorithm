
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


LL T, N, L;
LL A, B, C, D, X1, X2;
char c1, c2;
vector<string> dic;

void solve(LL t){
    cin >> L;
    dic.resize(L);
    for(int i=0; i<L; ++i) cin>>dic[i];
    cin >> c1 >> c2 >> N >> A >> B >> C >> D;
    string S;
    /* What a stupid mistake, need to refresh S at every iteration. */
    S += c1;
    S += c2;
    X1 = LL(c1);
    X2 = LL(c2);
    for(int j=2; j<N; ++j){
        LL X = ((A%D) * X2 + (B%D) * X1 + C%D) % D;
        char c = char(97 + X % 26);
        S += c;
        X1 = X2;
        X2 = X;
    }
    int ans = 0;
    for(string s: dic){
        cerr << s << endl;
        int length = s.size();
        vector<int> ref(260, 0), cnt(260, 0);
        for(char c: s) ref[int(c)]++;
        for(int i=0; i<length; ++i) cnt[int(S[i])]++;
        for(int i=0; i<=N-length; ++i){
            if(S[i] == s[0] && S[i+length-1] == s[length-1] && cnt==ref){
                ans++;
                break;
            }
            if(i<N-length){
                cnt[int(S[i])]--;
                cnt[int(S[i+length])]++;
            }
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
