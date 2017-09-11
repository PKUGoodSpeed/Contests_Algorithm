/*
 ***
 Question Name: ConvexScore
 ***
 Question Description:
 You are given N points (xi,yi) located on a two-dimensional plane. Consider a subset S of the N points that
 forms a convex polygon. Here, we say a set of points S forms a convex polygon when there exists a convex
 polygon with a positive area that has the same set of vertices as S. All the interior angles of the polygon
 must be strictly less than 180°.
 For a given set S, let n be the number of the points among the N points that are inside the convex hull of S
 (including the boundary and vertices). Then, we will define the score of S as 2^{n−|S|}.
 Compute the total score.
 ***
 Input:
 N
 x1 y1
 x2 y2
 ...
 xN yN
 ***
 Output:
 Total Score.
 
 ***
 Idea: count subsets
 */

#include <memory.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <functional>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>

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

int N;
vector<ii> PT;


// For mod questions
const LL MOD = 998244353;
int gcd(int x,int y){
    if(x<y) swap(x,y);
    if(!y) return x;
    return gcd(y, x%y);
}
inline LL Add(LL x,LL y){return (x+y)%MOD; }
inline LL Mul(LL x,LL y){return (x*y)%MOD; }
void Ad(LL &x, LL y){
    x += y;
    if(x >= MOD) x %= MOD;
}
void Mu(LL &x, LL y){
    x *= y;
    if(x >= MOD) x %= MOD;
}
LL Pow(LL x, LL k){
    LL ans = 1;
    while(k){
        if(1&k) Mu(ans, x);
        Mu(x, x);
        k >>= 1;
    }
    return ans;
}

class ConvexScore{
    vL pw2;
    vector<vb> coline;
    ii makeLine(int x, int y){
        if(!x) return ii(0,1);
        if(!y) return ii(1,0);
        int m = gcd(abs(x), abs(y));
        if(x >= 0) return ii(x/m, y/m);
        else return ii(-x/m, -y/m);
    }
    void init(int N){
        pw2.resize(N+1);
        pw2[0] = 1;
        for(int i=1;i<=N;++i) pw2[i] = Mul(pw2[i-1], 2);
        coline = vector<vb>(N,vb(N,false));
    }
    inline LL cntGroup(LL m){ return Add(pw2[m], MOD - 1 - m - m*(m-1)/2); }
    public:
    LL totalScore(int N, vector<ii> &PT){
        if(N<3) return 0;
        init(N);
        LL ans = 0, cnt = 0;
        for(int i=0;i<N;++i){
            map<ii,vi> line;
            for(int j=i+1;j<N;++j) if(!coline[i][j]){
                auto key = makeLine(PT[i].first-PT[j].first, PT[i].second-PT[j].second);
                line[key].push_back(j);
            }
            for(auto p:line){
                auto vec = p.second;
                int nv = (int)vec.size();
                if(nv<2) continue;
                Ad(cnt, cntGroup(nv+1));
                for(int j=0;j<nv;++j) for(int k = j+1;k<nv;++k) coline[vec[j]][vec[k]] = true;
            }
        }
        ans = Add(cntGroup(N), MOD - cnt);
        return ans;
    }
};


int main(){
    /*Write your code here*/
    cin>>N;
    PT.resize(N);
    for(int i=0;i<N;++i) cin>>PT[i].first>>PT[i].second;
    cout<<ConvexScore().totalScore(N, PT)<<endl;
    return 0;
}
