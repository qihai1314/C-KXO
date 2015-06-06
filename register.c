/*
	绘星注册文件
	Last update: 2010.4.24
*/

#include "headfile.h"
#include "MyFont.h"

void Error(char* tips);

//#define PrintChStr(ss,x,y) Print_zh(ss,x,y,0)
#define Print_zh(ss,x,y,sel) PrintChStr(ss,x,y)

//# ifdef RELEASE
static FONTCHARACTER regfile[] = { '\\','\\','f','l','s','0','\\','r','e','g','.','t','x','t' ,'\0'} ;
//# else
//static FONTCHARACTER regfile[] = { '\\','\\','c','r','d','0','\\','r','e','g','.','t','x','t' ,'\0'} ;
//# endif

//static char m_id[9] ;	/*  8 bytes starting at 0x8000FFD0   */	
static char m_id[9] ={'6', 'g', 'D', 'H','J', 'N', 'm', '6', '\0'};	/*  8 bytes starting at 0x8000FFD0   */	
int Get_Code()
{
	DWORD id_pointer = 0x8000FFD0 ;		
	char temp_step ;
	
	memset(m_id, 0, 9) ;  
	for (temp_step = 0 ; temp_step < 8 ; ++temp_step)
		m_id[temp_step] = *(char*)(id_pointer + temp_step) ;
	return ;
}
int Input_Regcode()
{
	unsigned int key ;
	char regstr[9] = {0, 0, 0, 0, 0, 0, 0, 0, '\0'} ;
	BYTE s1[]="机器码\0";
	BYTE s2[]="注册码\0";
	BYTE pos = 0 ; 
	BYTE str_flag = FALSE ;
	int x = 61 ;
	int y = 25 ;
	int ptr = -1 ;

	PopUpWin(3) ;
	s1[6]=0;
	SetMyFont(&stHz12x12,&stAsc6x12);
	DispStr( 18, 22, s1 );	//Print_zh("机器码\0", 18, 22, 0) ;
	PrintXY(x, y,(unsigned char*)m_id, 0) ;
	GetKey(&key) ;
	Bdisp_AllClr_DDVRAM() ;
	PopUpWin(3) ;
	s2[6]=0;
	DispStr( 18, 22, s2 );;//Print_zh("注册码\0", 18, 22, 0) ;
	while(str_flag != TRUE)
	{
		GetKey(&key) ;
		switch (key) {
		case KEY_CTRL_EXE: 
			regstr[pos] = '\0' ;
			str_flag =TRUE ;
			break ;
		case  KEY_CTRL_ALPHA:
			break ;
		case KEY_CTRL_DEL:
			if (pos)  regstr[--pos] = '\0' ; 
			PrintXY(x, y, (unsigned char *)"        ", 0) ;
			break ;
		default: break ;
		}
		/* Numbers and characters */
		if ( (pos < 8) &&
			((key >= KEY_CHAR_0 && key <= KEY_CHAR_9) || 
			(key >= KEY_CHAR_A && key <= KEY_CHAR_Z)) ) {
				regstr[pos] = (char)key ;
				++pos ;
		}
		PrintXY(x, y, (unsigned char *)regstr, 0) ;
	}
	Bfile_DeleteFile(regfile) ;
	if (Bfile_CreateFile(regfile, 8) < 0) Error("创建文件失败") ;
//	else Error("创建文件OK") ;
	ptr = Bfile_OpenFile(regfile, _OPENMODE_WRITE) ;
	if (ptr >= 0) {
		Bfile_WriteFile(ptr, regstr, 8) ;
		Bfile_CloseFile(ptr) ;
	}

	return ;
}

int Input_Regcode1()
{
	unsigned int key ;
	char regstr[9] = {0, 0, 0, 0, 0, 0, 0, 0, '\0'} ;
	BYTE pos = 0 ; 
	BYTE str_flag = FALSE ;
	int x = 61 ;
	int y = 25 ;
	int ptr = -1 ;

	PopUpWin(3) ;
	Print_zh("机器码\0", 18, 22, 0) ;
	PrintXY(x, y, (unsigned char*)m_id, 0) ;
	GetKey(&key) ;
	Bdisp_AllClr_DDVRAM() ;
	PopUpWin(3) ;
	Print_zh("注册码\0", 18, 22, 0) ;
	while(str_flag != TRUE)
	{
		GetKey(&key) ;
		switch (key) {
		case KEY_CTRL_EXE: 
			regstr[pos] = '\0' ;
			str_flag =TRUE ;
			break ;
		case  KEY_CTRL_ALPHA:
			break ;
		case KEY_CTRL_DEL:
			if (pos)  regstr[--pos] = '\0' ; 
			PrintXY(x, y, (unsigned char *)"        ", 0) ;
			break ;
		default: break ;
		}
		/* Numbers and characters */
		if ( (pos < 8) &&
		     ((key >= KEY_CHAR_0 && key <= KEY_CHAR_9) || 
		      (key >= KEY_CHAR_A && key <= KEY_CHAR_Z)) ) {
			regstr[pos] = (char)key ;
			++pos ;
		}
		PrintXY(x, y, (unsigned char *)regstr, 0) ;
	}
	Bfile_DeleteFile(regfile) ;
	if (Bfile_CreateFile(regfile, 8) < 0) Error("创建文件失败") ;
	ptr = Bfile_OpenFile(regfile, _OPENMODE_WRITE) ;
	if (ptr >= 0) {
		Bfile_WriteFile(ptr, regstr, 8) ;
		Bfile_CloseFile(ptr) ;
	}

	return ;
}

int CheckReg()
{
	int reg_ptr = -1 ;
	char reg_code[9] = {0, 0, 0, 0, 0, 0, 0, 0, '\0'} ;
	BYTE mix_code[9] = {0, 0, 0, 0, 0, 0, 0, 0, '\0'} ;
	char final_code[9] = {0, 0, 0, 0, 0, 0, 0, 0, '\0'} ;
	BYTE step ;
 	long l1,l2;
// 	unsigned int key;
	Get_Code() ;
	reg_ptr = Bfile_OpenFile(regfile, _OPENMODE_READ) ;
	if (reg_ptr >= 0) {
		Bfile_ReadFile(reg_ptr, reg_code, 8, 0) ;
		Bfile_CloseFile(reg_ptr) ;
		for (step = 0 ; step < 8 ; ++step)
			mix_code[step] = m_id[7 - step]^(0xA5 + step * 3);
		//p1=(long *)mix_code;
		//p2=(long *)(mix_code+4);
		mix_code[0]^=mix_code[6]; 	mix_code[1]^=mix_code[7]; 	mix_code[2]^=mix_code[4]; 	mix_code[3]^=mix_code[5];
		mix_code[0]^=mix_code[7];	mix_code[1]^=mix_code[6];	mix_code[2]^=mix_code[5];	mix_code[3]^=mix_code[4];
		l1=((long)mix_code[3]*256+mix_code[2])*65536l+((long)mix_code[1]*256+mix_code[0]);
		l2=((long)mix_code[7]*256+mix_code[6])*65536l+((long)mix_code[5]*256+mix_code[4]);
		l1=l1*l2;
//		sprintf(final_code, "%02X%02X%02X%02X", mix_code[0],  mix_code[1],  mix_code[2],  mix_code[3]) ;
		sprintf(final_code, "%08X", l1) ;
		for (step = 0 ; step < 8 ; ++step)
		{
			final_code[step]=toupper(final_code[step]);
			reg_code[step]=toupper(reg_code[step]);
		}
		if ( strcmp(reg_code, final_code) == 0) 
			return TRUE ;
//		PrintXY(10,20,(unsigned char *)final_code, 0) ;
//		GetKey(&key) ;
	}
	Input_Regcode() ;
	return FALSE ;
}

void Error(char* tips)
{
	PopUpWin(3) ;
	Print_zh(tips, 22, 22, 0) ;
	return ;
}
