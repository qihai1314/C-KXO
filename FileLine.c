#include <fxlib.h>
//#include "stdafx.h"
#include "fileLine.h"

#ifdef USE_VCDEMO

int Bfile_DeleteFile(const FONTCHARACTER *filename)
{
	return remove(filename);
}
int Bfile_ReadFile(FHANDLE HANDLE, void *buf, int size, int readpos)
{
	fseek(HANDLE,readpos,SEEK_SET);
	return fread(buf,1,size,HANDLE);
}
int Bfile_WriteFile(FHANDLE HANDLE, const void *buf, int size)
{
	return fwrite(buf,1,size,HANDLE);
}

int Bfile_GetFileSize(FHANDLE HANDLE)
{
	int size;
	int old;
	old=ftell (HANDLE);
	fseek (HANDLE, 0, SEEK_END);   // non-portable
    size=ftell (HANDLE);
	fseek (HANDLE, old, SEEK_SET);   // non-portable
	return size;
}
int Bfile_SeekFile(FHANDLE HANDLE, int pos)
{
	return fseek(HANDLE,pos,SEEK_SET);
}

FHANDLE Bfile_OpenFile(const FONTCHARACTER *filename, int mode)
{
	
	FHANDLE pf;
	if(mode==_OPENMODE_READ)
		pf=fopen(filename,"rb");
	else if(mode==_OPENMODE_WRITE)
		pf=fopen(filename,"wb");
	else //if(mode==_OPENMODE_READWRITE)
		pf=fopen(filename,"rb+");
	return pf;
}
int Bfile_CreateFile(const FONTCHARACTER *filename, int size)
{
	char *pbuf;
	FHANDLE fp;
	if(size<0)
		return -1;
	fp=fopen(filename,"w");
	if(fp==NULL)
		return -1;
	if(size>0)
	{
		pbuf=(char *)malloc(size);
		memset(pbuf,0,size);
		fwrite(pbuf,1,size,fp);
		free(pbuf);
	}
	fclose(fp);
	return 0;
}

#endif


#define LINEBUFFER_LEN	512

//返回文件行数,不存在或不成功则返回-1
int GetFileLineNum(const FONTCHARACTER * filename)
{
	char *pbuf;
	int len;
	int rn;
	int mln,sln;
	int fpos;
	char cLastChr;
	int nCurPos,nLinePos;
	int i;
	FHANDLE	hAndle;

	hAndle=Bfile_OpenFile(filename,_OPENMODE_READ);
	if(!IsFileOpenOK(hAndle))
		return -1;
	len=Bfile_GetFileSize(hAndle);
	if(len==0)
	{
		Bfile_CloseFile(hAndle);
		return 0;
	}
	pbuf=(char *)malloc(LINEBUFFER_LEN);
	if(pbuf==NULL)
	{
		Bfile_CloseFile(hAndle);
		return -1;
	}

	rn=0; fpos=0;
	sln=len;
	nCurPos=0; nLinePos=0;
	cLastChr=0;

	for(;sln>0;sln-=LINEBUFFER_LEN,fpos+=LINEBUFFER_LEN)
	{
		mln=sln;
		if(sln>=LINEBUFFER_LEN)
			mln=LINEBUFFER_LEN;
		Bfile_ReadFile(hAndle,pbuf,mln,fpos);	//读一块内容到缓冲pbuf

		for(i=0;i<mln;i++,nCurPos++)
		{
			if(cLastChr==0x0D && pbuf[i]==0x0A)
			{
				cLastChr=0x0C;	//置0d0a标志
			}
			else
			{
				if(cLastChr==0x0D||cLastChr==0x0A||cLastChr==0x0C)	//0d0a,0d,0a 这样的都算一行
				{
					nLinePos=nCurPos;	//下一行的位置
					rn++;				//加1行
				}
				cLastChr=0;				//清标志
				if(pbuf[i]==0x0D||pbuf[i]==0x0A)
					cLastChr=pbuf[i];	//置标志
			}
		}
	}
	if(nCurPos!=0)	//最后一行加上
	{
//		nLinePos=nCurPos;	//下一行的位置
		rn++;				//加1行
	}
	free(pbuf);
	return rn;
}

//读文件filename行nLineNo(0~)内容,存于cBuf[],最多读入长度nMaxLen,OK则返回读入的行长度,不存在或不成功则返回-1
int ReadFileLine(const FONTCHARACTER * filename,int nLineNo,char cBuf[],int nMaxLen)
{
	char *pbuf;
	int len;
	int rn;
	int mln,sln;
	int fpos;
	char cLastChr;
	int nCurPos,nLinePos;
	int i;
	FHANDLE	hAndle;
	BOOLL bFind=FALSE;

	if(nLineNo<0 || cBuf==NULL || nMaxLen<=0)
		return -1;

	cBuf[0]=0;
	hAndle=Bfile_OpenFile(filename,_OPENMODE_READ);
	if(!IsFileOpenOK(hAndle))
		return -1;
	len=Bfile_GetFileSize(hAndle);
	if(len==0)
	{
		Bfile_CloseFile(hAndle);
		return 0;
	}
	pbuf=(char *)malloc(LINEBUFFER_LEN);
	if(pbuf==NULL)
	{
		Bfile_CloseFile(hAndle);
		return -1;
	}
	
	rn=0; fpos=0;
	sln=len;
	nCurPos=0; nLinePos=0;
	cLastChr=0;

	for(;sln>0;sln-=LINEBUFFER_LEN,fpos+=LINEBUFFER_LEN)
	{
		mln=sln;
		if(sln>=LINEBUFFER_LEN)
			mln=LINEBUFFER_LEN;
		Bfile_ReadFile(hAndle,pbuf,mln,fpos);	//读一块内容到缓冲pbuf
		
		for(i=0;i<mln;i++,nCurPos++)
		{
			if(cLastChr==0x0D && pbuf[i]==0x0A)
			{
				cLastChr=0x0C;	//置0d0a标志
			}
			else
			{
				if(cLastChr==0x0D||cLastChr==0x0A||cLastChr==0x0C)	//0d0a,0d,0a 这样的都算一行
				{
					if(rn==nLineNo)
						bFind=TRUE;
					else
						nLinePos=nCurPos;	//下一行的位置
					rn++;				//加1行
				}
				cLastChr=0;				//清标志
				if(pbuf[i]==0x0D||pbuf[i]==0x0A)
					cLastChr=pbuf[i];	//置标志
			}
			if(bFind)
				break;
		}
		if(bFind)
			break;
	}
	if(nCurPos!=0 && nCurPos==len)	//最后一行加上
	{
//		nLinePos=nCurPos;	//下一行的位置
		if(rn==nLineNo)
			bFind=TRUE;
		rn++;				//加1行
	}
	free(pbuf);
	mln=-1;
	if(bFind)
	{
		mln=nCurPos-nLinePos;
		if(mln>nMaxLen)
			mln=nMaxLen;
		Bfile_ReadFile(hAndle,cBuf,mln,nLinePos);	//读一行内容到缓冲cbuf
		cBuf[mln]=0;
	}
	Bfile_CloseFile(hAndle);
	return mln;
}
//写文件filename行nLineNo(0~)内容cBuf[],OK则返回写入的行序号(0~),不成功则返回-1
int WriteFileLine(const FONTCHARACTER * filename,int nLineNo,char cBuf[])
{
	char *pbuf;
	int len;
	int rn;
	int mln;
	int i;
	int ln; 
	char lfcr[3]={0x0d,0x0a,0x0};
	BOOLL bCreateNew=FALSE;
	FHANDLE	hAndle;
	char *pp,*plast;
	char *pLinePos;
	int nLineLen;
	BOOLL bEquLenLine;
	int m,npos;

	if(nLineNo<0 || cBuf==NULL)
		return -1;
	ln=strlen(cBuf);

	mln=0;
	if(ln==0 || cBuf[ln-1]!=0x0A)	//加0d0a转行符
		mln=2;

	hAndle=Bfile_OpenFile(filename,_OPENMODE_READ); //WRITE
	if(!IsFileOpenOK(hAndle))	//不存在则建立
	{
		bCreateNew=TRUE;
	}
	else //if(!bCreateNew)
	{
		//存在则读入内存处理
		len=Bfile_GetFileSize(hAndle);
		if(len==0)	//空文件
		{
			Bfile_CloseFile(hAndle);
			Bfile_DeleteFile(filename);
			bCreateNew=TRUE;
		}
	}
	if(bCreateNew)	//建立新文件
	{
		if(Bfile_CreateFile(filename,ln+mln)<0)	//建立一个文件，如失败则返回
			return -1;
		hAndle=Bfile_OpenFile(filename,_OPENMODE_WRITE);
		if(!IsFileOpenOK(hAndle))	//不存在则返回
			return -1;
		Bfile_SeekFile(hAndle,0);
		Bfile_WriteFile(hAndle,cBuf,ln);
		if(mln==2)
			Bfile_WriteFile(hAndle,lfcr,mln);
		Bfile_CloseFile(hAndle);
		return 0;
	}
	//文件存在，则读入处理再进行重写
	pbuf=(char *)malloc(len+ln+mln+2);	//用文件长度和要写入的行长度总长申请内存
	if(pbuf==NULL)
	{
		Bfile_CloseFile(hAndle);
		return -1;
	}
	Bfile_ReadFile(hAndle,pbuf,len,0);

	rn=0;
	pp=pbuf; plast=pbuf;
	bEquLenLine=FALSE;
	while(1)
	{
		if(*pp==0x0d||*pp==0x0a)
		{
			if(*pp==0x0d && pp+1<pbuf+len && pp[1]==0x0a)	//0d,0a 算一行
			{
				pp++;
			}
			if(rn==nLineNo)
			{
				pLinePos=plast;
				nLineLen=pp+1-plast;
				if(nLineLen==ln+mln)	//等长行则直接写操作
				{
					bEquLenLine=TRUE; break;
				}
			}
			plast=pp+1;		//下一行的位置
			rn++;	//0d0a,0d,0a 这样的都算一行
		}
		pp++;
		if(pp>=pbuf+len)
			break;
	}
	if(plast<pbuf+len && !bEquLenLine)	//最后没换行符的算一行
	{
		if(rn==nLineNo)
		{
			pLinePos=plast;
			nLineLen=pbuf+len-plast;
			if(nLineLen==ln+mln)	//等长行则直接写操作
			{
				bEquLenLine=TRUE;
			}
		}
		rn++;
	}
	if(bEquLenLine)
	{
	Bfile_SeekFile(hAndle,pLinePos-pbuf);
		Bfile_WriteFile(hAndle,cBuf,ln);
		if(mln==2)
			Bfile_WriteFile(hAndle,lfcr,2);
		Bfile_CloseFile(hAndle);
		free(pbuf);
		return nLineNo; 
	}
	Bfile_CloseFile(hAndle);
	Bfile_DeleteFile(filename);
	if(nLineNo>=rn)	//在最后加
	{
		if(pbuf[len-1]!=0x0a)
		{
			pbuf[len++]=0x0d; pbuf[len++]=0x0a;
		}
		npos=len; len=len+ln+mln;
		nLineNo=rn;
	}
	else
	{
		npos=pLinePos-pbuf+nLineLen;
		m=ln+mln-nLineLen;
		if(m>=0)	//增加
		{
			for (i=len+m-1; m!=0 && i>=npos;i--)
			{
				pbuf[i]=pbuf[i-m];
			}
			len+=m;
		}
		else
		{
			m=-m;
			for (i=npos;i<len;i++)
			{
				pbuf[i-m]=pbuf[i];
			}
			len-=m;
		}
		if(pbuf[len-1]!=0x0a)	//最后没转行符，则加上
		{
			pbuf[len++]=0x0d; pbuf[len++]=0x0a;
		}
		npos=pLinePos-pbuf;
	}
	for (i=0;i<ln;i++)
	{
		pbuf[npos++]=cBuf[i];
	}
	if(mln==2)
	{
		pbuf[npos++]=0x0d; pbuf[npos++]=0x0a;
	}
	if(Bfile_CreateFile(filename,len)<0)
	{
		free(pbuf);
		return -1;
	}
	hAndle=Bfile_OpenFile(filename,_OPENMODE_WRITE);
	if(!IsFileOpenOK(hAndle))	//不存在则返回
	{
		free(pbuf);
		return -1;
	}
	Bfile_SeekFile(hAndle,0);
	Bfile_WriteFile(hAndle,pbuf,len);
	Bfile_CloseFile(hAndle);
	free(pbuf);
	return nLineNo;
}

//写文件filename的量szSect[]=内容cBuf[],OK则返回写入的行序号(0~),不成功则返回-1,如 "A=123" ,szSect[]="A", cBuf[]="123"
int WriteIniLine(const FONTCHARACTER * filename,char szSect[],char cBuf[])
{
	char *pbuf;
	int len;
	int rn;
	int mln;//,sln;
//	int fpos;
//	char cLastChr;
	int wlen;
	int i;
	BOOLL bCreateNew;
	char equchr[]="=";
	char lfcr[3]={0x0d,0x0a,0x0};
	FHANDLE	hAndle;
	int nLineNo=-1;
	char *pp,*plast;
	char *pLinePos;
	int nLineLen;
	BOOLL bEquLenLine;
	int m,npos;
	int l1,ln;

	if(filename==NULL || szSect==NULL || cBuf==NULL)
		return -1;

	l1=strlen(szSect); ln=strlen(cBuf);
	mln=0;
	if(ln==0 || cBuf[ln-1]!=0x0A)	//加0d0a转行符
		mln=2;
	wlen=l1+1+ln+mln;	//要写入的行长度

	bCreateNew=FALSE;

	hAndle=Bfile_OpenFile(filename,_OPENMODE_READ);//WRITE);
	if(!IsFileOpenOK(hAndle))	//不存在则建立
	{
		bCreateNew=TRUE;
	}
	else //if(!bCreateNew)
	{
		//存在则读入内存处理
		len=Bfile_GetFileSize(hAndle);
		if(len==0)	//空文件
		{
			Bfile_CloseFile(hAndle);
			Bfile_DeleteFile(filename);
			bCreateNew=TRUE;
		}
	}
	if(bCreateNew)	//建立新文件
	{
		if(Bfile_CreateFile(filename,wlen)<0)	//建立一个文件，如失败则返回
			return -1;
		hAndle=Bfile_OpenFile(filename,_OPENMODE_WRITE);
		if(!IsFileOpenOK(hAndle))	//不存在则返回
			return -1;
		Bfile_SeekFile(hAndle,0);
		Bfile_WriteFile(hAndle,szSect,l1);
		Bfile_WriteFile(hAndle,equchr,1);	//"="
		Bfile_WriteFile(hAndle,cBuf,ln);
		if(mln==2)
			Bfile_WriteFile(hAndle,lfcr,mln);
		Bfile_CloseFile(hAndle);
		return 0;
	}
	//文件存在，则读入处理再进行重写
	pbuf=(char *)malloc(len+wlen+2);	//用文件长度和要写入的行长度总长申请内存
	if(pbuf==NULL)
	{
		Bfile_CloseFile(hAndle);
		return -1;
	}
	Bfile_ReadFile(hAndle,pbuf,len,0);

	rn=0;
	pp=pbuf; plast=pbuf;
	bEquLenLine=FALSE;
	while(1)
	{
		if(*pp==0x0d||*pp==0x0a)
		{
			if(*pp==0x0d && pp+1<pbuf+len && pp[1]==0x0a)	//0d,0a 算一行
			{
				pp++;
			}
			if(pp+1-plast>=l1+1 && strncmp(szSect,plast,l1)==0 && plast[l1]=='=') //rn==nLineNo)
			{
				nLineNo=rn;
				pLinePos=plast;
				nLineLen=pp+1-plast;
				if(nLineLen==wlen)	//等长行则直接写操作
				{
					bEquLenLine=TRUE; break;
				}
			}
			plast=pp+1;		//下一行的位置
			rn++;	//0d0a,0d,0a 这样的都算一行
		}
		pp++;
		if(pp>=pbuf+len)
			break;
	}
	if(plast<pbuf+len && !bEquLenLine)	//最后没换行符的算一行
	{
		//if(rn==nLineNo)
		if(pp+1-plast>=l1+1 && strncmp(szSect,plast,l1)==0 && plast[l1]=='=') //rn==nLineNo)
		{
			nLineNo=rn;
			pLinePos=plast;
			nLineLen=pbuf+len-plast;
			if(nLineLen==wlen)	//等长行则直接写操作
			{
				bEquLenLine=TRUE;
			}
		}
		rn++;
	}
	if(bEquLenLine)
	{
/*		Bfile_SeekFile(hAndle,pLinePos-pbuf);
		Bfile_WriteFile(hAndle,szSect,l1);
		Bfile_WriteFile(hAndle,equchr,1);	//"="
		Bfile_WriteFile(hAndle,cBuf,ln);
		if(mln==2)
			Bfile_WriteFile(hAndle,lfcr,2);
		Bfile_CloseFile(hAndle);
		free(pbuf);
		return nLineNo;
*/
	}
	Bfile_CloseFile(hAndle);
	Bfile_DeleteFile(filename);
	if(nLineNo==-1)	//没找到，也就在最后加
	{
		if(pbuf[len-1]!=0x0a)
		{
			pbuf[len++]=0x0d; pbuf[len++]=0x0a;
		}
		npos=len; len=len+wlen;
		nLineNo=rn;
	}
	else
	{
		npos=pLinePos-pbuf+nLineLen;
		m=wlen-nLineLen;
		if(m>=0)	//增加
		{
			for (i=len+m-1; m!=0 && i>=npos;i--)
			{
				pbuf[i]=pbuf[i-m];
			}
			len+=m;
		}
		else
		{
			m=-m;
			for (i=npos;i<len;i++)
			{
				pbuf[i-m]=pbuf[i];
			}
			len-=m;
		}
		npos=pLinePos-pbuf;
	}
	for (i=0;i<l1;i++)
	{
		pbuf[npos++]=szSect[i];
	}
	pbuf[npos++]=equchr[0];
	for (i=0;i<ln;i++)
	{
		pbuf[npos++]=cBuf[i];
	}
	if(mln==2)
	{
		pbuf[npos++]=0x0d; pbuf[npos++]=0x0a;
	}
	if(len>0 && pbuf[len-1]!=0x0a)	//最后没转行符，则加上
	{
		pbuf[len++]=0x0d; pbuf[len++]=0x0a;
		// 			CString ss;	ss.Format("%d,%d",len,m); MessageBox(NULL,ss,NULL,MB_OK);
	}

	if(Bfile_CreateFile(filename,len)<0)
	{
		free(pbuf);
		return -1;
	}
	hAndle=Bfile_OpenFile(filename,_OPENMODE_WRITE);
	if(!IsFileOpenOK(hAndle))	//不存在则返回
	{
		free(pbuf);
		return -1;
	}
	Bfile_SeekFile(hAndle,0);
	Bfile_WriteFile(hAndle,pbuf,len);
	Bfile_CloseFile(hAndle);
	free(pbuf);
	return nLineNo;
}

//读文件filename的量szSect[]=内容到cBuf[],OK则返回读入实际长度,不成功则返回-1,如 "A=123" ,szSect[]="A", cBuf[]="123"
int ReadIniLine(const FONTCHARACTER * filename,char szSect[],char cBuf[],int nMaxLen)
{
	char *pbuf;
	char *pp,*plast;
	int i,len;
	int rn=0;
	FHANDLE	hAndle;

	int l1;
	char equchr[]="=";
	BOOLL bFindLine=FALSE;
	int nLineNo=-1;
	int nLineLen;
	char *pLinePos=NULL;

	if(filename==NULL || szSect==NULL || cBuf==NULL|| nMaxLen<=0)
		return -1;

	hAndle=Bfile_OpenFile(filename,_OPENMODE_READ);
	if(!IsFileOpenOK(hAndle))
		return -1;

	l1=strlen(szSect);
	cBuf[0]=0;
	len=Bfile_GetFileSize(hAndle);
	if(len==0)
	{
		Bfile_CloseFile(hAndle);
		return 0;
	}
	pbuf=(char *)malloc(len);
	if(pbuf==NULL)
	{
		Bfile_CloseFile(hAndle);
		return -1;
	}
	Bfile_ReadFile(hAndle,pbuf,len,0);

	pp=pbuf; plast=pbuf;
	while(1)
	{
		if(*pp==0x0d||*pp==0x0a)
		{
			if(*pp==0x0d && pp+1<pbuf+len && pp[1]==0x0a)	//0d,0a 算一行
			{
				pp++;
			}
			if(pp+1-plast>=l1+1 && strncmp(szSect,plast,l1)==0 && plast[l1]=='=') //rn==nLineNo)
			{
				nLineNo=rn;
				pLinePos=plast;
				nLineLen=pp+1-plast;
				bFindLine=TRUE; break;
			}
			rn++;	//0d0a,0d,0a 这样的都算一行
			plast=pp+1;		//下一行的位置
		}
		pp++;
		if(pp>=pbuf+len)
			break;
	}

	if(plast<pbuf+len && !bFindLine)	//最后没换行符的算一行
	{
		if(pp+1-plast>=l1+1 && strncmp(szSect,plast,l1)==0 && plast[l1]=='=') //rn==nLineNo)
		{
			nLineNo=rn;
			pLinePos=plast;
			nLineLen=pp+1-plast;
			bFindLine=TRUE; 
		}
		rn++;
	}
	if(bFindLine)
	{
		if(nLineLen>=1 && (pLinePos[nLineLen-1]==0x0a||pLinePos[nLineLen-1]==0x0d))
			nLineLen--;
		if(nLineLen>=1 && (pLinePos[nLineLen-1]==0x0a||pLinePos[nLineLen-1]==0x0d))
			nLineLen--;
		nLineLen-=l1; nLineLen--;
		if(nMaxLen>nLineLen)
			nMaxLen=nLineLen;
		if(nMaxLen<0)
			nMaxLen=0;
		for (i=0;i<nMaxLen;i++)
		{
			cBuf[i]=pLinePos[l1+1+i];
		}
		cBuf[nMaxLen]=0;
		return nMaxLen;
	}
	else
		nMaxLen=-1;
	free(pbuf);
	Bfile_CloseFile(hAndle);
	return nMaxLen;
}

