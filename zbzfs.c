#pragma once
#include <math.h>
//#include <iostream>
#include "headfile.h"
#include "cvs.h"
#include "zbzfs.h"

#define N_MAX 16


double ss;	// 起点桩号
double es;	// 终点桩号
double sx;	// 起点坐标X
double sy;	// 终点坐标Y
double sa;	// 起点坐标方位角(DEG)
int v;		// 线元转向,右转为1,左转为-1
double sp;	// 线元起点曲率,直线为0,圆曲线为1/R
double ep;	// 线元终点曲率,直线为0,圆曲线为1/R

	// 计算等分点处桩号
	// 计算n等分处时n取2,4,6..
	// 计算2n等分处时n取1,3,5...
	double s_function(double s, int n);
	// 计算里程s处曲率
	double p_function(double s);
	// 计算里程s处切线方位角(DEG)
	double a_function(double p, double s);

	// 计算里程s处坐标X/Y及坐标方位角A(DEG)
	double zbzs_m_xy(double s, int xy);
	double zbzs_m_a(double s);
	// 计算坐标X/Y对应的里程及偏距
	double zbfs_s_d(double px, double py, int sd);
//
//public:
//	// 构造函数，数据初始化
    void intialCZb(double,double ,double ,double,double,int,double,double);
//	
//	~CZb(void);
//	
	// 计算里程stake/偏距distance/角度angle处的坐标及坐标方位角(DEG)
	double zbzs_x(double stake, double distance,double angle);
	double zbzs_y(double stake, double distance,double angle);
	double zbzs_a(double stake, double distance,double angle);
	// 计算坐标为px/py处的里程及偏距
	double zbfs_s(double px, double py);
	double zbfs_d(double px, double py);


void intialCZb(double ss_v,double es_v,double sx_v,double sy_v,double sa_v,int v_v,double sp_v,double ep_v)
{	ss=ss_v;   // 起点桩号
	es=es_v;   // 终点桩号
	sx=sx_v;   // 起点坐标X
	sy=sy_v;   // 终点坐标Y
	sa=sa_v;   // 起点坐标方位角(DEG)
	v =v_v;    // 线元转向,右转为1,左转为-1
	sp=sp_v;   // 线元起点曲率,直线为0,圆曲线为1/R
	ep=ep_v;   // 线元终点曲率,直线为0,圆曲线为1/R
}

// 计算等分点处里程
// 计算n等分处时n取2,4,6...
// 计算2n等分处时n取1,3,5...
double s_function(double s, int n)
{	return (s-ss)*n/N_MAX+ss;
}

// 计算里程s处曲率
double p_function(double s)
{	return sp+(ep-sp)*(s-ss)/(es-ss);  //起点曲率+（起点曲率-起点曲率）*（计算器里程-起点里程）/(终点里程-起点里程）
}

// 计算里程s处切线方位角
double a_function(double p, double s)
{	return sa+90*v*(p+sp)*fabs(s-ss)/PI;  //起点方位角+90*线元偏向*（p是什么+起点曲率）*绝对值（计算点里程-起点里程）/π
}

// 计算里程s坐标X/Y
double zbzs_m_xy(double s, int xy)
{	// N_MAX等分点处里程
    double s_array[N_MAX];
    // N_MAX等分点处曲率
    double p_array[N_MAX];
    // N_MAX等分点处切线方位角
    double a_array[N_MAX];
	double sum_n_cos = 0;
	double sum_2n_cos = 0;
	double sum_n_sin = 0;
	double sum_2n_sin = 0;
	double s_p , s_a;
	double H = fabs(ss-s)/(N_MAX/2);
	// 数组初始化
	int iTmp;
	for (iTmp=0; iTmp<N_MAX; iTmp++)
	{	s_array[iTmp] = 0;
        p_array[iTmp] = 0;
        a_array[iTmp] = 0;
	}
	// 计算N_MAX(n&2n)等分点处里程到s_array(N_MAX)
	// 计算N_MAX(n&2n)等分点处曲率到p_array(N_MAX)
	// 计算N_MAX(n&2n)等分点处切线方位角到A_array(N_MAX)
	for (iTmp=0; iTmp<(N_MAX-1); iTmp++)
	{	s_array[iTmp] = s_function(s, iTmp+1);
		p_array[iTmp] = p_function(s_array[iTmp]);
		a_array[iTmp] = a_function(p_array[iTmp], s_array[iTmp]);
	}
	// 计算N_MAX/2(n)等分点处切线方位角余弦和sum_n_cos

    for (iTmp=1; iTmp<(N_MAX-1); iTmp=iTmp+2)
	{	
		sum_n_cos = sum_n_cos+cos(rad(a_array[iTmp]));
	}
	// 计算N_MAX(2n)等分点处切线方位角余弦和sum_2n_cos
	
	for (iTmp=0; iTmp<(N_MAX-1); iTmp=iTmp+2)
	{	sum_2n_cos = sum_2n_cos+cos(rad(a_array[iTmp]));
	}
	// 计算N_MAX/2(n)等分点处切线方位角正弦和sum_n_sin
	
    for (iTmp=1; iTmp<(N_MAX-1); iTmp=iTmp+2)
	{	sum_n_sin = sum_n_sin+sin(rad(a_array[iTmp]));
	}
	// 计算N_MAX(2n)等分点处切线方位角正弦和sum_2n_sin
	
	for (iTmp=0; iTmp<(N_MAX-1); iTmp=iTmp+2)
	{	sum_2n_sin = sum_2n_sin+sin(rad(a_array[iTmp]));
	}
	// 计算s处曲率s_p及切线方位角s_a
	
	s_p = p_function(s);
	s_a = a_function(s_p, s);

	// 计算坐标值
	
	if( xy==0 )
	{	return (sx + H / 6 * (cos(rad(sa)) + 4 * sum_2n_cos + 2 * sum_n_cos + cos(rad(s_a))));
	}
	else
	{	return (sy + H / 6 * (sin(rad(sa)) + 4 * sum_2n_sin + 2 * sum_n_sin + sin(rad(s_a))));
	}
}

// 计算里程s坐标方位角A
double zbzs_m_a(double s)
{	double ma;
	ma = a_function(p_function(s), s);
	if (ma>360)
	{	ma = ma-360;
	}
	if (ma<0)
	{	ma = ma+360;
	}
	return ma;
}

// 计算P点坐标px/py对应的里程及偏距
// 点P位置与所在线元共有三种情况（以圆曲线说明）
// 1. 位于线元内侧且位于圆心内侧 或 位于线元外侧
//    且d1(距线元起点法线垂距)小于线元长度采用算法A
// 2. 位于线元内侧且位于圆心外侧采用算法B
// 3. 位于线元外侧且d1距线元超过线元长度采用算法B
double zbfs_s_d(double px, double py, int sd)
{	// 计算线元终点坐标ex/ey及方位角ea
	double ex = zbzs_m_xy(es, 0);
	double ey = zbzs_m_xy(es, 1);
	double ea = zbzs_m_a (es);

	// 计算线元起终点至P点方位角之夹角
	double sa_spa_b = fabs(sa - azimuth(sx, sy, px, py) );
	double ea_epa_b = fabs(ea - azimuth(ex, ey, px, py) );

	double d;
	d = fabs( (py-sy) * cos(rad(sa-90)) - (px-sx) * sin(rad(sa-90)) );

	// 1. 位于线元内侧且位于圆心内侧 或 位于线元外侧
	//    且d1(距线元起点法线垂距)小于线元长度 算法A
	if( sa_spa_b<90 && ea_epa_b>90 && d<=fabs(es-ss) )
	{	double di=0; //定义临时距离di
		double pix=0, piy=0; //定义临时坐标pix,piy

		// 算法A
		///////////////////////////////////////////
		//std::cout << "调用算法A" << std::endl;
		///////////////////////////////////////////
		//(1)定义临时距离di,临时坐标pix,piy
        //(2)以ss+d作为试算里程计算坐标pix,piy
        //(3)计算ss+d处坐标方位角a_ssd
        //(4)计算di=(py-piy)*cos(a_ssd-90)-(px-pix)*sin(a_ssd-90)
        //(5)d=d+di
        //(6)计算ss+d处坐标至pix,piy
        //(7)如abs(di)≤0.001，则反算里程stake=ss+d/偏距distance=(piy-py)/sin(a_ssd-90)，否则重复(3)～(7)
		
		pix = zbzs_m_xy( ss+d, 0); //计算线元+D 坐标x
		piy = zbzs_m_xy( ss+d, 1); //计算线元+D 坐标y

		do
		{	di = (py-piy) * cos(rad( a_function(p_function(ss+d), ss+d )-90 ))  
			   - (px-pix) * sin(rad( a_function(p_function(ss+d), ss+d )-90 ));  //逐步逼近值，直到di小于0.001即是反算点对应的里程

			d = d + di; //d+逐步逼近值
			pix = zbzs_m_xy( ss+d, 0);  //逐步逼近坐标X 
			piy = zbzs_m_xy( ss+d, 1);  //逐步逼近坐标y
			//// DEBUG
			//std::cout << "di = " << di << std::endl;
			//std::cout << "da = " << a_function(p_function(ss+d), ss+d )-90 << std::endl;
			//getchar();
			//// END DEBUG
		}while( fabs(di)>0.001 );

		if( sd==0 )
		{	return ( ss+d );   //里程
		}
		else
		{	return (piy-py) / sin(rad( a_function(p_function(ss+d), ss+d )-90 ));   //偏距
		}

	}
	
	
	// 2. 位于线元内侧且位于圆心外侧 算法B
	// 3. 位于线元外侧且d1距线元超过线元长度 算法B

	else
	{
     //否则采用算法B
     //(1)定义里程s1/s2/s3
     //定义等分处坐标及方位角s2x/s2y/s2a
     //定义P至过s1/s2/s3法线垂距d1/d2/d3
     //(2)若P点至起点法线垂距d1<0.001 返回ss
     //(3)若P点至终点法线垂距d3<0.001 返回es
     //(4)起点里程赋值至s1: s1=ss
     //(5)终点里程赋值至s3: s3=es
     //(6)计算s1与s3中分点处里程s2: s2=0.5*(s3-s1)+s1
     //(7)计算s2处坐标值及方位角： s2x/s2y/s2a
     //(8)计算P点至s2法线垂距d2:  若d2<0.001 返回s2，即stake
     //(9)若d1*d2<0 --> s3=s2，否s1=s2
     //(10)重复(6)～(9)
	 
		double s1, s2, s3;
		double s2x, s2y, s2a;
		double d1, d2, d3;
		//// DEBUG
		//int n=1;
		//std::cout << "调用算法B" << std::endl;
		//// END DEBUG

		d1 = (py-sy) * cos(rad(sa-90)) - (px-sx) * sin(rad(sa-90));

		if( fabs(d1) < 0.001 )
		{	return ss;
		}
		d3 = (py-ey) * cos(rad(ea-90)) - (px-ex) * sin(rad(ea-90));
		if( fabs(d3) < 0.001 )
		{	return es;
		}

		s1 = ss;
		s3 = es;

		do
		{	s2 = 0.5 * (s3 - s1) + s1; //计算线元对中里程
			s2x = zbzs_m_xy( s2, 0 ); //计算线元对中x
			s2y = zbzs_m_xy( s2, 1 ); //计算线元对中y
			s2a = zbzs_m_a ( s2 );  ////计算线元对中点起点切线方位角

			d2 = (py-s2y) * cos(rad( s2a-90 )) - (px-s2x) * sin(rad( s2a-90 ));  

			if( d1*d2 < 0 )
			{	s3 = s2;
			}
			else
			{	s1 = s2;
			}
			//n++;
		}while( fabs(d2)>0.001 );
		//// DEBUG
		//std::cout << "运行次数="<< n <<"\n";
		//// END DEBUG
		if( sd==0 )
		{	return s2;
		}
		else
		{	return (s2y-py) / sin(rad( s2a-90 ));
		}
	}

}

/////////////////
// 外部调用函数
/////////////////
double zbzs_x(double stake, double distance, double angle)
{	return (zbzs_m_xy(stake, 0)+fabs(distance)*cos(rad(zbzs_m_a(stake)+sign(distance)*fabs(angle))));
}

double zbzs_y(double stake, double distance, double angle)
{	return (zbzs_m_xy(stake, 1)+fabs(distance)*sin(rad(zbzs_m_a(stake)+sign(distance)*fabs(angle))));
}

double zbzs_a(double stake, double distance, double angle)
{	double a;
	a = zbzs_m_a(stake)+sign(distance)*fabs(angle);
	if (a>360)
	{	a = a-360;
	}
	if (a<0)
	{	a = a+360;
	}
	return a;
}

double zbfs_s(double px, double py)
{	return zbfs_s_d(px, py, 0);
}

double zbfs_d(double px, double py)
{	return zbfs_s_d(px, py, 1);
}
