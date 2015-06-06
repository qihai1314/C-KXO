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
int Menu_Draw2()
{   
    int i=0;
	SetMyFont(&stHz8x8,&stAsc6x12); //设置中文大小8*8 
	DispStr(4,56,"反算 "); 
	PrintIcon(i++,"",mode<=MODE_INPUT_REAL);
	//PrintIcon(i++,"",mode>MODE_INPUT_REAL && mode<=MODE_DISP_P);
	//PrintIcon(i++,"",0);
	//PrintIcon(i++,"",0);
	//PrintIcon(5,"?",0);
}

void Menu_Proc2()
{
	switch (key)
	{
		case KEY_CTRL_F1:mode=MODE_INPUT_2_POINT;break;
		//case KEY_CTRL_F2:mode=MODE_INPUT_P_AND_D;break;
		case KEY_CTRL_F3:break;
		case KEY_CTRL_F4:break;
		case KEY_CTRL_F6:break;
	}
}
void Run_Circular()
{
	double x,y;
	int i;
	if (mode == MODE_INPUT_2_POINT)
	{
	    char *context[] = 
	   {"起弧X ","起弧Y ","终弧X ","终弧Y "};
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
			    DispStr(2,1, "圆 ");
			    DispStr(2,15,"弧 ");
			    DispStr(2,28,"坐 ");
			    DispStr(2,41,"标 ");
				ShowTitle(TITLE);
				for (i=0;i<4;++i)
				DispStr(16,4+i*12,context[i]);
				need_redraw = REFRESH_PART;
				Menu_Draw2();
			}
			if (need_redraw==REFRESH_PART)
			{
				for(i=0;i<4;++i)
				PrintFloat(value[i],50,4+i*12,index==i,setup_data.point);
				need_redraw = 0;
			}
			GetKey(&key);
			Menu_Proc2();
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
		{"距离:","方位: ","半径 ","间距 "};
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
			    DispStr(2,1, "圆 ");
			    DispStr(2,15,"弧 ");
			    DispStr(2,28,"坐 ");
			    DispStr(2,41,"标 ");
				ShowTitle(TITLE);
				for (i=0;i<4;++i)
				DispStr(16,4+i*12,context[i]);
				i=0;
				FloatToDegStr(common_data.position,strpos); //将角度分解度分秒格式
				PrintFloat(common_data.distance,50,4+i++*12,0,setup_data.point); //距离
				PrintXY(52,6+i++*12,strpos,0);  //角度
				need_redraw = REFRESH_PART;
				Menu_Draw2();
			}
			if (need_redraw==REFRESH_PART)
			{
				i = 2;
				PrintFloat(common_data.Spacing,50,4+i++*12,index==0,setup_data.point);     //半径
				PrintFloat(common_data.BeginStake,50,4+i++*12,index==1,setup_data.point);  //间距
				need_redraw = 0;
			}
			GetKey(&key);
			Menu_Proc2();
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
			    DispStr(2,1, "圆 ");
			    DispStr(2,15,"弧 ");
			    DispStr(2,28,"坐 ");
			    DispStr(2,41,"标 ");
				ShowTitle(TITLE);
				for (i=0;i<4;++i)
				DispStr(16,4+i*12,context[i]);
				Menu_Draw2();
				//ShowArrow(1);//////////////////////////////////////////////////////////
				need_redraw = REFRESH_PART;
			}
			if (need_redraw==REFRESH_PART)  //
			{
			    double A,B,C,Q,T;
				A = common_data.position - asin(common_data.distance/2.0/common_data.Spacing)/PI*180; //49.54652942
				if (common_data.Offset == 0 ) common_data.Offset==0.0000001;
				Q = abs(common_data.Offset)/(common_data.Offset+0.0000001); //0
				B = value[0]+cos((A*PI/180+PI/2))*common_data.Spacing; //451.672049
				C = value[1]+sin((A*PI/180+PI/2))*common_data.Spacing; //354.2852252
				T = A-90+(180*common_data.PegNo/common_data.Spacing/PI); //-40.45347058       
				x = B+common_data.Spacing * cos(T*PI/180)+(common_data.Offset * cos(T*PI/180+PI * Q)); 
				y = C+common_data.Spacing * sin(T*PI/180)+(common_data.Offset * sin(T*PI/180+PI * Q)); 
				i = 0;
				PrintFloat(common_data.PegNo,50,4+i++*12,index==0,setup_data.point);  //计算桩号显示
				PrintFloat(common_data.Offset,50,4+i++*12,index==1,setup_data.point); //偏距显示
				PrintFloat(x,50,4+i++*12,0,setup_data.point);  //计算结果X显示
				PrintFloat(y,50,4+i++*12,0,setup_data.point);  //计算结果Y显示
				need_redraw = 0;
			}
			//
			GetKey(&key);
			Menu_Proc2();
			if (key==KEY_CTRL_DOWN)
				if(prekey==key) mode = MODE_INPUT_REAL;
			if (!index)
			{
				if (key==KEY_CTRL_EXE || key == KEY_CTRL_RIGHT)
					common_data.PegNo += common_data.BeginStake,need_redraw = REFRESH_PART;
				else if (key==KEY_CTRL_LEFT)
					common_data.PegNo -= common_data.BeginStake,need_redraw = REFRESH_PART;
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
				Menu_Draw2();
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
			Menu_Proc2();
			InputDefProc(shice,2,50,4,mode,MODE_INPUT_ZH);
		}
	}//if mode
}


int BinMain_2()
{
	need_redraw = REFRESH_ALL;
	mode = MODE_INPUT_2_POINT;
	while (mode!=MODE_EXIT)
	{
		  Run_Circular();
		  MenuInit();
		//Run_F1_ZhenSuan();
	}
}