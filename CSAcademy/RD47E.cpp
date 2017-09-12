/*
 ***
 Question Name: Cut the Tree
 ***
 Question Description:
 Link: https://csacademy.com/contest/round-47/task/cut-the-trees/
 ***
 Input:
 ***
 Output:
 
 ***
 Idea: Using two priority_queues, one storing the trees that need to be cut (The maximum days that the tree can 
 grow after being cut), the other store the trees that do not need to be cut (The maximum days that the tree can 
 grow from the very beginning). Keep increasing the number of days (we count backward from the final day), and 
 keep updating the two queues. Until the first queue gets empty(). During this process, record the maximum 
 number of trees.
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

long N,D;

int main() {
    cin>>N>>D;
    vi H(N),G(N);
    for(int i=0;i<N;++i) cin>>H[i];
    for(int i=0;i<N;++i) cin>>G[i];
    priority_queue<ii,vector<ii>,greater<ii>> Q1,Q2;
    vi T(N);
    for(int i=0;i<N;++i){
        if(H[i]<=D) Q1.push(ii((D-H[i])/G[i], i));
        else{
            Q2.push(ii(D/G[i],i));
        }
    }
    int j = 0, cnt = 0, ans = 0;
    while(!Q2.empty()){
        while(!Q1.empty() && Q1.top().first<j){
            int k = Q1.top().second;
            Q1.pop();
            Q2.push(ii(D/G[k],k));
        }
        while(!Q2.empty() && Q2.top().first<j) Q2.pop();
        if(!Q2.empty()) {
            Q2.pop();
            ++cnt;
        }
        ans = max(ans, cnt + (int)Q1.size());
        ++j;
    }
    ans = max(ans, cnt + (int)Q1.size());
    cout<<ans<<endl;
    return 0;
}
