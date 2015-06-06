#include "headfile.h"
#include "xy.h"
#include "MyFont.h"
#include <fxlib.h>
#include <dispbios.h>
#include "fileline.h"

static char TITLE[] = "";

static FONTCHARACTER IniFile[] = { '\\','\\','c','r','d','0','\\','c','s','v','.','i','n','i' ,'\0'} ;
static FONTCHARACTER IniSet1[] = { '\\','\\','c','r','d','0','\\','s','e','t','1','.','i','n','i' ,'\0'} ;
static FONTCHARACTER IniSet2[] = { '\\','\\','c','r','d','0','\\','s','e','t','2','.','i','n','i' ,'\0'} ;


int computeZS ()
{
	uint refresh = 2,key;
	int  index = 0,i,hcs,ii;
	char ch;
	char ss[20];
	double ht,v,hd,bh;
	double value[4];
	for(ii=0;ii<4;ii++)
	{
		ReadFileLine(IniSet2,ii,ss,20-1);
		value[ii]=atof(ss);
	}
	//const char * context[] ={"","","",""};
	while(1){
		if (refresh == REFRESH_ALL){  //宏定义 REFRESH_ALL=2    全部
			refresh = REFRESH_PART;   //宏定义 REFRESH_PART=1   部分， REFRESH_PART赋值给refresh=1  
			Bdisp_AllClr_VRAM();      //清理屏幕
			SetMyFont(&stHz12x12,&stAsc6x12);  //定义字体大小
			DispStr(2,2,"线 ");
			DispStr(2,12,"路 ");
			DispStr(2,25,"正 ");
			DispStr(2,38,"算 ");
			ShowTitle(TITLE);  //标题显示
			DispStr(17,0,"\xD7\xAE\xBA\xC5:"); // \xD7\xAE\xBA\xC5
			DispStr(17,13,"偏距: ");
			DispStr(17,26,"夹角: ");
			DispStr(17,39,"\xB2\xE2\xB8\xDF : ");
			//DrawPicture (0, 4,11,47,PIC_ZS_TITLE);  //**************临时撤销，标题图片生成代码显示，记得删除图片生产代码
			//for (i=0;i<4;++i){
			//	PrintXY(19,4+i*12,(uchar*)context[i],0);
			//}
	
			SetMyFont(&stHz8x8,&stAsc6x12);
			DispStr(2,56,"\xC9\xE8\xD6\xC3 ");
			//DispStr(24,56,"\xB2\xCE\xCA\xFD "); 參數
			//DispStr(45,56,"\xBC\xD3\xD7\xAE "); 加
			//DispStr(66,56,"\xBC\xF5\xD7\xAE "); 
			//DispStr(108,56,"\xB0\xEF\xD6\xFA ");
			
		    PrintIcon (0,"",1);
			//PrintIcon (1,"",1);
			//PrintIcon (2,"",1);
			//PrintIcon (3,"",1);
			//PrintIcon (4,"",1);
			//PrintIcon (5,"",1);
		}
		
		if (refresh == REFRESH_PART){     //REFRESH_PART=1 更新部分
			for (i=0;i<4;++i){
				if (i==0 || i==1)	PrintFloat(value[i],48,0+i*13,index==i,4);	 
				if (i==3)	PrintFloat(value[i],48,0+i*13,index==i,4);
				if (i==2)	PrintDeg(48,0+i*13,value[i],index==i);
			}
			refresh = 0;
		}
		
		GetKey(&key);
		switch(key){
			case KEY_CTRL_F1	:
				SET();	refresh=REFRESH_ALL;	break;
			case KEY_CTRL_F2	:
				//ZSSET();refresh=REFRESH_ALL;	break;
			case KEY_CTRL_F3	:
				//value[0]=value[0]+zfset.zsm;refresh=REFRESH_ALL;index = 3;	break;
			case KEY_CTRL_F4	:
				//value[0]=value[0]-zfset.zsm;refresh=REFRESH_ALL;index = 3;	break;
			case KEY_CTRL_F5	:
				//Nodata();	refresh=REFRESH_ALL;	break;
			case KEY_CTRL_F6	:
				//About();	refresh=REFRESH_ALL;	break;
			case KEY_CTRL_UP	:
				refresh=REFRESH_PART;	--index;	break;
			case KEY_CTRL_DOWN	:
				refresh=REFRESH_PART;	++index;	break;
			case KEY_CTRL_EXE:
		 		if	(index<3) refresh=REFRESH_PART,++index;
				else{
		 			refresh=REFRESH_ALL;
					yscs.k=value[0];
					yscs.d=value[1];
					v=value[2];
					ht=value[3];
					yscs.xn=sd_to_xyaSrd(yscs.k,yscs.d,v,0);
					yscs.ye=sd_to_xyaSrd(yscs.k,yscs.d,v,1);
					yscs.fn=sd_to_xyaSrd(yscs.k,yscs.d,0,3);//角度V默认为0 否则会出错记得这里~！
					yscs.gch=zdm_to_gc(yscs.k);
					
		 			//ZS();
		 			//GC();
		 			//HP();
				 	//yscs.xn=yscs.xn+yscs.d*cos((yscs.fn+v)*PI/180);   //角度转换弧度
		 			//yscs.ye=yscs.ye+yscs.d*sin((yscs.fn+v)*PI/180);   //角度转换弧度
		 			//if	(yscs.d<0)	hcs=-1;	
		 			//if	(yscs.d>=0)	hcs=1;
		 			//if	(yscs.d*hcs<=zfset.zsp)	hd=0;
		 			//if	(zfset.zsh==0)	hd=0;
		 			//if	(yscs.d*hcs>zfset.zsp && yscs.d*hcs-zfset.zsp<zfset.zsh) hd=(yscs.d*hcs-zfset.zsp)*hcs;
		 			//if	(yscs.d*hcs-zfset.zsp>=zfset.zsh)	hd=zfset.zsh*hcs;
		 			//bh=yscs.gch+(yscs.hpd*hd)-ht;
					Bdisp_AllClr_VRAM();
					SetMyFont(&stHz12x12,&stAsc6x12);  //定义字体大小
			        DispStr(2,0, "计 ");
			        DispStr(2,12,"算 ");
			        DispStr(2,26,"结 ");
			        DispStr(2,39,"果 ");
					ShowTitle(TITLE);
					//DispStr(31,0, "桩号 ");
			        DispStr(17,0,"坐标X "); 
			        DispStr(17,13,"坐标Y ");
			        DispStr(17,26,"方位: ");
					DispStr(17,39,"基高: ");
					//PrintfXY (48,1,0,"%.4f",yscs.k);
					PrintfXY (48,2.5,0,"%.4f",yscs.xn);
					PrintfXY (48,16,0,"%.4f",yscs.ye);
					PrintDeg (46,27,yscs.fn,0); 
					PrintfXY (49,42,0,"%.4f",yscs.gch);	 
					
					//PrintfXY (6,47,0," P=%.5f",yscs.hpd);
					//PrintfXY (6,56,0," H=%.3f",bh);
					WaitKey();
					++index;
				}	break;
			case KEY_CTRL_EXIT:
				return 0;
			default:
				if ((ch=GetPressNumChar(key))!=0){
					char buf[14];
					int        r;
					refresh = REFRESH_PART;
					buf[0] = ch;   buf[1] = '\0';
					r = InputString (48,0+index*13,buf,0,12); //注意位移输入框的位置
					if (r != KEY_CTRL_EXIT){
						
						value[index] = atof(buf);
						if (index == 2){
							double	dd,ff,mm;
							dd = (int)value[2];
							ff = (int)((value[2]-dd)*100.0)/60.0;
							mm = (value[2]-dd)*100.0;
							mm = (mm - (int)mm)*100.0/3600.0;
							value[2]=dd+ff+mm;
						} 
						WriteFileLine(IniSet2,index,buf);
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
