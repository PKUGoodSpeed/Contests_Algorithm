/*
Problem: Statement
We have a convex polygon in the XY plane. The vertices of the polygon are the points (x[0], y[0]), (x[1], y[1]), ... in clockwise order. 
You are given the s x and y. 
In order to make the implementation simpler the polygon and its representation satisfy some additional constraints. 
Please read the Constraints section carefully. 
A three-dimensional solid is obtained by rotating this polygon around the Y axis. 
Compute and return the volume of the resulting solid.


Constraints:
- x will contain between 3 and 50 elements, inclusive.
- y will contain the same number of elements as x.
- Each element of x and y will be between -100 and 100, inclusive.
- The polygon will be convex.
- All vertices of the polygon will be distinct.
- The polygon will have exactly two vertices on the Y axis. Let's denote them (0, Ymin) and (0, Ymax) with Ymin < Ymax.
- The vertices will be listed in clockwise order, starting with (0, Ymax).
- The y-coordinates of all vertices will be between Ymin and Ymax, inclusive.
- No three points will lie on the same line.
*/


#include<bits/stdc++.h>

#define REP(i,s,n) for(int (i)=s; (i)<(int)(n);(i)++)
#define RIT(it,c) for(__typeof(c.begin()) it = c.begin();it!=c.end();it++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (int)(x).size()
#define MSET(m,v) memset(m,v,sizeof(m))

/* define class and method names */
#define TCC PolygonRotation
#define TCM getVolume


using namespace std;


typedef long long LL;
typedef long double LD;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<LL> vL;
typedef vector<bool> vb;

class TCC{
	const int N = 1000000;
	const double pi = 3.14159265359;
	double find_pts(map<double,double> &pt, double y){
		auto it1 = pt.upper_bound(y);
		auto it2 = --pt.upper_bound(y);
		double x1 = it2->second, y1 = it2->first, x2 = it1->second, y2 = it1->first;
		double ans = (y-y1)*x2 + (y2-y)*x1;
		return ans/(y2-y1);
	}
	double slope(map<double,double> &pt, double y){
	 	auto it1 = pt.upper_bound(y);
		auto it2 = --pt.upper_bound(y);
		if(fabs(it1->second == it2->second) < 1.E-6) return 100001.; 
		return fabs((it1->first - it2->first)/(it1->second - it2->second));
	}
public:
	double TCM(vector <int> x, vector <int> y){
		map<double, double> pt1,pt2;
		double ym = 0.,yM = double(y[0]);
		int i = 1, n = x.size();
		pt1[y[0]] = 0;
		pt2[y[0]] = 0;
		while(x[i]){
			pt1[y[i]] = double(x[i]);
			i++;
		}
		if(y[i]!=y[i-1]) pt1[y[i]] = 0;
		pt2[y[i]] = 0;
		ym = double(y[i]);
		while(i<n){
			pt2[y[i]] = -double(x[i]);
			i++;
		}
		double dy = fabs(yM - ym)/double(N);
		double ans = 0.;
		for(int i=0;i<N;++i){
			double y = ym + (i+0.5)*dy;
			double x1 = find_pts(pt1,y), x2 = find_pts(pt2,y);
			double s = (x1>x2? slope(pt1,y):slope(pt2,y));
			double x = max(x1,x2); 
			double xp = x+dy/2./s, xm = x - dy/2./s;
			double dv = pi*x*x*dy;
			ans += dv;
		}
		return ans;
	}
};

/* testing process */
int main(){
	TCC test;
	vi x{0, 3, 3, 0, -1, -1}, y{2, 2, -2, -2, -1, 1};
	auto ans = test.TCM(x,y);
	
	/* output results */
	cout<<ans;
}
