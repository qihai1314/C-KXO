#include "headfile.h"

extern COMMONDATA common_data;
void Pol(double a,double b,double x,double y,double *r,double *t)
{
	double c,d;
	double hd,ha,aa;
	c = x - a;
	d = y - b;
	if (c==0 && d>0) ha = PI/2;
	else if (c==0 && d<0) 
			ha = PI*1.5;
	else if (d==0 && c<0) 
			ha = PI;
	else if(d==0 && c>0)
			 ha = PI*2;
	 
	
	aa = atan(d/c);
	
	if		(c>0 && d>0) 
				ha = aa;
	else if (c>0 && d<0) 
				ha = aa + 2*PI;
	else if (c<0 && d<0) 
			ha = aa + PI;
	else if	(c<0 && d>0) 
			ha = aa + PI;
	
	ha = ha*180.0/PI;
	hd = sqrt(c*c+d*d);
	*r = hd;
	*t = ha;


} 

void CalcPosAndDistance	(double RX,double RY,double BX,double BY,double EP,
						 double *ZH,double *PJ)
{
	double distance,position,E;
	Pol (BX,BY,RX,RY,&distance,&position);
	if (EP<position)
		E = position-EP;
	else
		E = EP-position;
	E = E*PI/180.0;
	*ZH = common_data.BeginStake + distance*cos(E);
	*PJ = sin(E)*distance;

	if(!(EP<position))
		*PJ=-*PJ;
}