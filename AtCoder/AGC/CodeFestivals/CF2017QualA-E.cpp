/*
 ***
 Question Name: Modern Painting
 ***
 Question Link: http://code-festival-2017-quala.contest.atcoder.jp/tasks/code_festival_2017_quala_e
 ***
 Question Description:
 There is a matrix with N X M cells. There are painters stand on the edge of left, right, top and bottom. Painters paint the matrix one by one, each will paint an entire line or just stop where the is already painted. The people on the left, right, top, bottom are moving towards right, left, down, up respective. Compute how many different final configurations Mod 998244353.
 ***
 Idea:
 1, Suppose the first painter is the one moving vertically. Then the region can be devided into 3 sub regions: 1, [0,L-1]. 2.[L,R], 3, [R+1,M].
 2, The number ways can be computed by multiply the numbers of ways for these three subregions.
 3, #1: (X-1+Y+Z, Y+Z) ,which can be somehow easily proven. #2, 2^k. #3, similar as #1. We need to use partial sum to accelerate.
 4, Compute the ways vertically and horizontally separately.
 5, When you swap X1 and X2, you need to rotate the entire matrix, not just part of it.
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
typedef pair<int,int> ii;
typedef vector<long> vl;
typedef vector<bool> vb;
typedef unordered_set<int> ui;
typedef pair<long, long> ll;

const long MOD = 998244353;

class ModernPainting{
    long X1, X2, M, nTwo;
    string top,bot;
    vl posi, nega, invs;
    inline long mPlus(long x,long y){ return (x+y)%MOD; }
    void refMPlus(long &x, long y){
        x += y;
        if(x >= MOD) x %= MOD;
    }
    inline double mTimes(long x,long y){ return (x*y)%MOD; }
    void refMTimes(long &x,long y){
        x *= y;
        if(x >= MOD) x%=MOD;
    }
    long mPower(long n,long k){  // compute n^k (mod MOD)
        long ans = 1;
        while(k){
            if(1&k) refMTimes(ans, n);
            refMTimes(n, n);
            k >>= 1;
        }
        return ans;
    }
    long mInverse(long n){
        return mPower(n, MOD-2);
    }
    void init(){
        assert(M>0);
        posi = nega = vl(M+1, 1);
        invs = vl(2*M+1, 1);
        nTwo = 0;
        for(int i=0;i<M;++i) if(top[i]==bot[i]) ++nTwo;
        for(int i=2;i<=2*M;++i) invs[i] = mInverse(i);
        if(X1){
            long Y = 0, Z = 0;
            for(int i=1;i<=M;++i){
                long Y1 = Y + (top[i-1]=='1'), Z1 = Z + (bot[i-1]=='1');
                if(top[i-1]==bot[i-1]){
                    long fac = mTimes(mTimes(Y1+Z1+X1-1, Y1+Z1+X1-2), mTimes(invs[Y1+Z1], invs[Y1+Z1-1]));
                    posi[i] = mTimes(posi[i-1], mTimes(fac, invs[2]));
                }
                else{
                    long fac = mTimes(Y1+Z1+X1-1, invs[Y1+Z1]);
                    posi[i] = mTimes(posi[i-1], fac);
                }
                Y = Y1;
                Z = Z1;
            }
        }
        if(X2){
            long Y = 0, Z = 0;
            for(long i=M-1;i>=0;--i){
                long Y1 = Y + (top[i]=='1'), Z1 = Z + (bot[i]=='1');
                if(top[i]==bot[i]){
                    long fac = mTimes(mTimes(Y1+Z1+X2-1, Y1+Z1+X2-2), mTimes(invs[Y1+Z1], invs[Y1+Z1-1]));
                    nega[i] = mTimes(nega[i+1], mTimes(fac, invs[2]));
                }
                else{
                    long fac = mTimes(Y1+Z1+X2-1, invs[Y1+Z1]);
                    nega[i] = mTimes(nega[i+1], fac);
                }
                Y = Y1;
                Z = Z1;
            }
        }
        for(long i=M-1;i>=0;--i) refMPlus(nega[i], nega[i+1]);
    }
    long compCnt(){
        if(!X2) return (long)1;
        if(!X1) return nega[1];
        long ans = 0;
        for(int i=0;i<M;++i) refMPlus(ans, mTimes(posi[i], nega[i+1]));
        return ans;
    }
public:
    long solve(string t, string b,long x1, long x2){
        X1 = x1;
        X2 = x2;
        
        if(X1>X2) {
            /*
             **********************
             NEED TO ROTATE THE ENTIRE MATRIX, NOT JUST SWAP LEFT EDGE AND RIGH EDGE.
             **********************
             */
            swap(X1, X2);
            swap(t,b);
            reverse(t.begin(),t.end());
            reverse(b.begin(),b.end());
        }
        top.clear();
        bot.clear();
        for(int i=0;i<(int)b.size();++i) if(b[i]=='1'||t[i]=='1'){
            top += t[i];
            bot += b[i];
        }
        M = (int)top.size();
        if(!M) return (long)0;
        init();
        return mTimes(mPower(2, nTwo), compCnt());
    }
};

int main(){
    int n,m,cnt = 0;
    string A,B,C,D;
    cin>>n>>m>>A>>B>>C>>D;
    long X1 = 0, X2 = 0, ans = 0;
    for(int i=0;i<m;++i){
        X1 += (C[i] == '1');
        X2 += (D[i] == '1');
    }
    cnt += (int)X1 + (int)X2;
    ans += ModernPainting().solve(B, A, X1, X2);
    X1 = X2 = 0;
    for(int i=0;i<n;++i){
        X1 += (A[i] == '1');
        X2 += (B[i] == '1');
    }
    ans += ModernPainting().solve(C, D, X1, X2);
    cnt += (int)X1 + (int)X2;
    if(!cnt) cout<<1<<endl;
    else cout<<(ans%MOD)<<endl;
    return 0;
}

