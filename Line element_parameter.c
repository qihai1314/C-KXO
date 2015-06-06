#include "headfile.h"
#include "runmain.h"
#include "zbzfs.h"
#include "MyFont.h"
#include "cvs.h"
#include <stdarg.h>
            

double sd_to_xyaSrd( double stake, double distance, double angle, int xya );
double xy_to_sdSrd( double PX, double PY, int sd );
			
			
int PrintTables(short x,short y,char * str,short sel,short lbl)
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
int PrintTableFormats (short x,short y,short sel,short lbl,char * format,...)
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
int PrintTableIndexs (int y,int index)
{
	char buffer[8];
	if (index<0 || index>999) return 0;
	sprintf(buffer,"%d",index);
	y *= 8;
	Bdisp_AreaReverseVRAM(0,y,15,y+7);
	PrintMini(1,y+2,buffer,MINI_REV);
}
int WhetherCover()
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
int WheterSavaAS()
{
	char str[13]="";
	int suc,enter,i;
	for (i=0;i<13 && setup_data.route_name[i] != '.';++i)
		str[i] = setup_data.route_name[i];
	str[i>=13 ? 12 : i] = 0;
	PopUpWin(4);
	DispStr(24,8,"\xce\xc4\xbc\xfe\xc3\xfb(*.srd)");//file_name
	do
	{
		suc = InputString(24,24,str,1,8);
		if (suc==KEY_CTRL_EXIT) break;
		if (! str[0]) continue;
	}while(suc!=KEY_CTRL_EXE);
	if(suc!=KEY_CTRL_EXIT)
	{
		enter = 1;
		strcat(str,".srd");
		if (TestSRDFile(str))
		{
			enter = WhetherCover();
		}
		if (enter)
		{
			SaveSRDFile(str);
			strcpy(setup_data.route_name,str);
		}
	}
}

int SelSetupF5()
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
					
					for (i=0;i<13 && setup_data.route_name[i] != '.';++i)
						str[i] = setup_data.route_name[i];
					str[i>=13 ? 12 : i] = 0;
					PopUpWin(4);
					DispStr(24,8,"\xce\xc4\xbc\xfe\xc3\xfb(*.srd)");//file_name
					do
					{
						suc = InputString(24,24,str,1,8);
						if (suc==KEY_CTRL_EXIT) break;
						if (! str[0]) continue;
					}while(suc!=KEY_CTRL_EXE);
					if(suc!=KEY_CTRL_EXIT)
					{
						enter = 1;
						strcat(str,".srd");
						if (TestSRDFile(str))
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
							SaveSRDFile(str);
							strcpy(setup_data.route_name,str);
						}
					}     
					break;
				case 1:
					suc = SelectFiles (str);
					if (suc==-1)
					{
						PopUpWin(1);
						locate(7,4);Print("No File!");
						GetKey(&key);
					}
					if(suc==1)
					{
						LoadSRDFile (str);
						strcpy(setup_data.route_name,str);
						if(LoadSRDFile (setup_data.route_name)==1)
						SaveIniSRDFile();
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
							if(setup_data.route_name[0]==0)
				            {
					            WheterSavaAS();
				            }
				            else
				            {
					            SaveSRDFile(setup_data.route_name);
				            }
						}						
						setup_data.route_name[0]=0;
				        route_initial(&route);
	                    route_push_back(&route);
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


int XY_parameter()
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
	SetMyFont(&stHz12x12,&stAsc6x12);
   
	while(1){
		if (refresh==REDRAW_ALL){
			Bdisp_AllClr_VRAM();
			for (i=0;i<4;++i)
			     PrintTables(i,0,table_label[left+i],1,1);
			t = route.size<= 1 ? 2 : 5; //条件为真输出为2 否者为5
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
			for (i=0;i< t;++i)
			PrintIcon(i,icons[i],0);
			PrintIcon(5,"?",0);
			refresh = REDRAW_PART;
		}
		if (refresh==REDRAW_PART){
			double * sd;
			for (i=top;i<top+4 && i<route.size;++i){
				sd =  & (route.set[i].qd_zh);
				for (j=(left==0 ? 1:0);j<4;++j){
					//if (i==0 && j+left>2)
						//PrintTable(j,i+1-top,"",y==i && x-left==j,0);
					//else
						PrintTableFormats(j,i+1-top,y==i && x-left==j,0,"%lf",sd[j+left-1]);
				}
				if (left==0)
					PrintTableFormats(0,i+1-top,y==i && x-left==0,0,"%s",route.set[i].name);
				    PrintTableIndexs(i-top+1,i);
			}
			SetMyFont(&stHz12x12,&stAsc6x12);
			if(x>0){
				//if (!(y==0 && x>2)){
					sd =  & (route.set[y].qd_zh);
					DispStr(0,42,ch_text[x]);
					PrintFloat(sd[x-1],49,42,0,setup_data.point);
				//}
			}else{
				DispStr(0,42,ch_text[x]);
				PrintXY(51,44,route.set[y].name,0);
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
				if(setup_data.route_name[0]==0)
				{
					WheterSavaAS();
				}
				else
				{
					SaveSRDFile(setup_data.route_name);
				}
			}
			return 0 ;
		case KEY_CTRL_F1:					/* Set */
			refresh = REDRAW_ALL;
			SelSetupF5();
			break;
		case KEY_CTRL_F2:					/* Add */
			route_push_back (&route);
			y = route.size - 1;
			refresh = REDRAW_ALL;
			break;
		case KEY_CTRL_F3:					/* ins */
			//if (y==0) break;
			route_insert (&route,y);
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
				route_del(&route,y);y--;
			}
			break;
			
		 case KEY_CTRL_F5:					/* Del All */
			refresh = REDRAW_ALL;
			PopUpWin(4);DispStr(25,10,"清 空 所 有 ?");
			locate(3,5);Print("[F1]Yes   [F6]No");
			GetKey(&key);
			if (key==KEY_CTRL_F1){
				route_initial(&route);
	            route_push_back(&route);
			}
			break;

         case KEY_CTRL_F6:
		    refresh = REDRAW_ALL;
			PopUpWin(4);
			//PrintfXY (15,30,0,"%.3f",route.set[0].xy_qr);  
			//PrintfXY (70,30,0,"%.3f",route.set[0].xy_zr);  
			DispStr(15,10,"线路名称");
			if(setup_data.route_name[0]==0)
			{
			 DispStr(25,27,"请保存线路文件 ");
			}
			 //else
			//{
             //DispStr(25,27,setup_data.route_name);
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
				r = InputString(49,42,buffer,0,12);
				if (r!=KEY_CTRL_EXIT){
					double * sd;
					sd =  (double*)&(route.set[y].qd_zh);
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
					strncpy(route.set[y].name,buffer,12);
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
		if (y>=route.size) y = route.size - 1;
		if (y>top + 3) top = y - 3;
		if (y<top) top = y;
		if (x>left +3) left = x - 3;
		if (x<left) left = x;
	}
}


double sd_to_xyaSrd( double stake, double distance, double angle, int xya )
{	

    int i;
	double xy_a;
	double xy_qr;
	double xy_zr;
	
	for(i=0; i<=route.size; i++)
	{	
 
        if ( stake<route.set[0].qd_zh )  stake=route.set[0].qd_zh;
		if( stake>=route.set[i].qd_zh && stake<=route.set[i].zd_zh )
		{	
	        if (route.set[i].xy_qr < 1e-10)
			{  
		       xy_qr = 0;
		    }
			else
			{  
		       xy_qr = 1 / route.set[i].xy_qr;
			}
			if (route.set[i].xy_zr < 1e-10)
			{  
		       xy_zr=0;
		    }
			else
			{  
               xy_zr = 1 / route.set[i].xy_zr;
			}
			
			xy_a=deg(route.set[i].xy_a);
			
		    intialCZb(route.set[i].qd_zh, route.set[i].zd_zh, route.set[i].xy_x,route.set[i].xy_y, xy_a,route.set[i].xy_v,xy_qr,xy_zr);
			
			switch( xya )
			{	case 0:
					return zbzs_x(stake, distance, angle);
					break;
				case 1:
					return zbzs_y(stake, distance, angle);
					break;
				default:
					return zbzs_a(stake, distance, angle);
			}
		}
	}
	return 0;	
}



double xy_to_sdSrd( double PX, double PY, int sd )
{	

	double x = PX;
	double y = PY;

	double stake   = 0;		
	double mindist = 0;		
	
	int inum = 0;		

	double ex, ey, ea;
	double ped;
	double sx, sy, sa;	
	double psd;		
    double swapdist;
	int i;
	double xy_a;
	double xy_qr;
	double xy_zr;
	for(i=0; i<route.size; i++)
	{	
		sx = route.set[i].xy_x;
		sy = route.set[i].xy_y;
		sa = deg(route.set[i].xy_a);
		psd = (y - sy) * cos( rad(sa - 90) ) - (x - sx) * sin( rad(sa - 90) ); //结果可能正负
		
		if (route.set[i].xy_qr < 1e-10)
			{  
		       xy_qr = 0;
		    }
			else
			{  
		       xy_qr = 1 / route.set[i].xy_qr;
			}
		if (route.set[i].xy_zr < 1e-10)
			{  
		       xy_zr=0;
		    }
			else
			{  
               xy_zr = 1 / route.set[i].xy_zr;
			}

		intialCZb(route.set[i].qd_zh, route.set[i].zd_zh, route.set[i].xy_x,route.set[i].xy_y,deg(route.set[i].xy_a),route.set[i].xy_v,xy_qr,xy_zr);

		ex = zbzs_x(route.set[i].zd_zh, 0, 0);
		ey = zbzs_y(route.set[i].zd_zh, 0, 0);
		ea = zbzs_a(route.set[i].zd_zh, 0, 0);
		
		ped = (y - ey) * cos( rad(ea -90) ) - (x - ex) * sin( rad(ea - 90) );

		if( psd * ped <= 0)  
		{	inum++;
			if( inum==1 )
			{	mindist = zbfs_d(x, y);
				stake = zbfs_s(x, y);
			}
			else
			{	swapdist = zbfs_d(x, y);
				if( fabs(swapdist) < fabs(mindist) )
				{	mindist = swapdist;
					stake = zbfs_s(x, y);
				}
			}
		}
	}

	if( inum == 0 )
	{	return -(1e10);
	}

	if( sd==0 )
	{	return stake;
	}
	else
	{	return mindist;
	}
}


