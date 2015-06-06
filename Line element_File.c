#include "headfile.h"
#include "MyFont.h"
#include "runmain.h"

FONTCHARACTER * CharToFonts(const char *cFileName,FONTCHARACTER *fFileName);
char * FontToChars(const FONTCHARACTER *fFileName,char *cFileName);

//////////////////////////////////////////////////////////////
//					  Char <=> Font
///////////////////////////////////////////////////////////////
FONTCHARACTER * CharToFonts(const char *cFileName,FONTCHARACTER *fFileName)
{
	int i,len = strlen(cFileName);
	for(i=0; i<len ;++i)
		fFileName[i] = cFileName[i];
	fFileName[i]=0;
	return fFileName;
}
char * FontToChars(const FONTCHARACTER *fFileName,char *cFileName)
{
	int i = 0;
	while((cFileName[i]=fFileName[i])!=0)++i;
	return cFileName;
}

///////////////////////////////////////////////////////////////
//						File Directory
///////////////////////////////////////////////////////////////
int CreateDirectorys()
{
	FONTCHARACTER f_path_name[20];
	Bfile_CreateDirectory(CharToFonts("\\\\crd0\\SRD",f_path_name));
}

char szSrdDir[]="\\\\crd0\\SRD";
//char szSrdDir[]="\\\\fls0\\SRD";

///////////////////////////////////////////////////////////////
//							File List
///////////////////////////////////////////////////////////////
int SelectFiles (char * file_name)
// -1 no file , 1 complate ,0 cancel
{
	int key;
	char str[50]; //字符数组长度下标从0开始，共50个元素
	FONTCHARACTER find_path[50];   //获得路径
	FONTCHARACTER find_name[50];   //获得名字
	int find_h;
	int size = 0;
	int top = 0;
	int buttom = 0;
	int index,r,y;
	char *files;
	FILE_INFO file_info;
//	CharToFont("\\\\fls0\\SRD\\*.srd",find_path);
	sprintf(str,"%s\\*.srd",szSrdDir);
	CharToFonts(str,find_path);
	if(Bfile_FindFirst (find_path,&find_h,find_name,&file_info)==0)  //函数搜索目录中文件的名称符合指定的文件名
	{
		int i=0,ret;
		BOOL bFindFirst=TRUE; //定义一个布尔型变量初始化为真(true),对于bool类型，值只要不是0就是为真，即true；当值为0时为假，即false；
		size ++;  //使用size之后再加一（先计算再操作）
		while(Bfile_FindNext(find_h,find_name,&file_info)==0) //Bfile_FindNext 函数使用搜索处理定位匹配一个给定名称的文件名称。
		size++;
		Bfile_FindClose(find_h);  //Bfile_FindClose 关闭搜索指定处理函数
		files = (char*)malloc(size*13);
		index = 0;
		for(;;)
		{
			if(bFindFirst)  //if 值为真
				ret=Bfile_FindFirst (find_path,&find_h,find_name,&file_info);
			else 
				ret=Bfile_FindNext(find_h,find_name,&file_info);
			if(ret!=0)  //if 
				break;
			strncpy((files+13*i),FontToChars(find_name,str),13);
			if(strcmp((files+13*i),setup_data.route_name)==0) //文件选中后，现在记忆位置
			index=i; 
			i++;
			bFindFirst=FALSE;  //令值为假 即=0
		}
		Bfile_FindClose(find_h);  //Bfile_FindClose 关闭搜索指定处理函数
		r = 1;
		top = 0;
		buttom = 4;
		while(1)   
		{
			if (r)
			{
				Bdisp_AllClr_VRAM();
				//PopUpWin(6);
				DispStr(20,8,"线路文件: ");
				if (buttom-top>3)buttom = top + 3;
				if(top>index)
				{
					top = index;
					buttom = index + 3;
				}
				if (index>buttom)
				{
					buttom = index;
					top = buttom - 3;
				}
				if(buttom>size - 1)buttom = size - 1;
				if(top<0) top = 0;
				for (i=top;i<=buttom;++i)
				{
					//sprintf(str,"%13.13s",(files+13*i));
					//y=2+(i-top)*13;   //顶部文件位置
					//SetMyFont(&stHz12x12,&stAsc6x12);
					//DispStr(18,y,str); //str[]是字符串
					//if(index==i)
					//Bdisp_AreaReverseVRAM(15,y,20+13*6,y+11);
				    PrintfXY(20,22+(i-top)*8,index==i,"%13.13s",(files+13*i));
				}
				PrintXY(100,22,top>0?"\xE6\x92":" ",0);
				PrintXY(100,46,buttom<size-1?"\xE6\x93":" ",0);
				r = 0;
			}
			GetKey(&key);
			if (key==KEY_CTRL_UP) 	{if(--index<0) index = size - 1;r = 1;}
			if (key==KEY_CTRL_DOWN)	{if(++index>size - 1) index = 0;r = 1;}
			if (key==KEY_CTRL_EXE)
			{
				strcpy(file_name,(files+13*index));
				free (files);
				return 1;
			}
			if (key==KEY_CTRL_EXIT)
			{
				free (files);
				return 0;
			}
		}
	}
	else
		return -1;
	
}
///////////////////////////////////////////////////////////////
//							SRD
///////////////////////////////////////////////////////////////
int TestSRDFile (const char *file_name_c_a)
{
	FONTCHARACTER file_name_f[30];
	char file_name_c[30];
	int file_h;

	sprintf (file_name_c,"\\\\crd0\\SRD\\%s",file_name_c_a);	

	CharToFonts(file_name_c,file_name_f);
	file_h = Bfile_OpenFile (file_name_f,_OPENMODE_READ);
	
	if (file_h <0)
		return 0;
	else
	{
		Bfile_CloseFile (file_h);
		return 1;
	}
}

int DelSRDFile (const char *file_name_c_a)
{
	FONTCHARACTER file_name_f[30];
	char file_name_c[30];
	int file_h;

	sprintf (file_name_c,"\\\\crd0\\SRD\\%s",file_name_c_a);	

	CharToFonts(file_name_c,file_name_f);
	Bfile_DeleteFile (file_name_f);
	return 0;
}

int SaveSRDFile (const char *file_name_c_a)
{
	FONTCHARACTER file_name_f[30];
	char file_name_c[30];
	int file_h;

	sprintf (file_name_c,"\\\\crd0\\SRD\\%s",file_name_c_a);

	CharToFonts(file_name_c,file_name_f);
	
	Bfile_DeleteFile (file_name_f);
	Bfile_CreateFile (file_name_f,
	route.size * sizeof(POINT) + sizeof (ROUTE));
	file_h = Bfile_OpenFile (file_name_f,_OPENMODE_WRITE);
	
	Bfile_SeekFile (file_h,0);
	Bfile_WriteFile (file_h,&route,sizeof(ROUTE));
	
	Bfile_SeekFile (file_h,sizeof(ROUTE));
	Bfile_WriteFile (file_h,route.set,route.size * sizeof(POINT));

	Bfile_CloseFile (file_h);
	return 0;	
}

int LoadSRDFile (const char *file_name_c_a)    
{
	FONTCHARACTER file_name_f[30];
	char file_name_c[30];
	int file_h;
	
	sprintf (file_name_c,"\\\\crd0\\SRD\\%s",file_name_c_a);	

	CharToFonts(file_name_c,file_name_f);

	file_h = Bfile_OpenFile (file_name_f,_OPENMODE_READ);
	if(file_h>=0){
	    route_clr (&route);
	    Bfile_ReadFile(file_h,&route,sizeof(ROUTE),0);
	    route.set = (POINT*)calloc(route.size,sizeof(POINT));
	    Bfile_ReadFile(file_h,route.set,sizeof(POINT)*route.size,sizeof(ROUTE));
	
	    Bfile_CloseFile (file_h);
	    return 1;
	}
	return 0;
}


///////////////////////////////////////
/// ini
///////////////////////////////////////


//static FONTCHARACTER IniFile[] = { '\\','\\','f','l','s','0','\\','s','r','d','.','i','n','i' ,'\0'} ;
static FONTCHARACTER IniSRDFile[] = { '\\','\\','c','r','d','0','\\','s','r','d','.','i','n','i' ,'\0'} ;


void SaveIniSRDFile()
{
	int ptr = -1;
	int ln;
	Bfile_DeleteFile(IniSRDFile);
	ln=strlen(setup_data.route_name);
	if(ln==0)
		return;
	if (Bfile_CreateFile(IniSRDFile, ln) < 0) //Error("创建文件失败") ;
		return;
	//	else Error("创建文件OK") ;
	ptr = Bfile_OpenFile(IniSRDFile, _OPENMODE_WRITE) ;  // Bfile_OpenFile : 打开一个现有的文件。
	if (ptr >= 0) {
		Bfile_WriteFile(ptr, setup_data.route_name, ln) ;
		Bfile_CloseFile(ptr) ;
	}
}

int LoadLastDataSRDFile()
{
	char strFileName[50]; 
	int reg_ptr = -1;
	int ln;
	if(setup_data.route_name[0]==0)
	{
		reg_ptr = Bfile_OpenFile(IniSRDFile, _OPENMODE_READ) ;
		if (reg_ptr >= 0) {
			ln=Bfile_GetFileSize(reg_ptr);
			if(ln>0)
			{   
				if(ln>=sizeof(setup_data.route_name)-1)
					ln=sizeof(setup_data.route_name)-1;
				Bfile_ReadFile(reg_ptr, setup_data.route_name,ln,0) ;
				setup_data.route_name[ln]=0;
			}
			Bfile_CloseFile(reg_ptr) ;
			//PopUpWin(1);
	        //locate(7,4);Print(setup_data.route_name);
	        //GetKey(&key);
			//sprintf(strFileName,"\\\\crd0\\SRD\\%s",setup_data.route_name);
			LoadSRDFile(setup_data.route_name);
			return 1;
		}		
	}
	return 0;
}