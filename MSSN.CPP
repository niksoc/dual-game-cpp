#include<iostream.h>
#include<graphics.h>
#include<dos.h>
#include<conio.h>
#include<stdlib.h>
#include<bios.h>
#include<time.h>
#define SCREEN_W 640
#define SCREEN_H 480
#define GM_SPEED 5
#define LEFT 0x4B00
#define UP 0x4800
#define we rock
#define RIGHT 0x4D00
#define DOWN 0x5000
#define SPACE 14624
#define ENTER 7181
#define GM_RADIUS 9
int bk_col,key, ch,o;
int n_pl,n_lddr,n_mpl,n_bpl,n_sp;
int complete,lvl;
int inv(int a)
{
    if(a) return 0;
	else return 7;
}
class door
{ int x, y, col, k;
public:
    int getx() {return x;}
	int gety() {return y;}
void init_door(int x1,int y1,int c)
	{
	    x=x1;
	    y=y1;
	    col=c;
	    k=0;
	}

void draw()
{       setcolor(col);
	setfillstyle(1,col);
	bar(x,y,x+30,y+40);
	pieslice(x+15,y,0,180,15);
}
void erase()
{       setcolor(col);
	setfillstyle(1,bk_col);
	bar(x,y,x+30,y+40);
	pieslice(x+15,y,0,180,15);
}
void setk()
{
    k=1;
}
void open()
{
    if(!k) return;
    setfillstyle(1,inv(col));
	for(int i=0;i<12;i++)
	{       pieslice(x+15,y,0,180,15);
		bar(x,y,x+1,y+40);bar(x+29,y,x+30,y+40);
		bar(x-i+15,y-5,x+15+i,y+40);
		delay(100);
	}
	complete++;
}
}_door;
class man
{
 public:int x,y;
	int b,l;
	int xspeed,yspeed;
	int leg1,leg2;
	int ls;
	int jump_state;
	int prev_ysp;
	int mf;
	int lad,alad,ld;
	int sp;
 public:void init_man()
	{
	    x=50;
	    y=300;
	    b=15;
	    l=30;
	    ls=4;
	    leg1=ls/2+1;
	    leg2=b/2+ls/2+1;
	    alad=0;
	    sp=0;
	    mf=0;
	}
	void m_p(int xi, int yi, int type1,int dir, int range )
	{

		if(type1==0)
			{
			    if(abs(xi-x)==range) dir=-dir;
		    else if(xi==x)dir=-dir;
		x+=dir;
			}
			else
			{
				if(abs(yi-y)==range) dir=-dir;
				else if(yi==y)dir=-dir;
				y+=dir;
			}

	}
	int getx() {return x;}
	int gety() {return y;}
	int getxsp() {return xspeed;}
	int getprevysp() {return prev_ysp;}
	int getl() {return l;}
	void set(int x1, int y1, int xsp, int ysp, int spring, int jump, int m)
	{
	    if(x1!=-1) x=x1;
	    if(y1!=-1) y=y1;
	    if(xsp!=-1) xspeed=xsp;
	    if(ysp!=-1) yspeed=ysp;
	    if(spring!=-1) sp=spring;
	    if(jump!=-1) jump_state=jump;
	    if(m!=-1) mf=m;
	}
	int coll_r(int a=0)
	{
	    int n=0;
	    for(int i=0;i<=l;i++)
		if(getpixel(x+b+1,y+i)==inv(bk_col))
		   n++;
	    if(x+b>SCREEN_W) return 100;
	    return n;
	}
	int coll_l(int a=0)
	{
	    int n=0;
	    for(int i=0;i<=l;i++)
		if(getpixel(x-1,y+i)==inv(bk_col))
		    n++;
	    if(x<0) return 100;
	    return n;
	}
	int coll_u()
	{
	    for(int i=0;i<=b;i++)
		if(getpixel(x+i,y-1)==inv(bk_col) || x<0)
		    return 1;
	    return 0;
	}
	int coll_d(int k=0)
	{
	    for(int i=0;i<=b;i++)
		if(getpixel(x+i,y+l+1+k)==inv(bk_col))
		    return 1;
	    return 0;
	}
	void draw()
	{
	    setfillstyle(1,inv(bk_col));
	    setcolor(inv(bk_col));
	    bar(x,y,x+b,y+l-ls);
	    if(leg1>=ls/2 && leg1<=b-ls) bar(x+leg1,y+l-ls,x+leg1+ls/2,y+l);
	    if(leg2>=ls/2 && leg2<=b-ls) bar(x+leg2,y+l-ls,x+leg2+ls/2,y+l);
	}
	void erase()
	{
	    setfillstyle(1,bk_col);
	    setcolor(bk_col);
	    bar(x,y,x+b,y+l);
	}
	void in_air()
	{   o=0;
	    if(!alad) yspeed+=5;
	    sp=0;
	}
	void jump(int t=-30)
	{
	    if(o==1)yspeed=t * ((sp!=0)?(sp/20.0):1);
	    yspeed+=5;
	    if(yspeed<=0) jump_state=0;
	sp=0; o++;
    }
	void update_pos()
	{
	    if(x<0) x=0;
	    int i, flag, temp;
	    lad=0;
	    temp=key;
	    lad=0;
		if((coll_r()<8 && coll_r()) || (coll_l()<8 && coll_l())) lad=1;
	   else alad=0;
	    if(bioskey(1)!=0) key=bioskey(0);
	    if(key==ENTER) ch=1;
	    if(key!=UP && key!=DOWN && key!=RIGHT && key!=LEFT && key!=283 && key!=SPACE) key=temp;
	switch(key)
	{
	    case  LEFT :xspeed=-GM_SPEED;
		    break;
	    case  RIGHT:xspeed=GM_SPEED;
		    break;
	    case  UP   :if(_door.getx()+15>x && _door.getx()<x+b && _door.gety()+15>y && _door.gety()<y+l) _door.open();
		    xspeed=0;
		    if(lad==1)
		    {
			ld=-1;
		    }
			break;
	    case  DOWN :xspeed=0;
		    if(alad || (coll_d() && coll_d(1) && coll_d(2) && !coll_d(3))) ld=1;
		    break;
	    case SPACE :if(temp!=DOWN) key=temp; else xspeed=key=0;
		    if(!jump_state && (coll_d() || alad || mf))
		    {
		jump_state=1;o=1;
		yspeed=mf=0;
		    }
    }
	    if(jump_state) jump();
	    else if(!coll_d() || coll_d() && (!coll_d(1) || !coll_d(2) || !coll_d(3))) in_air();
		else yspeed=0;
	    for(i=0;i<abs(xspeed);i++)
	    {
	    if(xspeed>0)
	    {
		lad=0;
		if((coll_r()<8 && coll_r()) || (coll_l()<8 && coll_l())) lad=1;
		if(!coll_r() || lad)
		{
		    x++;
		}
		else
		{
		    xspeed=yspeed=jump_state=key=0;
		}
	    }
	    else
	    {
		lad=0;
		if((coll_r()<8 && coll_r()) || (coll_l()<8 && coll_l())) lad=1;
		if(!coll_l() || lad) x--;
		else
		{
		    xspeed=yspeed=jump_state=key=0;
		}
	    }
	}
	    for(int f=1, k=0;f!=0 && !lad;)
	    {
	    if(coll_l() && coll_r() || y+l>360)
			{
		y--;
				k=1;
			}
			else f=0;
	    }
	    if(k){draw_map();}
	    if(ld)
	{
	    yspeed=0;
	    alad=1;
	    if(ld==-1) y-=3;
		else {y+=3;}
	    ld=0;
	}
	    prev_ysp=yspeed;
	    for(i=0;i<abs(yspeed);i++)
	    {
	     if(jump_state || (yspeed)<0)
	    {
		lad=0;
		if((coll_r()<8 && coll_r()) || (coll_l()<8 && coll_l())) lad=1;
		if(!coll_u() || lad) y--;
		else
		{
		    yspeed=jump_state=0;
		}
	    }
	    else
	    {
	    lad=0;
	    if((coll_r()<8 && coll_r()) || (coll_l()<8 && coll_l())) lad=1;
	    if(!coll_d() || lad) y++;
	    else
		{
		    yspeed=jump_state=0;
		}
	    }
	    }
	    if(coll_d())
	    {

	    if(xspeed!=0)
	    {
	    if(leg1==b && abs(xspeed)/xspeed<0) leg1=-1;
	    if(leg1==0 && abs(xspeed)/xspeed>0) leg1=b+1;
	    if(leg2==b && abs(xspeed)/xspeed<0) leg2=-1;
	    if(leg2==0 && abs(xspeed)/xspeed>0) leg2=b+1;
	    leg1-=abs(xspeed)/xspeed;
	    leg2-=abs(xspeed)/xspeed;
	    }
	    if(xspeed==0)
		    {
			leg1=ls/2+1;
			leg2=b/2+ls/2+1;
		    }
	    }
	    else {
		    if(xspeed==0)
		    {
			leg1=ls/2+1;
			leg2=b/2+ls/2+1;
		    }
			else if(xspeed>0)
			    {
				leg1=ls/2;
				leg2=b/2+ls/2;
			    }
				else
				{
				    leg1=ls;
				    leg2=b/2+ls;
				}
		 }
	}
}m;
class doorkey
{
    int x,y,col,r,k;
    public:void init_doorkey(int x1,int y1,int c)
	    {
		x=x1;
		y=y1;
		col=c;
		r=5;
		k=0;
	    }
	   void draw()
	   {
		if(k)return;
		setcolor(col);
		for(int i=0;i<r;i+=2)
		{
		  circle(x,y,i);
		}
	   }
	   void erase()
	   {
	       setcolor(bk_col);
	       setfillstyle(1,bk_col);
	       bar(x-r,y-r,x+r,y+r);
	   }
	   void check()
	   {
	       if(abs(m.getx()+m.getl()/2-x)<20 && abs(m.gety()-y)<20) {k++;_door.setk();erase();}
	   }
}door_key;
class platform
{
    protected: int b,l,x,y,type,col,rest;
	public:	void init_pl(int x1,int y1,int k, int pl_col,int t=0)
	{
		type=t;
		col=pl_col;
		b=10;
		x=x1;
		y=y1;
		l=k;
		rest=0;
	}
	void draw_pl()
	{
	    if(type==1)
	    {
		if(rest==20)
		{
		  col=inv(col);
		  rest=0;
		}
	    }
		rest++;
			if(type==2)
		{     	setfillstyle(1,col);
			setcolor(col);
			bar(x,y,x+b,y+l);
		}
		else if(rest==1 || (type==0 && col==inv(bk_col)))
		{
			setfillstyle(1,col);
			setcolor(col);
			bar(x,y,x+l,y+b);
		}

	}
	void erase_pl()
	{
		 setfillstyle(1,bk_col);
		 setcolor(bk_col);
		 if(type==2)
		 bar(x,y,x+b,y+l);
		 else
		 bar(x,y,x+l,y+b);
	}
}k[20];
class spring
{
    int x,y;
    int a;
    int col;
    int rest;
 public:void init_spring(int x1, int y1, int c)
	{
	    x=x1;
	    y=y1;
	    col=c;
	    a=15;
	    rest=0;
	}
	void draw()
	{
	    setfillstyle(9,inv(col));
	    setcolor(col);
	    bar(x,y,x+a,y+a);
	    setfillstyle(1,bk_col);
	    int t;
	    if(rest>13) t=13; else t=rest;
	    if(coll_u()) {rest++;t=13;}
	bar(x,y,x+a,y+t);
	}
	int coll_u()
	{
	    for(int i=0;i<=a;i++)
	    if(getpixel(x+i,y-1)==inv(bk_col))
		return 1;
	    return 0;
	}
	void check_sp(man &a)
	{
	    if(!rest)
	    {
	    if(coll_u())
	    {
		a.set(-1,-1,-1,-1,a.getprevysp(),1,-1);o=1;
		rest=40;
	    }
	    }
		else rest--;
	}

}sp[5];
class ladder
{
	int b,l,x,y,col,gap;
	public:
	    void init_ladder(int b1,int x1,int y1, int c)
		{
		    col=c;
		    gap=15;
			l=16;
			b=b1;
			x=x1;
			y=y1;
		}
		int check()
		{
		    int n=y+b;
		    for(int y1=y;y1<n;y1=y1+gap+2)
			{
				if(getpixel(x,y1)!=col || getpixel(x+l,y1)!=col) return 1;
			}
			return 0;
		}
	    void draw_ladder()
		{
		    if(bk_col!=col)
		    {
			setfillstyle(1,col);
			setcolor(col);
			int n=y+b;
			for(int y1=y;y1<n;y1=y1+gap+2)
			{
				bar(x,y1,x+l,y1+2);
			}
	    }
    }
}lddr[5];
class moving_pl:public platform
{
	int 	type1, range, xi, yi, dir;
	public: void init_mpl(int x1, int y1, int k, int pl_col, int r, int type, int d)
		{
			type1=type;
			range=r;
			xi=x1;
			yi=y1;
			dir=-d;
			col=pl_col;
			b=10;
			x=x1;
			y=y1;
			l=k;
		}
		void move(man &m)
		{

			if(type1==0)
			{
			    if(abs(xi-x)==range) dir=-dir;
			    else if(xi==x)dir=-dir;
			    x+=dir;
			}
			else
			{
				if(abs(yi-y)==range) dir=-dir;
				else if(yi==y)dir=-dir;
				y+=dir;
			}
			for(int u=0;u<b;u++)
			if(m.gety()+m.getl()==y-1+u && m.getx()<x+l && m.getx()>x)
			m.m_p(xi,yi,type1,dir,range);
			for(u=-5;u<0;u++)
			if(m.gety()+m.getl()==y-1+u && m.getx()<x+l && m.getx()>x)
			m.set(-1,-1,-1,-1,-1,-1,1);

		}
}mpl[5];
void generate_map()
{
	if(lvl==1)
    {
	n_sp=n_pl=n_mpl=n_lddr=0;
	k[0].init_pl(0,300,58,7);
	k[1].init_pl(100,200,350,7);
	k[2].init_pl(400,60,240,7);
	k[3].init_pl(80,250,48,0);
	//mpl[0].init_mpl(100,200,50,7,120,1,5);
	//lddr[0].init_ladder(150,280,200,0);
	n_mpl=0;
	n_sp=1;
	n_lddr=0;
	n_pl=4;
	_door.init_door(550,15,0);
	sp[0].init_spring(500,341,0);
	door_key.init_doorkey(500,320,7);
    }
		if(lvl==0)
    {   n_sp=n_pl=n_mpl=n_lddr=0;
	_door.init_door(550,15,7);
	k[0].init_pl(500,56,140,0);
	k[1].init_pl(60,310,90,0);
	k[2].init_pl(100,270,90,7);
	k[3].init_pl(60,180,90,7);
	k[4].init_pl(180,220,90,0);
	k[5].init_pl(180,120,90,7);
	k[6].init_pl(335,160,90,0);
	k[7].init_pl(400,120,90,7);
	door_key.init_doorkey(500,200,0);
	n_pl=8;
     }
	if(lvl==2)
      {   n_sp=n_pl=n_mpl=n_lddr=0;
	  _door.init_door(300,15,7);
	  k[0].init_pl(250,56,100,0);
	  k[1].init_pl(410,300,40,7);
	  k[2].init_pl(0,175,650,0);
	  k[3].init_pl(130,170,5,0);
	  sp[0].init_spring(430,284,0);
	  door_key.init_doorkey(130,210,7);
	  mpl[0].init_mpl(160,155,50,7,100,1,-5);
	  n_pl=4;
	  n_mpl=1;
	  n_sp=1;

       }
	if(lvl==3)
      {  n_sp=n_pl=n_mpl=n_lddr=0;
	 _door.init_door(30,15,7);
	 mpl[0].init_mpl(100,100,60,7,100,1,5);
	lddr[0].init_ladder(150,455,150,0);
	k[0].init_pl(0,56,140,0);
	k[1].init_pl(480,300,90,7);
	mpl[1].init_mpl(320,140,50,0,145,0,-5);
	sp[0].init_spring(360,341,0);
	door_key.init_doorkey(550,200,0);
	n_pl=2;
	n_mpl=2;
	n_lddr=1;
	n_sp=1;
	}
	if(lvl==4)
      { n_sp=n_pl=n_mpl=n_lddr=0;
	_door.init_door(570,25,7);
	k[0].init_pl(560,25+40,120,0);
	k[9].init_pl(80,299,380,7);
	k[1].init_pl(80,170,380,7);
	k[8].init_pl(80,190,119,7,2);
	k[2].init_pl(450,180,129,7,2);
	mpl[0].init_mpl(490,220,50,0,150,1,-5);
	mpl[1].init_mpl(340, 150, 50, 0, 170, 0, -5);
       k[3].init_pl(310,70,100,7,2);
       k[4].init_pl(80,70,230,7,0);
       k[7].init_pl(80,70,120,7,2);
       k[6].init_pl(420,140,70,7,1);
       door_key.init_doorkey(200,230,0);
	lddr[0].init_ladder(150,20,180,0);
	n_lddr=1;
	n_pl=10;
	n_mpl=2;
      }
    //etc etc
}
void draw_map()
{

	setfillstyle(1,bk_col);
	bar(0,0,640,480);
	setfillstyle(1,inv(bk_col));
	setcolor(inv(bk_col));
	bar(0,360,640,480);
	for(int i=0;i<n_pl;i++)
	{
		k[i].draw_pl();
	}
	for(int j=0;j<n_mpl;j++)
	{
		mpl[j].draw_pl();
	}
	for(int k=0;k<n_lddr;k++)
	{
		lddr[k].draw_ladder();
	}
	_door.draw();
	door_key.draw();
}

void main()
{
	int gd=9,gm=2;
	char a[10];
	randomize();
	initgraph(&gd,&gm,"c:\\turboc3\\bgi\\");
	cleardevice();
	setfillstyle(1,0);
	bar(0,0,320,480);
	setfillstyle(1,7);
	bar(320,0,640,480);
	settextstyle(2,0,100);
	outtextxy(290,230,"DU");
	setcolor(0);
	outtextxy(330,230,"AL");
	getch();
	do{
    if(complete) lvl++;
    complete=0;
    cleardevice();
    generate_map();
	draw_map();
	_door.draw();
	door_key.draw();
	m.init_man();
	while(key!=283 && !complete)
	{
	   for(int i=0;i<n_pl;i++)
	   k[i].draw_pl();
	   for( i=0;i<n_mpl;i++)
       {
	    mpl[i].erase_pl();
	    mpl[i].move(m);
	    mpl[i].draw_pl();
       }

	   door_key.check();
	   m.draw();
       for(i=0;i<n_sp;i++)
       {
	   sp[i].check_sp(m);
	   sp[i].draw();
       }
       for(i=0;i<n_lddr;i++)
       {
	    if(lddr[i].check()) lddr[i].draw_ladder();
       }
       if(ch)
       {
	    bk_col=inv(bk_col);
	    draw_map();
	    ch=0;
       }
       delay(50);
       m.erase();
       m.update_pos();
    }
	cleardevice();
	//closing screen
	}while(key!=283);
	closegraph();
}
//thank you - SaNiMuSh