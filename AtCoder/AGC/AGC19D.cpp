/*
 ***
 Question Name: ShiftAndFlip
 ***
 Question Link: http://agc019.contest.atcoder.jp/tasks/agc019_d
 
 ***
 Idea: Consider during the process, the final shift d, the maximum right shift r and the maximum left shift l; Fix d, we can find r, l so that the number of operations is minimized. Then we run over d;
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

class ShiftAndFlip{
    void findLeftRight(vi &left, vi &right, string &B){
        int n = (int)B.size();
        left.resize(n);
        right.resize(n);
        string S = B + B + B;
        int l = 0;
        while(S[n-l] != '1') ++l;
        left[0] = l;
        for(int i=1;i<n;++i){
            if(S[n+i] != '1') left[i] = left[i-1] + 1;
            else left[i] = 0;
        }
        l = 0;
        while(S[n-1+l] != '1') ++l;
        right[n-1] = l;
        for(int i=n-2;i>=0;--i){
            if(S[n+i] != '1') right[i] = right[i+1] + 1;
            else right[i] = 0;
        }
        return;
    }
    int computeOp(string &A, string &B, int d, vi &left, vi &right){
        int n = (int)B.size(), cnt = 0;
        priority_queue<ii> l_list, r_list;
        vi nleft(n), nright(n);
        for(int i=0;i<n;++i) if(A[i] != B[(i+d+n)%n]){
            ++cnt;
            if(d>0){
                nleft[i] = left[i], nright[i] = max(0, right[i]-d);
            }
            else{
                nleft[i] = max(0, left[i] + d), nright[i] = right[i];
            }
            r_list.push(ii(nright[i],i));
        }
        if(r_list.empty()) return abs(d)+cnt;
        int ans = r_list.top().first;
        while(!r_list.empty()){
            int length = r_list.top().first;
            while (!r_list.empty() && r_list.top().first == length) {
                int j = r_list.top().second;
                r_list.pop();
                l_list.push(ii(nleft[j],j));
            }
            if(r_list.empty()) ans = min(ans, l_list.top().first);
            else ans = min(ans, l_list.top().first + r_list.top().first);
        }
        return abs(d) + 2*ans + cnt;
    }
    public:
    int Solution(string &A, string &B){
        if(B.find('1') == string::npos) return A.find('1')==string::npos? 0:-1;
        vi left,right;
        findLeftRight(left, right, B);
        int n = (int)B.size();
        int ans = 3*n;
        for(int d=-n;d<=n;++d){
            ans = min(ans, computeOp(A, B, d, left, right));
        }
        return ans;
    }
    
};

int main(){
    string A,B;
    cin>>A>>B;
    cout<<ShiftAndFlip().Solution(A, B)<<endl;
    return 0;
}
