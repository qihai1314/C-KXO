#ifndef USE_DEMO
  #include "headfile.h"
#endif
#include "MyFont.h"

short FindCh(uchar cc);
short FindHz(uchar c1,uchar c2);

#include "MyFontDot.inc"

CHRDOT_INFO stHz14x14={
	14,14,					//点阵大小12x12
	sizeof(HzTab14x14)/2,	//字符个数
	HzTab14x14,				//12x12点阵汉字表
	0,						//这里忽略
	HzDot14x14				//12x12点阵数据指针
};


CHRDOT_INFO stHz12x12={
	12,12,					//点阵大小12x12
	sizeof(HzTab12x12)/2,	//字符个数
	HzTab12x12,				//12x12点阵汉字表
	0,						//这里忽略
	HzDot12x12				//12x12点阵数据指针
};



CHRDOT_INFO stHz8x8={
	8,8,					//点阵大小8x8
	sizeof(HzTab8x8)/2,	    //字符个数
	HzTab8x8,				//8x8点阵汉字表
	0,						//这里忽略
	HzDot8x8				//8x8点阵数据指针
};


CHRDOT_INFO stAsc6x12={
	6,12,					//点阵大小6x12
	96,						//字符个数
	NULL,					//这里因是连续的,不用字符表
	0x20,					//从ASCII=0x20开始
	AscDot6x12				//12x12点阵数据指针
};


CHRDOT_INFO *g_pCurHzDotInfo=NULL;		//当前汉字点阵信息指针
CHRDOT_INFO *g_pCurAscDotInfo=NULL;		//当前英文点阵信息指针

BOOL s_bReverce=FALSE;

//置字体反白显示模式
void SetFontReverce(BOOL bReverce)
{
	s_bReverce=bReverce;
}

//设置汉字和英文点阵字库,pHzDotInfo:指向汉字的,pAscDotInfo:指向英文的
void SetMyFont(CHRDOT_INFO *pHzDotInfo,CHRDOT_INFO *pAscDotInfo)
{
	g_pCurHzDotInfo=pHzDotInfo;
	g_pCurAscDotInfo=pAscDotInfo;
}
//显示字符串str,字体由SetMyFont设定
void DispStr(short x,short y,char str[])
{
	DispStrN(x,y,str,-1);
}
//显示字符串str,最大长度为len(<0则用实际长度),字体由SetMyFont设定
void DispStrN(short x,short y,char str[],short len)
{
	uchar c,j;
	short i,cx,idx,ln;
	long lpos;
	CHRDOT_INFO *pstCI;
	if(len<0)
		len=strlen(str);
	j=0;
	cx=x;
	for(i=0;i<len;i++)
	{
		c=(uchar)str[i];
		if(c==0) 
			break;
		if(c<128) 
		{ 
			j=0;
			idx=FindCh(c);
			pstCI=g_pCurAscDotInfo;
//			DispCh(c); 
		}
		else if(j!=0 && (uchar)str[i-1]>127)
		{
			j=0;
			idx=FindHz((uchar)str[i-1],c);
			pstCI=g_pCurHzDotInfo;
//			DispHz(c); 
		}
		else
		{	j=1; continue; }
		if(pstCI==NULL)
			continue;
		if(idx<0)
		{
			idx=FindCh('?');		//if not find ,use '?' to replace
			pstCI=g_pCurAscDotInfo;
		}
		if(idx>=0 && pstCI!=NULL)
		{
			ln=(pstCI->nChrW+7)/8*pstCI->nChrH;
			lpos=idx;
			lpos=lpos*ln;	//计算点阵位置=索引*每字符点阵字节数	
			DrawDot(cx,y,pstCI->nChrW,pstCI->nChrH,(uchar *)pstCI->pChrDotData+lpos);
		}
		cx+=pstCI->nChrW;
	}
}

//显示字符串str,字体由SetMyFont设定
short FindHz(uchar c1,uchar c2)
{
	short i;
	short j=0;
	if(g_pCurHzDotInfo==NULL||g_pCurHzDotInfo->nChrNum<=0||g_pCurHzDotInfo->pChrTab==NULL||g_pCurHzDotInfo->pChrDotData==NULL)
		return -1;
	for (i=0;i<g_pCurHzDotInfo->nChrNum;i++,j+=2)
	{
		if(c1==g_pCurHzDotInfo->pChrTab[j] && c2==g_pCurHzDotInfo->pChrTab[j+1])
			return i;
	}
	return -1;
}

//在当前使用的点阵字库中,找代码为cc的英文索引,没有则返回-1
short FindCh(uchar cc)
{
	short i;
	short j=0;
	if(g_pCurAscDotInfo==NULL||g_pCurAscDotInfo->nChrNum<=0||g_pCurAscDotInfo->pChrDotData==NULL)
		return -1;
	if(g_pCurAscDotInfo->pChrTab==NULL)	//
	{
		if(cc<g_pCurAscDotInfo->cFirstCode)
			return -1;
		return cc-g_pCurAscDotInfo->cFirstCode;
	}
	for (i=0;i<g_pCurAscDotInfo->nChrNum;i++)
	{
		if(cc==g_pCurAscDotInfo->pChrTab[i])
			return i;
	}
	return -1;
}
#ifndef USE_DEMO
void DrawDot(int x,int y,int width,int height,unsigned char * pGraph)
{
	DISPGRAPH dg;
	dg.x = x; 
	dg.y = y;
	dg.GraphData.width = width;
	dg.GraphData.height = height;
	dg.GraphData.pBitmap = pGraph;
	dg.WriteModify = s_bReverce?IMB_WRITEMODIFY_REVERCE:IMB_WRITEMODIFY_NORMAL;
	dg.WriteKind = IMB_WRITEKIND_OVER;
	Bdisp_WriteGraph_DDVRAM(&dg);
}
#endif

