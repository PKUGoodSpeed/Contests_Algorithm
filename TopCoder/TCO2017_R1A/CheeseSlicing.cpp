/*
Problem Statement:
You want to make a lot of sandwiches. However, you only have a limited amount of cheese. 
The only piece of cheese you currently have is a rectangular block with dimensions A, B, and C. 
You can cut the block of cheese into smaller pieces. You are only allowed to cut as follows:
1£¬ Each cut must divide one block of cheese into two smaller blocks of cheese.
2£¬ Each cut must be parallel to one of the faces of the piece you are cutting.
3£¬ Each of the two smaller blocks must have integer dimensions.

When placing a block of cheese onto a piece of bread, the cheese is always rotated so that its shortest side is vertical. 
In other words, suppose you have a block of cheese with dimensions (X,Y,Z) such that X ¡Ý Y ¡Ý Z. 
If you place this block onto a piece of bread, its surface area will be X*Y and its thickness will be Z. 
A block of cheese is called a good slice if and only if its thickness is greater than or equal to S. 
(Recall that the thickness of a block is the length of its shortest side.) 
You can cut your block of cheese into arbitrarily many pieces, as long as you follow the rules given above. 
Your goal is to cut the block in such a way that maximizes the total surface area of all good slices among the pieces. 
Note that your way of cutting may also produce some pieces that are not good slices, but those pieces won't contribute to the surface area. 
The number of good slices does not matter, we only care about their surface. Different good slices may have different dimensions. 
You are given the s A, B, C, and S. Return the maximum total surface area of good slices you can get.

*/ 



#include<bits/stdc++.h>

#define REP(i,s,n) for(int (i)=s; (i)<(int)(n);(i)++)
#define RIT(it,c) for(__typeof(c.begin()) it = c.begin();it!=c.end();it++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (int)(x).size()
#define MSET(m,v) memset(m,v,sizeof(m))

/* define class and method names */
#define TCC CheeseSlicing
#define TCM totalArea


using namespace std;


typedef long long LL;
typedef long double LD;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<LL> vL;
typedef vector<bool> vb;

class TCC{
public:
	int TCM(int A, int B, int C, int S){
		if(A<S || B<S || C<S) return 0;
		int nx = A/S-1, ny = B/S-1, nz = C/S-1;
		int rx = A - nx*S, ry = B - ny*S, rz = C - nz*S;
		int ans = nx*ny*nz*S*S;
		ans += nx*ny*rz*S + ny*nz*rx*S + nz*nx*ry*S;
		ans += nx*ry*rz + ny*rx*rz + nz*rx*ry;
		vi tmp{rx,ry,rz};
		sort(tmp.begin(),tmp.end());
		ans += tmp[1]*tmp[2];
		return ans;		
	}
};


/* testing process */
int main(){
	TCC test;
	int A= 5, B = 3, C= 5, S = 3;
	auto ans = test.TCM(A,B,C,S);
	
	/* output results */
	cout<<ans;
}
