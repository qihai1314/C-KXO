#include "headfile.h"
#include "runmain.h"
#include "zbzfs.h"
#include "MyFont.h"
#include "cvs.h"
#include <stdarg.h>
          


int PrintTablesPM(short x,short y,char * str,short sel,short lbl)
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

int PrintTableFormatPM (short x,short y,short sel,short lbl,char * format,...)
{
	char buffer[128];
	va_list parglist;
	va_start(parglist, format);
	vsprintf(buffer,format, parglist);
	va_end(pArgList);
	buffer[6] = 0;
	PrintTablesPM(x,y,buffer,sel,lbl);
	return 0;
}
int PrintTableIndexPM (int y,int index)
{
	char buffer[8];
	if (index<0 || index>999) return 0;
	sprintf(buffer,"%d",index);
	y *= 8;
	Bdisp_AreaReverseVRAM(0,y,15,y+7);
	PrintMini(1,y+2,buffer,MINI_REV);
}
int WhetherCoverPM()
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
int WheterSavaASPM()
{
	char str[13]="";
	int suc,enter,i;
	for (i=0;i<13 && setup_data.jdfroute_name[i] != '.';++i)
		str[i] = setup_data.jdfroute_name[i];
	str[i>=13 ? 12 : i] = 0;
	PopUpWin(4);
	DispStr(24,8,"\xce\xc4\xbc\xfe\xc3\xfb(*.pm)");//file_name
	do
	{
		suc = InputString(24,24,str,1,8);
		if (suc==KEY_CTRL_EXIT) break;
		if (! str[0]) continue;
	}while(suc!=KEY_CTRL_EXE);
	if(suc!=KEY_CTRL_EXIT)
	{
		enter = 1;
		strcat(str,".pm");
		if (TestPMFile(str))
		{
			enter = WhetherCoverPM();
		}
		if (enter)
		{
			SavePMFile(str);
			strcpy(setup_data.pmroute_name,str);
		}
	}
}

int SelectfilePM()
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
					
					for (i=0;i<13 && setup_data.pmroute_name[i] != '.';++i)
						str[i] = setup_data.pmroute_name[i];
					str[i>=13 ? 12 : i] = 0;
					PopUpWin(4);
					DispStr(24,8,"\xce\xc4\xbc\xfe\xc3\xfb(*.pm)");//file_name
					do
					{
						suc = InputString(24,24,str,1,8);
						if (suc==KEY_CTRL_EXIT) break;
						if (! str[0]) continue;
					}while(suc!=KEY_CTRL_EXE);
					if(suc!=KEY_CTRL_EXIT)
					{
						enter = 1;
						strcat(str,".pm");
						if (TestJDFFile(str))
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
							SavePMFile(str);
							strcpy(setup_data.pmroute_name,str);
						}
					}     
					break;
				case 1:
					suc = SelectPMFile (str);
					if (suc==-1)
					{
						PopUpWin(1);
						locate(7,4);Print("No File!");
						GetKey(&key);
					}
					if(suc==1)
					{
						LoadPMFile  (str);
						strcpy(setup_data.pmroute_name,str);
						if(LoadPMFile  (setup_data.pmroute_name)==1)
						SaveIniPMFile();
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
							if(setup_data.pmroute_name[0]==0)
				            {
					            WheterSavaASPM();
				            }
				            else
				            {
					            SavePMFile(setup_data.pmroute_name);
				            }
						}						
						setup_data.pmroute_name[0]=0;
				        pmroute_initial(&pmroute);
	                    pmroute_push_back(&pmroute);
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


int PM_parameter()
{
	
	char * table_label[]= {"DH","QDZH","ZDZH","X","Y","FWJ","ZX","QDBJ","ZDBJ"};
	char * icons[]		= {"","","","",""};
	char * ch_text[]	= {"\xb5\xe3\xc3\xfb",
	                        "起点桩号",
							"终点桩号",
							"X坐标 ", 
							"Y坐标 ",
							"方位角 ",
							"转向 ",
							"起点半径",
							"终点半径"};
							
	int x = 0,y = 0,i,j,t;
	int left = 0,top = 0;
	int refresh = REDRAW_ALL;
	int enter,suc;
	char str[13]="";
	char c;
	

	PMproduce(); //打开交点参数转换平面参数
	InsertLine(l_pqx.length,&y,&refresh);
	GetListq();  //取链表链表线元参数

	while(1){
		if (refresh==REDRAW_ALL){
			Bdisp_AllClr_VRAM();
			for (i=0;i<4;++i)
			PrintTablesPM(i,0,table_label[left+i],1,1);
			t = pmroute.size<= 1 ? 2 : 5; //如果交点个数小于等于1 那么T=2 否则等于5
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
			for (i=top;i<top+4 && i<pmroute.size;++i){ 
				sd =  & (pmroute.set[i].pm_qk);
				for (j=(left==0 ? 1:0);j<4;++j){
					//if (i==0 && j+left>3)  //////////////////////////////////////////
					//PrintTablesPM(j,i+1-top,"",y==i && x-left==j,0);///////////////
					//else/////////
						PrintTableFormatPM(j,i+1-top,y==i && x-left==j,0,"%lf",sd[j+left-1]);
				}
				if (left==0)
					PrintTableFormatPM(0,i+1-top,y==i && x-left==0,0,"%s",pmroute.set[i].name);
				    PrintTableIndexPM(i-top+1,i);
			}
			SetMyFont(&stHz12x12,&stAsc6x12);
			if(x>0){
				//if (!(y==0 && x>2)){
					sd =  & (pmroute.set[y].pm_qk); //取地址的值***************
					DispStr(0,42,ch_text[x]);
					PrintFloat(sd[x-1],49,42,0,setup_data.point); //打印 
				//}
			}else{
				DispStr(0,42,ch_text[x]);
				PrintXY(51,44,pmroute.set[y].name,0);
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
			pmroute_initial(&pmroute);
	        pmroute_push_back(&pmroute);
		    InitList(&l_pqx);
			push_backList(&l_pqx);
			return 0 ;
			
		case KEY_CTRL_F1:					/* Set */
			refresh = REDRAW_ALL;
			SelectfilePM();
			break;
			
		case KEY_CTRL_F2:					/* Add */
		    pmroute_push_back (&pmroute);
			y = pmroute.size - 1;
			refresh = REDRAW_ALL;
			break;
			
		case KEY_CTRL_F3:					/* ins */
			//if (y==0) break;
			pmroute_insert (&pmroute,y);
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
				pmroute_del(&pmroute,y);y--;
			}
			break;
			
		 case KEY_CTRL_F5:					/* Del All */
			refresh = REDRAW_ALL;
			PopUpWin(4);DispStr(25,10,"清 空 所 有 ?");
			locate(3,5);Print("[F1]Yes   [F6]No");
			GetKey(&key);
			if (key==KEY_CTRL_F1){
				pmroute_initial(&pmroute);
	            pmroute_push_back(&pmroute);
			}
			break;
			

         case KEY_CTRL_F6:
		    refresh = REDRAW_ALL;
			//PrintfXY (70,30,0,"%.3f",route.set[0].xy_zr);  
			//DispStr(15,10,"线路名称");
			//if(setup_data.pmroute_name[0]==0)
			//{
			 //DispStr(25,27,"请保存线路文件 ");
			//}
			 //else
			//{
             //DispStr(25,27,setup_data.zdmroute_name);
			//}
          	break;	
		default:							/*other things*/
			if (x>0 && (c=GetPressNumChar(key))!=0){
				char buffer[14];
				int r;
				//if (y==0 && x > 3)break;
				buffer[0] = c;
				buffer[1] = '\0';
				r = InputString(49,42,buffer,0,12);
				if (r!=KEY_CTRL_EXIT){
					double * sd;
					sd =  (double*)&(pmroute.set[y].pm_qk);
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
					strncpy(pmroute.set[y].name,buffer,12);
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
		if (x<0) x = 8,y--;
		if (x>8) x = 0,y++;
		if (y<0) y = 0;
		if (y>=pmroute.size) y = pmroute.size - 1;
		if (y>top + 3) top = y - 3;
		if (y<top) top = y;
		if (x>left +3) left = x - 3;
		if (x<left) left = x;
	}
}

int InsertLine(int listLength,int* point_y,int* refresh)
{
	int i;
	for(i=0;i<listLength;i++)
	{
		pmroute_push_back (&pmroute);
		*point_y = pmroute.size - 1;
		*refresh = REDRAW_ALL;
	}
}

int GetListq()
{
	int iter;
	s_pqx temp;
	for(iter=0; iter<l_pqx.length; iter++)
	{	
        temp = GetList(&l_pqx,iter);
		pmroute.set[iter].pm_qk=temp.ss;
		pmroute.set[iter].pm_zk=temp.es;
		pmroute.set[iter].pm_qx=temp.sx;
		pmroute.set[iter].pm_qy=temp.sy;
		pmroute.set[iter].pm_qfj=temp.sa;
		pmroute.set[iter].pm_p_x=temp.v;
		pmroute.set[iter].pm_qr=temp.sp;
		pmroute.set[iter].pm_zr=temp.ep;
		PrintTableFormats1(15,15,0,0,"%lf", pmroute.set[iter].pm_qk);
		PrintTableFormats1(15,15,0,0,"%lf", pmroute.set[iter].pm_zk);
		PrintTableFormats1(15,15,0,0,"%lf", pmroute.set[iter].pm_qx);
		PrintTableFormats1(15,15,0,0,"%lf", pmroute.set[iter].pm_qy);
		PrintTableFormats1(15,15,0,0,"%lf", pmroute.set[iter].pm_qfj);
		PrintTableFormats1(15,15,0,0,"%lf", pmroute.set[iter].pm_p_x);
		PrintTableFormats1(15,15,0,0,"%lf", pmroute.set[iter].pm_qr);
		PrintTableFormats1(15,15,0,0,"%lf", pmroute.set[iter].pm_zr);
	}
} 

