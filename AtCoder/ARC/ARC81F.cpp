/*
 ***
 Question Name: FlipAndRectangles
 ***
 Question Link: http://arc081.contest.atcoder.jp/tasks/arc081_d
 
 ***
 Idea:  1. Define good/bad points： Intersection of 2X2 Square, if sum(#of'#')%2 == 0: good point; else: bad point
 2. It can be proved that, if a rectangle do not contain bad points, then we can use finite number of operations to turn it into black.
 3. Find the maximum rectangle that only contain good points.
 */

#include <memory.h>
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

class FlipAndRectangles{
    int di[4] = {0, 0, 1, 1};
    int dj[4] = {0, 1, 0, 1};
    int maxRecInLine(vi H){
        // Compute the max_rectangle in one dimension.
        if(H.empty()) return 0;
        H.insert(H.begin(), -2);
        H.push_back(-1);
        int n = (int)H.size(), ans = 0;
        stack<int> stk;
        stk.push(0);
        for(int i=1;i<n;++i){
            while(H[stk.top()] >= H[i]){
                int pivat = stk.top();
                stk.pop();
                ans = max(ans, (i - stk.top()) * (H[pivat]+1));
            }
            stk.push(i);
        }
        return ans;
    }
    public:
    int solution(vector<string> M){
        assert(!M.empty() && !M[0].empty());
        int n = (int)M.size(), m = (int)M[0].size();
        assert(n >= 2 && m >=2);
        int ans = max(n, m);
        // From left to right
        vi good(n-1,0);
        for(int j=0;j<m-1;++j){
            for(int i=0;i<n-1;++i){
                int cnt = 0;
                for(int k=0;k<4;++k) cnt += (M[i+di[k]][j+dj[k]]=='#');
                if(cnt%2) good[i] = 0;
                else ++good[i];
            }
            ans = max(ans, maxRecInLine(good));
        }
        
        return ans;
    }
};




int main(){
    int H,W;
    cin>>H>>W;
    vector<string> M(H);
    for(int i=0;i<H;++i) cin>>M[i];
    cout<<FlipAndRectangles().solution(M)<<endl;
    return 0;
}
