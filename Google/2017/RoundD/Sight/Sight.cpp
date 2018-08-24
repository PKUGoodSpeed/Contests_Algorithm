/*
 跟LIS 思路相似
 */

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


LL T, N, Ts, Tf;
vL S, F, D;
LL getNextTime(LL t, int i){
    LL k = (max(t, S[i]) - S[i] + F[i] - 1)/ F[i];
    return k*F[i] + S[i] + D[i];
}

void solve(LL t){
    cin >> N >> Ts >> Tf;
    S.resize(N-1);
    F.resize(N-1);
    D.resize(N-1);
    int ans = -1;
    for(int i=0; i<N-1; ++i) cin>>S[i]>>F[i]>>D[i];
    vL head{0L};
    for(int i=0; i<N-1; ++i){
        vL tmp(i+2);
        tmp[i+1] = getNextTime(head[i] + Ts, i);
        for(int j=i; j; --j) tmp[j] = min(getNextTime(head[j], i), getNextTime(head[j-1]+Ts, i));
        tmp[0] = getNextTime(head[0], i);
        swap(tmp, head);
    }
    while(ans < N-1 && head[ans+1] <= Tf) ++ans;
    if(ans == -1){
        cout<<"Case #" << t << ": " << setprecision(16)<< "IMPOSSIBLE" << endl;
        cerr<<"Case #" << t << ": " << setprecision(16) << "IMPOSSIBLE" << endl;
        return;
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
