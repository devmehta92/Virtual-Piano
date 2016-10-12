#include<iostream.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
#include<stdio.h>

class piano{
	private:
		unsigned int size;
		int addf,initx,inity,maxkeyh,maxkeyw,intkeyh,intkeywf,intkeyw1,intkeyw2,intkeyw3,recminx,recminy,recmaxx,recmaxy;
		void* key1;
		void* key2;
		void* key3;
		void* key4;
		void* frame;
	public:
		void init();
		void draw_keyboard();
		void keyboard_play();
		void error1();
		void note(unsigned freq,long millis,int x,int y,int color,int bcolor,char* name);
};
void piano::init(){
	addf=12;
	initx=getmaxx()/3.25;
	inity=getmaxy()/4;
	maxkeyh=inity+100;
	maxkeyw=initx+20;
	intkeyh=inity+50;
	intkeywf=initx+4;
	intkeyw1=((maxkeyw-initx)/2)+initx;
	intkeyw2=intkeyw1+intkeywf-initx;
	intkeyw3=intkeyw1-intkeywf+initx;
	recminx=initx+8*addf-3;
	recminy=inity-addf;
	recmaxx=initx+12*addf-3+3;
	recmaxy=inity-5*addf;

	size=imagesize(initx,inity+maxkeyh+5,initx+18*addf+maxkeyw,inity+maxkeyh+50);
	frame=malloc(size);

	int key1arr[]={initx,inity,initx,maxkeyh,maxkeyw,maxkeyh,maxkeyw,intkeyh,intkeyw1,intkeyh,intkeyw1,inity,initx,inity};
	int key2arr[]={initx,inity,initx,intkeyh-2,intkeyw2-2,intkeyh-2,intkeyw2-2,inity,initx,inity};
	int key3arr[]={intkeyw3,inity,intkeyw3,intkeyh,initx,intkeyh,initx,maxkeyh,maxkeyw,maxkeyh,maxkeyw,intkeyh,intkeyw2,intkeyh,intkeyw2,inity,intkeyw3,inity};
	int key4arr[]={intkeyw1,inity,intkeyw1,intkeyh,initx,intkeyh,initx,maxkeyh,maxkeyw,maxkeyh,maxkeyw,inity,intkeyw1,inity};

	setfillstyle(1,EGA_WHITE);
	fillpoly(7,key1arr);
	size=imagesize(initx,inity,maxkeyw,maxkeyh);
	key1= malloc(size);
	getimage(initx,inity,maxkeyw,maxkeyh,key1);
	putimage(initx,inity,key1,XOR_PUT);

	setcolor(EGA_WHITE);
	setfillstyle(1,EGA_BLACK);
	fillpoly(5,key2arr);
	size=imagesize(initx,inity,intkeyw2,intkeyh);
	key2 = malloc(size);
	getimage(initx,inity,intkeyw2,intkeyh,key2);
	putimage(initx,inity,key2,XOR_PUT);

	setfillstyle(1,EGA_WHITE);
	fillpoly(9,key3arr);
	size=imagesize(initx,inity,maxkeyw,maxkeyh);
	key3= malloc(size);
	getimage(initx,inity,maxkeyw,maxkeyh,key3);
	putimage(initx,inity,key3,XOR_PUT);

	fillpoly(7,key4arr);
	size=imagesize(initx,inity,maxkeyw,maxkeyh);
	key4= malloc(size);
	getimage(initx,inity,maxkeyw,maxkeyh,key4);
	putimage(initx,inity,key4,XOR_PUT);

}
void piano::error1(){
	setcolor(EGA_WHITE);
	settextjustify(1,1);
	outtextxy(recmaxx,(recmaxy+10)%getmaxy(),"Can't reduce further. Press any key...");
	getch();
	setcolor(EGA_BLACK);
	outtextxy(recmaxx,(recmaxy+10)%getmaxy(),"Can't reduce further. Press any key...");
}
void piano::draw_keyboard(){
	putimage(initx,inity,key1,XOR_PUT);
	putimage(initx+addf+2,inity,key2,XOR_PUT);
	putimage(initx+2*addf,inity,key3,XOR_PUT);
	putimage(initx+3*addf+6,inity,key2,XOR_PUT);
	putimage(initx+4*addf,inity,key4,XOR_PUT);
	putimage(initx+6*addf,inity,key1,XOR_PUT);
	putimage(initx+7*addf+2,inity,key2,XOR_PUT);
	putimage(initx+8*addf,inity,key3,XOR_PUT);
	putimage(initx+9*addf+4,inity,key2,XOR_PUT);
	putimage(initx+10*addf,inity,key3,XOR_PUT);
	putimage(initx+11*addf+6,inity,key2,XOR_PUT);
	putimage(initx+12*addf,inity,key4,XOR_PUT);
	putimage(initx+14*addf,inity,key1,XOR_PUT);
	putimage(initx+15*addf+2,inity,key2,XOR_PUT);
	putimage(initx+16*addf,inity,key3,XOR_PUT);
	putimage(initx+17*addf+6,inity,key2,XOR_PUT);
	putimage(initx+18*addf,inity,key4,XOR_PUT);
	rectangle(recminx,recminy,recmaxx,recmaxy);
}
void piano::note(unsigned freq,long millis,int x,int y,int color,int bcolor,char* name){
	x+=2;
	y+=2;
	int ocolor=getpixel(x,y);
	sound(freq);
	setfillstyle(1,color);
	floodfill(x,y,bcolor);
	floodfill(recminx+2,recminy-2,EGA_WHITE);
	setcolor(getmaxcolor()-color);
	settextjustify(1,1);
	settextstyle(0,0,3);
	outtextxy((recminx+(recmaxx-recminx)/2)+1,(recminy+(recmaxy-recminy)/2),name);
	delay(millis);
	x-=2;
	y-=2;
	setfillstyle(1,color);
	rectangle(x,2*maxkeyh-intkeyh,x+maxkeyw-initx,maxkeyh+addf);
	setfillstyle(1,ocolor);
	floodfill(x+2,y+2,bcolor);
	nosound();
}
void piano::keyboard_play(){

	/*
	cout<<"   w     e        t     y     u        o"<<endl
	    <<"a     s     d  f     g     h     j  k     l"<<endl
	    <<"C  C# D  D# E  F  F# G  G# A  A# B  C  C# D"<<endl
	    <<"\n<-Reduce Octave"<<endl
	    <<">-Increase Octave"<<endl
	    <<"m-Reset Octave"<<endl
	    <<"b-Increase Release Time (Sustain)"<<endl
	    <<"n-Decrease Release Time (Sustain)"<<endl
	    <<"\nx-Exit"<<endl;
	*/
	char ip='x';
	float octave=8.0;
	int dly=350;
	nosound();
	do{
		while(!kbhit()){
		       //	rectangle(initx,maxkeyh+3,18*addf+maxkeyw,inity+maxkeyh+50);
			getimage(initx,maxkeyh+5,18*addf+maxkeyw,inity+maxkeyh+50,frame);
			putimage(initx,maxkeyh+5,frame,XOR_PUT);
			putimage(initx,maxkeyh+6,frame,XOR_PUT);
			delay(10);
		}
		ip=getch();
		switch(ip){
			case 'a':
				note(32.7032*octave,dly,initx,inity,1,EGA_BLACK,"C");
				break;
			case 'w':
				note(34.6784*octave,dly,initx+addf+2,inity,2,EGA_WHITE,"C#");
				break;
			case 's':
				note(36.7081*octave,dly,2*addf+initx,intkeyh,3,EGA_BLACK,"D");
				break;
			case 'e':
				note(38.8909*octave,dly,initx+3*addf+6,inity,4,EGA_WHITE,"D#");
				break;
			case 'd':
				note(41.2034*octave,dly,4*addf+initx,intkeyh,5,EGA_BLACK,"E");
				break;
			case 'f':
				note(43.6535*octave,dly,initx+6*addf,inity,6,EGA_BLACK,"F");
				break;
			case 't':
				note(46.2493*octave,dly,initx+7*addf+2,inity,9,EGA_WHITE,"F#");
				break;
			case 'g':
				note(48.9994*octave,dly,8*addf+initx,intkeyh,10,EGA_BLACK,"G");
				break;
			case 'y':
				note(51.9131*octave,dly,initx+9*addf+4,inity,11,EGA_WHITE,"G#");
				break;
			case 'h':
				note(55.0000*octave,dly,10*addf+initx,intkeyh,12,EGA_BLACK,"A");
				break;
			case 'u':
				note(58.2705*octave,dly,initx+11*addf+6,inity,13,EGA_WHITE,"A#");
				break;
			case 'j':
				note(61.7354*octave,dly,12*addf+initx,intkeyh,14,EGA_BLACK,"B");
				break;
			case 'k':
				note(65.4064*octave,dly,initx+14*addf,inity,1,EGA_BLACK,"C");
				break;
			case 'o':
				note(69.2957*octave,dly,initx+15*addf+2,inity,2,EGA_WHITE,"C#");
				break;
			case 'l':
				note(73.4162*octave,dly,16*addf+initx,intkeyh,3,EGA_BLACK,"D");
				break;
			case 'p':
				note(77.7817*octave,dly,initx+17*addf+6,inity,4,EGA_WHITE,"D#");
				break;
			case '\;':
				note(82.4069*octave,dly,18*addf+initx,intkeyh,5,EGA_BLACK,"E");
				break;
			case '<':
				if(octave>1.0)
					octave/=2.0;
				else
					error1();
				break;
			case '>':
				octave*=2.0;
				break;
			case 'm':
				octave=8.0;
				break;
			case 'b':
				if(dly>=2000){
					cout<<"Release time is "<<(dly/1000)<<" seconds."<<endl
					    <<"Do you want to increase further? (y/n): ";
					if(getch()=='y'||getch()=='Y')
						dly+=20;
				}else
					dly+=20;
				break;
			case 'n':
				if(dly<=20)
					error1();
				else
					dly-=20;
				break;
			default:
				nosound();
		}
	}while(ip!='x');
	nosound();
}
void main(){
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "D:\\TC_1\\TB\\TC\\BGI");
	errorcode = graphresult();
	if (errorcode != grOk){
		cout<<"Graphics error:"<<endl<<grapherrormsg(errorcode);
		cout<<"Press any key to halt:";
		getch();
		exit(1);
	}
	piano p;
	p.init();
	p.draw_keyboard();
	p.keyboard_play();
	//getch();
	closegraph();
}