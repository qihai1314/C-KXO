#include "headfile.h"
#include "cvs.h"

#define MAX_PATH	250
#define CHR_ZERO	0 

#define COL_PQX_NUM	8
#define COL_SQX_NUM	7
#define COL_HP_NUM	3
#define COL_TOTAL_NUM	(COL_PQX_NUM+COL_SQX_NUM+COL_HP_NUM)	//18
#define MAX_LINECOL_NUM		20

static char TITLE[] = "";

int ReadDataFile (char *fname,char ** text);
int GetNextLineLen(TCHAR *p,BOOL bSetZero);
int GetStrLenFromStr(char * szStr,int nStrPos[],int nStrLen[],int nMaxN,BOOL bSetZero);
BOOL IsWhiteStr(char * p);


int GetNextLineLen(TCHAR *p,BOOL bSetZero)
{
	TCHAR ch;
	int m=0;
	while(1)
	{
		ch=p[m];
		if(ch==0)
			break;
		m++; 
		if(ch==0xd)//13
		{
			if(bSetZero)
				p[m-1]=CHR_ZERO;
			if(p[m]==0xa) // 10
			{
				if(bSetZero)
					p[m]=CHR_ZERO;
				m++; 
			}
			break;
		}
		if(ch==0xa)
		{
			if(bSetZero)
				p[m-1]=CHR_ZERO;
			if(p[m]==0xd) //0a,0d
			{
				if(bSetZero)
					p[m]=CHR_ZERO;
				m++; 
			}
			break;
		}
	}
	return m;
}
/*是否空串(空格串或长度为0的串)*/
BOOL IsWhiteStr(char * p)
{
	while(*p==0x20||*p==0x08) p++; //0x20=20
	if(p[0]==CHR_ZERO)
		return TRUE;
	return FALSE;
}
/*将szStr串中有','号隔开的串位置和长度取出，存于nStrPos[],nStrLen[]中,nMaxN:最多取的个数,返回实际个数*/
int GetStrLenFromStr(char *szStr,int nStrPos[],int nStrLen[],int nMaxN,BOOL bSetZero)
{
	int ln;
	int m=0;
	//	TCHAR ss[MAX_PATH];
	TCHAR *p=(TCHAR *)szStr;
	if(nMaxN<=0)
		return 0;
	
	while(*p==' ') p++;
	ln=strlen(p);
	if(ln==0||ln>MAX_PATH-1)
		return 0;
	for (;;)
	{
		TCHAR *pp=strchr(p,',');
		if(pp)
		{
			ln=pp-p;
		}
		else
		{
			ln=strlen(p); 
			if(ln>0 && p[ln-1]==0x0a) ln--;
		}
		if(bSetZero)
			p[ln]=0;
		nStrPos[m]=p-szStr;
		nStrLen[m]=ln;
		m++;
		if(m>nMaxN)
			return m;
		if(pp==NULL)
			break;
		p=pp+1;
	}
	return m;
}



FONTCHARACTER * char_to_font(const char *cFileName,FONTCHARACTER *fFileName)
{
	int i,len = strlen(cFileName);
	for(i=0; i<len ;++i)
	fFileName[i] = cFileName[i];
	fFileName[i]=0;
	return fFileName;
} 


int ReadDataFile (char *fname,char ** text)  //阅读数据文件
{
	int file_handle;                         //文件处理
	int len;
//	char fff[]="\\\\crd0\\YS\\a\\C1.csv";
	FONTCHARACTER font_file_name[50];
//	char_to_font(fff,font_file_name);
	char_to_font(fname,font_file_name);
	file_handle = Bfile_OpenFile (font_file_name,_OPENMODE_READ);
	if (file_handle<0)
		return -1;
	len = Bfile_GetFileSize (file_handle);
	*text = (char*)malloc(len+1);
	if (*text==0) return 0;
	Bfile_ReadFile (file_handle,*text,len,0);
	Bfile_CloseFile(file_handle);
	(*text)[len] = '\0';
	return 1;
}

int LoadDataFile(char *fname)  //加载数据文件
{
	int i,j1,j2,j3;
	char *text;//,c1[11],c2[8],c3[8],c4[11];
	float fV[COL_TOTAL_NUM];
	char *p,*pp;
	int ln,rn;
	int nStrPos[MAX_LINECOL_NUM],nStrLen[MAX_LINECOL_NUM];
	int cn;
    s_pqx newNode[1];
	BOOL bb,bEndPQX,bEndSQX,bEndHP;
	rn=0;
	Bdisp_AllClr_VRAM();
	i = ReadDataFile (fname,&text); 
	if (i<=0){ 
		PopUpWin(1);	ReadData_ERR();		//PrintChStr (fname+2,2,20);	WaitKey();		
		return 0;
	}

	bEndPQX=FALSE; bEndSQX=FALSE; bEndHP=FALSE;
	j1=0; j2=0; j3=0;
	p=text;
	while(1)
	{
		ln=GetNextLineLen(p,TRUE);
		if(ln==0)
			break;
		cn=GetStrLenFromStr(p,nStrPos,nStrLen,MAX_LINECOL_NUM,TRUE);
// 		ss.Format("%2d,%3d,%2d: ",rn+1,ln,cn); 
// 		strTemp+=ss;
		if(cn>COL_TOTAL_NUM)    //如果cn大于总列数7+7+4=18列
			cn=COL_TOTAL_NUM;   //cn=18
		for (i=0;cn==COL_TOTAL_NUM && i<COL_TOTAL_NUM;i++)	
		{
			pp=p+nStrPos[i];
			bb=IsWhiteStr(pp);
			if(!bb)
				fV[i]=atof(pp); //ss.Format("<%2d>%10.3f",i+1,atof(pp)); 
			if(i<COL_PQX_NUM)	//PQX
			{
				if(bEndPQX)	continue;
				if(bb)	//空行则结束
					bEndPQX=TRUE;
			}
			else if(i<COL_PQX_NUM+COL_SQX_NUM)	//SQX
			{
				if(bEndSQX)	continue;
				if(bb)	//空行则结束
					bEndSQX=TRUE;
			}
			else	//HP
			{
				if(bEndHP) continue;
				if(bb)	//空行则结束
					bEndHP=TRUE;
			}
		}
		if(bEndPQX && bEndSQX && bEndHP)	//结束
			break;
		if(cn==COL_TOTAL_NUM)  //
		{
		    if(!bEndPQX)
		    {
				 
			newNode[0].ss=fV[0];
			newNode[0].es=fV[1];
			newNode[0].sx=fV[2];
			newNode[0].sy=fV[3];
			newNode[0].sa=deg(fV[4]);
			newNode[0].v=fV[5];
			newNode[0].sp=fV[6];
			newNode[0].ep=fV[7];
			
			if (newNode[0].sp < 1e-10)
			{  
		       newNode[0].sp = 0;
		    }
			else
			{  
		       newNode[0].sp = 1 / newNode[0].sp;
			}
			if (newNode[0].ep < 1e-10)
			{  
		       newNode[0].ep=0;
		    }
			else
			{  
               newNode[0].ep = 1 / newNode[0].ep;
			}
			setup.db_num=j1;
			j1++;
			PushList(&l_pqx,newNode[0]);
		    }
			
		    if(!bEndSQX && j2<19)
		    {
			l_sqx[j2].s_qdk=fV[COL_PQX_NUM+0];
			l_sqx[j2].s_bpk=fV[COL_PQX_NUM+1];
			l_sqx[j2].s_bph=fV[COL_PQX_NUM+2];
			l_sqx[j2].s_qdi=fV[COL_PQX_NUM+3];
			l_sqx[j2].s_zdi=fV[COL_PQX_NUM+4];
			l_sqx[j2].s_r=fV[COL_PQX_NUM+5];
			l_sqx[j2].s_zdk=fV[COL_PQX_NUM+6];
			setup.dbs=j2;
			j2++;
		    }
			
		    if(!bEndHP && j3<69)
		    {
			hpys[j3].h_qdk=fV[COL_PQX_NUM+COL_SQX_NUM+0];
			hpys[j3].h_qdi=fV[COL_PQX_NUM+COL_SQX_NUM+1];
			hpys[j3].h_zdi=fV[COL_PQX_NUM+COL_SQX_NUM+2];
			setup.dbh=j3;
			j3++;
		    }
		}
		p+=ln;
		rn++; 
// 		if(rn>=69)
// 			break;
	}
	free(text);	
	if (j1+j2+j3==0)
	{ 
		PopUpWin(1);	Nodata();	return 0;
	}
	return 1;
}


int PQX_disp()
{
	unsigned int key;
	int record,j;
	j=setup.db_num;
	record=setup.db_num;
	while(j>=0){
		Bdisp_AllClr_VRAM();
		ShowTitle(TITLE);
		PrintfXY (3,56,0,"%d",record);                 
		PrintfXY (25,2,0,"QDK = %.4f",(GetList(&l_pqx,record).ss)); 
		PrintfXY (25,11,0,"QDA = %.6f",(GetList(&l_pqx,record).sa));
		PrintfXY (25,20,0,"X = %.4f",(GetList(&l_pqx,record).sx));
		PrintfXY (25,29,0,"Y = %.4f",(GetList(&l_pqx,record).sy));
		PrintfXY (25,38,0,"QDR = %.4f",(GetList(&l_pqx,record).sp));
		PrintfXY (25,47,0,"ZDR = %.4f",(GetList(&l_pqx,record).ep));
		PrintfXY (25,56,0,"ZDK = %.4f",(GetList(&l_pqx,record).v));
	GetKey(&key);
	switch(key){
		case KEY_CTRL_EXIT	:
			j=0;return 1;break;
		case KEY_CTRL_UP	:
			if (record>0){
				--record;	break;	
			}
			if (record<=0){
				record=j;	break;
			}
		case KEY_CTRL_DOWN	:
			if (record<j){
				++record;	break;
			}
			if (record>=j){
				record=0;	break;
			}
	}
}
return 1;	
}

int SQX_disp() 
{
	unsigned int key;
	int record,j;
	j=setup.dbs;
	record=setup.dbs;
	while(j>=0){
		Bdisp_AllClr_VRAM();
		ShowTitle(TITLE);
		PrintfXY (3,56,0,"%d",record);
		PrintfXY (25,2,0,"ZDK = %.3f",l_sqx[record].s_qdk);
		PrintfXY (25,11,0,"BPK = %.3f",l_sqx[record].s_bpk);
		PrintfXY (25,20,0,"BPH = %.3f",l_sqx[record].s_bph);
		PrintfXY (25,29,0,"I1 = %.4f",l_sqx[record].s_qdi);
		PrintfXY (25,38,0,"I2 = %.4f",l_sqx[record].s_zdi);
		
	GetKey(&key);
	switch(key){
		case KEY_CTRL_EXIT	:
			j=0;return 1;break;
		case KEY_CTRL_UP	:
			if (record>0){
				--record;	break;	
			}
			if (record<=0){
				record=j;	break;
			}
		case KEY_CTRL_DOWN	:
			if (record<j){
				++record;	break;
			}
			if (record>=j){
				record=0;	break;
			}
	}
}
return 1;	
}

int HP_disp() 
{
	unsigned int key;
	int record,j,hpbfh;
	j=setup.dbh;
	record=setup.dbh;
	while(j>=0){
		Bdisp_AllClr_VRAM();
		//PrintChStr("横 "	,1,1);  //*********临时撤销
		//PrintChStr("坡 "	,1,14);  //*********临时撤销
		//PrintChStr("参 "	,1,27);  //*********临时撤销
		//PrintChStr("数 "	,1,41);  //*********临时撤销
		ShowTitle(TITLE);
		//PrintChStr("起桩： "	,23,4);   //*********临时撤销
		//PrintChStr("横坡： "	,23,18);   //*********临时撤销
		//PrintChStr("终桩： "	,23,32);   //*********临时撤销
		//PrintChStr("横坡： "	,23,46);   //*********临时撤销
		PrintfXY (4,56,0,"%d",record);
		PrintfXY (55,7,0,"%.3f",hpys[record].h_qdk);
		PrintfXY (55,21,0,"%.4f",hpys[record].h_qdi);	
		PrintfXY (55,34,0,"%.3f",hpys[record].h_zdk);
		PrintfXY (55,49,0,"%.4f",hpys[record].h_zdi);
	GetKey(&key);
	switch(key){
		case KEY_CTRL_EXIT	:
			j=0;return 1;break;
		case KEY_CTRL_UP	:
			if (record>0){
				--record;	break;	
			}
			if (record<=0){
				record=j;	break;
			}
		case KEY_CTRL_DOWN	:
			if (record<j){
				++record;	break;
			}
			if (record>=j){
				record=0;	break;
			}
	}
}
return 1;	
}
