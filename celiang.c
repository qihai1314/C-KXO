#include<stdio.h>
#include "headfile.h"
#include "runmain.h"
#include "MyFont.h"


unsigned int key;
int mode,index,need_redraw;
COMMONDATA common_data={0,0,0,0,{0,0,0,0},0,0};
double *value = common_data.value;



void ShowTitle (char *title)
{
	//PrintChStrV(title,1,0);
	Bdisp_AreaReverseVRAM(1,0,13,50);
}

int InputDefProc (double *value,int index_max,int px,int py,int next_mode,int pre_mode)
{
	char ch;
	if (key==KEY_CTRL_UP)
	{
		if(--index<0)index = index_max-1;
		need_redraw = REDRAW_PART;
	}
	else if(key==KEY_CTRL_DOWN)
	{
		if(++index>index_max-1)index = 0;
		need_redraw = REDRAW_PART;
	}
	if (key==KEY_CTRL_EXIT)
	{
		mode = pre_mode;
	}
	if ((ch=GetPressNumChar(key))!=0 
			/*|| key==KEY_CTRL_LEFT || key==KEY_CTRL_RIGHT*/
			|| key==KEY_CTRL_DEL || key==KEY_CTRL_AC)
	{
		int suc;
		char str[30];
		/*if(key==KEY_CTRL_LEFT || key==KEY_CTRL_RIGHT)
		{
			ftoa(str,value[index],4);
		}*/
		if (key==KEY_CTRL_DEL || key==KEY_CTRL_AC)
		{
			str[0] = 0;
		}
		else
		{
			str[0] = ch;str[1] = 0;
		}
		suc = InputString(px,py+index*12,str,0,12);
		if(suc != KEY_CTRL_EXIT)
		{
			if(strlen(str)>0)value[index] = atof(str);
			switch(suc)
			{
				case KEY_CTRL_DOWN:
				case KEY_CTRL_EXE:
					if(++index>index_max-1)
					{
						mode = next_mode;
						index = 0;
					}
					break;
				case KEY_CTRL_UP:
					if(--index<0)index = index_max-1;
					break;
			}
		}
		else
		{
			mode = pre_mode;
		}
		need_redraw = 1;
	}
	return 0;
}

struct list l_pqx; 

s_sqx  l_sqx[19];

QXYS	qxys[2];
HPYS	hpys[50];
ZFSET	zfset	=	{0.0,0.0,0.0,0.0};
SETUP	setup	=	{0,0,0,0,0,0.0,0.0,0.0};
YSCS	yscs	=	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}; 

int LoadInit()
{
	int i;
	SetMyFont(&stHz14x14,&stAsc6x12);
	DispStr(22,4,"\xB2\xE2\xBC\xC6\xCA\xA6\xCC\xE5\xD1\xE9\xB0\xE6"); 
	for (i=10;i<118;++i){	
	    Bdisp_SetPoint_DD (i,55,1);
	    Bdisp_SetPoint_DD (i,56,1);
		Bdisp_SetPoint_DD (i,57,1);
		Bdisp_SetPoint_DD (i,58,1);
		Bdisp_SetPoint_DD (i,59,1);
		Bdisp_SetPoint_DD (i,60,1);
		Bdisp_SetPoint_DD (i,61,1);
		Bdisp_SetPoint_DD (i,62,1);
		Bdisp_SetPoint_DD (i,63,1);
		Bdisp_SetPoint_DD (i,64,1);
		Bdisp_DrawLineVRAM(0,31,127,31);
        Bdisp_DrawLineVRAM(63,0,63,63);
		Sleep(10);
	    }  

}



int AddIn_main(int isAppli, unsigned short OptionNum)
{
	uint refresh = 1,key;
	int nMenuIdx=-1;
	Bdisp_AllClr_DDVRAM(); 
	//while (CheckReg() != TRUE) ;
	Bdisp_AllClr_DDVRAM();
	JDFNewFolder();
	XYNewFolder();
	ZDMNewFolder();
	PMNewFolder();
	route_initial(&route);
	route_push_back(&route);
	
	jdfroute_initial(&jdfroute);
	jdfroute_push_back(&jdfroute);
	
	zdmroute_initial(&zdmroute);
	zdmroute_push_back(&zdmroute);
	
	pmroute_initial(&pmroute);
	pmroute_push_back(&pmroute);	
	LoadInit(); //加载测计师注册版
	
	//LoadLastDataFile(); //加载要素表格
	
	LoadLastDataJDFFile();
	
	LoadLastDataSRDFile();
	
	LoadLastDataSRDFile3();
	
	
	
	MenuInit();
	
    Bdisp_AllClr_DDVRAM();
    while(1){
			Bdisp_AllClr_VRAM();
			ListMenu();
			nMenuIdx=DoMyMenu();

		switch(nMenuIdx){
			case 1:
				refresh = 1;
				computeZS();
				break;
			case 2:
				refresh = 1;
				computeFS();
				break;
			//case 3:
				//refresh = 1;
				//SD();
				//break;
			case 5:
			    refresh = 1;
				ChangeSetup ();
				break;	
				
				
			case 7:	
			refresh = 1;
			JDF_parameter();
			break;	
		
			case 8:	
			refresh = 1;
			XY_parameter();
			break;
			
			case 9:	
			refresh = 1;
			ZDM_parameter();
			break;

			case 17:	
			refresh = 1;
			PM_parameter();
			break;
			
			
				
			case 22:
				refresh = 1;
				BinMain_1();
				break;
				
			case 23:
				refresh = 1;
				BinMain_2();
				break;	
				
			case -1:
				refresh = 1;
				About();
				break;
		}
    }
    return 1;
}


int JDFNewFolder()
{
	# ifdef RELEASE
	FONTCHARACTER pt_folder[] = { '\\','\\','f','l','s','0','\\','J','D','F','\0'} ;
	# else
	FONTCHARACTER pt_folder[] = { '\\','\\','c','r','d','0','\\','J','D','F','\0'} ;
	# endif
	
	Bfile_CreateDirectory(pt_folder) ;
}

int XYNewFolder()
{
	# ifdef RELEASE
	FONTCHARACTER pt_folder[] = { '\\','\\','f','l','s','0','\\','S','R','D','\0'} ;
	# else
	FONTCHARACTER pt_folder[] = { '\\','\\','c','r','d','0','\\','S','R','D','\0'} ;
	# endif
	
	Bfile_CreateDirectory(pt_folder) ;
}

int ZDMNewFolder()
{
	# ifdef RELEASE
	FONTCHARACTER pt_folder[] = { '\\','\\','f','l','s','0','\\','Z','D','M','\0'} ;
	# else
	FONTCHARACTER pt_folder[] = { '\\','\\','c','r','d','0','\\','Z','D','M','\0'} ;
	# endif
	
	Bfile_CreateDirectory(pt_folder) ;
}


int PMNewFolder()
{
	# ifdef RELEASE
	FONTCHARACTER pt_folder[] = { '\\','\\','f','l','s','0','\\','P','M','\0'} ;
	# else
	FONTCHARACTER pt_folder[] = { '\\','\\','c','r','d','0','\\','P','M','\0'} ;
	# endif
	
	Bfile_CreateDirectory(pt_folder) ;
}





#pragma section _BR_Size
unsigned long BR_Size;
#pragma section

#pragma section _TOP
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}
#pragma section
