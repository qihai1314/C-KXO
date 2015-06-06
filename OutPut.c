#include "headfile.h"

const int box_width = 12;

//2015年1月5日加入
void FloatToDegStr (double xx,char *str)
{
	int f1;
	double f2,f,x;
	char format[20];
	x=xx+0.000001;
	f1=(int)x;
	f2=((double)x-(double)f1)*60.0;
	f=(f2-(double)((int)f2))*60.0;
	sprintf(format,"%d\x9C%d'%.2f''",f1,(int)f2,f);
	sprintf(str,"%12s",format);
}


int value_to_deg (double xx,char str[])
{
	int f1,negtive = 0;
	char format[20];
	double f2,f,x;
	if (xx<0.0) negtive = 1,xx = -xx;
	x = xx;
	f1=(int)x;
	f2=((double)x-(double)f1)*60.0;
	f=(f2-(double)((int)f2))*60.0;
	sprintf(format,"%d\x9C%d'%.2f\"",negtive ? -f1:f1,(int)f2,f);
	sprintf(str,"%s",format);
	str[box_width] = '\0';
	return strlen(str);
}

void PrintDeg(int px,int py,double xx,int sel)
{
	char str[20];int i;
	i = value_to_deg(xx,str);
	DrawClearBox (px,py,px+box_width*6+3,py+8+3,sel);
	PrintXY(px+2+(box_width-i)*6,py+2,(uchar*)str,0);
	if(sel)Bdisp_AreaReverseVRAM(px+2,py+2,px+box_width*6+1,py+8+1);
	
}

int ftoa (char *str,double n,int digit)
{
	char format[10];
	sprintf (format,"%%%d.%dlf",box_width-(n<0.0 ? 1:0),digit);
	sprintf(str,format,n);
}

void PrintFloat(double n,int x,int y,int sel,int digit)
{
	char c[20];
	ftoa(c,n,digit);
	DrawClearBox (x,y,x+box_width*6+3,y+8+3,sel);
	c[box_width] = 0;
	PrintXY(x+2,y+2,(uchar*)c,0);
	if(sel)Bdisp_AreaReverseVRAM(x+2,y+2,x+box_width*6+1,y+8+1);
}

int PrintfXY(int x,int y,int sel,const char *cpFormat, ...)
{
	char cpBuffer[128];
	int len;
	va_list pArgList;
	va_start(pArgList, cpFormat);
	len = vsprintf(cpBuffer, cpFormat, pArgList);
	va_end(pArgList);
	PrintXY(x,y,(uchar*)cpBuffer,sel);
	return len;
}
