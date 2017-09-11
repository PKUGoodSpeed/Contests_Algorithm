/*
 ***
 Question Name: Sandglass
 ***
 Question Description:
 We have a sandglass consisting of two bulbs, bulb A and bulb B. These bulbs contain some amount of sand. When
 we put the sandglass, either bulb A or B lies on top of the other and becomes the upper bulb. The other bulb
 becomes the lower bulb.
 The sand drops from the upper bulb to the lower bulb at a rate of 1 gram per second. When the upper bulb no
 longer contains any sand, nothing happens.
 Initially at time 0, bulb A is the upper bulb and contains a grams of sand; bulb B contains X−a grams of sand 
 (for a total of X grams).
 We will turn over the sandglass at time r1,r2,..,rK. Assume that this is an instantaneous action and takes no time. Here, time t refer to the time t seconds after time 0.
 You are given Q queries. Each query is in the form of (ti,ai). For each query, assume that a=ai and find the amount of sand that would be contained in bulb A at time ti.
 ***
 Input:
 X
 K
 r1 r2 .. rK
 Q
 t1 a1
 t2 a2
 :
 tQ aQ
 ***
 Output:
 ans1
 ans2
 .
 .
 ansQ
 ***
 Idea: 1, maintain the linear function; 2, track when the two boundary merges, which is very important.
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

int X,K,Q;
vi R,T,A;

int comp(int a,int b,int c, int x){
    if(x>=a) return a+c;
    else if(x>=b) return x+c;
    else return b+c;
}

int main(){
    /*Write your code here*/
    cin>>X>>K;
    R.resize(K+2);
    R[0] = 0;
    R[K+1] = 1E9;
    for(int i=1;i<=K;++i) cin>>R[i];
    cin>>Q;
    T.resize(Q);
    A.resize(Q);
    for(int q=0;q<Q;++q) cin>>T[q]>>A[q];
    int a = X, b = 0, c = 0, i = 1, j = 0;
    vi ans(Q,0);
    bool merge = false;
    while(j<Q){
        if(1&i){
            while(j<Q && T[j]<=R[i]){
                int dt = T[j] - R[i-1];
                if(!merge){
                    int tmpa = a, tmpb = max(b,dt-c), tmpc = c-dt;
                    if(tmpb>=tmpa){
                        tmpb = tmpa = tmpc = 0;
                    }
                    ans[j] = comp(tmpa,tmpb,tmpc,A[j]);
                }
                else{
                    ans[j] = max(0,c-dt);
                }
                ++j;
            }
            int dt = R[i]-R[i-1];
            if(!merge){
                b = max(b,dt-c);
                c = c-dt;
                if(b>=a){
                    a = b = c = 0;
                    merge = true;
                }
            }
            else{
                a = b = 0;
                c = max(0,c - dt);
            }
            
        }
        else{
            while(j<Q && T[j]<=R[i]){
                int dt = T[j] - R[i-1];
                if(!merge){
                    int tmpa = min(a, X-c-dt), tmpb = b, tmpc = c+dt;
                    if(tmpb>=tmpa){
                        tmpa = tmpb = 0;
                        tmpc = X;
                    }
                    ans[j] = comp(tmpa,tmpb,tmpc,A[j]);
                    
                }
                else{
                    ans[j] = min(c+dt, X);
                }
                ++j;
            }
            int dt = R[i] - R[i-1];
            if(!merge){
                a = min(a,X-c-dt);
                c = c+dt;
                if(b>=a) {
                    a = b = 0;
                    c = X;
                    merge = true;
                }
            }
            else{
                a = b = 0;
                c = min(X,c + dt);
            }
        }
        ++i;
    }
    for(auto k:ans) cout<<k<<endl;
    return 0;
}
