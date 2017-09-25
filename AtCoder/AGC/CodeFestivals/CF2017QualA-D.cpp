/*
 ***
 Question Name: Four Coloring
 ***
 Question Link: http://code-festival-2017-quala.contest.atcoder.jp/tasks/code_festival_2017_quala_d
 ***
 Question Description:
 Give a H X M matrix, coloring its cells using four colors: Red, Yellow, Blue, Green. The Coloring need to satisfy that for any two cells whose Manhattan distance |x1 - x2| + |y1 - y2| = d (d is a given number), should be colored using different colors.
 Idea:
 1, Rotate the matrix by 45 degree.
 s.t. x' = x+y and y' = x-y. Then we actually convert the Manhattan distance of the original matrix in to the Chebyshev distance of the new matrix, which is max(|x1' - x2'|, |y1' - y2'|).
 2, Build squares with edges equal to d.
 3, Coloring the squares using the four different colors so that neighboring squares are colored with different colors, which is easy to accomplish.
 4, In this way we make sure that: (1) within one square, there is no two celss whose Chebyshev distance or the Manhattan distance equal to d (less that d). (2) for two cells from two different squares that are colored with the same color, the distance between them must larger than d.
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

typedef long long LL;
typedef long double LD;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<LL> vL;
typedef vector<bool> vb;
typedef unordered_set<int> ui;
typedef pair<LL,LL> pLL;

class FourColoring{
    vector<string> Templ= {"RY","BG"};
public:
    void solve(int H,int M, int d){
        for(int i=0;i<H;++i){
            for(int j=0;j<M;++j) cout<<Templ[((i+j+H+M)/d)%2][((i-j+H+M)/d)%2];
            cout<<endl;
        }
    }
};

int main(){
    int H,M,d;
    cin>>H>>M>>d;
    FourColoring().solve(H, M, d);
    return 0;
}
