/*
 ***
 Question Name: IntegerotS
 ***
 Question Link: http://tenka1-2017.contest.atcoder.jp/tasks/tenka1_2017_d
 ***
 Question Description:
 Given N pairs of numbers {(A_i, B_i)}, solve the constrained problem:
 maximize: \sum_i B_ki  s.t. |_i A_ki <= K, where K is given.
 ***
 Idea: Need to be familiar with Bit manipulations:
 1. When A_i > K, we do not even need to record A_i, since A_i | anything will > K.
 2. For example K in bits is 100101001:
 (1) We first consider |_i A_ki produces 1's that are located within the positions of 1's in K. For this we actually can quickly determine ki's by judging whether 11...1011010110 & A_ki equals 0, where 11...1011010110: defined as NK, is the bitwise not K.
     (2) Then we want to consider for each 1's, for example the 2 from right. We turn it into zero, and then we can ignore all the digits on the right of it. Thus, we want |_i A_ki is in the form of 100100XXX, which k_i can be quickly determined by judging whether 11...1011011000 & A_ki equals 0. We by order turn every digits from right to 0 until we meet with a 0. We turn that 0 into 1 and make the judgement. And then keep going on.
     (3) During the loop, we use NK &= N-1 to turn the 1 at every position into 0.
     (4) To get NK, we cannot use !K, instead, we need to use (-1)^K!
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

class IntegerotS{
    unordered_map<int, long> cnt;
    int K;
    void init(){
        int N;
        cin>>N>>K;
        for(int i=0;i<N;++i){
            int a,b;
            cin>>a>>b;
            if(a<=K) cnt[a] += (long)b;
        }
    }
    long pass(int nk){
        long ans = 0;
        for(auto p:cnt) if(!(p.first & nk)) ans += p.second;
        return ans;
    }
public:
    long solve(){
        init();
        int NK = (-1)^K;
        long ans = pass(NK);
        for(int j=0;j<32;++j){
            if(((NK>>j)&1) == 0){
                NK |= (1<<j);
                ans = max(ans, pass(NK));
            }
            NK &= NK-1;
        }
        return ans;
    }
};

int main(){
    std::ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cout<<IntegerotS().solve()<<endl;
    return 0;
}

