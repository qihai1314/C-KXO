#ifndef MYFONT_H_1234
#define	MYFONT_H_1234

#ifndef USE_DEMO
  #include "fxlib.h"
#endif

#include "math.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdarg.h"

#ifndef uchar 
   #define uchar	unsigned char
#endif

typedef struct tagCHRDOT_INFO {
	short nChrW;			//字符宽度(像素)
	short nChrH;			//字符高度(像素)
	short nChrNum;			//字符个数
	const uchar *pChrTab;			//字符表指针
	uchar cFirstCode;		//pChrTab=NULL时,用于英文连续编码字符的
	const uchar *pChrDotData;		//字符点阵数据指针
} CHRDOT_INFO;

extern CHRDOT_INFO stHz14x14;
extern CHRDOT_INFO stHz12x12;
extern CHRDOT_INFO stHz8x8;
extern CHRDOT_INFO stAsc6x12;

//置字体反白显示模式
void SetFontReverce(BOOL bReverce);

//设置汉字和英文点阵字库,pHzDotInfo:指向汉字的(没用到就置NULL),pAscDotInfo:指向英文的(没用到就置NULL)
void SetMyFont(CHRDOT_INFO *pHzDotInfo,CHRDOT_INFO *pAscDotInfo);

//显示字符串str,字体由SetMyFont设定
void DispStr(short x,short y,char str[]);
//显示字符串str,最大长度为len(<0则用实际长度),字体由SetMyFont设定
void DispStrN(short x,short y,char str[],short len);

#ifdef USE_DEMO
  #define DrawDot	DispAnyDot
#else
  void DrawDot(int x,int y,int width,int height,unsigned char * pGraph);
#endif


#endif
