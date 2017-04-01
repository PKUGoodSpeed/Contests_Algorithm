/*
 * TopCoder Challenge AcidRain
 * The Problem description is at https://community.topcoder.com/stat?c=problem_statement&pm=7388
 * Solution is using bit-manipulation
*/

#include<bits/stdc++.h>

#define REP(i,s,n) for(int (i)=s; (i)<(int)(n);(i)++)
#define RIT(it,c) for(__typeof(c.begin()) it = c.begin();it!=c.end();it++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (int)(x).size()
#define MSET(m,v) memset(m,v,sizeof(m))

/* define class and method names */
#define TCC AcidRain
#define TCM saveHarvest


using namespace std;


typedef long long LL;
typedef long double LD;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<LL> vL;
typedef vector<bool> vb;

class TCC{
    int transFer(vector<bool> &obst,int state,int N){
        int ans = 0;
        for(int j=0;j<N-1;j++){
            if(!(1&(state>>j))) continue;
            int l=j,r=j+1;
            while(l>=0 && r<N && obst[l] &&obst[r]){
                l--;
                r++;
            }
            if(l>=0 && !obst[l]) ans |= (1<<l);
            if(r<N && !obst[r]) ans |= (1<<(r-1));
        }
        return ans;
    }
public:
    int TCM(vector <int> b, vector <int> e, vector <int> y){
        int n = (int)b.size(),B = 12, E = 0;;
        map<int,int> layers;
        for(int i=0;i<n;i++){
            layers[y[i]] = 0;
            B = min(B,b[i]);
            E = max(E,e[i]);
        }
        int N = E-B, nLvl = (int)layers.size();
        for(int i=0;i<n;i++){
            for(int j=b[i]-B;j<e[i]-B;j++){
                layers[y[i]] |= (1<<j);
            }
        }
        vector<vector<bool> > old;
        for(auto pr:layers) {
            vector<bool> tmp(N,false);
            for(int j=0;j<N;j++) tmp[j] = (1&(pr.second>>j));
            old.push_back(tmp);
        }
        vi min_add((1<<(N-1)),N);
        min_add[(1<<(N-1))-1] = 0;
        for(int i=nLvl-1;i>=0;i--){
            vi tmp((1<<(N-1)),N);
            vector<bool> tmpvec(N,false);
            for(int k=0;k<(1<<N);k++){
                int count = 0;
                bool ok = true;
                for(int j=0;j<N && ok;j++){
                    tmpvec[j] = (1&(k>>j));
                    if( old[i][j] && !(1&(k>>j)) ) ok = false;
                    if( !old[i][j] && (1&(k>>j)) ) count++;
                }
                if(ok){
                    for(int j=0;j<(1<<(N-1));j++){
                        int new_state = transFer(tmpvec,j,N);
                        tmp[new_state] = min(tmp[new_state],min_add[j]+count);
                    }
                }
            }
            min_add.swap(tmp);
        }
        return min_add[0];
    }
};

/* testing process */
int main(){
	TCC test;
	vi b{1, 0, 3, 5}, e{4, 3, 5, 6}, y{10, 3, 1000, 8};
	auto ans = test.TCM(b, e, y);
	
	/* output results */
	cout<<ans<<endl;
}
