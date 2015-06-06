#include <stdio.h>
#include <math.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265358979323846
// 函数名：stod
// 声  明：double stod(const std::string &s);
// 参  数：字符串型的数字
// 返回值：双精度型的数字
double stod(const char *s)
{	
	double value;
	value=atof(s);
	return value;
}

// 函数名：stoi
// 声  明：int stoi(const std::string &s);
// 参  数：字符串型的数字
// 返回值：整型的数字
int stoi(const char *s)
{	int value;
	value = atoi(s);
	return value;
}

// 函数名：deg
// 声  明：double deg(double dms);
// 参  数：以度分秒为单位的角度
// 返回值：以角度为单位的角度
double deg(double dms)
{	double d=0, m=0, s=0;//度位,分位,秒位
	double zs=0, xs=0;
	xs = modf(dms,&zs);		d = zs;		xs = xs * 100.0000000001;
	xs = modf(xs,&zs);		m = zs / 60;
	 s = xs / 36;
	return(d+m+s);
}

// 函数名：dms  60进制小数点换DMS格式显示
// 声  明：double dms(double deg);
// 参  数：以角度为单位的角度
// 返回值：以度分秒为单位的角度
double dms(double deg)
{	double zs=0,xs=0;
	double d=0, m=0, s=0;

	xs=modf(deg,&zs);		d=zs;
	xs=modf(xs*60.0000000001,&zs);		m=zs;
	s=xs*60;

	return(d+m*0.01+s*0.0001);
}

// 函数名：rad
// 声  明：double  rad(double deg);
// 参  数：以角度为单位的角度
// 返回值：以弧度为单位的角度
double  rad(double deg)
{	return( deg * PI / 180);
}

// 函数名：arad
// 声  明：double arad(double rad);
// 参  数：以弧度为单位的角度
// 返回值：以角度为单位的角度
double arad(double rad)
{	return( rad * 180 / PI);
}

// 函数名：sign
// 声  明：double sign(double value);
// 参  数：数字
// 返回值：数字的符号，正号返回+1，负号返回-1
double sign(double value)
{	if(value<0)
	{	return -1;
	}
	else
	{	return +1;
	}
}

// 计算坐标方位角（返回值为角度）
// 函数名：azimuth
// 声  明：double azimuth(double x1, double y1, double x2, double y2);
// 参  数：P1点坐标(x1,y1)，P2点坐标(x2,y2)
// 返回值：P1点到P2点坐标方位角
double azimuth(double x1, double y1, double x2, double y2)
{	double dx = x2 - x1;
	double dy = y2 - y1;

	if( dy>=0 && dx>0 )
	{	return       arad( atan( fabs( dy/dx ) ) );
	}	
	if( dy>=0 && dx<0 )
	{	return 180 - arad( atan( fabs( dy/dx ) ) );
	}
	if( dy<0 && dx<0 )
	{	return 180 + arad( atan( fabs( dy/dx ) ) );
	}
	if( dy<0 && dx>0 )
	{	return 360 - arad( atan( fabs( dy/dx ) ) );
	}
	if( dy>0 && dx==0 )
	{	return 90;
	}
	if( dy<0 && dx==0 )
	{	return 270;
	}
	
	return -1;
}