/*
 ***
 Question Name: FlipAndRectangles (easier version)
 ***
 Question Link: http://arc081.contest.atcoder.jp/tasks/arc081_d
 If there is only one operation can be performed.
 
 ***
 Idea: This is a mistaken version. Just scan Horizontally and Vertically. Complexity = O(H*W)
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
                ans = max(ans, (i - stk.top() -1) * H[pivat]);
            }
            stk.push(i);
        }
        return ans;
    }
    public:
    int solution(vector<string> M){
        if(M.empty() || M[0].empty()) return 0;
        int n = (int)M.size(), m = (int)M[0].size(), ans = 0;
        // From left to right
        vi black(n,0), white(n,0);
        for(int j=0;j<m;++j){
            for(int i=0;i<n;++i){
                if(M[i][j] == '#'){
                    black[i] = (j?black[i]+1:1);
                    white[i] = 0;
                }
                else{
                    white[i] = (j?white[i]+1:1);
                    black[i] = 0;
                }
            }
            vi wht_pos={-1};
            for(int i=0;i<n;++i) if(!black[i]) wht_pos.push_back(i);
            wht_pos.push_back(n);
            if((int)wht_pos.size()==2) ans = max(ans, maxRecInLine(black));
            else{
                int L = (int)wht_pos.size();
                for(int i=1;i<L-1;++i){
                    vi tmp(black.begin()+wht_pos[i-1]+1, black.begin()+wht_pos[i+1]);
                    tmp[wht_pos[i] - wht_pos[i-1] - 1] = white[wht_pos[i]];
                    ans = max(ans, maxRecInLine(tmp));
                }
            }
        }
        black = white = vi(m, 0);
        for(int i=0;i<n;++i){
            for(int j=0;j<m;++j){
                if(M[i][j] == '#'){
                    black[j] = (i? black[j]+1:1);
                    white[j] = 0;
                }
                else{
                    white[j] = (i? white[j]+1:1);
                    black[j] = 0;
                }
            }
            vi wht_pos = {-1};
            for(int j=0;j<m;++j) if(white[j]) wht_pos.push_back(j);
            if((int)wht_pos.size() == 2) ans = max(ans, maxRecInLine(black));
            else{
                int L = (int)wht_pos.size();
                for(int j=1;j<L-1;++j){
                    vi tmp(black.begin()+wht_pos[j-1]+1, black.begin()+wht_pos[j+1]);
                    tmp[wht_pos[j] - wht_pos[j-1] - 1] = white[wht_pos[j]];
                    ans = max(ans, maxRecInLine(tmp));
                }
            }
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
