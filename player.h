#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include <stack>
#include <ncurses.h>
#include <string>
#include <stdlib.h>

using namespace std;
#define fa(i,a,b) for(int i=a;i <b ; ++i)


#define setl pair<int,int>
extern int visit[107][107];
extern char src[107][107];
extern stack <pair<int,int> > st;
extern vector< pair<int,int>> vs;

int vx[8] = {0,0,1,-1,1,1,-1,-1};
int vy[8] = {1,-1,0,0,1,-1,1,-1};

int u =0;


int merge(int y, int x)
{
	beep();
	u=1;

	setl p = st.top(); st.pop();
	vs.push_back(p);

	while(!st.empty())
	{
		setl temp = st.top(); st.pop();

		src[temp.first][temp.second]=' ';
		if(temp.first == p.first && temp.second == p.second) break;
		vs.push_back(temp);
	}

	return 0;
}

class Player
{
	public:
		Player(WINDOW * WIN,int y,int x, chtype c);

		void mvpre();
		void mvup();
		void mvdown();
		void mvleft();
		void mvright();
		int getmv();
		void display();
		void pushst();
		pair<int,int> getposition();

	private:
		int xLoc,yLoc,xMax,yMax;
		int preL = KEY_RIGHT;
		chtype character;
		WINDOW * curwin;
};

Player::Player(WINDOW * win, int y ,int x,chtype c)
{
	curwin = win;
	yLoc =y;
	xLoc = x;
	getmaxyx(curwin,yMax,xMax);
	keypad(curwin,true);
	character = c;
}

pair<int,int> Player::getposition()
{
    return {yLoc,xLoc};
}


void Player::mvup()
{
	if(preL== KEY_DOWN || preL == KEY_UP) return;

	visit[yLoc][xLoc]= 1;
	st.push({yLoc,xLoc});
	
	src[yLoc][xLoc] = '*';
	--yLoc;
	preL = KEY_UP;

	if(yLoc < 1) yLoc = 1;


	if(visit[yLoc][xLoc])
	{
		st.push({yLoc,xLoc});
		merge(yLoc,xLoc);
	}
	
}


void Player::mvdown()
{
	if(preL == KEY_UP || preL == KEY_DOWN) return;

	visit[yLoc][xLoc]= 1;
	st.push({yLoc,xLoc});

	src[yLoc][xLoc] = '*';
	++yLoc;
	preL = KEY_DOWN;
	
	if(yLoc > yMax-2) yLoc = yMax-2; 

	

	if(visit[yLoc][xLoc])
	{
		st.push({yLoc,xLoc});
		merge(yLoc,xLoc);
	}
	
}


void Player::mvleft()
{
	if(preL == KEY_RIGHT||preL==KEY_LEFT) return;

	visit[yLoc][xLoc]= 1;

	st.push({yLoc,xLoc});
	
	src[yLoc][xLoc] = '*';
	--xLoc;
	preL = KEY_LEFT;

	
	if(xLoc < 1) xLoc = 1;

	if(visit[yLoc][xLoc])
	{
		st.push({yLoc,xLoc});
		merge(yLoc,xLoc);
	}
	

}


void Player::mvright()
{
	if(preL == KEY_LEFT || preL == KEY_RIGHT) return;

	visit[yLoc][xLoc]= 1;

	st.push({yLoc,xLoc});
	
	src[yLoc][xLoc] = '*';
	++xLoc;
	preL = KEY_RIGHT;

	if(xLoc > xMax-2) xLoc = xMax-2;


	if(visit[yLoc][xLoc])
	{
		st.push({yLoc,xLoc});
		merge(yLoc,xLoc);
	}
}

void Player::mvpre()
{

	visit[yLoc][xLoc]= 1;
	bool ck=0;
	if(preL == KEY_LEFT || preL == KEY_RIGHT) 
	{
		st.push({yLoc,xLoc});
		src[yLoc][xLoc] = '-';
		if(preL == KEY_LEFT)
		{
			--xLoc;
			if(xLoc <1) 
			{
				xLoc=1;
				ck=true;
				st.pop();
			}
		}
		else
		{
			++xLoc;			
			if(xLoc > xMax-2) 
			{
				xLoc = xMax-2;
				ck=true;
				st.pop();
			}
		}		
	}
	else
	{
		st.push({yLoc,xLoc});
		src[yLoc][xLoc] = '|';
		if(preL == KEY_UP)
		{
			--yLoc;
			if(yLoc < 1) 
			{
				yLoc = 1;
				ck=true;
				st.pop();
			}

		}
		else
		{
			++yLoc;
			if(yLoc>yMax-2) 
			{
				yLoc = yMax-2;
				ck=true;
				st.pop();
			}
		}
		
	}
	

	if(!ck&&visit[yLoc][xLoc])
	{
		st.push({yLoc,xLoc});
		merge(yLoc,xLoc);
	}
}

int Player::getmv()
{
	int choice = wgetch(curwin);
	u = 0;
	switch (choice)
	{
		case KEY_UP:
			mvup();	
			break;
		case KEY_DOWN:
			mvdown();
			break;
		case KEY_LEFT:
			mvleft();
			break;
		
		case KEY_RIGHT:
			mvright();
			break;
		case -1:
			mvpre();
			break;

		default:
			break;
	}
	
	return u;
}


void Player::display()
{
	mvwaddch(curwin,yLoc,xLoc,character);
}

void Player::pushst()
{
	visit[yLoc][xLoc]=1;
}

#endif