#include "headfile.h"
#include "runmain.h"
#include "MyFont.h"


static char TITLE[] = "常用";

#define MODE_INPUT_2_POINT 1
#define MODE_INPUT_JJQZ 2
#define MODE_INPUT_ZH 3
#define MODE_INPUT_REAL 4
#define MODE_INPUT_P_AND_D 5
#define MODE_DISP_P 6



///////////////////////////////////////////
// 	F1 Commonly used
///////////////////////////////////////////
int Menu_Draw1()
{   
    int i=0;
    char *context[] = 
	{"反算 ","正算 ",};
	SetMyFont(&stHz8x8,&stAsc6x12); //设置中文大小8*8 
	DispStr(4,56,context[0]); 
	DispStr(24,56,context[1]); 
	PrintIcon(i++,"",mode<=MODE_INPUT_REAL);
	PrintIcon(i++,"",mode>MODE_INPUT_REAL && mode<=MODE_DISP_P);
	//PrintIcon(i++,"",0);
	//PrintIcon(i++,"",0);
	//PrintIcon(5,"?",0);
}

void Menu_Proc1()
{
	switch (key)
	{
		case KEY_CTRL_F1:mode=MODE_INPUT_2_POINT;break;
		case KEY_CTRL_F2:mode=MODE_INPUT_P_AND_D;break;
		case KEY_CTRL_F3:break;
		case KEY_CTRL_F4:break;
		case KEY_CTRL_F6:break;
	}
}
void Run_F1_FanSuan ()
{
	double x,y;
	int i;
	if (mode == MODE_INPUT_2_POINT)
	{
	    char *context[] = 
	   {"起点X ","起点Y ","终点X ","终点Y "};
		index = 0;
		need_redraw = REFRESH_ALL;
		while(mode == MODE_INPUT_2_POINT)
		{
			//// REDRAW
			if (need_redraw==REFRESH_ALL)
			{
				Bdisp_AllClr_DDVRAM();
				i = 0;
				SetMyFont(&stHz12x12,&stAsc6x12);  //定义字体大小
			    DispStr(2,1, "直 ");
			    DispStr(2,15,"线 ");
			    DispStr(2,28,"两 ");
			    DispStr(2,41,"点 ");
				ShowTitle(TITLE);
				
				for (i=0;i<4;++i)
				DispStr(16,4+i*12,context[i]);
				
				need_redraw = REFRESH_PART;
				Menu_Draw1();
			}
			if (need_redraw==REFRESH_PART)
			{
				for(i=0;i<4;++i)
					PrintFloat(value[i],50,4+i*12,index==i,setup_data.point);
				need_redraw = 0;
			}
			GetKey(&key);
			Menu_Proc1();
			if (key==KEY_CTRL_EXE)
			{
				mode = MODE_INPUT_JJQZ;
			}
			InputDefProc(value,4,50,4,MODE_INPUT_JJQZ,MODE_EXIT);
		}

	}
	///// Calculate and input Jian ju
	if (mode == MODE_INPUT_JJQZ)
	{
		char *context[] = 
		{"距离:","方位: ","间距 ","起桩 "};
		index = 0;
		need_redraw = REFRESH_ALL;
		Pol(value[0],value[1],value[2],value[3],&common_data.distance,&common_data.position);
		while(mode==MODE_INPUT_JJQZ)
		{
				
			if (need_redraw == REFRESH_ALL)
			{
				char strpos[20];
				Bdisp_AllClr_DDVRAM();
				SetMyFont(&stHz12x12,&stAsc6x12); 
				DispStr(2,1, "直 ");
			    DispStr(2,15,"线 ");
			    DispStr(2,28,"两 ");
			    DispStr(2,41,"点 ");
				ShowTitle(TITLE);
				for (i=0;i<4;++i)
				DispStr(16,4+i*12,context[i]);
				i=0;
				FloatToDegStr(common_data.position,strpos);
				PrintFloat(common_data.distance,50,4+i++*12,0,setup_data.point);
				PrintXY(52,6+i++*12,strpos,0);
				need_redraw = REFRESH_PART;
				Menu_Draw1();
			}
			if (need_redraw==REFRESH_PART)
			{
				i = 2;
				PrintFloat(common_data.Spacing,50,4+i++*12,index==0,setup_data.point);
				PrintFloat(common_data.BeginStake,50,4+i++*12,index==1,setup_data.point);
				need_redraw = 0;
			}
			GetKey(&key);
			Menu_Proc1();
			if (key==KEY_CTRL_EXE)
			{
				mode = MODE_INPUT_ZH;
			}
			InputDefProc((double*)(& common_data),2,50,28,MODE_INPUT_ZH,MODE_INPUT_2_POINT);
		}
	}//if
	if (mode == MODE_INPUT_ZH)
	{
		char *context[] = 
		{"桩号 ","偏距 ","坐标X:","坐标Y:"};
		int prekey = 0;
		index = 0;
		need_redraw = REFRESH_ALL;
		while(mode==MODE_INPUT_ZH)
		{
			if (need_redraw == REFRESH_ALL)
			{
			    SetMyFont(&stHz12x12,&stAsc6x12); 
				Bdisp_AllClr_DDVRAM();
				DispStr(2,1, "直 ");
			    DispStr(2,15,"线 ");
			    DispStr(2,28,"两 ");
			    DispStr(2,41,"点 ");
				ShowTitle(TITLE);
				for (i=0;i<4;++i)
				DispStr(16,4+i*12,context[i]);
				Menu_Draw1();
				//ShowArrow(1);//////////////////////////////////////////////////////////
				need_redraw = REFRESH_PART;
			}
			if (need_redraw==REFRESH_PART)
			{
				x = value[0]+(common_data.PegNo-common_data.BeginStake)*
					cos(common_data.position*PI/180.0)
					+common_data.Offset*cos(common_data.position*PI/180.0+PI/2);
				y = value[1]+(common_data.PegNo-common_data.BeginStake)*
					sin(common_data.position*PI/180.0)
					+common_data.Offset*sin(common_data.position*PI/180.0+PI/2);
				i = 0;
				PrintFloat(common_data.PegNo,50,4+i++*12,index==0,setup_data.point);
				PrintFloat(common_data.Offset,50,4+i++*12,index==1,setup_data.point);
				PrintFloat(x,50,4+i++*12,0,setup_data.point);
				PrintFloat(y,50,4+i++*12,0,setup_data.point);
				need_redraw = 0;
			}
			//
			GetKey(&key);
			Menu_Proc1();
			if (key==KEY_CTRL_DOWN)
				if(prekey==key) mode = MODE_INPUT_REAL;
			if (!index)
			{
				if (key==KEY_CTRL_EXE || key == KEY_CTRL_RIGHT)
					common_data.PegNo += common_data.Spacing,need_redraw = REFRESH_PART;
				else if (key==KEY_CTRL_LEFT)
					common_data.PegNo -= common_data.Spacing,need_redraw = REFRESH_PART;
			}
			InputDefProc(((double*)(&common_data)+2),2,50,4,mode,MODE_INPUT_JJQZ);
			prekey = key;
		}
	}//if mode
	if (mode == MODE_INPUT_REAL)
	{
		double shice[2];
		double zh,pj;
		char *context[] = 
		{"已知X","\已知Y","桩号:","\xc6\xab\xbe\xe0:"};
		shice[0] = x;shice[1] = y;
		index = 0;
		need_redraw = REFRESH_ALL;
		while(mode==MODE_INPUT_REAL)
		{
			if (need_redraw == REFRESH_ALL)
			{
				Bdisp_AllClr_DDVRAM();
				SetMyFont(&stHz12x12,&stAsc6x12); 
				DispStr(2,1, "直 ");
			    DispStr(2,15,"线 ");
			    DispStr(2,28,"两 ");
			    DispStr(2,41,"点 ");
				ShowTitle(TITLE);
				for (i=0;i<4;++i)
				DispStr(18,4+i*12,context[i]);
				Menu_Draw1();
				need_redraw = REFRESH_PART;
			}
			if (need_redraw==REFRESH_PART)
			{
				CalcPosAndDistance(	shice[0],shice[1],
									value[0],value[1],
									common_data.position,
							 		&zh,&pj);
				for (i=0;i<2;++i)
					PrintFloat(shice[i],50,4+i*12,index==i,setup_data.point);
				PrintFloat((float)zh,50,4+i++*12,0,setup_data.point);
				PrintFloat(pj,50,4+i++*12,0,setup_data.point);

			}
			GetKey(&key);
			Menu_Proc1();
			InputDefProc(shice,2,50,4,mode,MODE_INPUT_ZH);
		}
	}//if mode
}
void Run_F1_ZhenSuan ()
{
	int i;
	if (mode == MODE_INPUT_P_AND_D)
	{
		char *context[] = 
		{"起点X ","起点Y","距离:","方位:"};
		double data[4],deg_change;
		data[0]=common_data.value[0];
		data[1]=common_data.value[1];
		data[2]=common_data.distance;
		data[3]=deg_change=common_data.position;
		index = 0;
		need_redraw = REFRESH_ALL;
		while(mode == MODE_INPUT_P_AND_D)
		{
			//// REDRAW
			if (need_redraw==REFRESH_ALL)
			{
				Bdisp_AllClr_DDVRAM();
				i = 0;
				SetMyFont(&stHz12x12,&stAsc6x12); 
				DispStr(2,1, "普 ");
			    DispStr(2,15,"通 ");
			    DispStr(2,28,"反 ");
			    DispStr(2,41,"算 ");
				ShowTitle(TITLE);
				for (i=0;i<4;++i)
				DispStr(16,4+i*12,context[i]);
				need_redraw = REFRESH_PART;
				Menu_Draw1();
			}
			if (need_redraw==REFRESH_PART)
			{
				char strpos[20];
				DrawClearBox (50,40,125,51,index==3);
				FloatToDegStr(data[3],strpos);
				PrintXY(52,42,strpos,strpos[11]=0);
				if (index==3)Bdisp_AreaReverseVRAM(52,42,123,49);
				for(i=0;i<3;++i)
				PrintFloat(data[i],50,4+i*12,index==i,setup_data.point);
				need_redraw = 0;
			}
			GetKey(&key);
			Menu_Proc1();
			if (key==KEY_CTRL_EXE) mode = MODE_DISP_P;
			InputDefProc(data,4,50,4,MODE_DISP_P,MODE_EXIT);
			if (deg_change!=data[3])
			{
				double	x,y,z;
				x = (int)data[3];
				y = (int)((data[3]-x)*100.0)/60.0;
				z = (data[3]-x)*100.0;
				z = (z - (int)z)*100.0/3600.0;
				data[3]=deg_change=x+y+z;
			}
		}
		common_data.value[0]=data[0];
		common_data.value[1]=data[1];
		common_data.distance=data[2];
		common_data.position=data[3];
	}
	if (mode == MODE_DISP_P)
	{
		need_redraw = REFRESH_ALL;
		while(mode == MODE_DISP_P)
		{
			if (need_redraw==REFRESH_ALL)
			{
				Bdisp_AllClr_DDVRAM();
				i=0;
				SetMyFont(&stHz12x12,&stAsc6x12); 
				DispStr(2,1, "普 ");
			    DispStr(2,15,"通 ");
			    DispStr(2,28,"反 ");
			    DispStr(2,41,"算 ");
				ShowTitle(TITLE);
				DispStr(16,6, "坐标X ");
				DispStr(16,18,"坐标Y ");
				value[2] = value[0]+common_data.distance*
					cos(common_data.position*PI/180.0)
					+common_data.Offset*cos(common_data.position*PI/180.0+PI/2);
				value[3] = value[1]+common_data.distance*
					sin(common_data.position*PI/180.0)
					+common_data.Offset*sin(common_data.position*PI/180.0+PI/2);
				PrintFloat(value[2],50,6+i++*12,0,setup_data.point);
				PrintFloat(value[3],50,6+i*12,0,setup_data.point);
				Menu_Draw1();
			}
			GetKey(&key);
			Menu_Proc1();
			if (key==KEY_CTRL_EXIT || key==KEY_CTRL_EXE) mode = MODE_INPUT_P_AND_D;
		}
	}
}
int BinMain_1()
{
	need_redraw = REFRESH_ALL;
	mode = MODE_INPUT_2_POINT;
	while (mode!=MODE_EXIT)
	{
		Run_F1_FanSuan();
		Run_F1_ZhenSuan();
	}
}