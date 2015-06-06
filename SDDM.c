#include "headfile.h"


int SDDM ()
{
	uint refresh = 2,key;
	int  index = 0,i;
	char ch;
	double value[3] = {0.0,0.0,0.0};
	const char * context[] = {"Oh=:","Od=:","Or=:"};
	value[0]=setup.dmoh;
	value[1]=setup.dmod;
	value[2]=setup.dmor;
	while(1){
		if (refresh == REFRESH_ALL){
			refresh = REFRESH_PART;
			Bdisp_AllClr_VRAM();
			DrawPicture (36, 0,60,13,PIC_SD_SET);
			for (i=0;i<3;++i){
				PrintXY(14,18+i*13,(uchar*)context[i],0);
			}
			PrintIcon (0,"Rou",1);
			PrintIcon (1,"Set",1);
			PrintIcon (2,"OK",0);
			PrintIcon (3,"Disp",1);
			PrintIcon (4,"save",1);
			PrintIcon (5,"?",0);
		}
		if (refresh == REFRESH_PART){
			for (i=0;i<3;++i){
				PrintFloat(value[i],38,16+i*13,index==i,3);	
			}
			refresh = 0;
		}
		GetKey(&key);
		switch(key){
			case KEY_CTRL_F3:
				setup.dmoh=value[0];
				setup.dmod=value[1];
				setup.dmor=value[2];
				return 0;
			case KEY_CTRL_F4	:
			case KEY_CTRL_F5	:
				Nodata();	refresh=REFRESH_ALL;	break;
			case KEY_CTRL_F6	:
				About();	refresh=REFRESH_ALL;	break;			
			case KEY_CTRL_UP:
				refresh=REFRESH_PART;	--index;	break;
			case KEY_CTRL_DOWN:
				refresh=REFRESH_PART;	++index;	break;
			case KEY_CTRL_EXE:
				refresh = REFRESH_PART;	index++;	break;
			case KEY_CTRL_EXIT:
				setup.dmoh=value[0];
				setup.dmod=value[1];
				setup.dmor=value[2];
				return 0;
			default:
				if ((ch=GetPressNumChar(key))!=0){
					char buf[14];
					int        r;
					refresh = REFRESH_PART;
					buf[0] = ch;   buf[1] = '\0';
					r = InputString (38,16+index*13,buf,0,12);
					if (r != KEY_CTRL_EXIT){
						value[index] = atof(buf);
						if	(r==KEY_CTRL_DOWN)	++index;
						if	(r==KEY_CTRL_UP)	--index;
						if (r==KEY_CTRL_EXE )	++index;
					}
					break;
				}
		}
		if (index >=3) index = 0;
		if (index < 0) index = 2;
	}
}
