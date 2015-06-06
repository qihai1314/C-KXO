#include "headfile.h"

int computeGC ()
{
	uint refresh = 2,key;
	int  index = 0,i;
	char ch;
	double bm,bs,fs,fh;
	double value[4] = {0.0,0.0,0.0,0.0};
	const char * context[] = {"BM=:","BS=:","FS=:","FH=:"};

	while(1){
		if (refresh == REFRESH_ALL){
			refresh = REFRESH_PART;
			Bdisp_AllClr_VRAM();
			DrawPicture (30, 0,67,13,PIC_GC_TITLE);
			for (i=0;i<4;++i){
				PrintXY(50,18+i*12,(uchar*)context[i],0);
			}
		}
		if (refresh == REFRESH_PART){
			for (i=0;i<4;++i){
				PrintFloat(value[i],35,16+i*12,index==i,3);	
			}
			refresh = 0;
		}
		GetKey(&key);
		switch(key){
			case KEY_CTRL_UP	:
				refresh=REFRESH_PART;	--index;	break;
			case KEY_CTRL_DOWN	:
				refresh=REFRESH_PART;	++index;	break;
			case KEY_CTRL_EXE:
		 		if	(index<2) refresh=REFRESH_PART,++index;	break;
			case KEY_CTRL_EXIT:
				return 0;
			default:
				if ((ch=GetPressNumChar(key))!=0){
					char buf[14];
					int        r;

					refresh = REFRESH_PART;
					buf[0] = ch;   buf[1] = '\0';
					r = InputString (35,16+index*12,buf,0,12);
					if (r != KEY_CTRL_EXIT){
						value[index] = atof(buf);
						
						if	(r==KEY_CTRL_DOWN)		++index;
						if	(r==KEY_CTRL_UP)	--index;
						if (r==KEY_CTRL_EXE && index<2)	++index;
						if (r==KEY_CTRL_EXE && index==2){
							bm=value[0];
							bs=value[1];
							fs=value[2];
							value[3]=bm+bs-fs;
						}
					}	break;
				}
		}//switch
		if (index >=3) index = 0;
		if (index < 0) index = 2;
	}
}

