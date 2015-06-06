#include "headfile.h"

int ZSTOOL ()
{
	uint refresh = 2,key;
	int  index = 0,i;
	char ch;
	double zsx1,zsx2,zsy1,zsy2,zsd,zsv;
	double value[4] = {0.0,0.0,0.0,90.0};
	const char * context[] = {"X1=:","Y1=:"," D=:"," V=:"};

	while(1){
		if (refresh == REFRESH_ALL){
			refresh = REFRESH_PART;
			Bdisp_AllClr_VRAM();
			DrawPicture (29, 0,70,9,PIC_ZS_TOOL);
			for (i=0;i<4;++i){
				PrintXY(12,12+i*12,(uchar*)context[i],0);
			}
			PrintIcon (0,"ZS",1);
			PrintIcon (1,"FS",0);
			PrintIcon (2,"Disp",1);
			PrintIcon (3,"^o^",1);
			PrintIcon (4,"save",1);
			PrintIcon (5,"?",0);
		}
		if (refresh == REFRESH_PART){
			for (i=0;i<4;++i){
				if (i!=3)	PrintFloat(value[i],35,10+i*12,index==i,3);
				if (i==3)	PrintDeg(35,10+i*12,value[i],index==i);
			}
			refresh = 0;
		}
		GetKey(&key);

		switch(key){
			case KEY_CTRL_F1	:	break;
			case KEY_CTRL_F2	:	FSTOOL();	refresh=REFRESH_ALL;	break;
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
					zsx1=value[0];
					zsy1=value[1];
					zsd=value[2];
					zsv=value[3];
					zsx2=zsx1+zsd*cos(zsv*PI/180);
		 			zsy2=zsy1+zsd*sin(zsv*PI/180);
					PopUpWin (4);
					PrintfXY (24,11,0,"X= %.3f",zsx2);
					PrintfXY (24,22,0,"Y= %.3f",zsy2);
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
						if (index == 3){
							double	dd,ff,mm;
							dd = (int)value[3];
							ff = (int)((value[3]-dd)*100.0)/60.0;
							mm = (value[3]-dd)*100.0;
							mm = (mm - (int)mm)*100.0/3600.0;
							value[3]=dd+ff+mm;
						}
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

