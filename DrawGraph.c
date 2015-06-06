#include "headfile.h"
#include "MyFont.h"
void DrawPicture (int x,int y,int width,int height,unsigned char * pGraph)
{
	DISPGRAPH dg;
	dg.x = x; 
	dg.y = y;
	dg.GraphData.width = width;
	dg.GraphData.height = height;
	dg.GraphData.pBitmap = pGraph;
	dg.WriteModify = IMB_WRITEMODIFY_NORMAL;
	dg.WriteKind = IMB_WRITEKIND_OVER;
	Bdisp_WriteGraph_DDVRAM(&dg);
}

void DrawClearBox (int left,int top,int right,int bottom,int sel)
{
	DISPBOX box;
	box.left = left;box.top = top;box.right = right;box.bottom = bottom;
	Bdisp_AreaClr_DDVRAM (&box);
	if(sel)
	{
		Bdisp_DrawLineVRAM (box.left,box.top,box.right,box.top);
		Bdisp_DrawLineVRAM (box.left,box.bottom,box.right,box.bottom);
		Bdisp_DrawLineVRAM (box.left,box.top,box.left,box.bottom);
		Bdisp_DrawLineVRAM (box.right,box.top,box.right,box.bottom);
	}
}

void PrintIcon (int index,char* text,int sel) 
{
	index*=21;
	if (sel)
	{
		PrintXY(index+1+3*(3-strlen(text)),57,(uchar*)text,0);
		//PrintMini(index+1+2*(5-strlen(text)), 59, (uchar*)text,0);
		Bdisp_DrawLineVRAM(index,55,index+19,55);
		Bdisp_DrawLineVRAM(index,55,index,63);
	}
	else
	{
		PrintXY(index+3*(3-strlen(text)),56,(uchar*)text,0);
		//PrintMini(index+2*(5-strlen(text)), 59, (uchar*)text, 0);
		Bdisp_AreaReverseVRAM(index,55,index+19,63);
	}
}

void About()
{
    Bdisp_AllClr_VRAM();
	//PopUpWin (6);
	//PrintChStr("²âÁ¿ÉñÆ÷ÄÚ²â°æ ",22,6);
	PrintXY (50,22,(uchar*)"V1.0",0);
	PrintXY (30,34,(uchar*)"By Wukaibin",0);
	PrintXY (28,46,(uchar*)"QQ:183177496",0);
	WaitKey();
}
void Nodata()
{
	PopUpWin (1);
	PrintXY (16,24,(uchar*)"Sorry! No Data.",0);
	WaitKey();
}

void SQX_ERR()
{
	PopUpWin (1);
	PrintXY (16,24,(uchar*)"SQX Data Error!",0);
	WaitKey();
}
void HP_ERR()
{
	PopUpWin (1);
	
	PrintXY (16,24,(uchar*)"HP Data Error!",0);
	WaitKey();
}

void PQX_ERR()
{
	PopUpWin (1);
	PrintXY (16,24,(uchar*)"PQX Data Error!",0);
	WaitKey();
}

void ReadData_ERR()
{
	PopUpWin (1);
	PrintXY (16,24,(uchar*)"Read Data Error!",0);
	WaitKey();
}