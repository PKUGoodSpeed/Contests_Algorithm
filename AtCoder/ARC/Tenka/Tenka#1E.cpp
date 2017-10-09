
/*
 ***
 Question Name: CARtesian Coodinate
 ***
 Question Link: http://tenka1-2017.contest.atcoder.jp/tasks/tenka1_2017_e
 ***
 Given a set of lines, among which there are no parallel lines. Also none of those lines is parallel to x or y-axes. At each intersection point of each pair of line, there is a old car. Old car can only move along the direction of x or y-axes. Find a point in the plane tha can minimize the total path for moving all the cars towards that point.
 ***
 Idea:
 1. The path are Manhattan distances, therefore the minimum point lies at the midian of x's and y's. (Need to remember this conclusion. It is stupid to use ternary search to find the minimum.)
 2. Sliding x-axis and y-axis, then the number of intersection points that are swipted by the axes equals the number of inversions in the y/x-intersection array from the original order, which is the order of when x-axis is at y->-inf or y-axis is located at x->inf.
 3. Using mergeSort() to compute the number of inversions in an array.
 4, Use bi-section search to locate the x and y coordinates, which is the coordinates of the target point.
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
    int N,K;
    const ld e = 1.e-14, err = 1.e-11;
    ld Mx,mx,My,my;
    vector<vi> Ls;
    inline bool gt(ld x, ld y) { return x > y+e; }
    int mergeSort(vector<ld> &A, int l, int r){
        if(r-l <= 1) return 0;
        if(r-l==2){
            if(A[l] < A[l+1]) return 0;
            swap(A[l], A[l+1]);
            return 1;
        }
        int c = (l+r)/2, ans = 0;
        ans += mergeSort(A, l, c);
        ans += mergeSort(A, c, r);
        vector<ld> tmp(r - l, 0);
        int i = 0, j = 0;
        while(i< c-l || j <r-c){
            if(i == c-l) {
                tmp[i+j] = A[c+j];
                ++j;
            }
            else if(j==r-c) {
                tmp[i+j] = A[l+i];
                ++i;
            }
            else if(A[l+i] < A[c+j]){
                tmp[i+j] = A[l+i];
                ++i;
            }
            else{
                ans += c-l-i;
                tmp[i+j] = A[c+j];
                ++j;
            }
        }
        copy(tmp.begin(), tmp.end(), A.begin()+l);
        return ans;
    }
    
    int cntX(ld x){
        vector<ld> tmp;
        for(auto vec: Ls) tmp.push_back(ld(vec[2] - vec[0]*x)/vec[1]);
        return mergeSort(tmp, 0, N);
    }
    int cntY(ld y){
        vector<ld> tmp;
        for(auto vec: Ls) tmp.push_back(ld(vec[2] - vec[1]*y)/vec[0]);
        return mergeSort(tmp, 0, N);
    }
    void initX(){
        for(auto &vec: Ls) if(vec[1]<0){
            for(int i=0;i<3;++i) vec[i] *= -1;
        }
        sort(Ls.begin(), Ls.end(), [](const vi&A, const vi&B){return A[0]*B[1] < B[0]*A[1];});
    }
    void initY(){
        for(auto &vec: Ls) if(vec[1]<0){
            for(int i=0;i<3;++i) vec[i] *= -1;
        }
        sort(Ls.begin(), Ls.end(), [](const vi&A, const vi&B){
            if((ld(A[0])/A[1]) * (ld(B[0])/B[1]) >= 0) return ld(-A[0])/A[1] < ld(-B[0])/B[1];
            else if(ld(A[0])/A[1] < 0) return true;
            return false;
        });
    }
    ld findX(){
        initX();
        ld xl = mx, xr = Mx;
        while(xr - xl > err){
            ld c = (xl + xr)/2.;
            if(cntX(c) < (K+1)/2) xl = c;
            else xr = c;
        }
        return (xl + xr)/2.;
    }
    ld findY(){
        initY();
        ld yl = my, yu = My;
        while(yu - yl > err){
            ld c = (yl + yu)/2.;
            if(cntY(c) < (K+1)/2) yl = c;
            else yu = c;
        }
        return (yl + yu)/2.;
    }
public:
    ldld solve(){
        cin>>N;
        K = N*(N-1)/2;
        for(int i=0;i<N;++i){
            vi vec(3);
            for(int i=0;i<3;++i) cin>>vec[i];
            Ls.push_back(vec);
        }
        Mx = My = 1.E10;
        mx = my = -1.E10;
        ld x = findX(), y = findY();
        return ldld(x, y);
    }
};

int main(){
    std::ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    auto ans = CARtesianCoordinate().solve();
    cout<<setprecision(15);
    cout<<ans.first<<' '<<ans.second<<endl;
    return 0;
}
