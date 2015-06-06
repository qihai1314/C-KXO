#ifndef ZBZS_H
#define ZBZS_H

#define N_MAX 16

extern double ss;	// 起点桩号
extern double es;	// 终点桩号
extern double sx;	// 起点坐标X
extern double sy;	// 终点坐标Y
extern double sa;	// 起点坐标方位角(DEG)
extern int v;		// 线元转向,右转为1,左转为-1
extern double sp;	// 线元起点曲率,直线为0,圆曲线为1/R
extern double ep;	// 线元终点曲率,直线为0,圆曲线为1/R

	// 计算等分点处桩号
	// 计算n等分处时n取2,4,6..
	// 计算2n等分处时n取1,3,5...
	extern double s_function(double s, int n);
	// 计算里程s处曲率
	extern double p_function(double s);
	// 计算里程s处切线方位角(DEG)
	extern double a_function(double p, double s);

	// 计算里程s处坐标X/Y及坐标方位角A(DEG)
	extern double zbzs_m_xy(double s, int xy);
	extern double zbzs_m_a(double s);
	// 计算坐标X/Y对应的里程及偏距
	extern double zbfs_s_d(double px, double py, int sd);
//
//public:
//	// 构造函数，数据初始化
   extern  void intialCZb(double,double ,double ,double,double,int,double,double);
//	
//	~CZb(void);
//	
	// 计算里程stake/偏距distance/角度angle处的坐标及坐标方位角(DEG)
	extern double zbzs_x(double stake, double distance,double angle);
	extern double zbzs_y(double stake, double distance,double angle);
	extern double zbzs_a(double stake, double distance,double angle);
	// 计算坐标为px/py处的里程及偏距
	extern double zbfs_s(double px, double py);
	extern double zbfs_d(double px, double py);
#endif // ZBZS_H
