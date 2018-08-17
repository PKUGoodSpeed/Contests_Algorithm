
//
//  Created by Zebo Li on 7/7/18.
//  Copyright © 2017 Zebo Li. All rights reserved.
//

#include<cassert>
#include<string>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<memory.h>
#include<math.h>
#include<vector>
#include<algorithm>
#include<map>
#include<numeric>
#include<deque>
#include<set>
#include<functional>
#include<queue>
#include<stack>
#include<unordered_set>
#include<unordered_map>


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


LL T, N;
vector<LD> X, Y, W;
const LD C1 = 5./11.;
const LD C2 = 6./11.;
const LD ERR = 1.E-12;

LD getScore(LD x, LD y){
    LD ans = 0.0;
    for(int i=0; i<N; ++i) ans += max(abs(X[i] - x), abs(Y[i] - y)) * W[i];
    return ans;
}

LD search1D(LD x1, LD x2, const LD& y0){
    for(int i=0; i<100; ++i){
        LD m1 = x1 * C2 + x2 * C1, m2 = x1 * C1 + x2 * C2;
        LD u1 = getScore(m1, y0), u2 = getScore(m2, y0);
        if(u1 > u2) x1 = m1;
        else x2 = m2;
    }
    return getScore((x1 + x2)/2., y0);
}

LD search2D(LD x1, LD x2, LD y1, LD y2){
    for(int i=0; i<100; ++i){
        LD m1 = y1 * C2 + y2 * C1, m2 = y1 * C1 + y2 * C2;
        LD u1 = search1D(x1, x2, m1), u2 = search1D(x1, x2, m2);
        if(u1 > u2) y1 = m1;
        else y2 = m2;
    }
    return search1D(x1, x2, (y1 + y2)/2.);
}


void solve(LL t){
    cin >> N;
    X.resize(N);
    Y.resize(N);
    W.resize(N);
    for(int i=0; i<N; ++i) cin >> X[i] >> Y[i] >> W[i];
    LD ans = search2D(-LD(1001.), LD(1001.), -LD(1001.), LD(1001.));
    cout<<"Case #" << t << ": " << setprecision(16)<< ans << endl;
    cerr<<"Case #" << t << ": " << setprecision(16) << ans << endl;
}

class Solution {
    string getOpt(int i){
        assert(i<4);
        if(i==0) return "";
        if(i==1) return "+";
        if(i==2) return "-";
        else return "*";
    }
    long bin(long x, long y, char o){
        if(o == '+') return x + y;
        else if(o=='-') return x - y;
        else return x*y;
    }
    bool check(string s){
        int i = -1;
        cout<<s.size() << ' ' << int(i<s.size())<<endl;
        while(i<s.size()){
            cout<<s<<endl;
            auto j = s.find_first_of("*-+", i+1);
            if(j==string::npos) j = s.size();
            if(j-i-1 > 1 && s[i+1]=='0') return false;
            i = j;
        }
        return true;
    }
    long eval(string s){
        stack<long> C;
        stack<char> O;
        auto i = s.find_first_of("+-*");
        if(i==string::npos) return stol(s);
        long pre = 0L, cur = stol(s.substr(0, i));
        char op = '+';
        while(i<s.size() && i!=string::npos){
            if(s[i] == '*'){
                C.push(pre);
                O.push(op);
                pre = cur;
            }
            else{
                pre = bin(pre, cur, op);
                while(!C.empty()){
                    pre = bin(C.top(), pre, O.top());
                    C.pop();
                    O.pop();
                }
            }
            op = s[i];
            auto j = s.find_first_of("+-*", i+1);
            if(j==string::npos) j = s.size();
            cur = stol(s.substr(i+1, j-i-1));
            i = j;
        }
        pre = bin(pre, cur, op);
        while(!C.empty()){
            pre = bin(C.top(), pre, O.top());
            C.pop();
            O.pop();
        }
        return pre;
    }
public:
    vector<string> addOperators(string num, int target) {
        int n = num.size();
        long N = long(pow(4, n-1));
        vector<string> ans;
        if(!n) return ans;
        for(int k=0; k<N; ++k){
            string t = string(1, num[0]);
            for(int j=1, m=k; j<n; ++j){
                t += getOpt(m%4) + num[j];
                m /= 4;
            }
            if(check(t) && eval(t) == long(target)) ans.push_back(t);
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};


int main(int argc, char *argv[]) {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    /*assert(argc > 1);
    std::ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    freopen(argv[1],"r",stdin);
    freopen("output.txt","w",stdout);
    cin>>T;
    cerr<<T<<endl;
    for(LL t=1; t<=T; ++t) solve(t);*/
    auto ans = Solution().addOperators("105", 5);
    for(auto s: ans) cout<<s<<endl;
    return 0;
}
