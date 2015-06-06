
typedef struct
{
	double Spacing;				//间距
	double BeginStake;			//起桩
	double PegNo;				//桩号
	double Offset;				//偏距
	double value[4];			//(xa,ya)(xb,yb)
	double distance,position;		//距离、方位
}COMMONDATA;

// “设置”的数据
typedef struct
{
	int point; 	//小数点位数
	char jdfroute_name[13];
	char zdmroute_name[13];
	char route_name[13] ;
	char pmroute_name[13];
}SETUPDATA;


typedef struct
{
	char name[12];
	double jdf_jdzh;
	double jdf_jdx;
	double jdf_jdy;
	double jdf_ls1;
	double jdf_r;
	double jdf_ls2;
	double jdf_qdr;
	double jdf_zdr;

}JDFPOINT;

typedef struct
{
	JDFPOINT *set;
	int size;
}JDFROUTE;



typedef struct
{
	char name[12];
	double qd_zh,zd_zh,xy_x,xy_y,xy_a,xy_v,xy_qr,xy_zr;
}POINT;

typedef struct
{
	double qz;		//起算桩
	double zxz;		//转向值
	double fwj1;
	double jl1;
	POINT *set;		//线元集合，使用下标访问(l.set[n])
					//n从0开始，n最大值为size-1
	int size;		//线元个数
}ROUTE;



typedef struct
{
	char name[12];
	double zdm_bbzh;
    double zdm_bbgc;
    double zdm_r;
    double zdm_zdzh;
}ZDMPOINT;


typedef struct
{
	ZDMPOINT *set;
	int size;
}ZDMROUTE;

typedef struct
{
	char name[12];
	double pm_qk;
    double pm_zk;
    double pm_qx;
	double pm_qy;
	double pm_qfj; 
	double pm_p_x;
	double pm_qr;
	double pm_zr;
}PMPOINT;


typedef struct
{
	PMPOINT *set;
	int size;
}PMROUTE;



typedef struct 
{
	double ls1;	    /*前缓和曲线*/
	double r;	    /*圆曲线半径*/
	double ls2;	    /*后缓和曲线 */
	double p1,p2; 
	double q1,q2;
	double t1,t2;
	double l,e,zhz,hyz,yhz,hzz,zhx,zhy,hzx,hzy;
	POINT point;
}TEMP_POINT;



typedef struct
{
	double zhz;		//直缓点桩号
	double zhx;		//直缓点X坐标
	double zhy;		//直缓点Y坐标
	double qxz;		//圆曲线中桩
	double qxx;		//圆曲线中X坐标
	double qxy;		//圆曲线中y坐标
	double zjz;		//转角值
	double jdj;		//交点间距离
	double jdfwj;	//交点间方位角
}POINTRESULT;


void jdfroute_initial		(JDFROUTE *l);				
void jdfroute_push_back		(JDFROUTE *l);				
void jdfroute_insert		(JDFROUTE *l,int index);	
void jdfroute_del			(JDFROUTE *l,int index);	
void jdfroute_clr			(JDFROUTE *l);


void route_initial		(ROUTE *l);				//初始化线路
void route_push_back	(ROUTE *l);				//在末尾添加一个节点
void route_insert		(ROUTE *l,int index);	//在指定位置插入一个节点
void route_del			(ROUTE *l,int index);	//在指定位置删除一个节点
void route_clr			(ROUTE *l);				//清除所有节点	

void zdmroute_initial		(ZDMROUTE *l);				
void zdmroute_push_back		(ZDMROUTE *l);				
void zdmroute_insert		(ZDMROUTE *l,int index);	
void zdmroute_del			(ZDMROUTE *l,int index);	
void zdmroute_clr			(ZDMROUTE *l);		

void pmroute_initial		(PMROUTE *l);				
void pmroute_push_back		(PMROUTE *l);				
void pmroute_insert		    (PMROUTE *l,int index);	
void pmroute_del			(PMROUTE *l,int index);	
void pmroute_clr			(PMROUTE *l);	
	

	

extern JDFROUTE jdfroute;
extern ROUTE route;
extern ZDMROUTE zdmroute;
extern PMROUTE pmroute;

extern int whether_load;        // point out the file name last load 