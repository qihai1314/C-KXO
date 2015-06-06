#include "headfile.h"
#include "runmain.h"
#include "zbzfs.h"
#include "MyFont.h"
#include "cvs.h"
#include <stdarg.h>
          
double zdm_to_gc( double stake);

int PrintTables3(short x,short y,char * str,short sel,short lbl)
{
	int len;
	const int width = 28;
	len = strlen(str);
	x *= width;
	y *= 8;
	x += 16;
	if (sel)
	{
		Bdisp_AreaReverseVRAM(x,y,x+width-1,y+7);
		PrintMini(x+1+(lbl ? (width-5*len)/2:0),y+1,str,MINI_REV);
	}
	else
	{

		Bdisp_DrawLineVRAM(x+width-1,y,x+width-1,y+7);
		Bdisp_DrawLineVRAM(x,y+7,x+width-1,y+7);
		PrintMini(x+1+(lbl ? (width-5*len)/2:0),y+1,str,MINI_OVER);
	}
}

int PrintTableFormats3 (short x,short y,short sel,short lbl,char * format,...)
{
	char buffer[128];
	va_list parglist;
	va_start(parglist, format);
	vsprintf(buffer,format, parglist);
	va_end(pArgList);
	buffer[6] = 0;
	PrintTables(x,y,buffer,sel,lbl);
	return 0;
}
int PrintTableIndexs3 (int y,int index)
{
	char buffer[8];
	if (index<0 || index>999) return 0;
	sprintf(buffer,"%d",index);
	y *= 8;
	Bdisp_AreaReverseVRAM(0,y,15,y+7);
	PrintMini(1,y+2,buffer,MINI_REV);
}
int WhetherCover3()
{
	int enter;
	PopUpWin(5);
	DispStr(48,12,"覆盖?"); //fugai
	locate(7,5);Print("Yes : [F1]");
	locate(7,6);Print("No  : [F6]");
	do{
		GetKey(&key);
		if (key==KEY_CTRL_F6 || key==KEY_CTRL_EXIT){enter =0 ;break;}
		else if (KEY_CTRL_F1) {enter = 1;break;}
	}while(1);
	return enter;
}
int WheterSavaAS3()
{
	char str[13]="";
	int suc,enter,i;
	for (i=0;i<13 && setup_data.zdmroute_name[i] != '.';++i)
		str[i] = setup_data.zdmroute_name[i];
	str[i>=13 ? 12 : i] = 0;
	PopUpWin(4);
	DispStr(24,8,"\xce\xc4\xbc\xfe\xc3\xfb(*.zdm)");//file_name
	do
	{
		suc = InputString(24,24,str,1,8);
		if (suc==KEY_CTRL_EXIT) break;
		if (! str[0]) continue;
	}while(suc!=KEY_CTRL_EXE);
	if(suc!=KEY_CTRL_EXIT)
	{
		enter = 1;
		strcat(str,".zdm");
		if (TestSRDFile3(str))
		{
			enter = WhetherCover3();
		}
		if (enter)
		{
			SaveSRDFile3(str);
			strcpy(setup_data.zdmroute_name,str);
		}
	}
}

int Selectfile3()
{
	index = 0;
	need_redraw = REDRAW_PART;
	SetMyFont(&stHz12x12,&stAsc6x12);
	
	while(1)
	{
		if (need_redraw == REDRAW_PART)
		{
			PopUpWin(6);
			DrawPicture(32,9,	16,	10,	G_ICON_SAVE);	DispStr(48,8,"保存为 ");
			DrawPicture(32,25,	16,	10,	G_ICON_OPEN);	DispStr(48,24,"打开 ");
			DrawPicture(32,41,	16,	10,	G_ICON_OTHER);	DispStr(48,40,"新建 ");
			
			Bdisp_AreaReverseVRAM(14,8+16*index,112,20+index*16);
		}
		GetKey(&key);
		if (key==KEY_CTRL_UP) 	{if(--index<0) index = 2;need_redraw = REDRAW_PART;}
		if (key==KEY_CTRL_DOWN)	{if(++index>2) index = 0;need_redraw = REDRAW_PART;}
		if (key==KEY_CTRL_EXIT)	break;
		if (key==KEY_CTRL_EXE)
		{
			char str[13]="";
			int suc,enter,i;
			switch(index)
			{
				case 0:
					
					for (i=0;i<13 && setup_data.zdmroute_name[i] != '.';++i)
						str[i] = setup_data.zdmroute_name[i];
					str[i>=13 ? 12 : i] = 0;
					PopUpWin(4);
					DispStr(24,8,"\xce\xc4\xbc\xfe\xc3\xfb(*.zdm)");//file_name
					do
					{
						suc = InputString(24,24,str,1,8);
						if (suc==KEY_CTRL_EXIT) break;
						if (! str[0]) continue;
					}while(suc!=KEY_CTRL_EXE);
					if(suc!=KEY_CTRL_EXIT)
					{
						enter = 1;
						strcat(str,".zdm");
						if (TestSRDFile3(str))
						{
							PopUpWin(5);
							DispStr(48,12,"覆盖?"); //fugai
							locate(7,5);Print("Yes : [F1]");
							locate(7,6);Print("No  : [F6]");
							do{
								GetKey(&key);
								if (key==KEY_CTRL_F6 || key==KEY_CTRL_EXIT){enter =0 ;break;}
								else if (KEY_CTRL_F1) {enter = 1;break;}
							}while(1);
						}
						if (enter)
						{
							SaveSRDFile3(str);
							strcpy(setup_data.zdmroute_name,str);
						}
					}     
					break;
				case 1:
					suc = SelectFiles3 (str);
					if (suc==-1)
					{
						PopUpWin(1);
						locate(7,4);Print("No File!");
						GetKey(&key);
					}
					if(suc==1)
					{
						LoadSRDFile3 (str);
						strcpy(setup_data.zdmroute_name,str);
						if(LoadSRDFile3 (setup_data.zdmroute_name)==1)
						SaveIniSRDFile3();
						goto EXIT;
					}
					
				case 2:
					PopUpWin(5);
				    DispStr(48,12,"新建?"); 
				    locate(7,5);Print("Yes : [F1]");
					locate(7,6);Print("No  : [F6]");
					GetKey(&key);
					if (key==KEY_CTRL_F1){
						PopUpWin(5);
				        DispStr(40,12,"保存数据?"); 
				        locate(7,5);Print("Yes : [F1]");
					    locate(7,6);Print("No  : [F6]");
					    GetKey(&key);
						if(key==KEY_CTRL_F1)
						{
							if(setup_data.zdmroute_name[0]==0)
				            {
					            WheterSavaAS();
				            }
				            else
				            {
					            SaveSRDFile3(setup_data.zdmroute_name);
				            }
						}						
						setup_data.zdmroute_name[0]=0;
				        zdmroute_initial(&zdmroute);
	                    zdmroute_push_back(&zdmroute);
						goto EXIT;
			        }   
				    break;
					
				default:break;
			}
			need_redraw = REDRAW_PART;
		}
	}
	EXIT:
	return 0;
}


int ZDM_parameter()
{
	
	char * table_label[]= {"DH","BBZH","BBGC","BJ"};
	char * icons[]		= {"","","","",""};
	char * ch_text[]	= {"\xb5\xe3\xc3\xfb",
	                        "变坡桩号",
							"变坡高程",
							"半径 "};
	int x = 0,y = 0,i,j,t;
	int left = 0,top = 0;
	int refresh = REDRAW_ALL;
	int enter,suc;
	char str[13]="";
	char c;
	
   
	while(1){
		if (refresh==REDRAW_ALL){
			Bdisp_AllClr_VRAM();
			for (i=0;i<4;++i)
			PrintTables(i,0,table_label[left+i],1,1);
			t = zdmroute.size<= 1 ? 2 : 5; //如果交点个数小于等于1 那么T=2 否则等于5
			if 	(t>=2){
			SetMyFont(&stHz8x8,&stAsc6x12);
			DispStr(2,56,"\xCE\xC4\xBC\xFE");
		    DispStr(23,56,"添加");
			}
			if 	(t>2){
			SetMyFont(&stHz8x8,&stAsc6x12);
			DispStr(45,56,"插入 ");
		    DispStr(65,56,"删行 ");
			DispStr(86,56,"清空 ");
			}
			for (i=0;i< t;++i) // i<2 或  i<5
			PrintIcon(i,icons[i],0);  //打印下标 
			PrintIcon(5,"?",0);  //固定打印下标
			refresh = REDRAW_PART; // 重画部分
		}
		
		if (refresh==REDRAW_PART){  //如果画部分 
			double * sd;
			for (i=top;i<top+4 && i<zdmroute.size;++i){ 
				sd =  & (zdmroute.set[i].zdm_bbzh);
				for (j=(left==0 ? 1:0);j<4;++j){
					if (i==0 && j+left>2)  //////////////////////////////////////////
					   PrintTables3(j,i+1-top,"",y==i && x-left==j,0);///////////////
					else/////////
						PrintTableFormats3(j,i+1-top,y==i && x-left==j,0,"%lf",sd[j+left-1]);
				}
				if (left==0)
					PrintTableFormats3(0,i+1-top,y==i && x-left==0,0,"%s",zdmroute.set[i].name);
				PrintTableIndexs3(i-top+1,i);
			}
			SetMyFont(&stHz12x12,&stAsc6x12);
			if(x>0){
				//if (!(y==0 && x>2)){
					sd =  & (zdmroute.set[y].zdm_bbzh); //取地址的值
					DispStr(0,42,ch_text[x]);
					PrintFloat(sd[x-1],49,42,0,setup_data.point); //打印 
				//}
			}else{
				DispStr(0,42,ch_text[x]);
				PrintXY(51,44,zdmroute.set[y].name,0);
			}
			refresh = 0;
		}
		GetKey(&key);
		switch (key){
		case KEY_CTRL_UP:
			y--;refresh = REDRAW_ALL;break;
		case KEY_CTRL_DOWN:
			y++;refresh = REDRAW_ALL;break;
		case KEY_CTRL_LEFT:
			x--;refresh = REDRAW_ALL;break;
		case KEY_CTRL_RIGHT:
			x++;refresh = REDRAW_ALL;break;
		case KEY_CTRL_EXIT:
		    PopUpWin(5);
			DispStr(48,12,"保存?"); 
			locate(7,5);Print("Yes : [F1]");
			locate(7,6);Print("No  : [F6]");
			do{
				GetKey(&key);
				if (key==KEY_CTRL_F6 || key==KEY_CTRL_EXIT){enter =0 ;break;}
				else if (KEY_CTRL_F1) {enter = 1;break;}
			}while(1);
			if(enter)
			{
				if(setup_data.zdmroute_name[0]==0)
				{
					WheterSavaAS3();
				}
				else
				{
					SaveSRDFile3(setup_data.zdmroute_name);
				}
			}
			return 0 ;
		case KEY_CTRL_F1:					/* Set */
			refresh = REDRAW_ALL;
			Selectfile3();
			break;
		case KEY_CTRL_F2:					/* Add */
			zdmroute_push_back (&zdmroute);
			y = zdmroute.size - 1;
			refresh = REDRAW_ALL;
			break;
		case KEY_CTRL_F3:					/* ins */
			//if (y==0) break;
			zdmroute_insert (&zdmroute,y);
			y++;
			refresh = REDRAW_ALL;
			break;
		case KEY_CTRL_F4:					/* Del a point */
			//if (y==0) break;
			refresh = REDRAW_ALL;
			PopUpWin(4);DispStr(25,10,"删 除 一 行?");
			locate(3,5);Print("[F1]Yes   [F6]No");
			GetKey(&key);
			if (key==KEY_CTRL_F1){
				zdmroute_del(&zdmroute,y);y--;
			}
			break;
			
		 case KEY_CTRL_F5:					/* Del All */
			refresh = REDRAW_ALL;
			PopUpWin(4);DispStr(25,10,"清 空 所 有 ?");
			locate(3,5);Print("[F1]Yes   [F6]No");
			GetKey(&key);
			if (key==KEY_CTRL_F1){
				zdmroute_initial(&zdmroute);
	            zdmroute_push_back(&zdmroute);
			}
			break;

         case KEY_CTRL_F6:
		    refresh = REDRAW_ALL;
			PopUpWin(4);
			PrintfXY (15,10,0,"%.3f",zdmroute.set[1].zdm_bbgc);  
			GetKey(&key);
			PrintfXY (15,20,0,"%.3f",zdmroute.set[2].zdm_bbgc);  
			GetKey(&key);
			PrintfXY (15,30,0,"%.3f",zdmroute.set[3].zdm_bbgc);  
			GetKey(&key);
			//PrintfXY (70,30,0,"%.3f",route.set[0].xy_zr);  
			DispStr(15,10,"线路名称");
			if(setup_data.zdmroute_name[0]==0)
			{
			 DispStr(25,27,"请保存线路文件 ");
			}
			 //else
			//{
             //DispStr(25,27,setup_data.zdmroute_name);
			//}
			GetKey(&key);
          	break;	
		default:							/*other things*/
			if (x>0 && (c=GetPressNumChar(key))!=0){
				char buffer[14];
				int r;
				//if (y==0 && x > 2)break;
				buffer[0] = c;
				buffer[1] = '\0';
				buffer[1] = '\0';
				r = InputString(49,42,buffer,0,12);
				if (r!=KEY_CTRL_EXIT){
					double * sd;
					sd =  (double*)&(zdmroute.set[y].zdm_bbzh);
					sd[x-1] = atof(buffer);
					switch(r){
					case KEY_CTRL_UP:	y--;break;
					case KEY_CTRL_DOWN:	y++;break;
					case KEY_CTRL_EXE:	x++;break;
					}
				}
				refresh = REDRAW_ALL;
			}
			else if (x==0 && (c=GetPressChar(key))!=0){
				char buffer[14];
				int r;
				buffer[0] = c;
				buffer[1] = '\0';
				r = InputString(49,42,buffer,1,12);
				if (r!=KEY_CTRL_EXIT){
					strncpy(zdmroute.set[y].name,buffer,12);
					switch(r){
					case KEY_CTRL_UP:	y--;break;
					case KEY_CTRL_DOWN:	y++;break;
					case KEY_CTRL_EXE:	x++;break;
					}
				}
				refresh = REDRAW_ALL;
			}
			break;
		}
		if (x<0) x = 3,y--;
		if (x>3) x = 0,y++;
		if (y<0) y = 0;
		if (y>=zdmroute.size) y = zdmroute.size - 1;
		if (y>top + 3) top = y - 3;
		if (y<top) top = y;
		if (x>left +3) left = x - 3;
		if (x<left) left = x;
	}
}

double zdm_to_gc( double stake)
{
	int i; 
	double qxc,length,gc;
	double I1,I2,bad,cave_vex;
	for(i=1;i<zdmroute.size-1;i++)
	{
		if(stake>zdmroute.set[i].zdm_zdzh && zdmroute.set[i+1].zdm_r!=0)
			continue;
		else{
			
			I1 = (zdmroute.set[i].zdm_bbgc-zdmroute.set[i-1].zdm_bbgc)/(zdmroute.set[i].zdm_bbzh-zdmroute.set[i-1].zdm_bbzh);//前纵坡
			I2 =(zdmroute.set[i+1].zdm_bbgc-zdmroute.set[i].zdm_bbgc)/(zdmroute.set[i+1].zdm_bbzh-zdmroute.set[i].zdm_bbzh); //后纵坡
			bad = I2 - I1;
			cave_vex = zdmroute.set[i].zdm_r * (bad>=0?1:-1);
			qxc = zdmroute.set[i].zdm_zdzh - zdmroute.set[i].zdm_bbzh;  
			length = stake - zdmroute.set[i].zdm_bbzh;    
			gc = zdmroute.set[i].zdm_bbgc+I1*length;
			length=length+qxc; //
			if(length>0)
				gc = gc+length*length/2.0/cave_vex; 
			else{
				length = length - qxc;
				if(length>qxc)
				gc = zdmroute.set[i].zdm_bbgc+I2*length; 
			  
			}
		}
	 break;
	}
	 
	 return gc;
}

