
//
//  Created by Zebo Li on 7/7/18.
//  Copyright © 2017 Zebo Li. All rights reserved.
//

#include<cassert>
#include<string>
#include<iostream>
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


int T, N, K;

vi getPreOrder(vector<vi> &Tree, vi &label){
    int root = 1;
    vi ans;
    stack<int> STK;
    while(root || !STK.empty()){
        while(root){
            ans.push_back(label[root-1]);
            if(Tree[root-1][1]) STK.push(Tree[root-1][1]);
            root = Tree[root-1][0];
        }
        if(!STK.empty()){
            root = STK.top();
            STK.pop();
        }
    }
    return ans;
}

vi getPostOrder(vector<vi> &Tree, vi &label){
    int root = 1;
    vi ans;
    stack<int> STK;
    while(root || !STK.empty()){
        while(root){
            ans.push_back(label[root-1]);
            if(Tree[root-1][0]) STK.push(Tree[root-1][0]);
            root = Tree[root-1][1];
        }
        if(!STK.empty()){
            root = STK.top();
            STK.pop();
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}



void solve(int t){
    cin >> N >> K;
    vector<vi> A(N, vi(2, 0));
    for(int i=0; i<N; ++i) cin >> A[i][0] >> A[i][1];
    vi labels(N, 0);
    for(int i=0; i<N; ++i) labels[i] = i+1;
    vi pre = getPreOrder(A, labels);
    vi post = getPostOrder(A, labels);
    vi ans(N, 0);
    unordered_map<int, int> pre_position;
    unordered_set<int> rest;
    for(int i=0; i<N; ++i) {
        pre_position[pre[i]] = i;
        rest.insert(i);
    }
    int label = 1;
    while(!rest.empty() && label<=K){
        int j = *rest.begin();
        rest.erase(j);
        ans[post[j]-1] = label;
        while(rest.count(pre_position[post[j]])){
            j = pre_position[post[j]];
            rest.erase(j);
            ans[post[j]-1] = label;
        }
        ++label;
    }
    if(rest.empty() && label<=K){
        cout<<"Case #" << t << ": Impossible" << endl;
        cerr<<"Case #" << t << ": Impossible" << endl;
    }
    else{
        for(auto &k: ans) if(!k) k = K;
        cout<<"Case #" << t << ":";
        for(auto k: ans) cout << " " << k;
        cout << endl;
        cerr <<"Case #" << t << ":";
        for(auto k: ans) cerr << " " << k;
        cerr << endl;
    }
    post = getPostOrder(A, ans);
    pre = getPreOrder(A, ans);
    for(int i=0; i<N; ++i) assert(post[i] == pre[i]);
}


int main(int argc, char *argv[]) {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    assert(argc > 1);
    std::ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    freopen(argv[1],"r",stdin);
    freopen("output.txt","w",stdout);
    cin>>T;
    cerr<<T<<endl;
    for(LL t=1; t<=T; ++t) solve(t);
    return 0;
}
