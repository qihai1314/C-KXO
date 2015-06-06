#ifndef HEADFILE_H1234
#define HEADFILE_H1234

#include "fxlib.h"
#include "math.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdarg.h"
#include "Parameters_List.h"

typedef unsigned char	uchar;
typedef unsigned int	uint;

typedef struct
{
	double ss;
	double es;
	double sx;
	double sy;
	double sa;
	int v;
	double sp;
	double ep;
}s_pqx;

typedef struct list            //链表结构体
{
	int length;
	s_pqx node;                 // s_pqx新加记得修改
	struct list * next;
}List;

void InitList(List* qList);     //初始化链表
void PushList(List* qList,s_pqx s);  //// s_pqx新加记得修改
s_pqx GetList(List* qList,int index);  //// s_pqx新加记得修改
void push_backList(List* qList);
extern List  l_pqx;




typedef struct
{
	double s_qdk,s_bpk,s_bph,s_qdi,s_zdi,s_r,s_zdk;
}s_sqx;
extern s_sqx l_sqx[19];


typedef struct
{
	double p_qdk,p_qda,p_qdx,p_qdy,p_qdr,p_zdr,p_zdk;
}QXYS;
extern QXYS qxys[2];

typedef struct
{
	double h_qdk,h_qdi,h_zdi,h_zdk,h_zdm;
}HPYS;
extern HPYS hpys[50];

typedef struct{
	double k,xn,ye,fn;
	double d,x1,y1,gch,hpd;
}YSCS;
extern YSCS yscs;

typedef struct{
	int db_dir,db_num;
	int dbp,dbs,dbh;
	double dmor,dmoh,dmod;
}SETUP;
extern SETUP setup;

typedef struct{
	double ks,zsm,zsp,zsh;
}ZFSET;
extern ZFSET zfset;

void PrintDeg(int px,int py,double xx,int sel);                //角度
void PrintFloat(double n,int x,int y,int sel,int digit);       //精度为6~7位有效数字
int  PrintfXY(int x,int y,int sel,const char *cpFormat, ...);  //位置控制
void PrintIcon (int index,char* text,int sel);                 //画图标
void DrawPicture (int x,int y,int width,int height,unsigned char * pGraph);  //画BMP代码图案
void DrawClearBox (int left,int top,int right,int bottom,int sel);            //清除输入框


unsigned int WaitKey ();   //键入按键
int InputString(int x,int y,char *c,int type,int len); // type:0=数字 1=字符 
char GetPressNumChar	(int key);   //获得数字字符
char GetPressChar		(int key);   //获得按键字符

extern const uchar
PIC_MAIN_TITLE					[],
PIC_GC_TITLE					[],
PIC_SD_TITLE					[],
PIC_ZS_TITLE					[],
PIC_SD_SET						[],
PIC_ZS_TOOL						[],
PIC_FS_TOOL						[],
PIC_FS_TITLE					[],
PIC_SELDB						[],
PIC_LCW_SAVE                    [],  
PIC_DK_OPEN                     [],    
PIC_QT_OTHER                    [];   

extern const unsigned char G_graph_MainMenu[];
extern const unsigned char G_ICON_SAVE[];
extern const unsigned char G_ICON_OPEN[];
extern const unsigned char G_ICON_OTHER[];



// File2015.02.08

int TestSRDFile (const char *file_name_c_a);
int DelSRDFile (const char *file_name_c_a);
int SaveSRDFile (const char *file_name_c_a);
int SelectFile (char * file_name);
int SelectFiles (char * file_name);
int CreateDirectory();
int CreateDirectorys();
void SaveIniSRDFile();
int LoadLastDataSRDFile();
int PushIniFile(int index,char s[]);
extern int button; //控制正算界面按F1后默认的按钮值
int PMproduce();



double sd_to_xyaSrd( double stake, double distance, double angle, int xy );
double xy_to_sdSrd( double PX, double PY, int sd );
double zdm_to_gc( double stake);

///////////////////////////
//// Bincommon//////////////

extern const double PI;
void Pol(double a,double b,double x,double y,double *r,double *t);
void CalcPosAndDistance	(double RX,double RY,double BX,double BY,double EP,
						 double *ZH,double *PJ);
void FloatToDegStr (double xx,char *str);
double Point2Distance (POINT *p1,POINT *p2);

///////////////////////////////////////

//extern int mode;
///////////////////////////////////////
// Chinese 
extern int fh_HZK;  //定义一个全局变量
int OpenFont(),CloseFont();  //打开字库，关闭字库
int PrintChChar (unsigned char c1,unsigned char c2,int pX,int pY);
int PrintChStr  (unsigned char *cStr,int pX,int pY);
int PrintChStrV (unsigned char *cStr,int pX,int pY);

void ShowTitle (char *title);  //显示标题


#define	PI	(3.14159265) 
#define	REFRESH_ALL	2        //更新全部  REDRAW_ALL
#define REFRESH_PART	1    //更新部分   REDRAW_PART

//#define BYTE unsigned char
typedef unsigned long       DWORD ;
typedef unsigned char       BYTE ;
typedef unsigned short      WORD ;
typedef unsigned char	      BOOL ;

#define TCHAR char
//typedef int BOOL;

#define TRUE	1   //正确
#define FALSE	0   //错误

BOOL LoadLastDataFile();   //加载上次数据文件开关

FONTCHARACTER * CharToFont(const char *cFileName,FONTCHARACTER *fFileName);
char * FontToChar(const FONTCHARACTER *fFileName,char *cFileName);
int SelectFile (char * file_name);  //选择文件

void ReadData_ERR(); //阅读数据错误开关

int LoadDataFile(char *fname); //加载上次数据文件

extern char szCsvDir[]; //="\\\\crd0\\YS";

//register.c
int CheckReg(); //打开注册开关

//菜单MyMenu.c
//初始化
void MenuInit();
void ListMenu();		//显示菜单，包括标题和提示
int DoMyMenu();			//操作菜单,返回执行的菜单项索引,按退出键时，返回-1

#endif