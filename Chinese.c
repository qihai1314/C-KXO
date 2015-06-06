#include "headfile.h"
#include "MyFont.h"

#define IS_CH(C) ((C) & 0x80)
int fh_HZK = 0;

int OpenFont()
{
	FONTCHARACTER FileName[20];
	//CharToFont("\\\\fls0\\HZK12.df",FileName);
    CharToFont("\\\\crd0\\HZK12.df",FileName);
	fh_HZK = Bfile_OpenFile(FileName,_OPENMODE_READ);
	return fh_HZK;
}

int CloseFont()
{
	Bfile_CloseFile(fh_HZK);
	
}


int PrintChChar (unsigned char c1,unsigned char c2,int pX,int pY)
{
	unsigned char mat[12][2];
	int i,j,k;
	int sec,pot; 
	sec = c1-0xa0;
	pot = c2-0xa0;
	Bfile_ReadFile(fh_HZK,mat,24,(94*(sec-1)+(pot-1))*24l);
	DrawPicture (pX,pY,12,12,mat);
}

int PrintChStr (unsigned char *cStr,int pX,int pY)
{
	unsigned int key;
	unsigned char c[]=" ";
	while (*cStr)
	{
		if (IS_CH(*cStr))
		{
			unsigned char c1 = *cStr++,
						  c2 = *cStr;
			PrintChChar(c1,c2,pX,pY);
			++cStr;
			pX +=12;
		}
		else
		{
			c[0]=*(cStr++);
			if (c[0]!='\n')
			{
				PrintXY(pX,pY+3,c,0);
				pX +=6;
			}
		}
	}
	return 0;
}

int PrintChStrV (unsigned char *cStr,int pX,int pY)
{
	unsigned int key;
	unsigned char c[]=" ";
	while (*cStr)
	{
		if (IS_CH(*cStr))
		{
			unsigned char c1 = *cStr++,
						  c2 = *cStr;
			PrintChChar(c1,c2,pX,pY);
			++cStr;
			pY +=16;
		}
		else
		{
			c[0]=*(cStr++);
			if (c[0]!='\n')
			{
				PrintXY(pX,pY+3,c,0);
				pY +=10;
			}
		}
	}
	return 0;
}

