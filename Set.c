#include "headfile.h"
#include "MyFont.h"


#define MENUITEM_N	5
static char TITLE[] = "";

int PrintTable(short x,short y,char * str,short sel,short lbl)
{
	int len;
	const int width = 28;
	len = strlen(str);
	x *= width;
	y *= 8;  //y*8=y
	x += 16;
	if (sel)
	{
		Bdisp_AreaReverseVRAM(x,y,x+width-1,y+7);
		//PrintMini(x+1+(lbl ? (width-5*len)/2:0),y+1,str,MINI_REV);
	}
	else
	{

		Bdisp_DrawLineVRAM(x+width-1,y,x+width-1,y+7);
		Bdisp_DrawLineVRAM(x,y+7,x+width-1,y+7);
		//PrintMini(x+1+(lbl ? (width-5*len)/2:0),y+1,str,MINI_OVER);
	}
}

int PrintTableFormat (short x,short y,short sel,short lbl,char * format,...)
{
	char buffer[128];
	va_list parglist;
	va_start(parglist, format);
	vsprintf(buffer,format, parglist);
	va_end(pArgList);
	buffer[6] = 0;
	PrintTable(x,y,buffer,sel,lbl);
	return 0;
}

int PrintTableIndex (int y,int index)
{
	char buffer[8];
	if (index<0 || index>999) return 0;
	sprintf(buffer,"%d",index);
	y *= 8;
	Bdisp_AreaReverseVRAM(0,y,15,y+7);
	//PrintMini(1,y+2,buffer,MINI_REV);
}


void SaveIniFile();
char file_name[30]="";

//# ifndef RELEASE
//static FONTCHARACTER IniFile[] = { '\\','\\','f','l','s','0','\\','c','s','v','.','i','n','i' ,'\0'} ;
//# else
static FONTCHARACTER IniFile[] = { '\\','\\','c','r','d','0','\\','c','s','v','.','i','n','i' ,'\0'} ;
static FONTCHARACTER IniSet[] = { '\\','\\','c','r','d','0','\\','s','e','t','.','i','n','i' ,'\0'} ;
//# endif

void SaveIniFile()   //存数据
{
	int ptr = -1;
	int ln;
	Bfile_DeleteFile(IniFile);
	ln=strlen(file_name);
	if(ln==0)
		return;
	if (Bfile_CreateFile(IniFile, ln) < 0) //Error("创建文件失败") ;
		return;
	//	else Error("创建文件OK") ;
	ptr = Bfile_OpenFile(IniFile, _OPENMODE_WRITE) ;  // Bfile_OpenFile : 打开一个现有的文件。
	if (ptr >= 0) {
		Bfile_WriteFile(ptr, file_name, ln) ;
		Bfile_CloseFile(ptr) ;
	}
}

BOOL LoadLastDataFile()   //取数据
{
	char strFileName[50]; //字串文件名50个下标0开始
	int reg_ptr = -1;
	int ln;
	if(file_name[0]==0)	//从ini文件中读出上次的文件名
	{
		reg_ptr = Bfile_OpenFile(IniFile, _OPENMODE_READ) ; //// Bfile_OpenFile : 打开一个现有的文件。
		if (reg_ptr >= 0) {
			ln=Bfile_GetFileSize(reg_ptr);
			if(ln>0)
			{
				if(ln>=sizeof(file_name)-1)
					ln=sizeof(file_name)-1;
				Bfile_ReadFile(reg_ptr, file_name,ln,0) ;
				file_name[ln]=0;
			}
			Bfile_CloseFile(reg_ptr) ;
			sprintf(strFileName,"%s\\%s",szCsvDir,file_name);
			LoadDataFile(strFileName);
			return TRUE;
		}		
	}
	
	return FALSE;
}

int PushIniFile(int index,char s[])  //将s存放在set.ini文件的第index行
{
	
	char strFileName[50]; //字串文件名50个下标0开始
	int reg_ptr = -1;     
	int ln,l;              //ln存放s的长度，l存放set.int的大小
	int i,j,k;
	int EnterNumber = 0;
	ln=strlen(s);
	if(ln==0)
		return 0;
	reg_ptr = Bfile_OpenFile(IniSet, _OPENMODE_WRITE); //// Bfile_OpenFile : 打开一个现有的文件。
	if(reg_ptr<0&&index==0)
	{
		Bfile_DeleteFile(IniSet);
	    if (Bfile_CreateFile(IniSet, ln) < 0) //Error("创建文件失败") ; 路径文件名，大小
		    return 0;
		k = Bfile_OpenFile(IniSet, _OPENMODE_WRITE); //打开文件，打开模式是编写，返回值指定一个文件句柄，它是大于或等于0。
		sprintf(strFileName,"%s,",s);
		Bfile_WriteFile(k,strFileName,2); //handle of the file to write,pointer to buffer that writes data,number of bytes to write
		Bfile_CloseFile(k);
		return 1;
	}
	if (reg_ptr >= 0)
	{
		//reg_ptr = Bfile_OpenFile(IniSet, _OPENMODE_WRITE);
		l=Bfile_GetFileSize(reg_ptr); //获得文件字节大小
		Bfile_ReadFile(reg_ptr,strFileName,l,0); //处理文件的阅读，指向缓冲区读取数据，读取的字节数，指定位置读取
		Bfile_CloseFile(reg_ptr);//关闭一个打开的文件句柄
		for(i= 0;i<l;i++)
		{
			if(index>=EnterNumber&&index<(EnterNumber+1))  //在第一行和小于第一行的情况
			{
				for(j=i;j<ln&&strFileName[j]!=',';j++)
				{
					strFileName[j] = l;
				}
				EnterNumber++;
				break;
			}
			if(strFileName[i]==',')
			    EnterNumber++;
		}
		
		if(index>=EnterNumber)
		{
			for(j = i;j<ln+i;j++)
			{
				strFileName[j] = s[j-i];
			}
		    strFileName[j+1] = 0;
		    strFileName[j+2] = ',';
		}
		Bfile_DeleteFile(IniSet);
		if (Bfile_CreateFile(IniSet, ln) < 0) //Error("创建文件失败") ;
		     return 0;
	    reg_ptr = Bfile_OpenFile(IniSet, _OPENMODE_WRITE);
		Bfile_WriteFile(reg_ptr,strFileName,l);
		Bfile_CloseFile(reg_ptr);
	    return 1;
	}
	
	return 0;
}

int SET()

{   
    
	const BYTE *strMenu[MENUITEM_N]={

		"",
		"",
		"",
		"",
		""
	};
	double value[4] = {0.0,0.0,0.0,0.0};
	
	char ch;
	char strFileName[50];
	unsigned int key; 
	int need_redraw;
	int i,suc;
	int  index = 0;
	int button = 0;
	int need_pointout = 0;
	need_redraw = 1;
	i = setup.db_dir;
	zfset.zsm=value[1];
	yscs.d=value[2];
	yscs.d=value[3];
	PushIniFile(0,"1");
	while(1){
		if (need_redraw){
			int x,y;
			need_redraw = REFRESH_PART;
			Bdisp_AllClr_VRAM();
			SetMyFont(&stHz12x12,&stAsc6x12);
			DispStr(2,9, "设 ");
			DispStr(2,32,"置 ");
			ShowTitle(TITLE);
			sprintf(strFileName,"%s\\%s",szCsvDir,file_name);//+++++++++++
			if(file_name[0]==0&&button==0)
			    DispStr(50,4,"EXE选择文件 "); //显示选中后的线路文件+++++++++++++
			else if(file_name[0]!=0&&button==0)
				DispStr(50,4,file_name);
			else if(button==1)
			{
			    DispStr(50,4,"计算器数据 ");	
			}
			DispStr(17,4,"线路 ");	
			DispStr(17,17,"间距 ");
			DispStr(17,28,"边距L ");
			DispStr(17,40,"边距R ");
		}
		
	    if (need_redraw  == REFRESH_PART){    	 
	         for (i=0;i<4;++i){
             if (i==0)  Bdisp_AreaReverseVRAM(48,4+index*12,45+13*6,index*12+15);
			 if (i==1)	PrintFloat(value[i],48,4+i*12,index==i,3);
			 if (i==2)	PrintFloat(value[i],48,4+i*12,index==i,3);
		     if (i==3)	PrintFloat(value[i],48,4+i*12,index==i,3);
			 }  
		     need_redraw  = 0;	 
		}
		if(button==1&&need_pointout == 1)
		{
			PopUpWin(1);
		    SetMyFont(&stHz12x12,&stAsc6x12);
		    locate(7,4);
			DispStr(15,21,"已加载参数区数据 ");	
			need_pointout = 0;
			need_redraw = REFRESH_PART;
		}			
		GetKey(&key);
		switch(key){
		    case KEY_CTRL_UP:		 
			        need_redraw = REFRESH_PART; 	 
			        --index;  	
					break; 
			case KEY_CTRL_DOWN:		
			        need_redraw = REFRESH_PART;	     
					++index; 	
					break;
			case KEY_CTRL_RIGHT:  
                    need_pointout = 1;			
			        need_redraw = REFRESH_PART;      
					++button;  
					break;
			case KEY_CTRL_LEFT:        
			        need_redraw = REFRESH_PART;
                    need_pointout = 1;					
					--button;  
					break;
		    default:
		        if ((ch=GetPressNumChar(key))!=0 && index >= 1)
				{
					char buf[14];
					int        r;
					need_redraw = REFRESH_PART;
					buf[0] = ch;   buf[1] = '\0';
					r = InputString (48,4+index*12,buf,0,12); //注意位移输入框的位置
					if (r != KEY_CTRL_EXIT)
					{
						value[index] = atof(buf);
						
						if (index == 2)    yscs.d=value[2];      //将值付给边桩
						if (index == 3)    yscs.d=value[3];  //将值付给边桩
						
						if	(r==KEY_CTRL_DOWN)		++index;
						if	(r==KEY_CTRL_UP)	--index;
						if (r==KEY_CTRL_EXE && index<3)	++index;
					}
					break;
			    }
				
			    if (key == KEY_CTRL_EXE && index == 0&& button == 0) 
				{
				    setup.db_dir = i;
				    need_redraw = 1;
				    suc = SelectFile(file_name);//打开选择文件  并将个数保存suc
				    if (suc==-1)
					{
				        PopUpWin(1);    //弹出对话框
				        SetMyFont(&stHz12x12,&stAsc6x12);
				        locate(7,4);
				        DispStr(28,21,"没有线路文件 ");	
				        GetKey(&key);
				    }
					
				    if(suc==1)
					{  
 			        //locate(120,40); Print(strFileName);///////////////////////////////////////////////////
   			        //GetKey(&key);///////////////////////////////////////////////////
			        //strFileName; ///////////////////////////////////////////////////
				    sprintf(strFileName,"%s\\%s",szCsvDir,file_name);
				    if(LoadDataFile(strFileName)==1)
				    SaveIniFile();
				    }
					
			    }   
				break;
			case KEY_CTRL_F2:
					setup.db_dir = i;
					need_redraw = 1;
					PQX_disp();
					break;
		    case KEY_CTRL_F3:
					setup.db_dir = i;
					need_redraw = 1;
					SQX_disp();
					break;
			case KEY_CTRL_F4:
					setup.db_dir = i;
					need_redraw = 1;
					HP_disp();
					break;
					
			//case KEY_CTRL_F5:
					//setup.db_dir = i;
					//need_redraw = 1;
					//ChangeSetup();
					//break;		
			case KEY_CTRL_EXIT:		return 1;	break;
		}
		
		if (index >=4) index = 0;
		if (index < 0) index = 3;
        if (button>=2) button= 0;
        if (button< 0) button= 1;		
		
	}

}








