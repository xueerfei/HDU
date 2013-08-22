#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
bool map[10][10][5];
int d[4][2]={-1,0,0,-1,1,0,0,1};
int maze[10][10],b[10][10];
int tx,ty,px,py;

struct node
{
	int bx,by;
	int px,py;
	int step;
}cur,tmp;
bool flag;
int ax,ay;
int n,m;
node start;
int enx,eny;
bool dfs(int x,int y)
{
	if(x==tx && y==ty)
		return 1;
	if(x<0|| x>=n ||y<0 || y>=m)
		return 0;
	if(x==ax && y==ay) //箱子挡住了
		return 0;
	if(b[x][y]==1)
		return 0;
	b[x][y]=1;
	return dfs(x+1,y) ||dfs(x-1,y) ||dfs(x,y+1) ||dfs(x,y-1);
}
int res;
queue<node>qu;
void bfs()
{
	start.step=0;
	while(!qu.empty()) qu.pop();
	//queue<node>qu;
	qu.push(start);
	//node cur,tmp;
	while(!qu.empty())
	{
		cur=qu.front();  qu.pop();
		if(cur.bx==enx && cur.by==eny)
		{
			flag=true;
			res=cur.step;
			return;
		}
		for(int i=0;i<4;i++)
		{
			tmp.bx=cur.bx+d[i][0];
			tmp.by=cur.by+d[i][1];//下一个箱子的位置
			//原来箱子的位置；
			ax=cur.bx;
			ay=cur.by;
			//人要到的位置
			tx=cur.bx-d[i][0];
			ty=cur.by-d[i][1];
			//原来人的位置
			tmp.px=cur.px;
			tmp.py=cur.py;
			tmp.step=cur.step+1;
			if(tmp.bx>=0&&tmp.bx<n && tmp.by>=0&&tmp.by<m && 
				maze[tmp.bx][tmp.by]!=1 &&!map[tmp.bx][tmp.by][i])
			{
				memcpy(b,maze,sizeof(maze));
				if(tx>=0&&tx<n && ty>=0&&ty<m && maze[tx][ty]!=1 &&
					dfs(tmp.px,tmp.py))//人能到达箱子的后方
				{
					if(tmp.bx==enx && tmp.by==eny)
					{
						flag=1;
						res=tmp.step;
						return ;
					}
					tmp.px=tx,tmp.py=ty;
					map[tmp.bx][tmp.by][i]=1;
					qu.push(tmp);
				}
			}
		}
	}
}
int main()
{
	int t;
	scanf("%d",&t);
	
		while(t--)
		{
			scanf("%d %d",&n,&m);
			for(int i=0;i<n;i++)
				for(int j=0;j<m;j++)
				{
					scanf("%d",&maze[i][j]);
					if(maze[i][j]==2)//箱子坐标
						start.bx=i,start.by=j;
					else if(maze[i][j]==3)//目标坐标
						enx=i,eny=j;
					else if(maze[i][j]==4)//人的坐标
						start.px=i,start.py=j;
				}
			memset(map,0,sizeof(map));
			flag=0;
			res=0;
			bfs();
			if(flag)
			{
				 printf("%d\n", res); 
			}
			else
				 printf("-1\n");  
		}
	
	return 0;
}