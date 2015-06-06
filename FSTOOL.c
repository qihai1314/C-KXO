#include "headfile.h"

int FSTOOL ()
{
	uint refresh = 2,key;
	int  index = 0,i;
	char ch;
	double fsx1,fsx2,fsy1,fsy2,fsd,fsv;
	double value[4] = {0.0,0.0,0.0,0.0};
	const char * context[] = {"X1=:","Y1=:","X2=:","Y2=:"};

	while(1){
		if (refresh == REFRESH_ALL){
			refresh = REFRESH_PART;
			Bdisp_AllClr_VRAM();
			DrawPicture (29, 0,70,9,PIC_FS_TOOL);
			for (i=0;i<4;++i){
				PrintXY(12,12+i*12,(uchar*)context[i],0);
			}
			PrintIcon (0,"ZS",0);
			PrintIcon (1,"FS",1);
			PrintIcon (2,"Disp",1);
			PrintIcon (3,"^=^",1);
			PrintIcon (4,"save",1);
			PrintIcon (5,"?",0);
		}
		if (refresh == REFRESH_PART){
			for (i=0;i<4;++i){
				PrintFloat(value[i],35,10+i*12,index==i,3);
			}
			refresh = 0;
		}
		GetKey(&key);
		switch(key){
			case KEY_CTRL_F1	:	return 0;	break;
			case KEY_CTRL_F2	:	break;
			case KEY_CTRL_F3	:
			case KEY_CTRL_F4	:
			case KEY_CTRL_F5	:	Nodata();	refresh=REFRESH_ALL;	break;
			case KEY_CTRL_F6	:	About();	refresh=REFRESH_ALL;	break;
			case KEY_CTRL_UP	:	refresh=REFRESH_PART;	--index;	break;
			case KEY_CTRL_DOWN	:	refresh=REFRESH_PART;	++index;	break;
			case KEY_CTRL_EXE:
		 		if	(index<3) refresh=REFRESH_PART,++index;
				else{
		 			refresh=REFRESH_ALL;
					fsx1=value[0];
					fsy1=value[1];
					fsx2=value[2];
					fsy2=value[3];
					fsd = sqrt((fsx2-fsx1)*(fsx2-fsx1)+(fsy2-fsy1)*(fsy2-fsy1));
 					fsv = atan((fsy2-fsy1)/(fsx2-fsx1+1e-12))/PI*180.0;
					if (fsx2 -fsx1< 0.0)	fsv += 180.0;
					if (fsv<0.0)	fsv += 360.0;
					
					PopUpWin (4);
					PrintfXY (16,11,0,"D= %.3f",fsd);
					PrintXY (16,22,(uchar*)"F= ",0);PrintDeg (32,22,fsv,0);
					PrintfXY (24,33,0,"Press any key");
					WaitKey();
					++index;
				}
				break;
			case KEY_CTRL_EXIT:
				return 0;
			default:
				if ((ch=GetPressNumChar(key))!=0){
					char buf[14];
					int        r;
					refresh = REFRESH_PART;
					buf[0] = ch;   buf[1] = '\0';
					r = InputString (35,10+index*12,buf,0,12);
					if (r != KEY_CTRL_EXIT){
						value[index] = atof(buf);
						if	(r==KEY_CTRL_DOWN)		++index;
						if	(r==KEY_CTRL_UP)	--index;
						if (r==KEY_CTRL_EXE && index<3)	++index;
					}
					break;
				}
		}
		if (index >=4) index = 0;
		if (index < 0) index = 3;
	}
}

