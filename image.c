#include"Gwent.h"

/*
	函数原型：void DrawSword(double cx, double cy, double length);
	传入参数：中心位置坐标 cx, cy, 长度length; 
	返 回 值：无
	函数功能：画一个倾斜45度的黑色剑图案, 注意该函数会使画笔变为白色 
*/
void DrawSword(double cx, double cy, double length){
	SetPenColor("Black");
	SetPenSize(0.01);
	StartFilledRegion(1);//剑柄 
	MovePen(cx-length*pow(2,0.5)/4,cy-length*pow(2,0.5)/4);
	DrawLine(0,length/13);
	DrawLine(length*0.18,length*0.18);
	DrawLine(length/13,-length/13);
	DrawLine(-length*0.18,-length*0.18);
	DrawLine(-length/13,0);	
	EndFilledRegion();
	StartFilledRegion(1);//剑肩 
	MovePen(cx-length*0.125-length*pow(2,0.5)/20,cy-length*0.125+length*pow(2,0.5)/20);
	DrawLine(length*pow(2,0.5)/10,-length*pow(2,0.5)/10);
	DrawLine(length*0.1,-length*0.06);
	DrawLine(-length*0.3,length*0.3);
	EndFilledRegion();
	StartFilledRegion(1);//剑身 
	MovePen(cx-length*0.1,cy-length*0.1);
	DrawLine(length*0.05,-length*0.05);
	DrawLine(length*0.37,length*0.33);
	double xn=GetCurrentX();
	double yn=GetCurrentY();
	DrawLine(cx+length*pow(2,0.5)/4-xn,cy+length*pow(2,0.5)/4-yn);
	DrawLine(xn-cx-length*(0.14+pow(2,0.5)/4),yn-cy+length*(0.14-pow(2,0.5)/4));
	DrawLine(-length*0.33,-length*0.37);
	EndFilledRegion();
	StartFilledRegion(1);//剑脊 
	SetPenColor("White"); 
	MovePen(cx-length*0.105,cy-length*0.095);
	DrawLine(length*0.01,-length*0.01);
	DrawLine(length*(0.3-pow(2,0.5)/100),length*(0.3));
	EndFilledRegion();
}

/*
	函数原型：void DrawBow(double cx, double cy, double length);
	传入参数：中心位置坐标 cx, cy, 长度length; 
	返 回 值：无
	函数功能：画一个倾斜45度的黑色弓箭图案, 注意该函数会使画笔变为白色 
*/
void DrawBow(double cx, double cy, double length){
	SetPenColor("Black");
	SetPenSize(0.01);

	StartFilledRegion(1);//箭翎 
	MovePen(cx-length*pow(2,0.5)/4+length/20,cy-length*pow(2,0.5)/4+length/20);
	DrawLine(-length/20,0);
	DrawLine(length/10,length/10);
	DrawLine(length/20,0);
	double xn=GetCurrentX();
	double yn=GetCurrentY();
	DrawLine(0,-length/20);
	DrawLine(-length/10,-length/10);
	DrawLine(0,length/20);
	EndFilledRegion();
	StartFilledRegion(1);//箭镞 
	MovePen(cx-length*pow(2,0.5)/4+length*0.65-length/18,cy-length*pow(2,0.5)/4+length*0.65);
	DrawLine(length/18,0);
	DrawLine(0,-length/18);
	DrawLine(length*0.058,length*0.112);
	EndFilledRegion();
	StartFilledRegion(1);//弓身 
	MovePen(cx-length*0.35,cy+length*0.5);
	DrawArc(length*0.85,90,-90);
	DrawArc(length*0.935,5,80);
	EndFilledRegion();
	if(length>2){
		SetPenSize(length);
	}else{
		SetPenSize(length*5);
	}
	SetPenColor("White");
	DrawLine(length*0.85,-length*0.85);
	SetPenColor("Black");//弓弦 
	SetPenSize(length*0.8);
	MovePen(xn,yn);
	DrawLine(-length*0.1,length*0.7);
	MovePen(xn,yn);
	DrawLine(length*0.7,-length*0.094);
	SetPenSize(2*length);//箭杆 
	MovePen(cx-length*pow(2,0.5)/4+length/10,cy-length*pow(2,0.5)/4+length/10);
	DrawLine(length*0.55,length*0.55);
	SetPenColor("White");//装饰 
	if(length>=1){
		SetPenSize(length*0.8);
		MovePen(cx+length*0.05,cy+length*0.05);
		DrawLine(length/7,length/7);
	}
}

/*
	函数原型：void DrawSiege(double cx, double cy, double length);
	传入参数：中心位置坐标 cx, cy, 长度length; 
	返 回 值：无
	函数功能：画一个黑色攻投石车图案
*/
void DrawSiege(double cx, double cy, double length){
	SetPenColor("Black");
	StartFilledRegion(1);//车身 
	DrawBox(cx-length*0.3,cy-length*0.3,length*0.6,length*0.12);
	EndFilledRegion();
	MovePen(cx-length*0.29,cy-length*0.23);
	StartFilledRegion(1);//车轮 
	DrawArc(0.08*length,90,360);
	EndFilledRegion();
	MovePen(cx+length*0.29,cy-length*0.23);
	StartFilledRegion(1);
	DrawArc(0.08*length,90,360);
	EndFilledRegion();
	MovePen(cx-length*0.3,cy-length*0.23);//支撑架 
	SetPenSize(length*2);
	DrawLine(length*0.55,length*0.4);
	DrawLine(0,-length*0.4);
	MovePen(cx+0.29*length,cy-0.18*length);//抛掷杠杆 
	SetPenSize(length*3);
	DrawLine(-length*0.55,length*0.26);
	MovePen(cx-length*0.23,cy+length*0.08);//载物筐 
	SetPenSize(0.01);
	StartFilledRegion(1);
	DrawLine(-length*0.12,0);
	DrawLine(-length*0.165,length*0.09);
	DrawLine(0,length*0.12*6/11);
	EndFilledRegion();
}
/*
	函数原型：void DrawFrost(double cx, double cy, double length);
	传入参数：中心位置坐标 cx, cy, 长度length; 
	返 回 值：无
	函数功能：画一个黑色雪花图案
*/
void DrawFrost(double cx, double cy, double length){
	double r=length*0.25;
	double rx=length*0.25;
	SetPenColor("Black");
	SetPenSize(r*10); //雪花主干 
	MovePen(cx,cy);
	DrawLine(0,r);
	MovePen(cx,cy);
	DrawLine(0,-r);
	MovePen(cx,cy);
	DrawLine(r*pow(3,0.5)/2,r*0.5);
	MovePen(cx,cy);
	DrawLine(-r*pow(3,0.5)/2,-r*0.5);
	MovePen(cx,cy);
	DrawLine(r*pow(3,0.5)/2,-r*0.5);
	MovePen(cx,cy);
	DrawLine(-r*pow(3,0.5)/2,r*0.5);
	SetPenSize(r*10); //雪花末梢
	MovePen(cx,cy+r);
	DrawLine(0,rx);
	MovePen(cx,cy+r);
	DrawLine(rx*0.5,rx*0.866);
	MovePen(cx,cy+r);
	DrawLine(-rx*0.5,rx*0.866);
	MovePen(cx,cy-r);
	DrawLine(0,-rx);
	MovePen(cx,cy-r);
	DrawLine(rx*0.5,-rx*0.866);
	MovePen(cx,cy-r);
	DrawLine(-rx*0.5,-rx*0.866);
	MovePen(cx+r*pow(3,0.5)/2,cy+r*0.5);
	DrawLine(rx*0.866,rx*0.5);
	MovePen(cx+r*pow(3,0.5)/2,cy+r*0.5);
	DrawLine(rx,0);
	MovePen(cx+r*pow(3,0.5)/2,cy+r*0.5);
	DrawLine(rx*0.5,rx*0.866);
	MovePen(cx-r*pow(3,0.5)/2,cy-r*0.5);
	DrawLine(-rx*0.866,-rx*0.5);
	MovePen(cx-r*pow(3,0.5)/2,cy-r*0.5);
	DrawLine(-rx,0);
	MovePen(cx-r*pow(3,0.5)/2,cy-r*0.5);
	DrawLine(-rx*0.5,-rx*0.866);
	MovePen(cx+r*pow(3,0.5)/2,cy-r*0.5);
	DrawLine(rx*0.866,-rx*0.5);
	MovePen(cx+r*pow(3,0.5)/2,cy-r*0.5);
	DrawLine(rx,0);
	MovePen(cx+r*pow(3,0.5)/2,cy-r*0.5);
	DrawLine(rx*0.5,-rx*0.866);
	MovePen(cx-r*pow(3,0.5)/2,cy+r*0.5);
	DrawLine(-rx*0.866,rx*0.5);
	MovePen(cx-r*pow(3,0.5)/2,cy+r*0.5);
	DrawLine(-rx,0);
	MovePen(cx-r*pow(3,0.5)/2,cy+r*0.5);
	DrawLine(-rx*0.5,rx*0.866);
}
/*
	函数原型：void DrawFrost(double cx, double cy, double length);
	传入参数：中心位置坐标 cx, cy,长度length; 
	返 回 值：无
	函数功能：画一个黑色雾图案
*/
void DrawFog(double cx, double cy, double length){
	SetPenColor("Black");
	SetPenSize(0.01);//月亮
	MovePen(cx-length*0.3,cy);
	StartFilledRegion(1);
	DrawArc(length*0.45,180,360);
	EndFilledRegion();
	MovePen(cx-length*0.1,cy);
	SetPenColor("White");
	StartFilledRegion(1);
	DrawArc(length*0.4,180,360);
	EndFilledRegion();
	
	StartFilledRegion(1);
	SetPenColor("White");
	DrawBox(cx-length*0.55,cy-length*0.2,length,length*0.4);
	EndFilledRegion();
	
	SetPenColor("Black");//雾气 
	SetPenSize(length*2);
	MovePen(cx-length*0.5,cy+length*0.15);
	DrawLine(length*0.7,0);
	MovePen(cx-length*0.3,cy+length*0.05);
	DrawLine(length*0.8,0);
	MovePen(cx-length*0.5,cy-length*0.05);
	DrawLine(length*0.7,0);
	MovePen(cx-length*0.3,cy-length*0.15);
	DrawLine(length*0.7,0);
}
/*
	函数原型：void DrawFrost(double cx, double cy, double r);
	传入参数：中心位置坐标 cx, cy, 半径r; 
	返 回 值：无
	函数功能：画一个黑色雨滴图案
*/
void DrawRain(double cx, double cy, double size){
	SetPenColor("Black");
	SetPenSize(0.01);
	double length=size*0.6;
//	MovePen(cx-0.707*length,cy-0.707*length);
//	DrawLine(2,2);
	StartFilledRegion(1);//雨点 
	MovePen(cx-length*0.707,cy-length*0.707); 
	DrawArc(length*0.403,225,360);
	EndFilledRegion();
	StartFilledRegion(1);
	MovePen(cx-length*0.606,cy-length*0.064);
	DrawLine(length*1.04,length*0.5);
	DrawLine(-length*0.51,-length*1.08);
	EndFilledRegion();
	SetPenColor("White");
	MovePen(cx-length*0.28,cy-length*0.08);//雨点高光
	SetPenSize(length*8);
	DrawArc(length*0.7,105,40);
	

}
/*
	函数原型：void DrawLight(double cx, double cy, double r, double a,);
	传入参数：太阳中心坐标cx，cy，太阳半径r, 光芒角度 a; 
	返 回 值：无
	函数功能：画一根黑色太阳光芒 
*/
void DrawLight(double cx, double cy, double r, double a){
	double an=3.14*a/180;
	SetPenColor("Black");
	SetPenSize(r*5);
	MovePen(cx+r*0.55*cos(an+22.5*3.14/180),cy+r*0.55*sin(an+22.5*3.14/180));
	DrawLine(r*0.1*cos(an+22.5*3.14/180),r*0.1*sin(an+22.5*3.14/180));
	SetPenSize(r*5);
	MovePen(cx+r*0.5*cos(an),cy+r*0.5*sin(an)); 
	DrawLine(r*0.2*cos(an),r*0.2*sin(an));
	
	StartFilledRegion(1);
	SetPenSize(r*2);
	double ca = an+0.12;
	MovePen(cx+r*0.68*cos(ca),cy+r*0.68*sin(ca));
	DrawArc(r*1.5,90+a,-30);
	DrawArc(r*1.5,75+a,30);
	EndFilledRegion();
	
	StartFilledRegion(1);
	SetPenSize(r*2);
	double da = ca+0.4;
	MovePen(cx+r*0.8*cos(da),cy+r*0.8*sin(da));
	DrawArc(r*1,90+a,-30);
	DrawArc(r*1,75+a,30);
	EndFilledRegion();
	
	
}
/*
	函数原型：void DrawSun(double cx, double cy, double r);
	传入参数：中心位置坐标 cx, cy, 半径r; 
	返 回 值：无
	函数功能：画一个黑色太阳图案
*/
void DrawSun(double cx, double cy, double r){
	SetPenColor("Black");
	SetPenSize(0.01);
	StartFilledRegion(1);
	MovePen(cx+r*0.5,cy);
	DrawArc(r*0.5,0,360);
	EndFilledRegion();
	double length=r*0.5;
	DrawLight(cx, cy, r, 0);
	DrawLight(cx, cy, r, 45);
	DrawLight(cx, cy, r, 90);
	DrawLight(cx, cy, r, 135);
	DrawLight(cx, cy, r, 180);
	DrawLight(cx, cy, r, 225);
	DrawLight(cx, cy, r, 270);
	DrawLight(cx, cy, r, 315);
}
/*
	函数原型：void DrawBurn(double cx, double cy, double size);
	传入参数：中心位置坐标 cx, cy, 大小size; 
	返 回 值：无
	函数功能：画一个黑色骷髅头 
*/
void DrawBurn(double cx, double cy, double size){
	SetPenColor("Black");
	SetPenSize(0.01);
	MovePen(cx+size*0.45,cy+size*0.1);
	
	StartFilledRegion(1);
	DrawArc(size*0.45,-10,200);
	EndFilledRegion();
	
	StartFilledRegion(1);
	MovePen(cx-size*0.44,cy+size*0.1);
	DrawLine(size*0.03,-size*0.166);
	DrawLine(size*0.833,0);
	DrawLine(size*0.03,size*0.166);
	EndFilledRegion();
	
	MovePen(cx-size*0.405,cy-size*0.0755);
	StartFilledRegion(1);
	DrawArc(size*0.15,190,80);
	DrawLine(size*0.53,0);
	DrawArc(size*0.15,270,80);
	EndFilledRegion();
	
	StartFilledRegion(1);
	SetPenColor("Black"); 
	DrawBox(cx-size*0.28,cy-size*0.3,size*0.58,size*0.1);
	EndFilledRegion();
	
	SetPenColor("White"); 
	DrawLine(0,size*0.1);
	StartFilledRegion(1);
	DrawArc(size*0.1,90,-90);
	EndFilledRegion();
	
	StartFilledRegion(1);
	DrawLine(-size*0.1,0);
	DrawLine(0,size*0.1);
	EndFilledRegion();
	
	MovePen(cx+size*0.3,cy-size*0.3);
	StartFilledRegion(1);
	DrawLine(-size*0.1,0);
	DrawLine(size*0.1,size*0.1);
	EndFilledRegion();
	
	StartFilledRegion(1);
	DrawArc(size*0.1,90,90);
	EndFilledRegion();
	SetPenColor("Black");
	
	StartFilledRegion(1);
	DrawLine(0,-size*0.1);
	DrawLine(-size*0.38,0);
	DrawLine(0,size*0.1);
	EndFilledRegion();
	
	MovePen(cx-size*0.18,cy-size*0.4);
	StartFilledRegion(1);
	DrawArc(size*0.75,255,30);
	EndFilledRegion();
	
	SetPenColor("White");
	MovePen(cx-size*0.1,cy-size*0);
	StartFilledRegion(1);
	DrawArc(size*0.11,0,360);
	EndFilledRegion();
	
	MovePen(cx+size*0.12,cy-size*0);
	StartFilledRegion(1);
	DrawArc(size*0.11,180,360);
	EndFilledRegion();
	
	MovePen(cx,cy-size*0.12);
	StartFilledRegion(1);
	DrawLine(size*0.03,-size*0.1);
	DrawLine(-size*0.06,0);
	EndFilledRegion();
}
/*
	函数原型：void DrawHorn(double cx, double cy, double size);
	传入参数：中心位置坐标 cx, cy, 大小size; 
	返 回 值：无
	函数功能：画一个黑色号角 
*/
void DrawHorn(double cx, double cy, double size){
	SetPenSize(1);
	
	MovePen(cx-size*0.25,cy-size*0.1);
	SetPenColor("Black");
	StartFilledRegion(1);
	DrawLine(-size*0.085,-size*0.15);
	DrawArc(size*0.8,-110,50);
	DrawLine(-size*0.14,size*0.26);
	EndFilledRegion();
	SetPenColor("White");
	StartFilledRegion(1);
	DrawArc(size*0.7,-50,-40);
	DrawLine(size*0.3,size*0.15);
	EndFilledRegion();
	
	StartFilledRegion(1);//高光 
	MovePen(cx+size*0.21,cy-size*0.04);
	DrawArc(size*0.65,-60,-35);
	DrawLine(size*0.35,size*0.1);
	EndFilledRegion();
	DrawLine(-size*0.35,-size*0.1);
	SetPenColor("Black");
	StartFilledRegion(1);
	DrawArc(size*0.65,-90,34);
	EndFilledRegion();
	
	MovePen(cx+size*0.22,cy+size*0.1);
	StartFilledRegion(1);
	DrawLine(size*0.16,-size*0.29);
	DrawLine(size*0.05,0);
	DrawLine(-size*0.19,size*0.35);
	EndFilledRegion();
	
	MovePen(cx-size*0.38,cy-size*0.27);
	StartFilledRegion(1);
	DrawLine(size*0.11,size*0.19);
	DrawLine(-size*0.05,size*0.01);
	DrawLine(-size*0.09,-size*0.15);
	EndFilledRegion();
	
	StartFilledRegion(1);
	MovePen(cx-size*0.38,cy-size*0.11);
	DrawArc(size*0.04,0,360);
	EndFilledRegion();
	
	MovePen(cx-size*0.28,cy-size*0.05);
	SetPenSize(size*2);
	DrawLine(size*0.24,size*0.36);
	DrawLine(size*0.2,-size*0.24);
}
/*
	函数原型：void DrawSpy(double cx, double cy, double size);
	传入参数：中心位置坐标 cx, cy, 大小size; 
	返 回 值：无
	函数功能：画一个黑色眼睛 
*/
void DrawSpy(double cx, double cy, double size){
	SetPenColor("Black");
	MovePen(cx+size*0.5,cy);
	SetPenSize(size*4);
	DrawArc(size*0.65,40,100);
	DrawArc(size*0.65,220,100);
	MovePen(cx+size*0.23,cy);
	DrawArc(size*0.23,0,360);
	SetPenSize(size*6);
	MovePen(cx-size*0.19*0.707,cy+size*0.19*0.707);
	DrawArc(size*0.19,135,160);
	StartFilledRegion(1);
	SetPenSize(1);
	MovePen(cx+size*0.12,cy);
	DrawArc(size*0.12,0,360);
	EndFilledRegion();
}
/*
	函数原型：void DrawMedic(double cx, double cy, double size);
	传入参数：中心位置坐标 cx, cy, 大小size; 
	返 回 值：无
	函数功能：画一个黑色心和十字 
*/
void DrawMedic(double cx, double cy, double size){
	SetPenColor("Black");
	SetPenSize(1);
	MovePen(cx,cy+size*0.3);
	StartFilledRegion(1);
	DrawArc(size*0.3,135,-165);
	DrawArc(size*1.8,-30,-22.9);
	DrawArc(size*1.8,232.9,-22.9);
	DrawArc(size*0.3,210,-165);
	EndFilledRegion();
	SetPenColor("White");
	SetPenSize(size*10);
	MovePen(cx,cy+size*0.3);
	DrawLine(0,-size*0.88);
	MovePen(cx-size*0.47,cy-size*0.05);
	DrawLine(size*0.93,0);
}
/*
	函数原型：void DrawBond(double cx, double cy, double size);
	传入参数：中心位置坐标 cx, cy, 大小size; 
	返 回 值：无
	函数功能：画一双手握在一起 
*/
void DrawBond(double cx, double cy, double size){
	SetPenColor("Black");
	SetPenSize(size);
	MovePen(cx-size*0.45,cy+size*0.2);
	DrawLine(size*0.15,0);
	DrawLine(size*0.1,-size*0.05);
	DrawLine(size*0.4,0);
	DrawLine(size*0.28,-size*0.21);
	
	DrawArc(size*0.06,45,-180);
	DrawLine(-size*0.12,size*0.09);
	
	DrawLine(size*0.16,-size*0.12);
	DrawArc(size*0.06,45,-180);
	DrawLine(-size*0.16,size*0.12);
	
	DrawLine(size*0.14,-size*0.105);
	DrawArc(size*0.06,45,-180);
	DrawLine(-size*0.12,size*0.09);
	
	DrawLine(size*0.1,-size*0.075);
	DrawArc(size*0.05,45,-180);
	DrawLine(-size*0.12,size*0.09);
	
	DrawLine(size*0.025,size*0.04);
	DrawLine(-size*0.32,size*0.2);
	DrawArc(size*0.06,45,90);
	DrawArc(size*0.06,-45,-50);
	DrawLine(-size*0.05,0);
	DrawLine(0,size*0.28);
	
	SetPenSize(size*9);
	MovePen(cx-size*0.28,cy-size*0.12);
	DrawLine(-size*0.03,-size*0.048);
	MovePen(cx-size*0.192,cy-size*0.175);
	DrawLine(-size*0.03,-size*0.048);
	MovePen(cx-size*0.104,cy-size*0.23);
	DrawLine(-size*0.03,-size*0.048);
	SetPenSize(size*8);
	MovePen(cx-size*0.016,cy-size*0.285);
	DrawLine(-size*0.025,-size*0.040);
	SetPenSize(1);
	MovePen(cx+size*0.7,cy+size*0.18);
	StartFilledRegion(1);
	DrawLine(-size*0.2,0);
	DrawLine(-size*0.2,size*0.12);
	DrawLine(-size*0.45,0);
	DrawArc(size*0.06,90,180);
	DrawLine(size*0.36,0);
	DrawLine(size*0.36,-size*0.27);
	DrawLine(size*0.13,0);
	DrawLine(0,size*0.27);
	EndFilledRegion();
}
/*
	函数原型：void DrawMuster(double cx, double cy, double size);
	传入参数：中心位置坐标 cx, cy, 大小size; 
	返 回 值：无
	函数功能：画两个黑色头盔 
*/
void DrawMuster(double cx, double cy, double size){
	SetPenColor("Black");
	SetPenSize(1);
	MovePen(cx-size*0.15,cy-size*0.3);
	StartFilledRegion(1);
	DrawLine(-size*0.35,size*0.2);
	DrawLine(size*0.14,size*0.08);
	DrawLine(size*0.21,-size*0.12);
	DrawLine(size*0.21,size*0.12);
	DrawLine(size*0.14,-size*0.08);
	DrawLine(-size*0.35,-size*0.2);
	EndFilledRegion();
	
	MovePen(cx-size*0.15,cy-size*0.1);
	StartFilledRegion(1);
	DrawLine(-size*0.18,size*0.103);
	DrawLine(size*0.03,size*0.1);
	DrawLine(0,size*0.18);
	DrawLine(size*0.15,size*0.08);
	DrawLine(size*0.15,-size*0.08);
	DrawLine(0,-size*0.18);
	DrawLine(size*0.03,-size*0.1);
	DrawLine(-size*0.18,-size*0.103);
	EndFilledRegion();
	SetPenColor("White");
	SetPenSize(size*3);
	DrawLine(0,size*0.21);
	DrawArc(size*0.4,-90,14);
	DrawArc(size*0.4,-75,-28);
	
	SetPenColor("Black");
	SetPenSize(1);
	MovePen(cx+size*0.27,cy-size*0.12);
	StartFilledRegion(1);
	DrawLine(size*0.18,size*0.102);
	DrawLine(-size*0.084,size*0.048);
	DrawLine(-size*0.126,-size*0.072);
	DrawLine(-size*0.126,size*0.072);
	DrawLine(-size*0.035,-size*0.02);
	EndFilledRegion();
	
	MovePen(cx+size*0.24,cy-size*0.01);
	StartFilledRegion(1);
	DrawLine(-size*0.108,size*0.0618);
	DrawLine(size*0.018,size*0.06);
	DrawLine(0,size*0.108);
	DrawLine(size*0.09,size*0.048);
	DrawLine(size*0.09,-size*0.048);
	DrawLine(0,-size*0.108);
	DrawLine(size*0.018,-size*0.06);
	DrawLine(-size*0.108,-size*0.0618);
	EndFilledRegion();
	
	SetPenColor("White");
	SetPenSize(size*1.8);
	DrawLine(0,size*0.126);
	DrawArc(size*0.24,-90,14);
	DrawArc(size*0.24,-75,-28);
}
/*
	函数原型：void DrawBoost(double cx, double cy, double length);
	传入参数：中心位置坐标 cx, cy, 大小length; 
	返 回 值：无
	函数功能：画一个黑色十字 
*/
void DrawBoost(double cx, double cy, double length){
	double size=length*0.6;
	SetPenColor("Black");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(cx,cy+size*0.5);
	DrawLine(size*0.2,0);
	DrawLine(-size*0.05,-size*0.35);
	DrawLine(size*0.35,size*0.05);
	DrawLine(0,-size*0.4);
	DrawLine(-size*0.35,size*0.05);
	DrawLine(size*0.05,-size*0.35);
	DrawLine(-size*0.4,0);
	DrawLine(size*0.05,size*0.35);
	DrawLine(-size*0.35,-size*0.05);
	DrawLine(0,size*0.4);
	DrawLine(size*0.35,-size*0.05);
	DrawLine(-size*0.05,size*0.35);
	DrawLine(size*0.2,0);
	EndFilledRegion();
	SetPenSize(length*2);
	MovePen(cx-length*0.5,cy);
	DrawLine(size*0.15,size*0.4);
	MovePen(cx-length*0.5,cy);
	DrawLine(size*0.15,-size*0.4);
	MovePen(cx+length*0.5,cy);
	DrawLine(-size*0.15,size*0.4);
	MovePen(cx+length*0.5,cy);
	DrawLine(-size*0.15,-size*0.4);
	
	MovePen(cx-length*0.42,cy);
	DrawLine(size*0.075,size*0.2);
	MovePen(cx-length*0.42,cy);
	DrawLine(size*0.075,-size*0.2);
	MovePen(cx+length*0.42,cy);
	DrawLine(-size*0.075,size*0.2);
	MovePen(cx+length*0.42,cy);
	DrawLine(-size*0.075,-size*0.2);
}
