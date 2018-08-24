/*
 偶数情况下的corner case 一直没弄对，其实就是在loop的过程中，排除k=1，也就是刚好4个部门的情况即可。
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


LL T, Max, Min, Mea, Med;
vector<vL> R;

void solve(LL t){
    cin >> Min >> Max >> Mea >> Med;
    int ans = 0;
    if(Min == Max){
        if(Min == Mea && Min == Med) ans = 1;
        else ans = -1;
    }
    else if(Max < Min) ans = -1;
    else if(Max > Min){
        if(Med > Max || Med < Min || Mea >= Max || Mea <= Min) ans = -1;
        else if(Max + Min == 2*Mea && Mea == Med) ans = 2;
        else if(Min + Max + Med == 3 * Mea) ans = 3;
        else if(Min + Max + 2*Med == 4 * Mea) ans = 4;
        else if(Min + Max + Med > 3*Mea){
            if(Min + Med >= 2*Mea) ans = -1;
            else{
                long k = (Max - Mea - 1)/(2*Mea - Med - Min);
                if(Max + Min + (k+1)*Med + (k-1)*Min <= (2*k+2) * Mea && k > 1) ans = 2*k + 2;
                else ans = 2*k + 3;
            }
        }
        else if(Min + Max + Med < 3*Mea){
            if(Max + Med <= 2*Mea) ans = -1;
            else{
                long k = (Mea - Min -1)/(Max + Med - 2*Mea);
                if(Max + Min + (k-1)*Max + (k+1)*Med >= (2*k+2) * Mea && k > 1) ans = 2*k + 2;
                else ans = 2*k +3;
            }
        }
    }
    if(ans == -1){
        cout<<"Case #" << t << ": " << setprecision(16)<< "IMPOSSIBLE" << endl;
        cerr<<"Case #" << t << ": " << setprecision(16) << "IMPOSSIBLE" << endl;
    }
    else {
        cout<<"Case #" << t << ": " << setprecision(16)<< ans << endl;
        cerr<<"Case #" << t << ": " << setprecision(16) << ans << endl;
    }
    
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
