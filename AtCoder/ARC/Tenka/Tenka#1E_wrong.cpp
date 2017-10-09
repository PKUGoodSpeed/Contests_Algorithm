/*
 ***
 Question Name:CARtesian Coordinate
 ***
 Question Link: http://tenka1-2017.contest.atcoder.jp/tasks/tenka1_2017_e
 ***
 Find a point which is minimizely away from all the intersection points of N lines
 ***
 Idea: Here I use ternary search to go through all the points, which runs into problem due to the large scale.
 */

#include <memory.h>
#include <ctime>
#include <random>
#include <iomanip>
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

typedef long double ld;
typedef vector<int> vi;
typedef vector<long> vl;
typedef vector<bool> vb;
typedef vector<double> vd;
typedef pair<int,int> ii;
typedef pair<long, long> ll;
typedef unordered_set<int> ui;
typedef pair<ld, ld> ldld;

class CARtesianCoordinate{
    const ld C1 = 5./11., C2 = 6./11., err = 1.E-10;
    bool gt(ld x, ld y){
        return x > y + 1.e-14;
    }
    ld Mx, mx, My, my;
    vector<ldld> pts;
    inline ld dis(ldld pt, ld x, ld y){
        return fabsl(x - pt.first) + fabsl(y - pt.second);
    }
    inline ld sumDis(ld x, ld y){
        ld ans = 0.;
        for(auto pt:pts) ans += dis(pt, x, y);
        return ans;
    }
    inline ldld crossPoint(int A1, int B1, int C1, int A2, int B2, int C2){
        assert(A1*B2 != A2*B1);
        return ldld((ld)(C1*B2 - C2*B1)/(A1*B2 - A2*B1), (ld)(C1*A2 - C2*A1)/(B1*A2 - B2*A1));
    }
    void init(){
        int N;
        cin>>N;
        //pts.push_back(ldld((ld)0., (ld)0.));
        vector<vi> lines;//{vi{0, 1, 0}, vi{1, 0, 0}};
        Mx = mx = My = my = (ld)0.;
        for(int i=0;i<N;++i){
            int A, B, C;
            cin>>A>>B>>C;
            for(auto vec:lines){
                auto pt = crossPoint(A, B, C, vec[0], vec[1], vec[2]);
                Mx = max(Mx, pt.first);
                mx = min(mx, pt.first);
                My = max(My, pt.second);
                my = min(my, pt.second);
                pts.push_back(pt);
            }
            lines.push_back(vi{A, B, C});
        }
    }
    ld opt1(ld &x, ld y){
        ld xl = mx, xr = Mx;
        while(xr - xl > err){
            ld x1 = xl*C2 + xr*C1, x2 = xl*C1 + xr*C2;
            ld res1 = sumDis(x1, y), res2 = sumDis(x2, y);
            if(gt(res1, res2)) xl = x1;
            else xr = x2;
        }
        x = (xl + xr)/2.;
        return sumDis(x, y);
    }
    ld opt2(ld &x, ld &y){
        ld yl = my, yu = My, x1 = 0., x2 = 0.;
        while(yu - yl > err){
            ld y1 = yl*C2 + yu*C1, y2 = yl*C1 + yu*C2;
            ld res1 = opt1(x1, y1), res2 = opt1(x2, y2);
            if(gt(res1,res2)) yl = y1;
            else yu = y2;
        }
        x = (x1+x2)/2.;
        y = (yl+yu)/2.;
        return sumDis(x, y);
    }
public:
    ldld solve(){
        init();
        ld x = 0., y = 0.;
        opt2(x, y);
        return ldld(x,y);
    }
};

int main(){
    std::ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    auto ans = CARtesianCoordinate().solve();
    cout<<setprecision(12);
    cout<<ans.first<<' '<<ans.second<<endl;
    return 0;
}
