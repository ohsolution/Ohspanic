#ifndef _MONSTER_H_
#define _MONSTER_H_
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <random>
#include <string.h>
#include "attack.h"
using namespace std;

pair<int,int> vu[8] = {{0,1},{0,-1},{1,0},{-1,0},{-1,1},{1,-1},{1,1},{-1,-1}};

struct info
{
    int yp,xp;
    char ch;
};


extern vector<at> attv;
extern bool warning[107][107];

int attarr[5] = {20,10,60,10,10};
extern int visit[107][107];
info vm[5][13]=
{
    {{0,0,'o'},{-1,-1,'\\'},{-1,1,'/'},{-200,-200,'x'},},
    {{-1,0,'^'},{0,2,'>'},{0,-2,'<'},{2,0,'V'},{1,-2,'<'},{1,2,'>'},{0,1,']'},{0,-1,'['},{1,1,']'},{1,-1,'['},{0,0,' '},{1,0,' '},{-200,-200,'x'},},
    {{0,0,'O'},{2,0,'$'},{0,2,'$'},{1,1,'$'},{1,-1,'$'},{-1,1,'$'},{-1,-1,'$'},{-2,0,'$'},{0,-2,'$'},{-200,-200,'x'},},
};

pair<int,int> movearr[5]= {{4,4},{4,0},{8,0}};
unsigned int sedarr[10] = {8,13,19,27,43,55,171,113,211,310};
int s;
int a3;
extern int mode;


void attack(int atp,int y,int x,int * a2)
{
    if(atp == 0)
    {
        fa(i,4,8)
        {
            at temp;
            int ny = y+vu[i].first;
            int nx = x+vu[i].second;

            if(ny <=0 || nx <=0 || ny >=39 || nx >=79);
            else
            {    
                temp.curpos = {ny,nx};
                temp.dir = {vu[i].first,vu[i].second};
                temp.tp = atp;
                temp.period= 5; 
                chtype tch = '*' | COLOR_PAIR(1);
                temp.ch = tch;
                attv.push_back(temp);
            }
        }
    }
    else if(atp==1)
    {
        if(*a2==0)
        {
            fa(i,0,6)
            {
                at temp;
                int ny = y+vm[atp][i].yp;
                int nx = x+vm[atp][i].xp;

                if(ny <=0 || nx <=0 || ny >=39 || nx >=79);
                else
                {
                    temp.curpos = {ny,nx};
                    if(vm[atp][i].ch== '>') temp.dir={0,1};
                    else if(vm[atp][i].ch=='<') temp.dir= {0,-1};
                    else if(vm[atp][i].ch=='^') temp.dir={-1,0};
                    else temp.dir={1,0};

                    temp.tp = atp;
                    temp.period= 3;
                    chtype tch = vm[atp][i].ch | COLOR_PAIR(2);
                    temp.ch = tch;
                    attv.push_back(temp);
                }
            }   
        }

        else if(*a2==1)
        {
            vm[atp][10].ch='0';
        }

        else if(*a2==2) vm[atp][11].ch='0';

        else if(*a2==3)
        {
            vm[atp][10].ch=' ';
            vm[atp][11].ch=' ';
            vm[atp][0].ch='0';
            vm[atp][3].ch ='0';
        }
        else if(*a2==4)
        {
            vm[atp][0].ch='^';
            vm[atp][3].ch='V';

            at temp;
            temp.bomb = 30;
            temp.period=5;
            chtype tch = '0' | COLOR_PAIR(7);
            temp.ch=tch;
            temp.tp=5;
            temp.curpos = {y-1,x};
            temp.dir = {-1,0};
            attv.push_back(temp);
            temp.curpos = {y+2,x};
            temp.dir = {1,0};
            attv.push_back(temp);
        }

        ++(*a2);
        if(*a2==5) *a2=0;

    }
    else if(atp==2)
    {
        
        if(!a3)
        {
            fa(i,0,8)
            {
                at temp;
                int ny = y+vu[i].first;
                int nx = x+vu[i].second;

                if(ny <=0 || nx <=0 || ny >=39 || nx >=79);
                else
                {    
                    temp.curpos = {ny,nx};
                    temp.dir = {vu[i].first,vu[i].second};
                    temp.tp = 3;
                    temp.period= 3;
                    temp.bomb=21; 
                    chtype tch = 'O' | COLOR_PAIR(atp+1);
                    temp.ch = tch;
                    attv.push_back(temp);
                }
            }
        }
        else if(a3 == 1)
        {
            vm[2][0].ch = '!';
            
            fa(i,0,8)
            {
                fa(j,1,100)
                {
                    at temp;                        
                    int ny = y+vu[i].first*j;
                    int nx = x+vu[i].second*j;

                    if(ny <=0 || nx <=0 || ny >=39 || nx >=79 || visit[ny][nx])
                    {
                        break;
                    }
                    else
                    {                            
                        warning[ny][nx]=1;
                    }
                }
            }
        }
        else
        {
            
            fa(i,0,8)
            {
                fa(j,1,100)
                {
                    at temp;                        
                    int ny = y+vu[i].first*j;
                    int nx = x+vu[i].second*j;

                    if(ny <=0 || nx <=0 || ny >=39 || nx >=79 || visit[ny][nx])
                    {
                        break;
                    }
                    else
                    {    
                        temp.curpos = {ny,nx};
                        temp.dir = {vu[i].first,vu[i].second};
                        temp.tp = atp;
                        temp.period= 1; 
                        chtype tch;
                        tch = ' ' | COLOR_PAIR(8);
                        temp.ch = tch;
                        attv.push_back(temp);
                    }
                }
            }

            memset(warning,0,sizeof(warning));

            vm[2][0].ch = 'O';
        }
        

        if(++a3 == 3) a3=0;
    }
    else
    {
        
    }

    return;
}

class Monster
{
	public:
		Monster(WINDOW * WIN,int y,int x, int t,int mvv);

		void getrandmv();
		void display();
        bool check();
        bool getposition(pair<int,int> p);

	private:
		int xLoc,yLoc,xMax,yMax,ty;
        int hp;
        int att=0;
        int a2=0;
        int mv=0;
		chtype character;
		WINDOW * curwin;
};


Monster::Monster(WINDOW * win, int y ,int x,int t,int mvv)
{
	curwin = win;
	yLoc =y;
	xLoc = x;
    mv =mvv;
	getmaxyx(curwin,yMax,xMax);
	keypad(curwin,true);
	ty = t;
    hp = t+1;
}

bool Monster::getposition(pair<int,int> p)
{
    for(auto x : vm[ty])
    {
        if(x.ch == 'x') break;
        if(p.first==yLoc+x.yp&&xLoc+x.xp==p.second) return 1;
    }
    return 0;
}

bool Monster::check()
{
    int s =0;
    int num = 0;

    for(int i = xLoc+1; i< 79 ; ++i)
    {
        if(visit[yLoc][i])
        {
            while(++i)
            {
                if(!visit[yLoc][i]) break;
            }
            ++num;
        }
    }
    if(num%2)
    {
        ++s;
    }
    
    num = 0;
    
    for(int i = xLoc-1; i> 0 ; --i)
    {
        if(visit[yLoc][i])
        {
            while(--i)
            {
                if(!visit[yLoc][i]) break;
            }
            ++num;
        }
    }
    if(num%2)
    {
        ++s;
    }
    

    num=0;

    for(int i = yLoc-1; i> 0 ; --i)
    {
        if(visit[i][xLoc])
        {
            while(--i)
            {
                if(!visit[yLoc][i]) break;
            }
            ++num;
        }
    }
    if(num%2)
    {
        ++s;
    }

    num=0;

    for(int i = yLoc+1; i< 39 ; ++i)
    {
        if(visit[yLoc][i])
        {
            while(++i)
            {
                if(!visit[yLoc][i]) break;
            }
            ++num;
        }
    }
    if(num%2)
    {
        ++s;
    }


    if(s>=3)
    {
        --hp;
        if(hp==0) return 1;
    }
    
    return 0;
}


void Monster::getrandmv()
{
    if(++mv!=mode) return;

    mv=0;
    
    mt19937 engine((unsigned int)time(NULL));
    uniform_int_distribution<int> distribution(0,100);
    auto generator = bind(distribution,engine);

    ++s;
    if(s==10) s= 0;

    int ger = sedarr[s] * generator();

    int dir = (ger%movearr[ty].first)+movearr[ty].second;

    att += generator()%3;

    bool mk =true;

    if(att> attarr[ty])
    {
        att =0;

        attack(ty,yLoc,xLoc,&a2);
    }
    else
    {
        if(a3==2 && ty==2) return;

        L3:

        yLoc += vu[dir].first;
        xLoc += vu[dir].second;

        bool ok = true;

        for(auto x : vm[ty])
        {
            if(x.ch=='x') break;

            int ny = yLoc + x.yp;
            int nx = xLoc + x.xp;

            if(ny >= 39 || nx >= 79 || ny <=0 || nx <=0 || visit[ny][nx])
            {
                ok =false;
                break;
            }
        }

        if(!ok)
        {
            yLoc -= vu[dir].first;
            xLoc -= vu[dir].second;
            if(mk)
            {
                dir = (generator()%4)+4;
                mk = false;
                goto L3;
            }
        }    
    }

    return;
}

void Monster::display()
{
    wattron(curwin,COLOR_PAIR(hp));

    for(auto x : vm[ty])
    {
        if(x.ch == 'x') break;
        mvwaddch(curwin,yLoc+x.yp,xLoc+x.xp,x.ch);
    }
    wattroff(curwin,COLOR_PAIR(hp));
}





















#endif
