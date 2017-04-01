/*
Problem Statement:
This task is about a group of people who like to play ping pong. 
All games of ping pong mentioned in this task are one-on-one games. 
You are given a skills. Each element of skills is the skill level of one person in the group. 
The skill levels are all distinct. Whenever two people play a game of ping pong, the one with the higher skill level always wins. 
All people in the group would like to play but they only have a single table. Therefore, only two people can play at any given time. 
There will be a sequence of games, numbered starting from 1. Game 1 will be played by the players who correspond to skills[0] and skills[1]. 
All the remaining people will form a queue, in the order in which they are given in skills. 
After each game the following things will happen, in order:
1, The person who lost the game leaves the table and goes to the end of the queue.
2, If the person who won the game has already won N games in a row, they also leave the table and they go to the end of the queue 
(behind the person who lost the last game).
3, While there are fewer than two people at the table, the first person in the queue leaves the queue and goes to the table.
4, The two people at the table play the next game.
You are given the skills, the N, and an K. 
Return the two-element { L, W }, where L and W are the skills of the loser and the winner of game K, in this order.
*/ 


#include<bits/stdc++.h>

#define REP(i,s,n) for(int (i)=s; (i)<(int)(n);(i)++)
#define RIT(it,c) for(__typeof(c.begin()) it = c.begin();it!=c.end();it++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (int)(x).size()
#define MSET(m,v) memset(m,v,sizeof(m))

/* define class and method names */
#define TCC PingPongQueue
#define TCM whoPlaysNext


using namespace std;


typedef long long LL;
typedef long double LD;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<LL> vL;
typedef vector<bool> vb;

class TCC{
public:
	vector <int> TCM(vector <int> skills, int N, int K){
		queue<int> Q;
		int n = skills.size(), p1 = 0, p2 = 1;
		vi score(n,0);
		for(int i=2;i<n;++i) Q.push(i);
		for(int i=1;i<K;++i){
			if(skills[p1] < skills[p2]) swap(p1,p2);
			score[p2] = 0;
			score[p1]++;
			Q.push(p2);
			p2 = Q.front();
			Q.pop();
			if(score[p1] == N){
				score[p1] = 0;
				Q.push(p1);
				p1 = Q.front();
				Q.pop();
			}
		}
		if(skills[p1]<skills[p2]) swap(p1,p2);
		return vi{skills[p2], skills[p1]};
	}
};


/* testing process */
int main(){
	TCC test;
	vi sk{49, 24, 26, 12, 5, 33, 25, 30, 35, 41, 46, 23, 21, 3, 38, 43, 11, 19, 34, 29, 20, 32, 39, 7, 50};
	int N = 10, K = 399; 
	auto ans = test.TCM(sk,N,K);
	
	/* output results */
	for(auto m:ans) cout<<m<<endl;
}
