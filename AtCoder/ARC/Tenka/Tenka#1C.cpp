/*
 ***
 Question Name: 4/N
 ***
 Question Link: http://tenka1-2017.contest.atcoder.jp/tasks/tenka1_2017_c
 ***
 Question Description:
 Given N, find n, m, h s.t. 4/N == 1/n + 1/m + 1/h
 ***
 Idea: Use Bruce Force for n and m. Take care on:
 1. n, m must starts from 1 instead of 0;
 2. The over flow problem.
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

int N;

int main(){
    std::ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>N;
    for(int n=max(1,N/4);n<=3500;++n) for(int m=n;m<=3500;++m){
        long de = (long)4*n*m - (long)N*m - (long)N*n;
        if(de <= 0) continue;
        long nu = (long)N*m*n;
        if(!(nu%de)){
            cout<<n<<' '<<m<<' '<<nu/de<<endl;
            return 0;
        }
    }
    return 0;
}
