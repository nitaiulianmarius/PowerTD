#include<iostream>
#include<stdio.h>
#include<graphics.h>
#include<fstream>
#include<conio.h>
#include<time.h>
#include<windows.h>
#define u PU
int p=15,PU=55,x,y,n,m;

//wood 8,15,18
//boss 10;20;29;
int viatalvl[50]={0,10,42,65,100,150,250,350,500,700,900,1000,1100,1384,1445,1580,1700,1600,1806,2125,3000,3275,3465,3560,3615,3935,4165,4405,4655,4800,10000,10000,50000,100000,400000,700000};
int gold[50]={    0, 1, 1, 1,  1,  1,  1,  4,  5,  5,  3,   2,   2,   2,   2,   2,   3,   3,   5,   10,  1,   3,   4,   4,   4,   4,   5,   5,  10,  5,   15,  10,   15,   15,   25,   35};

int ContorNext;
int timestart;
int lastbutton=10000;

int maxx=1000;
int maxy=627;

int ncannon=1,narrow=1,nfire=1,nwatter=1,nearth=1,nboss=1,ninamic=1;

int action;
/*
	action = 1 => constr cannon
	action = 2 => constr arrow
	action = 3 => constr watter
	action = 4 => constr earth
	action = 5 => constr fire
	action = 6 => constr boss
*/
#define C 1
#define A 2
#define W 3
#define E 4
#define F 5
#define B 6

  
char l[30][30];

using namespace std;


struct Level
{
	int x,y;
	int nr;

	void draw(int x,int y);
	void del();
	void update();
	
	Level()
	{
           nr=1;
    }

}level;



struct Inamic
{
	int x,y;
	int nr;
	int stare;
	int directie;
	int viata;
	int maxviata;

	void draw(int i);
	void del(int i);
	void update(int i);

	Inamic()
	{
		stare=1;
		directie=3;
		x=4*PU;
		y=0;
		viata=maxviata=viatalvl[level.nr];
	};

}pc[30];



struct Viata
{
	int x,y;
	int nr;

	void draw(int x,int y);
	void del();
	void update();

	Viata()
	{
		nr=25;
	};

}heal;



struct Bani
{
	int x,y;
	int nr;

	void draw(int x,int y);
	void del();
	void update();

	Bani()
	{
		nr=40;
	};

}money;



struct Lemne
{
	int x,y;
	int nr;

	void draw(int x,int y);
	void del();
	void update();

	Lemne()
	{
		nr=0;
	};
}wood;



struct Leveltime
{
	int x,y;
	int time;

	void draw(int x,int y);
	void del();
	void update();

	Leveltime()
	{
		time=10000;
	};

}leveltime;



struct Button
{
	int x1,y1,x2,y2;
	int nr;
	int itower;
	char text[30];

	void create(int nr,int x1,int y1,int x2,int y2,char *text);
	bool click(int nr);
	bool pointer(int nr);

}buton[30];



struct CannonTower
{
	int x,y;
	int nr;

	int dmg;
	int range;
	float speed;
	int nextattacktime;
	int lastattacktime;
	int cost;
	int up;
	int sell;
	int lvl;
	int maxlvl;

	void draw(int nr,int x,int y);
	void del(int nr);
	void upgrade(int nr);
	void info(int nr);

	CannonTower()
	{
		dmg=9;
		range=2;
		speed=1.5;
		cost=9;
		up=15;
		sell=6;
		lvl=1;
		maxlvl=3;
		nextattacktime=667;
		lastattacktime=0;
	}

}cannon[1001];



struct ArrowTower
{
	int x,y;
	int nr;

	int dmg;
	int range;
	float speed;
	int nextattacktime;
	int lastattacktime;
	int cost;
	int up;
	int sell;
	int lvl;
	int maxlvl;

	void draw(int nr,int x,int y);
	void del(int nr);
	void upgrade(int nr);
	void info(int nr);

	ArrowTower()
	{
		dmg=6;
		range=3;
		speed=3;
		cost=7;
		up=13;
		sell=5;
		lvl=1;
		maxlvl=3;
		nextattacktime=330;
		lastattacktime=0;
	}

}arrow[1001];



struct FireTower
{
	int x,y;
	int nr;

	int dmg;
	int range;
	float speed;
	int nextattacktime;
	int lastattacktime;
	int cost;
	int up;
	int sell;
	int lvl;
	int maxlvl;

	void draw(int nr,int x,int y);
	void del(int nr);
	void upgrade(int nr);
	void info(int nr);

	FireTower()
	{
		dmg=75;
		range=3;
		speed=2;
		cost=50;
		up=75;
		sell=37;
		lvl=1;
		maxlvl=4;
		nextattacktime=500;
		lastattacktime=0;
	}

}fire[1001];



struct WatterTower
{
	int x,y;
	int nr;

	int dmg;
	int range;
	float speed;
	int nextattacktime;
	int lastattacktime;
	int cost;
	int up;
	int sell;
	int lvl;
	int maxlvl;

	void draw(int nr,int x,int y);
	void del(int nr);
	void upgrade(int nr);
	void info(int nr);

	WatterTower()
	{
		dmg=25;
		range=2;
		speed=4;
		cost=50;
		up=25;
		sell=37;
		lvl=1;
		maxlvl=4;
		nextattacktime=250;
		lastattacktime=0;
	}

}watter[1001];



struct EarthTower
{
	int x,y;
	int nr;

	int dmg;
	int range;
	float speed;
	int nextattacktime;
	int lastattacktime;
	int cost;
	int up;
	int sell;
	int lvl;
	int maxlvl;

	void draw(int nr,int x,int y);
	void del(int nr);
	void upgrade(int nr);
	void info(int nr);

	EarthTower()
	{
		dmg=144;
		range=3;
		speed=0.4;
		cost=50;
		up=75;
		sell=37;
		lvl=1;
		maxlvl=4;
		nextattacktime=2500;
		lastattacktime=0;
	}

}earth[1001];



struct BossTower
{
	int x,y;
	int nr;

	int dmg;
	int range;
	float speed;
	int nextattacktime;
	int lastattacktime;
	int cost;
	int up;
	int sell;
	int lvl;
	int maxlvl;

	void draw(int nr,int x,int y);
	void del(int nr);
	void upgrade(int nr);
	void info(int nr);

	BossTower()
	{
		dmg=2000;
		range=7;
		speed=0.4;
		cost=200;
		up=190;
		sell=150;
		lvl=1;
		maxlvl=2;
		nextattacktime=2500;
		lastattacktime=0;
	}

}boss[1001];



void Inamic::draw(int i)
{
     u-=28;
     pc[i].x+=14;
	 pc[i].y+=14;
     pc[i].nr=i;

	if(level.nr%2)
	{
    setlinestyle(SOLID_LINE,0,1);
	setcolor(YELLOW);
	circle(pc[i].x+0.5*PU,pc[i].y+0.5*PU,0.28*PU);
	setcolor(LIGHTBLUE);
	circle(pc[i].x+0.5*PU,pc[i].y+0.5*PU,0.18*PU);
	setcolor(LIGHTGREEN);
	line(pc[i].x+0.3*PU,pc[i].y+0.7*PU,pc[i].x+3,pc[i].y+0.8*PU);
	line(pc[i].x+0.7*PU,pc[i].y+0.7*PU,pc[i].x+PU-3,pc[i].y+0.8*PU);
	setlinestyle(SOLID_LINE,0,3);
	float dist;
    dist=(float)pc[i].viata/pc[i].maxviata*PU;
	line(pc[i].x+2,pc[i].y+3,pc[i].x+2+dist,pc[i].y+3);
	}
	else
	{
    setlinestyle(SOLID_LINE,0,1);
	setcolor(YELLOW);
	circle(pc[i].x+0.5*PU,pc[i].y+0.5*PU,0.2*PU);
	setcolor(LIGHTBLUE);
	circle(pc[i].x+0.5*PU,pc[i].y+0.5*PU,0.3*PU);
	setcolor(LIGHTGREEN);
	circle(pc[i].x+0.5*PU,pc[i].y+0.5*PU,0.4*PU);
	setlinestyle(SOLID_LINE,0,3);
	float dist;
    dist=(float)pc[i].viata/pc[i].maxviata*PU;
	line(pc[i].x+2,pc[i].y+3,pc[i].x+2+dist-3,pc[i].y+3);
	}
     pc[i].x-=14;
	 pc[i].y-=14;
	 u+=28;
}



void Inamic::del(int i)
{
	setfillstyle(0,0);
	bar(pc[i].x+12,pc[i].y+14,pc[i].x+PU-7,pc[i].y+PU-14);
}



void Inamic::update(int i)
{
	int xc,yc;
	xc=pc[i].x/PU;
	yc=pc[i].y/PU;
	pc[i].del(i);
	if(l[yc][xc]!='0'&&yc*PU==pc[i].y&&xc*PU==pc[i].x)
			pc[i].directie=l[yc][xc]-48;
	if(pc[i].directie==1)
		pc[i].y-=5;
	if(pc[i].directie==2)
		pc[i].x+=5;
	if(pc[i].directie==3)
		pc[i].y+=5;
	if(pc[i].directie==4)
		pc[i].x-=5;
	pc[i].draw(i);
}



void Viata::draw(int x,int y)
{
	heal.x=x;
	heal.y=y;
	char v[5];
	sprintf(v,"%d",heal.nr);
	setcolor(YELLOW);
	setlinestyle(SOLID_LINE,0,1);
    circle(x+p,y+p/2,p/2-1);        // cap
    line(x+p,y+p,x+p,y+1.3*p);    // corp
    line(x+p,y+1.3*p,x+p/2,y+2*p-5);  // piciorul stang
    line(x+p,y+1.3*p,x+1.5*p,y+2*p-5); // piciorul drept
    line(x+p,y+p,x+p/2,y+1.2*p); // mana stanga
    line(x+p,y+p,x+1.5*p,y+1.2*p); // mana dreapta
	setcolor(WHITE);
	outtextxy(x+2*p,y+p/2,v);
}



void Viata::del()
{
	char v[5];
	sprintf(v,"%d",heal.nr);
	setfillstyle(0,0);
	bar(heal.x,heal.y,heal.x+p+textwidth(v)+20,heal.y+p+10);
}



void Viata::update()
{
	heal.del();
	heal.nr--;
	heal.draw(heal.x,heal.y);
}



void Bani::draw(int x,int y)
{
	money.x=x;
	money.y=y;
	char v[5];
	sprintf(v,"%d",money.nr);
	setcolor(YELLOW);
	circle(x+p,y+p,p);
	setcolor(WHITE);
	outtextxy(x+2*p+3,y+p/2,v);
}



void Bani::del()
{
	char v[5];
	sprintf(v,"%d",money.nr);
	setfillstyle(0,0);
	bar(money.x+2*p+2,heal.y,money.x+2*p+textwidth(v)+15,money.y+2*p);
}



void Bani::update()
{
	money.del();
	money.draw(money.x,money.y);
}



void Lemne::draw(int x,int y)
{
	wood.x=x;
	wood.y=y;
	char v[5];
	sprintf(v,"%d",wood.nr);
	setcolor(GREEN);
	circle(x+p,y+p,p);
	for(int i=x;i<x+2*p;i++)
		for(int j=y;j<=y+2*p;j++)
		{
			int dx=x+p-i;
			int dy=y+p-j;
			if(dx*dx+dy*dy<=p*p)
				putpixel(i,j,GREEN);
		}
	setcolor(WHITE);
	outtextxy(x+2*p+3,y+p/2,v);
}



void Lemne::del()
{
	char v[5];
	sprintf(v,"%d",wood.nr);
	setfillstyle(0,0);
	bar(wood.x,wood.y,wood.x+2*p+textwidth(v)+20,wood.y+2*p);
}



void Lemne::update()
{
	wood.del();
	wood.draw(wood.x,wood.y);
}



void Level::draw(int x,int y)
{
	level.x=x;
	level.y=y;
	char v[5];
	sprintf(v,"%d",level.nr);
	setcolor(WHITE);
	outtextxy(x,y,"Level:");
	outtextxy(x+textwidth("Level:")+3,y,v);
}



void Level::del()
{
	char v[30];
	sprintf(v,"Level: %d",level.nr);
	setfillstyle(0,0);
	bar(level.x,level.y,level.x+textwidth(v)+20,level.y+textheight(v));
}



void Level::update()
{
	level.del();
	level.nr++;
	level.draw(level.x,level.y);
}



void Leveltime::draw(int x,int y)
{
	leveltime.x=x;
	leveltime.y=y;
	char v[30];
	sprintf(v,"Next level in: %ds",leveltime.time/1000);
	setcolor(WHITE);
	outtextxy(x,y,v);
}



void Leveltime::del()
{
	char v[30];
	sprintf(v,"Next level in: %ds",leveltime.time/1000);
	setfillstyle(0,0);
	bar(leveltime.x,leveltime.y,leveltime.x+textwidth(v)+20,leveltime.y+textheight(v));
}



void Leveltime::update()
{
	leveltime.del();
	leveltime.draw(leveltime.x,leveltime.y);
}



void Button::create(int nr,int x1,int y1,int x2,int y2,char *text)
{
	buton[nr].nr=nr;
	buton[nr].x1=x1;
	buton[nr].x2=x2;
	buton[nr].y1=y1+5;
	buton[nr].y2=y2+5;
	strcpy(buton[nr].text,text);
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar(x1,y1,x2,y2);
	setfillstyle(0,BLACK);
	bar(x1+5,y1+5,x2-5,y2-5);
	setlinestyle(SOLID_LINE,0,3);
	setcolor(LIGHTGREEN);
	rectangle(x1,y1,x2,y2);

	int color;
	for(int i=x1+5;i<=x2-5;i++)
		for(int j=y1+5;j<=y2-5;j++,color=rand()%100)
		{
			if(color<90)
				color=BLACK;
			else
				color=BLUE;
			putpixel(i,j,color);
		}


	outtextxy((x1+x2)/2-textwidth(text)/2,(y1+y2)/2-textheight(text)/2,text);
}



bool Button::click(int nr)
{
	if(buton[nr].x1<=x&&x<=buton[nr].x2)
		if(buton[nr].y1<=y&&y<=buton[nr].y2)
			return true;
	return false;
}



bool Button::pointer(int nr)
{
	if(buton[nr].x1<=mousex()&&buton[nr].x2>=mousex())
		if(buton[nr].y1<=mousey()&&buton[nr].y2>=mousey())
			return true;
	return false;
}



void CannonTower::draw(int nr,int x,int y)
{
	CannonTower();
	cannon[nr].x=x;
	cannon[nr].y=y;
	cannon[nr].nr=nr;
	money.nr-=cannon[nr].cost;
    money.update();
	x*=u;
	y*=u;
	x+=8;
	y+=8;
	u-=16;
	int r=u/2;
	setfillstyle(0,0);
	bar(x,y,x+u,y+u);
	setcolor(LIGHTGRAY);
	circle(x+r,y+r,r);
	for(int i=x;i<=x+u;i++)
		for(int j=y;j<=y+u;j++)
		{
			int dx=x+r-i;
			int dy=y+r-j;
			if(dx*dx+dy*dy<=r*r)
				putpixel(i,j,LIGHTGRAY);
		}
	setcolor(LIGHTGREEN);
	line(x+r,y,x+r,y+u);
	line(x,y+r,x+u,y+r);
	line(x,y,x+u,y+u);
	line(x,y+u,x+u,y);
	x-=8;
	y-=8;
	u+=16;
}



void CannonTower::del(int nr)
{
	setfillstyle(1,BLUE);
	cout<<cannon[nr].x<<' '<<cannon[nr].y<<endl;
	bar(cannon[nr].x,cannon[nr].y,cannon[nr].x+u,cannon[nr].y+u);
	l[cannon[nr].y][cannon[nr].x]='x';
	money.nr+=cannon[nr].sell;
	money.update();
}



void CannonTower::upgrade(int nr)
{
	if(money.nr>=cannon[nr].up)
	{
		money.nr-=cannon[nr].up;

		if(cannon[nr].lvl==1)
		{
			cannon[nr].dmg=24;
			cannon[nr].range=2;
			cannon[nr].speed=1.5;
			cannon[nr].cost=0;
			cannon[nr].up=26;
			cannon[nr].sell=18;
			cannon[nr].lvl=2;
		}

		else
			if(cannon[nr].lvl==2)
			{
				cannon[nr].dmg=50;
				cannon[nr].range=2;
				cannon[nr].speed=1.5;
				cannon[nr].cost=0;
				cannon[nr].up=0;
				cannon[nr].sell=37;
				cannon[nr].lvl=3;
			}
	money.update();
	}
}



void CannonTower::info(int nr)
{
     bar(13*u+5,7*u+5,17*u-5,maxy-55);
     int xt=14*u-u/2,yt=7*u+u/4;
     char dmg[3],range[3],speed[3],cost[3]="-",up[3]="-",sell[3],lvl[3];
	 setcolor(LIGHTGREEN);
     sprintf(cost,"Cost: %d",cannon[nr].cost);
     sprintf(up,"Upgrade: %d",cannon[nr].up);
     sprintf(lvl,"[%d]",cannon[nr].lvl);
     sprintf(dmg,"Dmg: %d",cannon[nr].dmg);
     sprintf(range,"Range: %d",cannon[nr].range);
     sprintf(speed,"Speed: %.f/s",cannon[nr].speed);
     sprintf(sell,"Sell: %d",cannon[nr].sell);
     outtextxy(xt+0.7*u,yt,"Cannon");
     outtextxy(xt+0.7*u+textwidth("Cannon "),yt,lvl);
     xt=14*u-u/2-10,yt=7*u+u/2;
     outtextxy(xt,yt+20,cost);
     outtextxy(xt,yt+35,dmg);
     outtextxy(xt,yt+50,range);
     outtextxy(xt,yt+65,speed);
     outtextxy(xt,yt+80,up);
     outtextxy(xt,yt+95,sell);
	 if(nr!=1000)
	 {
		 if(cannon[nr].lvl<cannon[nr].maxlvl)
			buton[6].create(6,xt,yt+118,15*u,maxy-63,"Upgrade [C]");
		 buton[7].create(7,xt+1.8*u,yt+118,15*u+1.7*u,maxy-63,"Sell [C]");
		 buton[6].itower=nr;
		 buton[7].itower=nr;
	 }
}



void ArrowTower::draw(int nr,int x,int y)
{
	ArrowTower();
	arrow[nr].x=x;
	arrow[nr].y=y;
	arrow[nr].nr=nr;
	money.nr-=arrow[nr].cost;
    money.update();
	x*=u;
	y*=u;
	x+=8;
	y+=8;
	u-=16;
	int r=u/2;
	setfillstyle(0,0);
	bar(x,y,x+u,y+u);
	setcolor(LIGHTGRAY);
	circle(x+r,y+r,r);
	for(int i=x;i<=x+u;i++)
		for(int j=y;j<=y+u;j++)
		{
			int dx=x+r-i;
			int dy=y+r-j;
			if(dx*dx+dy*dy<=r*r)
				putpixel(i,j,LIGHTGRAY);
		}
	setcolor(RED);
	line(x+r,y,x+r,y+u);
	line(x,y+r,x+u,y+r);
	line(x,y,x+u,y+u);
	line(x,y+u,x+u,y);
	x-=18;
	y-=18;
	u+=16;
}



void ArrowTower::del(int nr)
{
	setfillstyle(1,BLUE);
	bar(arrow[nr].x,arrow[nr].y,arrow[nr].x+u,arrow[nr].y+u);
	money.nr+=arrow[nr].sell;
	money.update();
}



void ArrowTower::upgrade(int nr)
{
	if(money.nr>=arrow[nr].up)
	{
		money.nr-=arrow[nr].up;

		if(arrow[nr].lvl==1)
		{
			arrow[nr].dmg=16;
			arrow[nr].range=3;
			arrow[nr].speed=3;
			arrow[nr].cost=0;
			arrow[nr].up=32;
			arrow[nr].sell=15;
			arrow[nr].lvl=2;
		}

		else
			if(arrow[nr].lvl==2)
			{
				arrow[nr].dmg=39;
				arrow[nr].range=4;
				arrow[nr].speed=4;
				arrow[nr].cost=0;
				arrow[nr].up=0;
				arrow[nr].sell=39;
				arrow[nr].lvl=3;
				arrow[nr].nextattacktime=250;
			}
	money.update();
	}
}



void ArrowTower::info(int nr)
{
     bar(13*u+5,7*u+5,17*u-5,maxy-50-5);
     int xt=14*u-u/2,yt=7*u+u/4;
     char dmg[3],range[3],speed[3],cost[3]="-",up[3]="-",sell[3],lvl[3];
	 setcolor(LIGHTGREEN);
     sprintf(cost,"Cost: %d",arrow[nr].cost);
     sprintf(up,"Upgrade: %d",arrow[nr].up);
     sprintf(lvl,"[%d]",arrow[nr].lvl);
     sprintf(dmg,"Dmg: %d",arrow[nr].dmg);
     sprintf(range,"Range: %d",arrow[nr].range);
     sprintf(speed,"Speed: %.f/s",arrow[nr].speed);
     sprintf(sell,"Sell: %d",arrow[nr].sell);
     outtextxy(xt+0.7*u,yt,"Arrow");
	 outtextxy(xt+0.7*u+textwidth("Arrow "),yt,lvl);
     xt=14*u-u/2-10,yt=7*u+u/2;
     outtextxy(xt,yt+20,cost);
     outtextxy(xt,yt+35,dmg);
     outtextxy(xt,yt+50,range);
     outtextxy(xt,yt+65,speed);
     outtextxy(xt,yt+80,up);
     outtextxy(xt,yt+95,sell);
	 if(nr!=1000)
	 {
			if(arrow[nr].lvl<arrow[nr].maxlvl)
				buton[6].create(6,xt,yt+118,15*u,maxy-63,"Upgrade [A]");
		 buton[7].create(7,xt+1.8*u,yt+118,15*u+1.7*u,maxy-63,"Sell [A]");
		 buton[6].itower=nr;
		 buton[7].itower=nr;
	 }
}



void FireTower::draw(int nr,int x,int y)
{
	FireTower();
	fire[nr].x=x;
	fire[nr].y=y;
	fire[nr].nr=nr;
	money.nr-=fire[nr].cost;
    money.update();
	x*=u;
	y*=u;
	x+=8;
	y+=8;
	u-=16;
	int r=u/2;
	setfillstyle(1,RED);
	bar(x,y,x+u,y+u);
	setcolor(0);
	line(x+r,y,x+r,y+u);
	line(x,y+r,x+u,y+r);
	line(x,y,x+u,y+u);
	x-=8;
	y-=8;
	u+=16;
}



void FireTower::del(int nr)
{
	setfillstyle(1,BLUE);
	bar(fire[nr].x,fire[nr].y,fire[nr].x+u,fire[nr].y+u);
	money.nr+=fire[nr].sell;
	money.update();
}



void FireTower::upgrade(int nr)
{
	if(money.nr>=fire[nr].up)
	{
		money.nr-=fire[nr].up;

		if(fire[nr].lvl==1)
		{
			fire[nr].dmg=175;
			fire[nr].range=3;
			fire[nr].speed=2;
			fire[nr].cost=0;
			fire[nr].up=100;
			fire[nr].sell=93;
			fire[nr].lvl=2;
		}

		else
			if(fire[nr].lvl==2)
			{
				fire[nr].dmg=300;
				fire[nr].range=3;
				fire[nr].speed=2;
				fire[nr].cost=0;
				fire[nr].up=150;
				fire[nr].sell=168;
				fire[nr].lvl=3;
			}

			else
				if(fire[nr].lvl==3)
				{
					fire[nr].dmg=400;
					fire[nr].range=3;
					fire[nr].speed=2;
					fire[nr].cost=0;
					fire[nr].up=0;
					fire[nr].sell=281;
					fire[nr].lvl=4;
				}
	money.update();
	}
}



void FireTower::info(int nr)
{
     bar(13*u+5,7*u+5,17*u-5,maxy-50-5);
     int xt=14*u-u/2,yt=7*u+u/4;
     char dmg[3],range[3],speed[3],cost[3]="-",up[3]="-",sell[3],lvl[3];
	 setcolor(LIGHTGREEN);
     sprintf(cost,"Cost: %d",fire[nr].cost);
     sprintf(up,"Upgrade: %d",fire[nr].up);
     sprintf(lvl,"[%d]",fire[nr].lvl);
     sprintf(dmg,"Dmg: %d",fire[nr].dmg);
     sprintf(range,"Range: %d",fire[nr].range);
     sprintf(speed,"Speed: %.f/s",fire[nr].speed);
     sprintf(sell,"Sell: %d",fire[nr].sell);
     outtextxy(xt+0.7*u,yt,"Fire");
	 outtextxy(xt+0.7*u+textwidth("Fire "),yt,lvl);
     xt=14*u-u/2-10,yt=7*u+u/2;
     outtextxy(xt,yt+20,cost);
     outtextxy(xt,yt+35,dmg);
     outtextxy(xt,yt+50,range);
     outtextxy(xt,yt+65,speed);
     outtextxy(xt,yt+80,up);
     outtextxy(xt,yt+95,sell);
	 if(nr!=1000)
	 {
		 if(fire[nr].lvl<fire[nr].maxlvl)
			buton[6].create(6,xt,yt+118,15*u,maxy-63,"Upgrade [F]");
		 buton[7].create(7,xt+1.8*u,yt+118,15*u+1.7*u,maxy-63,"Sell [F]");
		 buton[6].itower=nr;
		 buton[7].itower=nr;
	 }
}



void WatterTower::draw(int nr,int x,int y)
{
	WatterTower();
	watter[nr].x=x;
	watter[nr].y=y;
	watter[nr].nr=nr;
	money.nr-=watter[nr].cost;
    money.update();
	x*=u;
	y*=u;
	x+=8;
	y+=8;
	u-=16;
	int r=u/2;
	setfillstyle(1,LIGHTBLUE);
	bar(x,y,x+u,y+u);
	setcolor(0);
	line(x+r,y,x+r,y+u);
	line(x,y+r,x+u,y+r);
	line(x,y,x+u,y+u);
	x-=8;
	y-=8;
	u+=16;
}



void WatterTower::del(int nr)
{
	setfillstyle(1,BLUE);
	bar(watter[nr].x,watter[nr].y,watter[nr].x+u,watter[nr].y+u);
	money.nr+=watter[nr].sell;
	money.update();
}



void WatterTower::upgrade(int nr)
{
	if(money.nr>=watter[nr].up)
	{
		money.nr-=watter[nr].up;

		if(watter[nr].lvl==1)
		{
			watter[nr].dmg=30;
			watter[nr].range=2;
			watter[nr].speed=4;
			watter[nr].cost=0;
			watter[nr].up=25;
			watter[nr].sell=56;
			watter[nr].lvl=2;
		}

		else
			if(watter[nr].lvl==2)
			{
				watter[nr].dmg=35;
				watter[nr].range=3;
				watter[nr].speed=5;
				watter[nr].cost=0;
				watter[nr].up=25;
				watter[nr].sell=75;
				watter[nr].lvl=3;
				watter[nr].nextattacktime=200;
			}

			else
				if(watter[nr].lvl==3)
				{
					watter[nr].dmg=50;
					watter[nr].range=3;
					watter[nr].speed=6;
					watter[nr].cost=0;
					watter[nr].up=0;
					watter[nr].sell=93;
					watter[nr].lvl=4;
					watter[nr].nextattacktime=167;
				}
	money.update();
	}
}



void WatterTower::info(int nr)
{
     bar(13*u+5,7*u+5,17*u-5,maxy-50-5);
     int xt=14*u-u/2,yt=7*u+u/4;
     char dmg[3],range[3],speed[3],cost[3]="-",up[3]="-",sell[3],lvl[3];
	 setcolor(LIGHTGREEN);
     sprintf(cost,"Cost: %d",watter[nr].cost);
     sprintf(up,"Upgrade: %d",watter[nr].up);
     sprintf(lvl,"[%d]",watter[nr].lvl);
     sprintf(dmg,"Dmg: %d",watter[nr].dmg);
     sprintf(range,"Range: %d",watter[nr].range);
     sprintf(speed,"Speed: %.f/s",watter[nr].speed);
     sprintf(sell,"Sell: %d",watter[nr].sell);
     outtextxy(xt+0.7*u,yt,"Watter");
	 outtextxy(xt+0.7*u+textwidth("Watter "),yt,lvl);
     xt=14*u-u/2-10,yt=7*u+u/2;
     outtextxy(xt,yt+20,cost);
     outtextxy(xt,yt+35,dmg);
     outtextxy(xt,yt+50,range);
     outtextxy(xt,yt+65,speed);
     outtextxy(xt,yt+80,up);
     outtextxy(xt,yt+95,sell);
	 if(nr!=1000)
	 {
		if(watter[nr].lvl<watter[nr].maxlvl)
			buton[6].create(6,xt,yt+118,15*u,maxy-63,"Upgrade [W]");
		 buton[7].create(7,xt+1.8*u,yt+118,15*u+1.7*u,maxy-63,"Sell [W]");
		 buton[6].itower=nr;
		 buton[7].itower=nr;
	 }
}



void EarthTower::draw(int nr,int x,int y)
{
	EarthTower();
	earth[nr].x=x;
	earth[nr].y=y;
	earth[nr].nr=nr;
	money.nr-=earth[nr].cost;
    money.update();
	x*=u;
	y*=u;
	x+=8;
	y+=8;
	u-=16;
	int r=u/2;
	setfillstyle(1,BROWN);
	bar(x,y,x+u,y+u);
	setcolor(0);
	line(x+r,y,x+r,y+u);
	line(x,y+r,x+u,y+r);
	line(x,y,x+u,y+u);
	x-=8;
	y-=8;
	u+=16;
}



void EarthTower::del(int nr)
{
	setfillstyle(1,BLUE);
	bar(earth[nr].x,earth[nr].y,earth[nr].x+u,earth[nr].y+u);
	money.nr+=earth[nr].sell;
	money.update();
}



void EarthTower::upgrade(int nr)
{
	if(money.nr>=earth[nr].up)
	{
		money.nr-=earth[nr].up;

		if(earth[nr].lvl==1)
		{
			earth[nr].dmg=288;
			earth[nr].range=4;
			earth[nr].speed=0.5;
			earth[nr].cost=0;
			earth[nr].up=100;
			earth[nr].sell=93;
			earth[nr].lvl=2;
			earth[nr].nextattacktime=2000;
		}

		else
			if(earth[nr].lvl==2)
			{
				earth[nr].dmg=576;
				earth[nr].range=4;
				earth[nr].speed=0.5;
				earth[nr].cost=0;
				earth[nr].up=150;
				earth[nr].sell=168;
				earth[nr].lvl=3;
			}

			else
				if(earth[nr].lvl==3)
				{
					earth[nr].dmg=1152;
					earth[nr].range=4;
					earth[nr].speed=0.5;
					earth[nr].cost=0;
					earth[nr].up=0;
					earth[nr].sell=281;
					earth[nr].lvl=4;
				}
	money.update();
	}
}



void EarthTower::info(int nr)
{
     bar(13*u+5,7*u+5,17*u-5,maxy-50-5);
     int xt=14*u-u/2,yt=7*u+u/4;
     char dmg[3],range[3],speed[3],cost[3]="-",up[3]="-",sell[3],lvl[3];
	 setcolor(LIGHTGREEN);
     sprintf(cost,"Cost: %d",earth[nr].cost);
     sprintf(up,"Upgrade: %d",earth[nr].up);
     sprintf(lvl,"[%d]",earth[nr].lvl);
     sprintf(dmg,"Dmg: %d",earth[nr].dmg);
     sprintf(range,"Range: %d",earth[nr].range);
     sprintf(speed,"Speed: %.1f/s",earth[nr].speed);
     sprintf(sell,"Sell: %d",earth[nr].sell);
     outtextxy(xt+0.7*u,yt,"Earth");
	 outtextxy(xt+0.7*u+textwidth("Earth "),yt,lvl);
     xt=14*u-u/2-10,yt=7*u+u/2;
     outtextxy(xt,yt+20,cost);
     outtextxy(xt,yt+35,dmg);
     outtextxy(xt,yt+50,range);
     outtextxy(xt,yt+65,speed);
     outtextxy(xt,yt+80,up);
     outtextxy(xt,yt+95,sell);
	 if(nr!=1000)
	 {
		if(earth[nr].lvl<earth[nr].maxlvl)
			buton[6].create(6,xt,yt+118,15*u,maxy-63,"Upgrade [E]");
		 buton[7].create(7,xt+1.8*u,yt+118,15*u+1.7*u,maxy-63,"Sell [E]");
		 buton[6].itower=nr;
		 buton[7].itower=nr;
	 }
}



void BossTower::draw(int nr,int x,int y)
{
	BossTower();
	boss[nr].x=x;
	boss[nr].y=y;
	boss[nr].nr=nr;
	money.nr-=boss[nr].cost;
    money.update();
	x*=u;
	y*=u;
	x+=8;
	y+=8;
	u-=16;
	int r=u/2,r2=r/2;
	setfillstyle(0,0);
	bar(x,y,x+u,y+u);
	setcolor(LIGHTGREEN);
	circle(x+r,y+r,r);
	for(int i=x;i<=x+u;i++)
		for(int j=y;j<=y+u;j++)
		{
			int dx=x+r-i;
			int dy=y+r-j;
			if(dx*dx+dy*dy<=r*r)
				putpixel(i,j,LIGHTGREEN);
		}
	setcolor(0);
	circle(x+r,y+r,r2);
	for(int i=x;i<x+u;i++)
		for(int j=y;j<y+u;j++)
		{
			int dx=x+r-i;
			int dy=y+r-j;
			if(dx*dx+dy*dy<=r2*r2)
				putpixel(i,j,YELLOW);
		}
	line(x+r,y,x+r,y+u);
	line(x,y+r,x+u,y+r);
	x-=8;
	y-=8;
	u+=16;
}



void BossTower::del(int nr)
{
	setfillstyle(1,BLUE);
	bar(boss[nr].x,boss[nr].y,boss[nr].x+u,boss[nr].y+u);
	money.nr+=boss[nr].sell;
	money.update();
}



void BossTower::upgrade(int nr)
{
	if(boss[nr].lvl==1&&money.nr>=boss[nr].up)
	{
		money.nr-=boss[nr].up;
		boss[nr].dmg=2000;
		boss[nr].range=7;
		boss[nr].speed=2;
		boss[nr].cost=0;
		boss[nr].up=0;
		boss[nr].sell=292;
		boss[nr].lvl=2;
		boss[nr].nextattacktime=250;
		money.update();
	}
}



void BossTower::info(int nr)
{
     bar(13*u+5,7*u+5,17*u-5,maxy-50-5);
     int xt=14*u-u/2,yt=7*u+u/4;
     char dmg[3],range[3],speed[3],cost[3]="-",up[3]="-",sell[3],lvl[3];
	 setcolor(LIGHTGREEN);
     sprintf(cost,"Cost: %d",boss[nr].cost);
     sprintf(up,"Upgrade: %d",boss[nr].up);
     sprintf(lvl,"[%d]",boss[nr].lvl);
     sprintf(dmg,"Dmg: %d",boss[nr].dmg);
     sprintf(range,"Range: %d",boss[nr].range);
     sprintf(speed,"Speed: %.1f/s",boss[nr].speed);
     sprintf(sell,"Sell: %d",boss[nr].sell);
     outtextxy(xt+0.7*u,yt,"Boss");
	 outtextxy(xt+0.7*u+textwidth("Boss "),yt,lvl);
     xt=14*u-u/2-10,yt=7*u+u/2;
     outtextxy(xt,yt+20,cost);
     outtextxy(xt,yt+35,dmg);
     outtextxy(xt,yt+50,range);
     outtextxy(xt,yt+65,speed);
     outtextxy(xt,yt+80,up);
     outtextxy(xt,yt+95,sell);
	 if(nr!=1000)
	 {
		 if(boss[nr].lvl<boss[nr].maxlvl)
			buton[6].create(6,xt,yt+118,15*u,maxy-63,"Upgrade [B]");
		 buton[7].create(7,xt+1.8*u,yt+118,15*u+1.7*u,maxy-63,"Sell [B]");
		 buton[6].itower=nr;
		 buton[7].itower=nr;
	 }
}



void _zid(int y,int x)
{
	/*
    setfillstyle(SOLID_FILL,BLUE);
    bar(x*u,y*u,x*u+PU,y*u+PU);
	*/
	int color;
	for(int i=x*u;i<=x*u+PU;i++)
		for(int j=y*u;j<=y*u+PU;j++,color=rand()%100)
		{
			if(color<60)
				color=BLACK;
			else
				color=BLUE;

			putpixel(i,j,color);
		}
}



void ReadLabirint()
{
     int i,j;
	ifstream f("map.txt");
	f>>n>>m;
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
		{
			f>>l[i][j];
			if(l[i][j]=='x')
				_zid(i,j);
		}

	f.close();
}



void DisplayGame()
{
	initwindow(maxx,maxy,"Power TD Game",(getmaxwidth()-maxx)/2,(getmaxheight()-maxy)/2);
	setviewport(10,10,maxx-10,maxy-10,1);
	ReadLabirint();
	money.draw(m*u+u,p);
		for(int i=money.x;i<=money.x+2*p;i++)
		for(int j=money.y;j<=money.y+2*p;j++)
		{
			int dx=money.x+p-i;
			int dy=money.y+p-j;
			if(dx*dx+dy*dy<=p*p)
				putpixel(i,j,YELLOW);
		}
	wood.draw(m*u+2.3*u,p);
	heal.nr=25;
	heal.draw(m*u+3.3*u,p);
	level.draw(maxx-5*u,maxy-40);
	leveltime.draw(maxx-3*u-u/4,maxy-40);
	buton[0].create(0,13*u,  u,17*u,2*u-10,"Cannon tower");
	buton[1].create(1,13*u,2*u,17*u,3*u-10,"Arrow tower");
	buton[2].create(2,13*u,3*u,17*u,4*u-10,"Watter essence");
	buton[3].create(3,13*u,4*u,17*u,5*u-10,"Earth essence");
	buton[4].create(4,13*u,5*u,17*u,6*u-10,"Fire essence");
	buton[5].create(5,13*u,6*u,17*u,7*u-10,"Boss tower");
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar(13*u,7*u,17*u,maxy-50);
	setfillstyle(0,BLACK);
	bar(13*u+5,7*u+5,17*u-5,maxy-50-5);
	setlinestyle(SOLID_LINE,0,3);
	setcolor(LIGHTGREEN);
	rectangle(13*u,7*u,17*u,maxy-50);
	
}



void VerifMouseClick()
{
     long a=0;
	do{getmouseclick(WM_LBUTTONDOWN,x,y);}while(++a<510000&&x==-1);
	if(buton[0].click(0))//cannon
		action=C;

	else
	if(buton[1].click(1))//arrow
		action=A;

	else
	if(buton[2].click(2))//watter
	{
		if(wood.nr>=1&&!strcmp(buton[2].text,"Watter essence"))
		{
			wood.nr--;
			wood.update();
			buton[2].create(2,13*u,3*u,17*u,4*u-10,"Watter tower");
			watter[1000].info(1000);
        }
		else
			action=W;
	}
	else	
	if(buton[3].click(3))//earth
	{
		if(wood.nr>=1&&!strcmp(buton[3].text,"Earth essence"))
		{
			wood.nr--;
			wood.update();
			buton[3].create(3,13*u,4*u,17*u,5*u-10,"Earth tower");
			earth[1000].info(1000);
        }
		else
			action=E;
	}
	else
	if(buton[4].click(4))//fire
	{
		if(wood.nr>=1&&!strcmp(buton[4].text,"Fire essence"))
		{
			wood.nr--;
			wood.update();
			buton[4].create(4,13*u,5*u,17*u,6*u-10,"Fire tower");
			fire[1000].info(1000);
        }
		else
			action=F;
	}
	else
	if(buton[5].click(5))//boss
	{
		if(strcmp(buton[2].text,"Watter essence")&&strcmp(buton[3].text,"Earth essence")&&strcmp(buton[4].text,"Fire essence"))
			action=B;
	}
	else
	if(buton[6].click(6))//upgrade
	{
		int i=buton[6].itower;
		if(strchr(buton[6].text,'C'))
		{
			cannon[i].upgrade(i);
			cannon[i].info(i);
		}
		if(strchr(buton[6].text,'A'))
		{
			arrow[i].upgrade(i);
			arrow[i].info(i);
		}
		if(strchr(buton[6].text,'W'))
		{
			watter[i].upgrade(i);
			watter[i].info(i);
		}
		if(strchr(buton[6].text,'F'))
		{
			fire[i].upgrade(i);
			fire[i].info(i);
		}
		if(strchr(buton[6].text,'E'))
		{
			earth[i].upgrade(i);
			earth[i].info(i);
		}
		if(strchr(buton[6].text,'B'))
		{
			boss[i].upgrade(i);
			boss[i].info(i);
		}
	}
//sell
	else
	{
		x/=u;
		y/=u;
		if((x>0||y>0)&&l[y][x]=='x')
		{
			if(action)
			{
			l[y][x]=action;
				switch(action)
				{
				case C:
					if(money.nr>=cannon[ncannon+1].cost)
						cannon[++ncannon].draw(ncannon,x,y);
					action=0;
					break;
				case A:
					if(money.nr>=arrow[narrow+1].cost)
						arrow[++narrow].draw(narrow,x,y);
					action=0;
					break;
				case W:
					if(money.nr>=watter[nwatter+1].cost)
						watter[++nwatter].draw(nwatter,x,y);
					action=0;
					break;
				case E:
					if(money.nr>=earth[nearth+1].cost)
						earth[++nearth].draw(nearth,x,y);
					action=0;
					break;
				case F:
					if(money.nr>=fire[nfire+1].cost)
						fire[++nfire].draw(nfire,x,y);
					action=0;
					break;
				case B:
					if(money.nr>=boss[nboss].cost)
						boss[++nboss].draw(nboss,x,y);
					action=0;
					break;
				}
			}
		}
			else
			{
				int i,ok=1;
				switch(l[y][x])
				{
				case C:
					for(i=1;i<=ncannon&&ok;i++)
						if(cannon[i].x==x&&cannon[i].y==y)
							ok=0;
						cannon[i].info(i);
					break;
				case A:
					for(i=1;i<=narrow&&ok;i++)
						if(arrow[i].x==x&&arrow[i].y==y)
							ok=0;
						arrow[i].info(i);
					break;
				case W:
					for(i=1;i<=nwatter&&ok;i++)
						if(watter[i].x==x&&watter[i].y==y)
							ok=0;
						watter[i].info(i);
					break;
				case E:
					for(i=1;i<=nearth&&ok;i++)
						if(earth[i].x==x&&earth[i].y==y)
							ok=0;
						earth[i].info(i);
					break;
				case F:
					for(i=1;i<=nfire&&ok;i++)
						if(fire[i].x==x&&fire[i].y==y)
							ok=0;
						fire[i].info(i);
					break;
				case B:
					for(i=1;i<=nboss&&ok;i++)
						if(boss[i].x==x&&boss[i].y==y)
							ok=0;
						boss[i].info(i);
					break;
				}
			}
	}// click in blue area
}



void VerifMousePointer()
{
getmouseclick(WM_LBUTTONDOWN,x,y);
setcolor(LIGHTGREEN);
	if(buton[0].pointer(0)&&lastbutton)
	{
		cannon[1000].info(1000);
		lastbutton=0;
	}
	else
	if(buton[1].pointer(1)&&lastbutton!=1)
	{
		arrow[1000].info(1000);
		lastbutton=1;
	}
	else
	if(buton[2].pointer(2)&&lastbutton!=2)
	{
		setfillstyle(0,BLACK);
		bar(13*u+5,7*u+5,17*u-5,maxy-50-5);
		if(!strcmp(buton[2].text,"Watter essence"))
		{
			outtextxy(14*u-u/2,7*u+u/4,"Watter essence");
			int xt=14*u-u/2,yt=7*u+u/1.6;
			outtextxy(xt,yt,"cost: 1 wood");
        }
		else
			watter[1000].info(1000);
		lastbutton=2;
	}
	else	
	if(buton[3].pointer(3)&&lastbutton!=3)
	{
        bar(13*u+5,7*u+5,17*u-5,maxy-50-5);
		if(!strcmp(buton[3].text,"Earth essence"))
		{
			outtextxy(14*u-u/2,7*u+u/4,"Earth essence");
			int xt=14*u-u/2,yt=7*u+u/1.6;
			outtextxy(xt,yt,"cost: 1 wood");
		}
		else
			earth[1000].info(1000);
		lastbutton=3;
	}
	else
	if(buton[4].pointer(4)&&lastbutton!=4)
	{
        bar(13*u+5,7*u+5,17*u-5,maxy-50-5);
		if(!strcmp(buton[4].text,"Fire essence"))
		{
			outtextxy(14*u-u/2,7*u+u/4,"Fire essence");
			int xt=14*u-u/2,yt=7*u+u/1.6;
			outtextxy(xt,yt,"cost: 1 wood");
		}
		else
			fire[1000].info(1000);
		lastbutton=4;
	}
	else
	if(buton[5].pointer(5)&&lastbutton!=5)
	{
        bar(13*u+5,7*u+5,17*u-5,maxy-50-5);
		if(!strcmp(buton[2].text,"Watter essence")||!strcmp(buton[3].text,"Earth essence")||!strcmp(buton[4].text,"Fire essence"))
		{
		outtextxy(14*u-u/2,7*u+u/4,"Boss tower");
		int xt=14*u-u/2,yt=7*u+u/1.6;
		outtextxy(xt,yt,"cost: All the essences");
		}
		else
			boss[1000].info(1000);
		lastbutton=5;
	}
}



void UpdatePc()
{
		for(int i=1;i<=ninamic;i++)
		{
			if(pc[i].viata<=0&&pc[i].stare)
			{
				pc[i].stare=0;
				pc[i].del(i);
				money.nr+=gold[level.nr];
				money.update();
			}
			if(pc[i].stare)
				pc[i].update(i);
			if(pc[i].x==6*PU&&!pc[i].y&&pc[i].stare)
			{
				pc[i].del(i);
				pc[i].x=4*PU;
				heal.update();
			}
        }
       	if(clock()-ContorNext>=395&&ninamic<20)
		{
			ninamic++;
			ContorNext=clock();
        }
}



void VerifAtack()
{
	int i,j,dx,dy,r,ntinte,ok;
	int CurrentTime=clock();
	for(i=1;i<=ncannon;i++,ntinte=2)//cannon
		if(CurrentTime-cannon[i].lastattacktime>=cannon[i].nextattacktime)
		{
			cannon[i].lastattacktime=CurrentTime;
		for(j=1;j<=ninamic&&ntinte;j++)
			if((cannon[i].x||cannon[i].y)&&pc[j].stare)
			{
				int xt=cannon[i].x*u+u/2;
				int yt=cannon[i].y*u+u/2;
				int xp=pc[j].x+u/2;
				int yp=pc[j].y+u/2;
				dx=xt-xp;
				dy=yt-yp;
				r=cannon[i].range*u;
				if(dx*dx+dy*dy<=r*r)
				{
					pc[j].viata-=cannon[i].dmg;
					ntinte--;
				}
		    }
		}
	for(i=1;i<=narrow;i++,ok=1)//arrow
		if(CurrentTime-arrow[i].lastattacktime>=arrow[i].nextattacktime)
		{
			arrow[i].lastattacktime=CurrentTime;
		for(j=1;j<=ninamic&&ok;j++)
			if((arrow[i].x||arrow[i].y)&&pc[j].stare)
			{
				int xt=arrow[i].x*u+u/2;
				int yt=arrow[i].y*u+u/2;
				int xp=pc[j].x+u/2;
				int yp=pc[j].y+u/2;
				dx=xt-xp;
				dy=yt-yp;
				r=arrow[i].range*u;
				if(dx*dx+dy*dy<=r*r)
				{
					pc[j].viata-=arrow[i].dmg;
					ok=0;
				}
	        }
		}
	for(i=1;i<=nwatter;i++,ntinte=3)//watter
		if(CurrentTime-watter[i].lastattacktime>=watter[i].nextattacktime)
		{
			watter[i].lastattacktime=CurrentTime;
		for(j=1;j<=ninamic&&ntinte;j++)
			if((watter[i].x||watter[i].y)&&&pc[j].stare)
			{
				int xt=watter[i].x*u+u/2;
				int yt=watter[i].y*u+u/2;
				int xp=pc[j].x+u/2;
				int yp=pc[j].y+u/2;
				dx=xt-xp;
				dy=yt-yp;
				r=watter[i].range*u;
				if(dx*dx+dy*dy<=r*r)
				{
					pc[j].viata-=watter[i].dmg;
					ntinte--;
				}
			}
		}
	for(i=1;i<=nearth;i++,ok=1)//earth
		if(CurrentTime-earth[i].lastattacktime>=earth[i].nextattacktime)
		{
			earth[i].lastattacktime=CurrentTime;
		for(j=1;j<=ninamic&&ok;j++)
			if((earth[i].x||earth[i].y)&&pc[j].stare)
			{
				int xt=earth[i].x*u+u/2;
				int yt=earth[i].y*u+u/2;
				int xp=pc[j].x+u/2;
				int yp=pc[j].y+u/2;
				dx=xt-xp;
				dy=yt-yp;
				r=earth[i].range*u;
				if(dx*dx+dy*dy<=r*r)
				{
					pc[j].viata-=earth[i].dmg;
					ok=0;
				}
		    }
		}
	for(i=1;i<=nfire;i++,ntinte=2)//fire
		if(CurrentTime-fire[i].lastattacktime>=fire[i].nextattacktime)
		{
			fire[i].lastattacktime=CurrentTime;
		for(j=1;j<=ninamic&&ntinte;j++)
			if((fire[i].x||fire[i].y)&&pc[j].stare)
			{
				int xt=fire[i].x*u+u/2;
				int yt=fire[i].y*u+u/2;
				int xp=pc[j].x+u/2;
				int yp=pc[j].y+u/2;
				dx=xt-xp;
				dy=yt-yp;
				r=fire[i].range*u;
				if(dx*dx+dy*dy<=r*r)
				{
					pc[j].viata-=fire[i].dmg;
					ntinte--;
				}
			}
		}
	for(i=1;i<=nboss;i++,ok=1)//boss
		if(CurrentTime-boss[i].lastattacktime>=boss[i].nextattacktime)
		{
			boss[i].lastattacktime=CurrentTime;
		for(j=1;j<=ninamic&&ok;j++)
			if((boss[i].x||boss[i].y)&&pc[j].stare)
			{
				int xt=boss[i].x*u+u/2;
				int yt=boss[i].y*u+u/2;
				int xp=pc[j].x+u/2;
				int yp=pc[j].y+u/2;
				dx=xt-xp;
				dy=yt-yp;
				r=boss[i].range*u;
				if(dx*dx+dy*dy<=r*r)
				{
					pc[j].viata-=boss[i].dmg;
					ok=0;
				}
		    }
		}
}



void VerifNextLevel()
{
	int i;
	for(i=1;i<=ninamic&&!pc[i].stare;i++);
	if(i>20)
	{
		int start=clock()+3200;
		do
		{
			VerifMousePointer();
			VerifMouseClick();
			leveltime.time=start-clock();
			leveltime.update();
		}while(leveltime.time>0);
		level.update();
		ninamic=1;
		ContorNext=clock();
		for(i=1;i<=20;i++)
		{
		pc[i].stare=1;
		pc[i].directie=3;
		pc[i].x=4*PU;
		pc[i].y=0;
		pc[i].viata=pc[i].maxviata=viatalvl[level.nr];
        }
		if(level.nr==8||level.nr==15||level.nr==18)
		{
			wood.nr++;
			wood.update();
		}
	}
}



void PlayTheGame()
{
    DisplayGame();
   	ContorNext=clock();
   	
// asteapta 10 secunde la inceput de lvl 1. timp in care poti doar construi sau da up.
        int start=clock()+10000;
   		do
		{
			VerifMousePointer();
			VerifMouseClick();
			leveltime.time=start-clock();
			leveltime.update();
		}while(leveltime.time>0);
		

	for(level.nr=1;level.nr<=30&&heal.nr>=0;)
	{
       if(clock()-timestart>1)
       {
        UpdatePc();
        timestart=clock();
       }
        VerifMousePointer();
		VerifMouseClick();
		VerifAtack();
		VerifNextLevel();
		
		//delay(10);
	}
	
	if(heal.nr<0)
		initwindow(280,80,"You lost",getmaxwidth()/2-140,getmaxheight()/2-40);
	else
		initwindow(280,80,"You win",getmaxwidth()/2-140,getmaxheight()/2-40);

		buton[0].create(0,10,10,125,60,"Restart");
		buton[1].create(1,135,10,270,60,"Inchide");
		
		do
		{
  			getmouseclick(WM_LBUTTONDOWN,x,y);        
		}while(x==-1&&(!buton[0].click(0)||!buton[1].click(1)));

		if(buton[0].click(0))
		{
			closegraph();
			PlayTheGame();
		}
		closegraph();
		system("exit");

}



void Instructiuni()
{
	x=20;
	y=20;
    initwindow(500,220,"Instructiuni",getmaxwidth()/2-200,getmaxheight()/2-150);
	outtextxy(x+200,y,"Power TD");
	
	outtextxy(x,y+40,"Trebuie sa construiesti tunuri pentru a distruge monstrii ce apar");
	outtextxy(x,y+55,"Dai click pe unul din butoanele din dreapta apoi pe zona albastra");
	outtextxy(x,y+70,"Tunurile tale pot deveni mai bune marindu-le levelul:");
	outtextxy(x,y+85,"Dai click pe tunul din zona albastra apoi in dreapta e butonul \"Upgrade\"");
	outtextxy(x,y+100,"Fiecare tun are niste caracteristici ce apar in zona din dreapta jos !");
	outtextxy(x+400,y+120,"Bafta !");
	outtextxy(x,y+180,"Nita Iulian a X-a 1-4.2.2014");
	
    buton[0].create(0,260,170,420,210,"Incepe jocul");
	buton[1].create(1,430,170,490,210,"Iesi");
	do
	{
		getmouseclick(WM_LBUTTONDOWN,x,y);
	}while(x==-1&&(!buton[0].click(0)||!buton[1].click(1)));
	
	if(buton[0].click(0))
	{
		closegraph();
        PlayTheGame();
	}
}



int main()
{
    initwindow(280,180,"Power TD",getmaxwidth()/2-140,getmaxheight()/2-90);
    buton[0].create(0,10,10,270,50,"Incepe jocul");
	buton[1].create(1,10,60,270,100,"Instructiuni");
	buton[2].create(2,10,110,270,160,"Inchide jocul");

	do
	{
		getmouseclick(WM_LBUTTONDOWN,x,y);
	}while(x==-1);

	closegraph();
    if(buton[0].click(0))
		PlayTheGame();

	if(buton[1].click(1))
		Instructiuni();
}
