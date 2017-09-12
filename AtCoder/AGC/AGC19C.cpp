/*
 ***
 Question Name: Fountain Walk
 ***
 Question Link: http://agc019.contest.atcoder.jp/tasks/agc019_c
 
 ***
 Idea: The critial thing is an O(n logn) Algorithm to count the maximum length of the increasing subsequence.
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

/* Here is an O(n logn) Algorithm to count the maximum increasing subsequence. Here for conveniece, we assume the elements of A are all non-negative */
int maxSubseq(vi A){
    set<ii> dp; // This set store pairs of (last number, length), we know the two input parameters are positively correlated
    dp.insert(ii(-1,0));
    for(auto k:A){
        auto pre = --dp.lower_bound(ii(k,0));
        int L = pre->second+1;
        ++pre;
        // Then we erase those subsequeces that the ending element is larger than k, but the sequence is shorter than the one we just found
        while(pre!=dp.end() && pre->second<=L) pre = dp.erase(pre);
        dp.insert(ii(k, L));
    }
    /* The last element in the set is the one we try to find */
    return (--dp.end())->second;
}


class FountainWalk{
    const LD pi = 3.141592653589793238L;
    LD edge = 100.;
    LD radius = 10.;
    public:
    LD Solution(int x1, int y1, int x2, int y2, vector<ii> &fountains){
        bool rev = false;
        if((long)(x1-x2)*(long)(y1-y2) < 0) rev = true;
        sort(fountains.begin(), fountains.end());
        if(rev) reverse(fountains.begin(), fountains.end());
        vi Seq;
        for(auto pos:fountains) Seq.push_back(pos.second);
        int cnt = maxSubseq(Seq);
        LD ans = edge*(abs(x1-x2) + abs(y1-y2)) - (LD)cnt*radius*((LD)2. - pi/2.);
        if(cnt == min(abs(x1-x2)+1, abs(y1-y2)+1)) ans += radius*pi/2.;
        return ans;
    }
};

int main(){
    int x1,y1,x2,y2,N;
    cin>>x1>>y1>>x2>>y2>>N;
    int xm = min(x1, x2), xM = max(x1, x2), ym = min(y1, y2), yM = max(y1, y2);
    vector<ii> fountains;
    for(int i=0;i<N;++i){
        int x, y;
        cin>>x>>y;
        if(x>=xm && x<=xM && y>=ym && y<= yM) fountains.push_back(ii(x,y));
    }
    cout <<setprecision(31);
    cout<<FountainWalk().Solution(x1, y1, x2, y2, fountains)<<endl;
}

