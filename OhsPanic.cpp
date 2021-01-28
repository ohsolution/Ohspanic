#include <ncurses.h>
#include <string>
#include <stdlib.h>
#include "player.h"
#include "monster.h"
#include "attack.h"
#include <ctime>
#include <chrono>
#include <thread>
#include <fstream>
#include <utility>
#include <stdio_ext.h>
#include <string.h>
#include <stdio.h>
#include <stack>
#include <vector>
#include <algorithm>
#define setl pair<int,int>
#define fa(i,a,b) for(int i=a;i < b; ++i)

using namespace std;
using namespace std::this_thread;
using namespace std::chrono_literals;


const int max_v = (int)1e2+7;
int coin;
int specialcoin;
extern pair<int,int> vu[8];
bool warning[max_v][max_v];
int mode=1;
bool cheat=0;
char name[5][45] = {
    {"               ##  ##     #    #  # ### ####"},
    {"  ##   #  # ' #    # #   # #   ## #  #  #   "},
    {" #  #  ####    #   ##   #####  # ##  #  #   "},
    {" #  #  #  #     #  #   #     # #  # ### ####"},
    {"  ##   #  #   ##   #                        "}
        };

char wg[39][79]=
{
    {"                                                                              "},
    {"                                                                              "},
    {"                                                                              "},
    {"                                                                              "},
    {"                                                                              "},
    {"     #           #                                                            "},
    {"      #         #     ###      #        #                                     "},
    {"       #       #     #####     #        #                                     "},
    {"        #     #     #     ##   #        #                                     "},
    {"         #   #     ##     ##   #        #                                     "},
    {"          # #      #      ##   #        #                                     "},
    {"           #       ##     ##   #        #                                     "},
    {"           #       ##     ##   #        #                                     "},
    {"           #        #     #    ##########                                     "},
    {"           #         #####                                                    "},
    {"                       #                                                      "},
    {"                                                                              "},
    {"                                                                              "},
    {"                                                                              "},
    {"          #           #           # ##############  #        #                "},
    {"           #         # #         #        #         ##       #                "},
    {"            #       #   #       #         #         # #      #                "},
    {"             #     #     #     #          #         #  #     #                "},
    {"              #   #       #   #           #         #   ##   #                "},
    {"               # #         # #            #         #     #  #                "},
    {"                #           #             #         #      # #                "},
    {"                                    ##############  #       #                 "},
    {"                                                                              "},
    {"                                                                              "},
    {"                                                                              "},
    {"                                                                              "},
    {"                                                                              "},
    {"                                               developed by Ohsolution.       "},
    {"                                                                              "},
    {"                                                                              "},
    {"                                                                              "},
    {"                                                                              "},
    {"                                                                              "}
};


int visit[max_v][max_v];
char arr[max_v][max_v]; // ans
char src[max_v][max_v] = {' ',}; // display
vector <setl > vs;
vector < Monster *> mon;
vector <at> attv;
stack <setl > st;


bool cmp(at a, at b)
{
    return a.tp > b.tp;
}


int main(int argc, char ** argv)
{
    // init
    initscr();
    cbreak();
    noecho();

    start_color();
    int sy,sx;
    getmaxyx(stdscr,sy,sx);
    sy /=8; // 6
    sx/=4; //62

    WINDOW * outerwin = newwin(40,80,sy,sx); // row colunm by bx
    WINDOW * coinwin = newwin(3,15,sy+1,sx+1);
    WINDOW * titlewin = newwin(5,47,sy+10,sx+16);
    WINDOW * menuwin = newwin(4,40,sy+30,sx+21);
    

    box(outerwin,0,0); // win two chtype default 0,0

    refresh();
    wrefresh(outerwin);
    wrefresh(coinwin);
    wrefresh(menuwin);

    init_pair(1,COLOR_BLUE,COLOR_BLUE);
    chtype pix= ' ' | COLOR_PAIR(1);

    fa(i,0,5)
    {
        fa(j,0,45)
        {
            if(name[i][j]=='#')
            {
                mvwaddch(titlewin,i,j,pix);
            }
        }
    }

    wrefresh(titlewin);
    
    wattron(menuwin,A_BLINK);
    wattron(coinwin,A_BLINK);
   
    while(1)
    {
        halfdelay(5);

        wrefresh(menuwin);


        if(coin)
        {
            mvwprintw(menuwin,1,0,"     Press the enter key!!!    ");
        }
        else
        {
            mvwprintw(menuwin,1,0,"     Insert the coin with c key");
        }

        mvwprintw(coinwin,1,0," Coin(s) : %d",coin);


        wrefresh(menuwin);
        wrefresh(coinwin);
        
        char ch= getch();
        
        if(ch == 'c' || ch == 'C')
        {
            beep();
            if(coin==9) 
            {   
                coin=9;
                ++specialcoin;
            }
            else ++coin;
        }
        else if(ch == '\n' && coin)
        {
            --coin;
            break;
        }
        else if(ch=='7')
        {
            mode=2;
        }
        else if(ch=='0') cheat=1;
    }

    if(specialcoin==7)
    {
        system("xdg-open support/TheStarsOfSemi.jpg");
        system("canberra-gtk-play -f support/R.ogg");               
        getch(); 
    }

    clear();
    refresh();
    endwin();

    while(1)
    {
        initscr();
        nocbreak();
        noecho();
        start_color();
        
        init_pair(1,COLOR_RED,COLOR_BLACK);
        init_pair(2,COLOR_YELLOW,COLOR_BLACK);
        init_pair(3,COLOR_BLUE,COLOR_BLACK);
        init_pair(4,COLOR_GREEN,COLOR_BLACK);
        init_pair(5,COLOR_CYAN,COLOR_BLACK);
        init_pair(8,COLOR_BLUE,COLOR_BLUE);

        init_pair(6,COLOR_MAGENTA,COLOR_BLACK);
        init_pair(7,COLOR_RED,COLOR_YELLOW);

        chtype bomb = 'V' | COLOR_PAIR(7);
        chtype charc = '@' | COLOR_PAIR(6);
        chtype warn = '!' | COLOR_PAIR(4) | A_BLINK;

        fa(i,0,max_v)
        {
            fa(j,0,max_v)
            {
                src[i][j] = ' ';
                visit[i][j] = 0;
                warning[i][j]=0;
            }
        }

        vs.clear();
        mon.clear();
        attv.clear();

        WINDOW * outerwin = newwin(40,80,sy,sx); // row colunm by bx
        WINDOW * coinwin = newwin(3,15,sy-3,sx+1);

        box(outerwin,0,0);

        mvwprintw(coinwin,1,0," Coin(s) : %d",coin);

        wrefresh(outerwin);
        wrefresh(coinwin);

        halfdelay(1);        
        
        Player * p = new Player(outerwin,20,40,charc);
        mon.push_back(new Monster(outerwin,10,20,0,0));
        mon.push_back(new Monster(outerwin,30,20,0,0));
        mon.push_back(new Monster(outerwin,10,60,0,0));
        mon.push_back(new Monster(outerwin,30,60,0,0));
        mon.push_back(new Monster(outerwin,20,10,1,0));
        mon.push_back(new Monster(outerwin,20,70,1,0));
        mon.push_back(new Monster(outerwin,10,40,1,0));
        mon.push_back(new Monster(outerwin,30,40,1,0));
        mon.push_back(new Monster(outerwin,4,4,2,0));

        curs_set(0);

        p->pushst();
        bool cok = false;
        while(!cok || cheat)
        {
            
            if(p->getmv())// 폭발 시 check
            {
                 // 몬스터 체킹 -> 체력 dec -> visit 초기화 src 라인 제거 
                
                
                for(auto x : vs)
                {
                    mvwaddch(outerwin,x.first,x.second,bomb);
                }

                 
                while(!st.empty())
                {
                    setl cur= st.top();
                    st.pop();

                    visit[cur.first][cur.second] =0;
                    src[cur.first][cur.second]=' ';
                }

                
                wrefresh(outerwin);

                sleep_for(500ms);

                int msi= mon.size();

                

               for(int i=0;i<mon.size();++i)
               {
                   if(mon[i]->check())
                   {
                       beep();
                       auto a = mon.begin();
                       fa(j,0,i) ++a;
                       mon.erase(a);
                       --i;
                   }
               }


               

               for(auto x : vs) visit[x.first][x.second] = 0;

               vs.clear();


               p->pushst();
            }
            
            for(auto x : mon)
            {
                x->getrandmv();
            }
            
            int atsi= attv.size();
            setl cp = p->getposition(); 
            for(int i=0;i<atsi;++i)
            {
                auto &x = attv[i];

                if(x.tp==3||x.tp==5) --x.bomb;

                x.period--;

                if(x.period ==0)
                {
                    int nx = x.curpos.x + x.dir.x;
                    int ny = x.curpos.y + x.dir.y;
                                        
                    if(nx <=0 || ny <=0 || nx >=79 || ny>=39 || visit[ny][nx])
                    {   
                        x.tp = -1;
                        x.bomb=0;
                    }
                    else
                    {
                        x.curpos.x = nx;
                        x.curpos.y = ny;
                        x.period = 3;                        
                    }                    
                }

                if(x.tp==5 && (!x.bomb))
                {
                    fa(i,0,8)
                    {
                        at temp;
                        int ny = x.curpos.y+vu[i].first;
                        int nx = x.curpos.x+vu[i].second;

                        if(ny <=0 || nx <=0 || ny >=39 || nx >=79 || visit[ny][nx]);
                        else
                        {    
                            temp.curpos = {ny,nx};
                            temp.dir = {vu[i].first,vu[i].second};
                            temp.tp = 0;
                            temp.period= 3; 
                            chtype tch = '*' | COLOR_PAIR(2);
                            temp.ch = tch;
                            attv.push_back(temp);
                        }
                    }
                    x.tp=-1;
                }

                if(x.tp==3 && (!x.bomb))
                {
                    int ut=14;
                    
                    while(ut)
                    {
                        at temp;
                        int ny = x.curpos.y+(x.dir.y*ut);
                        int nx = x.curpos.x+(x.dir.x*ut);

                        if(ny <=0 || nx <=0 || ny >=39 || nx >=79 || visit[ny][nx]);
                        else
                        {    
                            temp.curpos = {ny,nx};
                            temp.dir = x.dir;
                            temp.tp = 0;
                            temp.period= 1; 
                            chtype tch = '*' | COLOR_PAIR(3);
                            temp.ch = tch;
                            attv.push_back(temp);
                        }

                        ut-=2;
                    }

                    x.tp=-1;
                }

                if(x.curpos.y == cp.first && x.curpos.x == cp.second) cok=true;                        
            }

            sort(attv.begin(),attv.end(),cmp);
            while(!attv.empty())
            {
                if(attv.back().tp !=-1) break;
                attv.pop_back();
            }

            for(int i = 1 ; i<39 ; ++ i )//1 ~ 38 , 1 ~ 78
            {
                for(int j = 1 ; j <79; ++j)
                {
                    if(warning[i][j]&&(!visit[i][j])) 
                    {                        
                        mvwaddch(outerwin,i,j,warn);                        
                    }
                    else mvwaddch(outerwin,i,j,src[i][j]);   
                }
            }

            p->display();
        
            for(auto x : mon)
            {
                x->display();
            }

            for(auto x : attv)
            {
                mvwaddch(outerwin,x.curpos.y,x.curpos.x,x.ch);
            }

            wrefresh(outerwin);

            
            for(auto x : mon)
            {                
                if(x->getposition(cp))
                {
                    cok =true;
                }                
            }

            if(mon.empty()) goto wingame;
        }


        
        if(coin)
        {
            --coin;
            clear();
            refresh();
            endwin();
        }
        else
        {
            wclear(coinwin);
            WINDOW * coinwin = newwin(3,15,sy-3,sx+1);
            WINDOW * rewin = newwin(3,50,sy-3,sx+20);
            int lt = 9;

            halfdelay(10);

            do
            {
                mvwprintw(rewin,1,0,"Insert the coin !!! %d",lt);
                mvwprintw(coinwin,1,0, "Coin(s) : %d",coin);
                --lt;

                char cch = getch();
                if(cch == 'c' || cch == 'C')
                {
                    ++coin;                    
                }
                else if(cch =='\n') break;

                wrefresh(rewin);
                wrefresh(coinwin);
            } while (lt >=0);
                        
            if(coin)
            {
                --coin;
                clear();
                refresh();
                endwin();
                continue;
            }

            break;
        }
    }


    goto Losegame;

    {
        wingame:
        wclear(coinwin);
        refresh();

        start_color();
        init_pair(10,COLOR_CYAN,COLOR_CYAN);
        chtype sch = ' ' | COLOR_PAIR(10);
        
        fa(i,1,38)
        {
            fa(j,1,78)
            {
                if(wg[i][j] =='#') mvwaddch(outerwin,i,j,sch);
                else if(wg[i][j]!=' ') mvwaddch(outerwin,i,j,wg[i][j]);
                else mvwaddch(outerwin,i,j,' ');
            }
        }

        wrefresh(outerwin);
        system("canberra-gtk-play -f support/ending.ogg");
        getch();
    }

    Losegame:

    clear();
    refresh();
    endwin();

    system("clear");
    return 0;
}
	
